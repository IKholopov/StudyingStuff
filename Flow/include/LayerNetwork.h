#ifndef FLOW_LAYERNETWORK_H
#define FLOW_LAYERNETWORK_H

#include <limits>
#include <queue>

#include "ResidualNetwork.h"
#include "NetworkDelta.h"
#include "TIAGraphDeltaIds.h"

template <class FlowType>
class LayerNetwork : public NetworkGraph<FlowType>
{
    public:
        ~LayerNetwork();

        LayerNetwork(unsigned long long source, unsigned long long sink, ResidualNetwork<FlowType>& base, IMultiGraph& implementation);
        LayerNetwork(unsigned long long source, unsigned long long sink, ResidualNetwork<FlowType>& base, IMultiGraph& implementation,
                     std::vector<NetworkDelta>* deltas);
        void FindBlockingPath(ResidualNetwork<FlowType>& residual);
        void FindBlockingPath(ResidualNetwork<FlowType>& residual, std::vector<NetworkDelta>* deltas);
        const std::vector<unsigned long long>* GetDistances() const;
        virtual void BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* edge)> operation, bool straight = true);
    private:
        std::vector<bool> activeEdges;
        unsigned long long activeEdgesCounter ;
        std::vector<bool> activeVertecies;
        std::vector<FlowType> inSums;
        std::vector<FlowType> outSums;
        std::vector<unsigned long long>* distances;
        unsigned long long source;
        unsigned long long sink;
        bool CopyEdge(Edge* edge);
        void UpdatePotential(unsigned long long v);
        void UpdatePotential(unsigned long long v, NetworkDelta* delta);
        unsigned long long VertexPotential(unsigned long long v);
};

template <class FlowType>
LayerNetwork<FlowType>::~LayerNetwork()
{
    delete distances;
}
template <class FlowType>
LayerNetwork<FlowType>::LayerNetwork(unsigned long long source, unsigned long long sink,
                                               ResidualNetwork<FlowType>& base,
                                     IMultiGraph& implementation):NetworkGraph<FlowType>(base.Size(), implementation)
{
    this->source = source;
    this->sink = sink;
    distances = new std::vector<unsigned long long>(this->Size(), 0);
    base.BFS(source, [this](unsigned long long u, unsigned long long v, Edge* e){
        if(this->distances->at(v) == 0 && v != u)
            this->distances->at(v) = this->distances->at(u) + 1;
        return true;
    },
    [](Edge* edge){
        return static_cast<NetworkEdge<FlowType>*>(edge)->GetCapacity() > 0;
    }, true);
    distances->at(source) = 0;
    auto edges = base.GetAllEdgesConst();
    for(auto e = edges->begin(); e != edges->end(); ++e)
        if(distances->at((*e)->From) + 1 == distances->at((*e)->To) && distances->at((*e)->To) <= distances->at(sink))
            this->CopyEdge((*e)->Clone());
    activeEdges.resize(base.GetIdCounter(), 1);
    activeEdgesCounter = this->GetIdCounter();
    activeVertecies.resize(this->Size(), 1);
}
template <class FlowType>
LayerNetwork<FlowType>::LayerNetwork(unsigned long long source, unsigned long long sink, ResidualNetwork<FlowType>& base,
                                     IMultiGraph& implementation, std::vector<NetworkDelta>* deltas):NetworkGraph<FlowType>(base.Size(), implementation)
{
    NetworkDelta currentDelta(LAYERED);
    currentDelta.SetMessage("Layered network: Creating layered network");
    this->source = source;
    this->sink = sink;
    distances = new std::vector<unsigned long long>(this->Size(), 0);
    base.BFS(source, [this](unsigned long long u, unsigned long long v, Edge* e){
        if(this->distances->at(v) == 0 && v != u)
            this->distances->at(v) = this->distances->at(u) + 1;
        return true;
    },
    [](Edge* edge){
        return static_cast<NetworkEdge<FlowType>*>(edge)->GetCapacity() > 0;
    }, true);
    distances->at(source) = 0;
    auto edges = base.GetAllEdgesConst();
    std::vector<bool> addedNodes;
    addedNodes.resize(base.Size(), 0);
    for(auto e = edges->begin(); e != edges->end(); ++e)
        if(distances->at((*e)->From) + 1 == distances->at((*e)->To)  && distances->at((*e)->To) <= distances->at(sink))
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            addedNodes[edge->From] = 1;
            addedNodes[edge->To] = 1;
            this->CopyEdge(edge->Clone());
            currentDelta.AddEdgeChange(new NetworkEdgeChange(edge->GetId(), edge->From, edge->To, edge->GetCapacity(), edge->GetFlow()));
        }
    for(unsigned long long i = 0; i < addedNodes.size(); ++i)
        if(addedNodes[i] == 1)
            currentDelta.AddNodeChange(new NetworkNodeChange(i, 0));
    activeEdges.resize(base.GetIdCounter(), 1);
    activeEdgesCounter = this->GetIdCounter();
    activeVertecies.resize(this->Size(), 1);

    deltas->push_back(currentDelta);
}
template <class FlowType>
bool LayerNetwork<FlowType>::CopyEdge(Edge* edge)
{
    this->IncreaseIdCounter();
    this->OrientedGraph::AddEdge(edge);
    return true;
}
template <class FlowType>
void LayerNetwork<FlowType>::FindBlockingPath(ResidualNetwork<FlowType> &residual)
{
    std::vector<FlowType> flow(this->Size(), 0);
    for(unsigned long long v = 0; v < this->Size(); ++v) //Create Vertex Potential;
    {
        if(v == this->source)
        {
            auto edges = this->GetOutgoing(v);
            unsigned long long sum = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
            {
                auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
                sum += edge->GetCapacity();
            }
            outSums.push_back(sum);
            inSums.push_back(0);
        }
        else if(v == this->sink)
        {
            auto edges = this->GetIngoing(v);
            unsigned long long sum = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                sum += static_cast<NetworkEdge<FlowType>*>(*e)->GetCapacity();
            inSums.push_back(sum);
            outSums.push_back(sum);
        }
        else
        {
            auto edges = this->GetIngoing(v);
            unsigned long long ingoing = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                ingoing += static_cast<NetworkEdge<FlowType>*>(*e)->GetCapacity();
            edges = this->GetOutgoing(v);
            unsigned long long outgoing = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                outgoing += static_cast<NetworkEdge<FlowType>*>(*e)->GetCapacity();
            inSums.push_back(ingoing);
            outSums.push_back(outgoing);
        }
    }
    for(int v = 0; v < this->Size(); ++v)
        UpdatePotential(v);
    while(activeEdgesCounter > 0)
    {
        unsigned long long min = std::numeric_limits<unsigned long long>::max();
        unsigned long long minVertex = source;
        for(int i = 0; i < this->Size(); ++i)
            if(activeVertecies[i] && min > VertexPotential(i))
            {
                min = VertexPotential(i);
                minVertex = i;
            }
        assert(min != 0);
        auto p = VertexPotential(minVertex);
        flow[minVertex] = p;
        this->BFS(minVertex, [this, &flow, &residual](unsigned long long from, unsigned long long to, Edge* e){
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            auto deltaFlow = flow[from] < edge->GetCapacity() ? flow[from] : edge->GetCapacity();
            residual.AddFlow(from, to, edge->GetId(), deltaFlow);
            flow[to] += deltaFlow;
            flow[from] -= deltaFlow;
            this->outSums[from] -= deltaFlow;
            this->inSums[to] -= deltaFlow;
            edge->SetCapacity(edge->GetCapacity() - deltaFlow);
            if(edge->GetCapacity() == 0)
            {
                this->activeEdges[edge->GetId()] = 0;
                --(this->activeEdgesCounter);
            }
            return flow[from] > 0;
        }, true);
        flow[minVertex] = p;
        this->BFS(minVertex, [this, &flow, &residual](unsigned long long to, unsigned long long from, Edge* e){
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            auto deltaFlow = flow[to] < edge->GetCapacity() ? flow[to] : edge->GetCapacity();
            residual.AddFlow(from, to, edge->GetId(), deltaFlow);
            flow[to] -= deltaFlow;
            flow[from] += deltaFlow;
            this->outSums[from] -= deltaFlow;
            this->inSums[to] -= deltaFlow;
            edge->SetCapacity(edge->GetCapacity() - deltaFlow);
            if(edge->GetCapacity() == 0)
            {
                this->activeEdges[edge->GetId()] = 0;
                --(this->activeEdgesCounter);
            }
            return flow[to] > 0;
        }, false);
        for(unsigned long long v = 0; v < this->Size(); ++v)
            UpdatePotential(v);
    }
}
template <class FlowType>
void LayerNetwork<FlowType>::FindBlockingPath(ResidualNetwork<FlowType> &residual, std::vector<NetworkDelta>* deltas)
{
    std::vector<FlowType> flow(this->Size(), 0);
    NetworkDelta delta(LAYERED);
    delta.SetMessage("Layered Networking: calculating potentials");
    for(unsigned long long v = 0; v < this->Size(); ++v)    //Create Vertex Potential;
    {
        if(v == this->source)
        {
            auto edges = this->GetOutgoing(v);
            unsigned long long sum = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
            {
                auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
                sum += edge->GetCapacity();
            }
            outSums.push_back(sum);
            inSums.push_back(0);

        }
        else if(v == this->sink)
        {
            auto edges = this->GetIngoing(v);
            unsigned long long sum = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                sum += static_cast<NetworkEdge<FlowType>*>(*e)->GetCapacity();
            inSums.push_back(sum);
            outSums.push_back(sum);
        }
        else
        {
            auto edges = this->GetIngoing(v);
            unsigned long long ingoing = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                ingoing += static_cast<NetworkEdge<FlowType>*>(*e)->GetCapacity();
            edges = this->GetOutgoing(v);
            unsigned long long outgoing = 0;
            for(auto e = edges->begin(); e != edges->end(); ++e)
                outgoing += static_cast<NetworkEdge<FlowType>*>(*e)->GetCapacity();
            inSums.push_back(ingoing);
            outSums.push_back(outgoing);
        }
    }
    for(int v = 0; v < this->Size(); ++v)
        UpdatePotential(v, &delta);
    deltas->push_back(delta);
    while(activeEdgesCounter > 0)
    {
        unsigned long long min = std::numeric_limits<unsigned long long>::max();
        unsigned long long minVertex = source;
        for(int i = 0; i < this->Size(); ++i)
            if(activeVertecies[i] && min > VertexPotential(i))
            {
                min = VertexPotential(i);
                minVertex = i;
            }
        NetworkDelta minDelta(LAYERED);
        minDelta.AddNodeChange(new NetworkNodeChange(minVertex, VertexPotential(minVertex), 1, true));
        deltas->push_back(minDelta);
        assert(min != 0);
        auto p = VertexPotential(minVertex);
        flow[minVertex] = p;
        NetworkDelta pushDelta(LAYERED);
        pushDelta.SetMessage("Layered network: Pushing flow");
        NetworkDelta residualDelta(RESIDUAL);
        residualDelta.SetMessage("Residual network: pushing flow in residual");
        this->BFS(minVertex, [this, &flow, &residual, &residualDelta, &pushDelta](unsigned long long from, unsigned long long to, Edge* e){
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            auto deltaFlow = flow[from] < edge->GetCapacity() ? flow[from] : edge->GetCapacity();
            residual.AddFlow(from, to, edge->GetId(), deltaFlow, &residualDelta);
            pushDelta.AddEdgeChange(new NetworkEdgeChange(edge->GetId(), edge->From, edge->To, edge->GetCapacity() - deltaFlow, edge->GetFlow() + deltaFlow,
                                                          1, true));
            flow[to] += deltaFlow;
            flow[from] -= deltaFlow;
            this->outSums[from] -= deltaFlow;
            this->inSums[to] -= deltaFlow;
            edge->SetCapacity(edge->GetCapacity() - deltaFlow);
            if(edge->GetCapacity() == 0)
            {
                pushDelta.AddEdgeChange(new NetworkEdgeChange(edge->GetId(), edge->From, edge->To, edge->GetCapacity(), edge->GetFlow(), 0));
                this->activeEdges[edge->GetId()] = 0;
                --(this->activeEdgesCounter);
            }
            return flow[from] > 0;
        }, true);
        flow[minVertex] = p;
        this->BFS(minVertex, [this, &flow, &residual, &residualDelta, &pushDelta](unsigned long long to, unsigned long long from, Edge* e){
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            auto deltaFlow = flow[to] < edge->GetCapacity() ? flow[to] : edge->GetCapacity();
            pushDelta.AddEdgeChange(new NetworkEdgeChange(edge->GetId(), edge->From, edge->To, edge->GetCapacity() - deltaFlow, edge->GetFlow() + deltaFlow,
                                                          1, true));
            residual.AddFlow(from, to, edge->GetId(), deltaFlow, &residualDelta);
            flow[to] -= deltaFlow;
            flow[from] += deltaFlow;
            this->outSums[from] -= deltaFlow;
            this->inSums[to] -= deltaFlow;
            edge->SetCapacity(edge->GetCapacity() - deltaFlow);
            if(edge->GetCapacity() == 0)
            {
                pushDelta.AddEdgeChange(new NetworkEdgeChange(edge->GetId(), edge->From, edge->To, edge->GetCapacity(), edge->GetFlow(), 0));
                this->activeEdges[edge->GetId()] = 0;
                --(this->activeEdgesCounter);
            }
            return flow[to] > 0;
        }, false);
        deltas->push_back(pushDelta);
        deltas->push_back(residualDelta);
        NetworkDelta newPotentialDelta(LAYERED);
        newPotentialDelta.SetMessage("Layered network: updating potentials");
        for(unsigned long long v = 0; v < this->Size(); ++v)
            UpdatePotential(v, &newPotentialDelta);
        deltas->push_back(newPotentialDelta);
    }
    NetworkDelta removeDelta(LAYERED, 1);
    removeDelta.SetMessage("Residual network: removing layered network");
    auto allEdges = this->GetAllEdges();
    for(auto e: *allEdges)
        if(activeEdges[e->GetId()])
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(e);
            removeDelta.AddEdgeChange(new NetworkEdgeChange(edge->GetId(), edge->From, edge->To,
                                                            edge->GetCapacity(), edge->GetFlow(), 0));
        }
    for(long long i = 0; i < activeVertecies.size(); ++i)
        if(activeVertecies[i])
            removeDelta.AddNodeChange(new NetworkNodeChange(i, 0, 0));
    deltas->push_back(removeDelta);
    delete allEdges;
}
template <class FlowType>
const std::vector<unsigned long long>* LayerNetwork<FlowType>::GetDistances() const
{
    return distances;
}
template <class FlowType>
void LayerNetwork<FlowType>::UpdatePotential(unsigned long long v)
{
    if(VertexPotential(v) == 0 && activeVertecies[v])
    {
        activeVertecies[v] = 0;
        auto in = this->GetIngoing(v);
        for(auto e = in->begin(); e != in->end(); ++e)
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            if(activeEdges[edge->GetId()])
            {
                activeEdges[edge->GetId()] = 0;
                outSums[edge->From] -= edge->GetCapacity();
                --activeEdgesCounter;
                UpdatePotential(edge->From);
            }
        }
        auto out = this->GetOutgoing(v);
        for(auto e = out->begin(); e != out->end(); ++e)
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            if(activeEdges[edge->GetId()])
            {
                activeEdges[edge->GetId()] = 0;
                inSums[edge->To] -= edge->GetCapacity();
                --activeEdgesCounter;
                UpdatePotential(edge->To);
            }
        }
    }
}
template <class FlowType>
void LayerNetwork<FlowType>::UpdatePotential(unsigned long long v, NetworkDelta* delta)
{
    auto potential = VertexPotential(v);
    if(potential != 0 && activeVertecies[v])
        delta->AddNodeChange(new NetworkNodeChange(v, potential));
    if(potential == 0 && activeVertecies[v])
    {
        delta->AddNodeChange(new NetworkNodeChange(v, potential, 0));
        activeVertecies[v] = 0;
        auto in = this->GetIngoing(v);
        for(auto e = in->begin(); e != in->end(); ++e)
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            if(activeEdges[edge->GetId()])
            {

                delta->AddEdgeChange(new NetworkEdgeChange(edge->GetId(), edge->From, edge->To, edge->GetCapacity(), edge->GetFlow(), 0));

                activeEdges[edge->GetId()] = 0;
                outSums[edge->From] -= edge->GetCapacity();
                --activeEdgesCounter;
                UpdatePotential(edge->From, delta);
            }
        }
        auto out = this->GetOutgoing(v);
        for(auto e = out->begin(); e != out->end(); ++e)
        {
            auto edge = static_cast<NetworkEdge<FlowType>*>(*e);
            if(activeEdges[edge->GetId()])
            {

                delta->AddEdgeChange(new NetworkEdgeChange(edge->GetId(), edge->From, edge->To, edge->GetCapacity(), edge->GetFlow(), 0));

                activeEdges[edge->GetId()] = 0;
                inSums[edge->To] -= edge->GetCapacity();
                --activeEdgesCounter;
                UpdatePotential(edge->To, delta);
            }
        }
    }
}
template <class FlowType>
unsigned long long LayerNetwork<FlowType>::VertexPotential(unsigned long long v)
{
    if(v == source)
        return outSums.at(v);
    if(v == source)
        return inSums.at(v);
    auto in = inSums.at(v);
    auto out = outSums.at(v);
    return in < out ? in : out;
}
template <class FlowType>
void LayerNetwork<FlowType>::BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* e)> operation, bool straight)
{
    enum Color{White, Grey, Black};
    std::vector<Color> vertexes (this->Size(), Color::White);
    std::queue<unsigned long long> q;
    q.push(source);
    while(!q.empty())
    {
        unsigned long long u = q.front();
        q.pop();
        if(vertexes[u] != Color::White)
            continue;
        vertexes[u] = Color::Grey;
        auto childs = straight ? this->GetOutgoing(u): this->GetIngoing(u);
        for(auto v = childs->begin(); v != childs->end(); ++v)
        {
            if(!activeEdges[(*v)->GetId()])
                continue;
            auto vert = straight ? (*v)->To : (*v)->From;
            if(!operation(u, vert, *v))
            {
                q.push(vert);
                break;
            }
            q.push(vert);
        }
        vertexes[u] = Color::Black;
    }
}

#endif
