#ifndef FLOW_RESIDUALGRAPH_H
#define FLOW_RESIDUALGRAPH_H

#include <utility>
#include "NetworkGraph.h"

template <class FlowType>
class ResidualNetwork: public NetworkGraph<FlowType>
{
    public:
        ResidualNetwork(IMultiGraph& implementation, NetworkGraph<FlowType>& graph);
        void AddFlow(unsigned long long from, unsigned long long to, unsigned long long id , FlowType flow);
        std::pair<NetworkGraph<FlowType>*, std::vector<long long>* > GetLayeredNetwork(unsigned long long source, IMultiGraph &implementation);
    private:
        NetworkGraph<FlowType>* base;
};


template <class FlowType>
ResidualNetwork<FlowType>::ResidualNetwork(IMultiGraph &implementation, NetworkGraph<FlowType> &graph):NetworkGraph<FlowType>(graph.Size(), implementation)
{
    base = &graph;
    auto edges = graph.GetAllEdgesConst();
    for(auto e = edges->begin(); e != edges->end(); ++e)
        this->AddEdge((*e)->Clone());
}

template <class FlowType>
void ResidualNetwork<FlowType>::AddFlow(unsigned long long from, unsigned long long to, unsigned long long id, FlowType flow)
{
    auto directEdge = static_cast<NetworkEdge<FlowType>*>(this->GetEdge(from, to, id));
    assert(directEdge != NULL);
    assert(directEdge->GetCapacity() - flow >= 0);
    directEdge->SetCapacity(directEdge->GetCapacity() - flow);
    auto reversedEdge = static_cast<NetworkEdge<FlowType>*>(this->BaseGraph::GetEdge(to, from));
    if(reversedEdge == NULL)
    {
        this->AddEdge(new NetworkEdge<FlowType>(0, to, from, flow, 0));
    }
    else reversedEdge->SetCapacity(reversedEdge->GetCapacity()+ flow);
}

#endif
