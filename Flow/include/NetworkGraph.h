#ifndef FLOW_NETWORKGRAPH_H
#define FLOW_NETWORKGRAPH_H

#include <utility>
#include "NetworkEdge.h"
#include "OrientedGraphValuedEdge.hpp"

template <class FlowType>
class NetworkGraph: public OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>>
{
    public:
        NetworkGraph(IGraph& graph): OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>>(graph) {}
        NetworkGraph(unsigned long long size, IGraph& graph):OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>>(size, graph) {}
        NetworkGraph(IGraph* graph): OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>>(graph) {}
        NetworkGraph(unsigned long long size, IGraph* graph):OrientedGraphValuedEdge<NetworkEdgeValue<FlowType>>(size, graph) {}
        ~NetworkGraph() {}

        std::pair<NetworkGraph<FlowType> *, std::vector<long> *> GetLayeredNetwork(unsigned long long source, unsigned long long sink);\
        void AddFlowToResidiual(unsigned long long from, unsigned long long to, FlowType flow);
        void FlowFromResidual(NetworkGraph<FlowType> &residual);
};

#endif

template <class FlowType>
std::pair<NetworkGraph<FlowType>*, std::vector<long>* > NetworkGraph<FlowType>::GetLayeredNetwork(unsigned long long source, unsigned long long sink)
{
    std::vector<long>* distances = new std::vector<long>(this->Size(), 0);
    this->BFS(source, [&distances](unsigned long long u, unsigned long long v){
        if(distances->at(v) == 0)
            distances->at(v) = distances->at(u) + 1;
    });
    distances->at(source) = 0;
    IGraph* implementation = this->graph->Clone();
    implementation->DeleteAllEdges();
    NetworkGraph<FlowType>* layered = new NetworkGraph<FlowType>(this->Size(), implementation);
    std::vector<Edge*> edges = this->GetAllEdges();
    for(auto e = edges.begin(); e != edges.end(); ++e)
        if(distances->at((*e)->From) + 1 == distances->at((*e)->To))
            layered->BaseGraph::AddEdge((*e)->Clone());
    return std::pair<NetworkGraph<FlowType>*, std::vector<long>* >(layered, distances);
}
template <class FlowType>
void NetworkGraph<FlowType>::AddFlowToResidiual(unsigned long long from, unsigned long long to, FlowType flow)
{
    auto directEdge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(this->GetEdge(from, to));
    assert(directEdge != NULL);
    assert(directEdge->GetValue().Capacity - flow >= 0);
    if(directEdge->GetValue().Capacity == flow)
        this->graph->DeleteEdge(from, to);
    else
        directEdge->SetValue(NetworkEdgeValue<FlowType>(directEdge->GetValue().Capacity - flow, directEdge->GetValue().Flow));
    auto reversedEdge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(this->GetEdge(to, from));
    if(reversedEdge == NULL)
        this->BaseGraph::AddEdge(new ValuedEdge<NetworkEdgeValue<FlowType>>(to, from, NetworkEdgeValue<FlowType>(flow, 0)));
    else reversedEdge->SetValue(NetworkEdgeValue<FlowType>(reversedEdge->GetValue().Capacity + flow, reversedEdge->GetValue().Flow));

}
template <class FlowType>
void NetworkGraph<FlowType>::FlowFromResidual(NetworkGraph<FlowType> &residual)
{
    std::vector<Edge*> edges = this->GetAllEdges();
    for(auto e = edges.begin(); e != edges.end(); ++e)
    {
        ValuedEdge<NetworkEdgeValue<FlowType>>* edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(*e);
        if(!residual.CheckEdge(edge->From, edge->To))
            edge->SetValue(NetworkEdgeValue<FlowType>(edge->GetValue().Capacity, edge->GetValue().Capacity));
        else
        {
            auto resEdge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(residual.GetEdge(edge->From, edge->To));
            if(edge->GetValue().Capacity - resEdge->GetValue().Capacity >= 0)
                edge->SetValue(NetworkEdgeValue<FlowType>(edge->GetValue().Capacity, edge->GetValue().Capacity - resEdge->GetValue().Capacity));
        }
    }
}
