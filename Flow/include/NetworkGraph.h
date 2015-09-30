#ifndef FLOW_NETWORKGRAPH_H
#define FLOW_NETWORKGRAPH_H

#include <utility>
#include "NetworkEdge.h"
#include "OrientedGraphValuedEdge.hpp"

template <class FlowType>
class NetworkGraph: public OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>*>
{
    public:
        NetworkGraph(IGraph& graph): OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>*>(graph) {}
        NetworkGraph(unsigned int size, IGraph& graph):OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>*>(size, graph) {}
        NetworkGraph(IGraph* graph): OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>*>(graph) {}
        NetworkGraph(unsigned int size, IGraph* graph):OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>*>(size, graph) {}
        ~NetworkGraph() {}

        std::pair<NetworkGraph<FlowType>*, std::vector<unsigned int>*> GetLayeredNetwork(unsigned int source, unsigned int sink);\
        void AddResidiual(unsigned int from, unsigned int to, FlowType flow);
};

#endif

template <class FlowType>
std::pair<NetworkGraph<FlowType>*, std::vector<unsigned int>* > NetworkGraph<FlowType>::GetLayeredNetwork(unsigned int source, unsigned int sink)
{
    std::vector<unsigned int>* distances = new std::vector<unsigned int>(this->Size(), 0);
    this->BFS(source, [&distances](unsigned int u, unsigned int v){
        if(distances->at(v) == 0)
            distances->at(v) = u + 1;
    });
    IGraph* implementation = this->graph->Clone();
    implementation->DeleteAllEdges();
    NetworkGraph<FlowType>* layered = new NetworkGraph<FlowType>(this->Size(), implementation);
    std::vector<Edge*> edges = this->GetAllEdges();
    for(auto e: edges)
        if(distances->at(e->From) + 1 == distances->at(e->To))
            layered->BaseGraph::AddEdge(e->Clone());
    return std::pair<NetworkGraph<FlowType>*, std::vector<unsigned int>* >(layered, distances);
}
template <class FlowType>
void NetworkGraph<FlowType>::AddResidiual(unsigned int from, unsigned int to, FlowType flow)
{
    auto directEdge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>*>*>(this->GetEdge(from, to));
    assert(directEdge == NULL);
    assert(directEdge->GetValue()->Capacity - flow >= 0);
    directEdge->GetValue()->Capacity -= flow;
    auto reversedEdge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>*>*>(this->GetEdge(to, from));
    if(reversedEdge == NULL)
        this->BaseGraph::AddEdge(new ValuedEdge<NetworkEdgeValue<FlowType>*>(from, to, new NetworkEdgeValue<FlowType>(flow, 0)));

}
