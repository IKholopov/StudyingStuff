#ifndef FLOW_RESIDUALGRAPH_H
#define FLOW_RESIDUALGRAPH_H

#include "NetworkGraph.h"
#include "NetworkDelta.h"

#include <utility>

template <class FlowType>
class ResidualNetwork: public NetworkGraph<FlowType>
{
    public:
        ResidualNetwork(IMultiGraph& implementation, NetworkGraph<FlowType>& graph_);

        void addFlow(unsigned long long from, unsigned long long to, unsigned long long id , FlowType flow);
        void addFlow(unsigned long long from, unsigned long long to, unsigned long long id , FlowType flow, NetworkDelta* delta);
        std::pair<NetworkGraph<FlowType>*, std::vector<long long>* > getLayeredNetwork(unsigned long long source, IMultiGraph &implementation);
    private:
        NetworkGraph<FlowType>* base_;
};


template <class FlowType>
ResidualNetwork<FlowType>::ResidualNetwork(IMultiGraph &implementation, NetworkGraph<FlowType> &graph):NetworkGraph<FlowType>(graph.size(), implementation)
{
    base_ = &graph;
    auto edges = graph.getAllEdgesConst();
    for(auto e = edges->begin(); e != edges->end(); ++e)
        this->addEdge((*e)->clone());
}

template <class FlowType>
void ResidualNetwork<FlowType>::addFlow(unsigned long long from, unsigned long long to, unsigned long long id, FlowType flow)
{
    auto directEdge = static_cast<NetworkEdge<FlowType>*>(this->getEdge(from, to, id));
    assert(directEdge != NULL);
    assert(directEdge->getCapacity() - flow >= 0);
    directEdge->setCapacity(directEdge->getCapacity() - flow);
    auto reversedEdge = static_cast<NetworkEdge<FlowType>*>(this->BaseGraph::getEdge(to, from));
    if(reversedEdge == NULL) {
        this->addEdge(new NetworkEdge<FlowType>(0, to, from, flow, 0));
    }
    else reversedEdge->setCapacity(reversedEdge->getCapacity()+ flow);
}
template <class FlowType>
void ResidualNetwork<FlowType>::addFlow(unsigned long long from, unsigned long long to, unsigned long long id, FlowType flow,
                                        NetworkDelta* delta)
{
    auto directEdge = static_cast<NetworkEdge<FlowType>*>(this->getEdge(from, to, id));
    assert(directEdge != NULL);
    assert(directEdge->getCapacity() - flow >= 0);
    directEdge->setCapacity(directEdge->getCapacity() - flow);
    delta->addEdgeChange(new NetworkEdgeChange(directEdge->getId(), directEdge->From, directEdge->To, directEdge->getCapacity(), directEdge->getFlow()));
    auto reversedEdge = static_cast<NetworkEdge<FlowType>*>(this->BaseGraph::getEdge(to, from));
    if(reversedEdge == NULL) {
        this->addEdge(new NetworkEdge<FlowType>(0, to, from, flow, 0));
        reversedEdge = static_cast<NetworkEdge<FlowType>*>(this->BaseGraph::getEdge(to, from));
    }
    else reversedEdge->setCapacity(reversedEdge->getCapacity()+ flow);
    delta->addEdgeChange(new NetworkEdgeChange(reversedEdge->getId(), reversedEdge->From, reversedEdge->To, reversedEdge->getCapacity(), reversedEdge->getFlow()));
}

#endif
