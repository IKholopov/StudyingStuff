#ifndef FLOW_NETWORKGRAPH_H
#define FLOW_NETWORKGRAPH_H

#include <utility>
#include "IMultiGraph.h"
#include "OrientedGraph.h"
#include "NetworkEdge.h"

template <class FlowType>
class NetworkGraph: public OrientedGraph
{
    public:
        NetworkGraph(IMultiGraph& graph): OrientedGraph(graph) {this->idCounter = 0;}
        NetworkGraph(unsigned long long size, IMultiGraph& graph):OrientedGraph(size, graph) {this->idCounter = 0;}
        NetworkGraph(IMultiGraph* graph): OrientedGraph(graph) {this->idCounter = 0;}
        NetworkGraph(unsigned long long size, IMultiGraph* graph):OrientedGraph(size, graph) {this->idCounter = 0;}
        ~NetworkGraph() {}

        bool CheckEdge(long long from, long long to, unsigned long long id);
        Edge* GetEdge(long long from, long long to, unsigned long long id);
        const std::vector<Edge*>* GetAllEdgesConst() const;
        const std::vector<Edge*>* GetOutgoing(unsigned long long vertex) const;
        const std::vector<Edge*>* GetIngoing(unsigned long long vertex) const;
        unsigned long long GetIdCounter() const;
        bool AddEdge(Edge* edge);
        void FlowFromResidual(NetworkGraph<FlowType> &residual);
        virtual void BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* edge)> operation,
                         std::function<bool(Edge* edge)> edgeCondition, bool straight = true);
    protected:
        void  IncreaseIdCounter();
    private:
        unsigned long long idCounter;
};


template <class FlowType>
bool NetworkGraph<FlowType>::CheckEdge(long long from, long long to, unsigned long long id)
{
    auto edges = this->GetOutgoing(from);
    for(auto e = edges->begin(); e != edges->end(); ++e)
    {
       if((*e)->To == to && (*e)->GetId() == id )
           return true;
    }
    return false;
}
template <class FlowType>
Edge* NetworkGraph<FlowType>::GetEdge(long long from, long long to, unsigned long long id)
{
    auto edges = this->GetOutgoing(from);
    for(auto e = edges->begin(); e != edges->end(); ++e)
        if((*e)->To == to && (*e)->GetId() == id )
            return *e;
    return NULL;
}
template <class FlowType>
const std::vector<Edge*>* NetworkGraph<FlowType>::GetAllEdgesConst() const
{
    return static_cast<IMultiGraph*>(this->graph)->GetAllEdgesConst();
}
template <class FlowType>
const std::vector<Edge *> *NetworkGraph<FlowType>::GetOutgoing(unsigned long long vertex) const
{
    return static_cast<IMultiGraph*>(this->graph)->GetOutgoing(vertex);
}
template <class FlowType>
const std::vector<Edge *> *NetworkGraph<FlowType>::GetIngoing(unsigned long long vertex) const
{
    return static_cast<IMultiGraph*>(this->graph)->GetIngoing(vertex);
}
template <class FlowType>
unsigned long long NetworkGraph<FlowType>::GetIdCounter() const
{
    return idCounter;
}
template <class FlowType>
bool NetworkGraph<FlowType>::AddEdge(Edge* edge)
{
    edge->SetId(this->GetIdCounter());
    IncreaseIdCounter();
    this->OrientedGraph::AddEdge(edge);
}
template <class FlowType>
void NetworkGraph<FlowType>::FlowFromResidual(NetworkGraph<FlowType> &residual)
{
    auto edges = this->GetAllEdges();
    for(auto e = edges->begin(); e != edges->end(); ++e)
    {
        NetworkEdge<FlowType>* edge = static_cast<NetworkEdge<FlowType>*>(*e);
        auto resEdge = static_cast<NetworkEdge<FlowType>*>(residual.GetEdge(edge->From, edge->To, edge->GetId()));
        if(edge->GetCapacity() - resEdge->GetCapacity() >= 0)
            edge->SetFlow(edge->GetCapacity() - resEdge->GetCapacity());
    }
    delete edges;
}
template <class FlowType>
void NetworkGraph<FlowType>::IncreaseIdCounter()
{
    ++idCounter;
}
template <class FlowType>
void NetworkGraph<FlowType>::BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* e)> operation,
                                 std::function<bool(Edge* edge)> edgeCondition, bool straight)
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
            if(!edgeCondition(*v))
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
