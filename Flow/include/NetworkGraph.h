#ifndef FLOW_NETWORKGRAPH_H
#define FLOW_NETWORKGRAPH_H

#include "IMultiGraph.h"
#include "OrientedGraph.h"
#include "NetworkEdge.h"
#include "NetworkDelta.h"

#include <utility>
#include <queue>

template <class FlowType>
class NetworkGraph: public OrientedGraph
{
    public:
        NetworkGraph(IMultiGraph& graph): OrientedGraph(graph) {this->idCounter = 0;}
        NetworkGraph(unsigned long long size, IMultiGraph& graph):OrientedGraph(size, graph) {this->idCounter = 0;}
        NetworkGraph(IMultiGraph* graph): OrientedGraph(graph) {this->idCounter = 0;}
        NetworkGraph(unsigned long long size, IMultiGraph* graph):OrientedGraph(size, graph) {this->idCounter = 0;}
        ~NetworkGraph() {}

        bool checkEdge(long long from, long long to, unsigned long long id);
        Edge* getEdge(long long from, long long to, unsigned long long id);
        const std::vector<Edge*>* getAllEdgesConst() const;
        const std::vector<Edge*>* getOutgoing(unsigned long long vertex) const;
        const std::vector<Edge*>* getIngoing(unsigned long long vertex) const;
        unsigned long long getIdCounter() const;
        bool addEdge(Edge* edge);
        void flowFromResidual(NetworkGraph<FlowType> &residual);
        void flowFromResidual(NetworkGraph<FlowType> &residual, NetworkDelta* delta);
        virtual void BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* edge)> operation,
                         std::function<bool(Edge* edge)> edgeCondition, bool straight = true);
    protected:
        void  increaseIdCounter();
    private:
        unsigned long long idCounter;
};

template <class FlowType>
bool NetworkGraph<FlowType>::checkEdge(long long from, long long to, unsigned long long id)
{
    auto edges = this->getOutgoing(from);
    for(auto e = edges->begin(); e != edges->end(); ++e)
    {
       if((*e)->To == to && (*e)->getId() == id )
           return true;
    }
    return false;
}
template <class FlowType>
Edge* NetworkGraph<FlowType>::getEdge(long long from, long long to, unsigned long long id)
{
    auto edges = this->getOutgoing(from);
    for(auto e = edges->begin(); e != edges->end(); ++e)
        if((*e)->To == to && (*e)->getId() == id )
            return *e;
    return NULL;
}
template <class FlowType>
const std::vector<Edge*>* NetworkGraph<FlowType>::getAllEdgesConst() const
{
    return static_cast<IMultiGraph*>(this->graph_)->getAllEdgesConst();
}
template <class FlowType>
const std::vector<Edge *> *NetworkGraph<FlowType>::getOutgoing(unsigned long long vertex) const
{
    return static_cast<IMultiGraph*>(this->graph_)->getOutgoing(vertex);
}
template <class FlowType>
const std::vector<Edge *> *NetworkGraph<FlowType>::getIngoing(unsigned long long vertex) const
{
    return static_cast<IMultiGraph*>(this->graph_)->getIngoing(vertex);
}
template <class FlowType>
unsigned long long NetworkGraph<FlowType>::getIdCounter() const
{
    return idCounter;
}
template <class FlowType>
bool NetworkGraph<FlowType>::addEdge(Edge* edge)
{
    edge->setId(this->getIdCounter());
    increaseIdCounter();
    this->OrientedGraph::addEdge(edge);
    return true;
}
template <class FlowType>
void NetworkGraph<FlowType>::flowFromResidual(NetworkGraph<FlowType> &residual)
{
    auto edges = this->getAllEdges();
    for(auto e = edges->begin(); e != edges->end(); ++e)
    {
        NetworkEdge<FlowType>* edge = static_cast<NetworkEdge<FlowType>*>(*e);
        auto resEdge = static_cast<NetworkEdge<FlowType>*>(residual.getEdge(edge->From, edge->To, edge->getId()));
        if(edge->getCapacity() - resEdge->getCapacity() >= 0)
            edge->setFlow(edge->getCapacity() - resEdge->getCapacity());
    }
    delete edges;
}
template <class FlowType>
void NetworkGraph<FlowType>::flowFromResidual(NetworkGraph<FlowType> &residual, NetworkDelta* delta)
{
    auto edges = this->getAllEdges();
    for(auto e = edges->begin(); e != edges->end(); ++e)
    {
        NetworkEdge<FlowType>* edge = static_cast<NetworkEdge<FlowType>*>(*e);
        auto resEdge = static_cast<NetworkEdge<FlowType>*>(residual.getEdge(edge->From, edge->To, edge->getId()));
        if(edge->getCapacity() - resEdge->getCapacity() >= 0) {
            edge->setFlow(edge->getCapacity() - resEdge->getCapacity());
            delta->addEdgeChange(new NetworkEdgeChange(edge->getId(), edge->From, edge->To, edge->getCapacity(), edge->getFlow()));
        }
    }
    delete edges;
}
template <class FlowType>
void NetworkGraph<FlowType>::increaseIdCounter()
{
    ++idCounter;
}
template <class FlowType>
void NetworkGraph<FlowType>::BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* e)> operation,
                                 std::function<bool(Edge* edge)> edgeCondition, bool straight)
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
            if(!edgeCondition(*v))
                continue;
            auto vert = straight ? (*v)->To : (*v)->From;
            q.push(vert);
            if(!operation(u, vert, *v)) {
                break;
            }
        }
        vertexes[u] = Color::Black;
    }
}


#endif
