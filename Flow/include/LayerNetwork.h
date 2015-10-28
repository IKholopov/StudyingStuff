#ifndef FLOW_LAYERNETWORK_H
#define FLOW_LAYERNETWORK_H

#include "ResidualNetwork.h"
#include "NetworkDelta.h"
#include "TIAGraphDeltaIds.h"

#include <queue>
#include <limits>

template <class FlowType>
class LayerNetwork : public NetworkGraph<FlowType>
{
    public:
        ~LayerNetwork();

        LayerNetwork(unsigned long long source_, unsigned long long sink_, ResidualNetwork<FlowType>& base, IMultiGraph& implementation);
        LayerNetwork(unsigned long long source_, unsigned long long sink_, ResidualNetwork<FlowType>& base, IMultiGraph& implementation,
                     std::vector<NetworkDelta>* deltas);
        void findBlockingPath(ResidualNetwork<FlowType>& residual);
        void findBlockingPath(ResidualNetwork<FlowType>& residual, std::vector<NetworkDelta>* deltas);
        const std::vector<unsigned long long>* getDistances() const;
        virtual void BFS(unsigned long long source_, std::function<bool(unsigned long long, unsigned long long, Edge* edge)> operation, bool straight = true);
    private:
        std::vector<bool> activeEdges_;
        unsigned long long activeEdgesCounter_ ;
        std::vector<bool> activeVertecies_;
        std::vector<FlowType> inSums_;
        std::vector<FlowType> outSums_;
        std::vector<unsigned long long>* distances_;
        unsigned long long source_;
        unsigned long long sink_;
        bool copyEdge(Edge* edge);
        void updatePotential(unsigned long long v);
        void updatePotential(unsigned long long v, NetworkDelta* delta);
        unsigned long long vertexPotential(unsigned long long v);
};

template <class FlowType>
LayerNetwork<FlowType>::~LayerNetwork()
{
    delete distances_;
}
template <class FlowType>
LayerNetwork<FlowType>::LayerNetwork(unsigned long long source, unsigned long long sink,
                                               ResidualNetwork<FlowType>& base,
                                     IMultiGraph& implementation):NetworkGraph<FlowType>(base.size(), implementation)
{
    this->source_ = source;
    this->sink_ = sink;
    distances_ = new std::vector<unsigned long long>(this->size(), 0);
    base.BFS(source, [this](unsigned long long u, unsigned long long v, Edge* e){
        if(this->distances_->at(v) == 0 && v != u)
            this->distances_->at(v) = this->distances_->at(u) + 1;
        return true;
    },
    [](Edge* edge){
        return static_cast<NetworkEdge<FlowType>*>(edge)->getCapacity() > 0;
    }, true);
    distances_->at(source) = 0;
    auto edges = base.getAllEdgesConst();
    for(auto e = edges->begin(); e != edges->end(); ++e)
        if(distances_->at((*e)->From) + 1 == distances_->at((*e)->To) && distances_->at((*e)->To) <= distances_->at(sink))
            this->copyEdge((*e)->clone());
    activeEdges_.resize(base.getIdCounter(), 1);
    activeEdgesCounter_ = this->getIdCounter();
    activeVertecies_.resize(this->size(), 1);
}
template <class FlowType>
LayerNetwork<FlowType>::LayerNetwork(unsigned long long source, unsigned long long sink, ResidualNetwork<FlowType>& base,
                                     IMultiGraph& implementation, std::vector<NetworkDelta>* deltas):NetworkGraph<FlowType>(base.size(), implementation)
{
    NetworkDelta currentDelta(LAYERED);
    currentDelta.setMessage("Layered network: Creating layered network");
    this->source_ = source;
    this->sink_ = sink;
    distances_ = new std::vector<unsigned long long>(this->size(), 0);
    base.BFS(source, [this](unsigned long long u, unsigned long long v, Edge* e){
        if(this->distances_->at(v) == 0 && v != u)
            this->distances_->at(v) = this->distances_->at(u) + 1;
        return true;
    },
    [](Edge* edge){
        return static_cast<NetworkEdge<FlowType>*>(edge)->getCapacity() > 0;
    }, true);
    distances_->at(source) = 0;
    auto edges = base.getAllEdgesConst();
    std::vector<bool> addedNodes;
    addedNodes.resize(base.size(), 0);
    for(auto e = edges->begin(); e != edges->end(); ++e)
        if(distances_->at((*e)->From) + 1 == distances_->at((*e)->To)  && distances_->at((*e)->To) <= distances_->at(sink)) {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            addedNodes[edge->From] = 1;
            addedNodes[edge->To] = 1;
            this->copyEdge(edge->clone());
            currentDelta.addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To, edge->getCapacity(), edge->getFlow()));
        }
    for(unsigned long long i = 0; i < addedNodes.size(); ++i)
        if(addedNodes[i] == 1)
            currentDelta.addNodeChange(new NetworkNodeChange(i, 0));
    activeEdges_.resize(base.getIdCounter(), 1);
    activeEdgesCounter_ = this->getIdCounter();
    activeVertecies_.resize(this->size(), 1);

    deltas->push_back(currentDelta);
}
template <class FlowType>
bool LayerNetwork<FlowType>::copyEdge(Edge* edge)
{
    this->increaseIdCounter();
    this->OrientedGraph::addEdge(edge);
    return true;
}
template <class FlowType>
void LayerNetwork<FlowType>::findBlockingPath(ResidualNetwork<FlowType> &residual)
{
    std::vector<FlowType> flow(this->size(), 0);
    for(unsigned long long v = 0; v < this->size(); ++v) //Create Vertex Potential;
    {
        if(v == this->source_) {
            auto edges = this->getOutgoing(v);
            unsigned long long sum = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
            {
                auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
                sum += edge->getCapacity();
            }
            outSums_.push_back(sum);
            inSums_.push_back(0);
        }
        else if(v == this->sink_) {
            auto edges = this->getIngoing(v);
            unsigned long long sum = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                sum += static_cast<NetworkEdge<FlowType>*>(*e)->getCapacity();
            inSums_.push_back(sum);
            outSums_.push_back(sum);
        }
        else {
            auto edges = this->getIngoing(v);
            unsigned long long ingoing = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                ingoing += static_cast<NetworkEdge<FlowType>*>(*e)->getCapacity();
            edges = this->getOutgoing(v);
            unsigned long long outgoing = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                outgoing += static_cast<NetworkEdge<FlowType>*>(*e)->getCapacity();
            inSums_.push_back(ingoing);
            outSums_.push_back(outgoing);
        }
    }
    for(int v = 0; v < this->size(); ++v)
        updatePotential(v);
    while(activeEdgesCounter_ > 0)
    {
        unsigned long long min = std::numeric_limits<unsigned long long>::max();
        unsigned long long minVertex = source_;
        for(int i = 0; i < this->size(); ++i)
            if(activeVertecies_[i] && min > vertexPotential(i)) {
                min = vertexPotential(i);
                minVertex = i;
            }
        assert(min != 0);
        auto p = vertexPotential(minVertex);
        flow[minVertex] = p;
        this->BFS(minVertex, [this, &flow, &residual](unsigned long long from, unsigned long long to, Edge* e){
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            auto deltaFlow = flow[from] < edge->getCapacity() ? flow[from] : edge->getCapacity();
            residual.addFlow(from, to, edge->getId(), deltaFlow);
            flow[to] += deltaFlow;
            flow[from] -= deltaFlow;
            this->outSums_[from] -= deltaFlow;
            this->inSums_[to] -= deltaFlow;
            edge->setCapacity(edge->getCapacity() - deltaFlow);
            if(edge->getCapacity() == 0) {
                this->activeEdges_[edge->getId()] = 0;
                --(this->activeEdgesCounter_);
            }
            return flow[from] > 0;
        }, true);
        flow[minVertex] = p;
        this->BFS(minVertex, [this, &flow, &residual](unsigned long long to, unsigned long long from, Edge* e){
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            auto deltaFlow = flow[to] < edge->getCapacity() ? flow[to] : edge->getCapacity();
            residual.addFlow(from, to, edge->getId(), deltaFlow);
            flow[to] -= deltaFlow;
            flow[from] += deltaFlow;
            this->outSums_[from] -= deltaFlow;
            this->inSums_[to] -= deltaFlow;
            edge->setCapacity(edge->getCapacity() - deltaFlow);
            if(edge->getCapacity() == 0) {
                this->activeEdges_[edge->getId()] = 0;
                --(this->activeEdgesCounter_);
            }
            return flow[to] > 0;
        }, false);
        for(unsigned long long v = 0; v < this->size(); ++v)
            updatePotential(v);
    }
}
template <class FlowType>
void LayerNetwork<FlowType>::findBlockingPath(ResidualNetwork<FlowType> &residual, std::vector<NetworkDelta>* deltas)
{
    std::vector<FlowType> flow(this->size(), 0);
    NetworkDelta delta(LAYERED);
    delta.setMessage("Layered Networking: calculating potentials");
    for(unsigned long long v = 0; v < this->size(); ++v)    //Create Vertex Potential;
    {
        if(v == this->source_) {
            auto edges = this->getOutgoing(v);
            unsigned long long sum = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
            {
                auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
                sum += edge->getCapacity();
            }
            outSums_.push_back(sum);
            inSums_.push_back(0);

        }
        else if(v == this->sink_) {
            auto edges = this->getIngoing(v);
            unsigned long long sum = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                sum += static_cast<NetworkEdge<FlowType>*>(*e)->getCapacity();
            inSums_.push_back(sum);
            outSums_.push_back(sum);
        }
        else {
            auto edges = this->getIngoing(v);
            unsigned long long ingoing = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                ingoing += static_cast<NetworkEdge<FlowType>*>(*e)->getCapacity();
            edges = this->getOutgoing(v);
            unsigned long long outgoing = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                outgoing += static_cast<NetworkEdge<FlowType>*>(*e)->getCapacity();
            inSums_.push_back(ingoing);
            outSums_.push_back(outgoing);
        }
    }
    for(int v = 0; v < this->size(); ++v)
        updatePotential(v, &delta);
    deltas->push_back(delta);
    while(activeEdgesCounter_ > 0)
    {
        unsigned long long min = std::numeric_limits<unsigned long long>::max();
        unsigned long long minVertex = source_;
        for(int i = 0; i < this->size(); ++i)
            if(activeVertecies_[i] && min > vertexPotential(i)) {
                min = vertexPotential(i);
                minVertex = i;
            }
        NetworkDelta minDelta(LAYERED);
        minDelta.addNodeChange(new NetworkNodeChange(minVertex, vertexPotential(minVertex), 1, true));
        deltas->push_back(minDelta);
        assert(min != 0);
        auto p = vertexPotential(minVertex);
        flow[minVertex] = p;
        NetworkDelta pushDelta(LAYERED);
        pushDelta.setMessage("Layered network: Pushing flow");
        NetworkDelta residualDelta(RESIDUAL);
        residualDelta.setMessage("Residual network: pushing flow in residual");
        this->BFS(minVertex, [this, &flow, &residual, &residualDelta, &pushDelta](unsigned long long from, unsigned long long to, Edge* e){
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            auto deltaFlow = flow[from] < edge->getCapacity() ? flow[from] : edge->getCapacity();
            residual.addFlow(from, to, edge->getId(), deltaFlow, &residualDelta);
            pushDelta.addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To, edge->getCapacity() - deltaFlow, edge->getFlow() + deltaFlow,
                                                          1, true));
            flow[to] += deltaFlow;
            flow[from] -= deltaFlow;
            this->outSums_[from] -= deltaFlow;
            this->inSums_[to] -= deltaFlow;
            edge->setCapacity(edge->getCapacity() - deltaFlow);
            if(edge->getCapacity() == 0) {
                pushDelta.addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To, edge->getCapacity(), edge->getFlow(), 0));
                this->activeEdges_[edge->getId()] = 0;
                --(this->activeEdgesCounter_);
            }
            return flow[from] > 0;
        }, true);
        flow[minVertex] = p;
        this->BFS(minVertex, [this, &flow, &residual, &residualDelta, &pushDelta](unsigned long long to, unsigned long long from, Edge* e){
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            auto deltaFlow = flow[to] < edge->getCapacity() ? flow[to] : edge->getCapacity();
            pushDelta.addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To, edge->getCapacity() - deltaFlow, edge->getFlow() + deltaFlow,
                                                          1, true));
            residual.addFlow(from, to, edge->getId(), deltaFlow, &residualDelta);
            flow[to] -= deltaFlow;
            flow[from] += deltaFlow;
            this->outSums_[from] -= deltaFlow;
            this->inSums_[to] -= deltaFlow;
            edge->setCapacity(edge->getCapacity() - deltaFlow);
            if(edge->getCapacity() == 0) {
                pushDelta.addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To, edge->getCapacity(), edge->getFlow(), 0));
                this->activeEdges_[edge->getId()] = 0;
                --(this->activeEdgesCounter_);
            }
            return flow[to] > 0;
        }, false);
        deltas->push_back(pushDelta);
        deltas->push_back(residualDelta);
        NetworkDelta newPotentialDelta(LAYERED);
        newPotentialDelta.setMessage("Layered network: updating potentials");
        for(unsigned long long v = 0; v < this->size(); ++v)
            updatePotential(v, &newPotentialDelta);
        deltas->push_back(newPotentialDelta);
    }
    NetworkDelta removeDelta(LAYERED, 1);
    removeDelta.setMessage("Residual network: removing layered network");
    auto allEdges = this->getAllEdges();
    for(auto e: *allEdges)
        if(activeEdges_[e->getId()]) {
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            removeDelta.addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To,
                                                            edge->getCapacity(), edge->getFlow(), 0));
        }
    for(long long i = 0; i < activeVertecies_.size(); ++i)
        if(activeVertecies_[i])
            removeDelta.addNodeChange(new NetworkNodeChange(i, 0, 0));
    deltas->push_back(removeDelta);
    delete allEdges;
}
template <class FlowType>
const std::vector<unsigned long long>* LayerNetwork<FlowType>::getDistances() const
{
    return distances_;
}
template <class FlowType>
void LayerNetwork<FlowType>::updatePotential(unsigned long long v)
{
    if(vertexPotential(v) == 0 && activeVertecies_[v]) {
        activeVertecies_[v] = 0;
        auto in = this->getIngoing(v);
        for(auto e = in->begin(); e != in->end(); ++e)
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            if(activeEdges_[edge->getId()]) {
                activeEdges_[edge->getId()] = 0;
                outSums_[edge->From] -= edge->getCapacity();
                --activeEdgesCounter_;
                updatePotential(edge->From);
            }
        }
        auto out = this->getOutgoing(v);
        for(auto e = out->begin(); e != out->end(); ++e)
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            if(activeEdges_[edge->getId()]) {
                activeEdges_[edge->getId()] = 0;
                inSums_[edge->To] -= edge->getCapacity();
                --activeEdgesCounter_;
                updatePotential(edge->To);
            }
        }
    }
}
template <class FlowType>
void LayerNetwork<FlowType>::updatePotential(unsigned long long v, NetworkDelta* delta)
{
    auto potential = vertexPotential(v);
    if(potential != 0 && activeVertecies_[v])
        delta->addNodeChange(new NetworkNodeChange(v, potential));
    if(potential == 0 && activeVertecies_[v]) {
        delta->addNodeChange(new NetworkNodeChange(v, potential, 0));
        activeVertecies_[v] = 0;
        auto in = this->getIngoing(v);
        for(auto e = in->begin(); e != in->end(); ++e)
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            if(activeEdges_[edge->getId()]) {

                delta->addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To, edge->getCapacity(), edge->getFlow(), 0));

                activeEdges_[edge->getId()] = 0;
                outSums_[edge->From] -= edge->getCapacity();
                --activeEdgesCounter_;
                updatePotential(edge->From, delta);
            }
        }
        auto out = this->getOutgoing(v);
        for(auto e = out->begin(); e != out->end(); ++e)
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            if(activeEdges_[edge->getId()]) {

                delta->addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To, edge->getCapacity(), edge->getFlow(), 0));

                activeEdges_[edge->getId()] = 0;
                inSums_[edge->To] -= edge->getCapacity();
                --activeEdgesCounter_;
                updatePotential(edge->To, delta);
            }
        }
    }
}
template <class FlowType>
unsigned long long LayerNetwork<FlowType>::vertexPotential(unsigned long long v)
{
    if(v == source_)
        return outSums_.at(v);
    if(v == source_)
        return inSums_.at(v);
    auto in = inSums_.at(v);
    auto out = outSums_.at(v);
    return in < out ? in : out;
}
template <class FlowType>
void LayerNetwork<FlowType>::BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* e)> operation, bool straight)
{
    enum Color{White, Grey, Black};
    std::vector<Color> vertexes (this->size(), Color::White);
    std::queue<unsigned long long> q;
    q.push(source);
    while(!q.empty())
    {
        unsigned long long u = q.front();
        q.pop();
        if(vertexes[u] != Color::White)
            continue;
        vertexes[u] = Color::Grey;
        auto childs = straight ? this->getOutgoing(u): this->getIngoing(u);
        for(auto v = childs->begin(); v != childs->end(); ++v)
        {
            if(!activeEdges_[(*v)->getId()])
                continue;
            auto vert = straight ? (*v)->To : (*v)->From;
            if(!operation(u, vert, *v)) {
                q.push(vert);
                break;
            }
            q.push(vert);
        }
        vertexes[u] = Color::Black;
    }
}

#endif
