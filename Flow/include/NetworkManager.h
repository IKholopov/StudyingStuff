#ifndef FLOW_NETWORKMANAGER_H
#define FLOW_NETWORKMANAGER_H

#include "LayerNetwork.h"
#include "NetworkDelta.h"
#include "ParentChildListOriented.h"
#include "TIAGraphDeltaIds.h"

#include <vector>
#include <queue>
#include <istream>
#include <ostream>

namespace GraphLibrary {

template <class FlowType>
class NetworkManager
{
    public:
        static NetworkManager<FlowType>& instance();
        void  threeIndiansAlgorithm(NetworkGraph<FlowType>& graph,
                                                      unsigned long long source, unsigned long long sink,
                                                      IMultiGraph *residualImpl = new ParentChildListOriented(),
                                                      IMultiGraph *layeredImpl = new ParentChildListOriented());
        std::vector<NetworkDelta>*  threeIndiansAlgorithmDelta(NetworkGraph<FlowType>& graph,
                                                      unsigned long long source, unsigned long long sink,
                                                      IMultiGraph *residualImpl = new ParentChildListOriented(),
                                                      IMultiGraph *layeredImpl = new ParentChildListOriented());
        std::pair<std::vector<Edge>*,NetworkGraph<FlowType>*> readGraph(std::istream& stream, IMultiGraph *realization);
        void writeGraphFlow(std::ostream& stream, NetworkGraph<FlowType>* graph, std::vector<Edge>* edges);

    private:
        NetworkManager() {}
};

template <class FlowType>
NetworkManager<FlowType>& NetworkManager<FlowType>::instance()
{
    static NetworkManager<FlowType> instance;
    return instance;
}
template <class FlowType>
void NetworkManager<FlowType>::threeIndiansAlgorithm(NetworkGraph<FlowType> &graph,
                                                                       unsigned long long source, unsigned long long sink,
                                                     IMultiGraph* residualImpl, IMultiGraph* layeredImpl)
{

    assert(source < graph.size() && sink < graph.size());
    ResidualNetwork<FlowType>* residualNetwork = new ResidualNetwork<FlowType>(*residualImpl, graph);
    while(true)
    {
        auto layeredNetwork = new LayerNetwork<FlowType>(source, sink, *residualNetwork, *static_cast<IMultiGraph*>((*layeredImpl).clone()));
        if(layeredNetwork->getDistances()->at(sink) == 0) {
            delete layeredNetwork;
            break;
        }
        layeredNetwork->findBlockingPath(*residualNetwork);
        delete layeredNetwork;
    }
    graph.flowFromResidual(*residualNetwork);
    delete residualNetwork;
    delete layeredImpl;
}
template <class FlowType>
std::vector<NetworkDelta>* NetworkManager<FlowType>::threeIndiansAlgorithmDelta(NetworkGraph<FlowType>& graph, unsigned long long source, unsigned long long sink, IMultiGraph* residualImpl, IMultiGraph* layeredImpl)
{
    std::vector<NetworkDelta>* deltas = new std::vector<NetworkDelta>();
    ///ORIGINALGRAPH_ID = 0
    ///RESIDUAL_ID = 1
    ///LAYERED_ID = 2
    assert(source < graph.size() && sink < graph.size());
    ResidualNetwork<FlowType>* residualNetwork = new ResidualNetwork<FlowType>(*residualImpl, graph);
    while(true)
    {
        auto layeredNetwork = new LayerNetwork<FlowType>(source, sink, *residualNetwork,
                                                         *static_cast<IMultiGraph*>((*layeredImpl).clone()), deltas);
        if(layeredNetwork->getDistances()->at(sink) == 0) {
            delete layeredNetwork;
            break;
        }
        layeredNetwork->findBlockingPath(*residualNetwork, deltas);
        delete layeredNetwork;
    }
    NetworkDelta originalDelta(0);
    originalDelta.setMessage("Original network: get flow from residual");
    graph.flowFromResidual(*residualNetwork, &originalDelta);
    deltas->push_back(originalDelta);
    delete residualNetwork;
    delete layeredImpl;
    return deltas;
}
template <class FlowType>
std::pair<std::vector<Edge> *, NetworkGraph<FlowType> *> NetworkManager<FlowType>::readGraph(std::istream &stream, IMultiGraph* realization)
{
    unsigned long long n, m, from, to;
    FlowType val;
    stream >> n;
    stream >> m;
    std::vector<Edge>* edges = new std::vector<Edge>();
    NetworkGraph<FlowType>* graph = new NetworkGraph<FlowType>(n, realization);
    for(unsigned long long i = 0; i < m; ++i)
    {
        stream >> from;
        stream >> to;
        stream >> val;
        edges->push_back(NetworkEdge<FlowType>(i, from - 1, to - 1, val, 0));
        graph->addEdge(new NetworkEdge<FlowType>(i, from - 1, to - 1, val, 0));
    }
    return std::pair<std::vector<Edge>*, NetworkGraph<FlowType>*>(edges, graph);
}
template <class FlowType>
void NetworkManager<FlowType>::writeGraphFlow(std::ostream &stream, NetworkGraph<FlowType> *graph, std::vector<Edge> *edges)
{
    auto e = graph->getOutgoing(0);
    FlowType sum = 0;
    for(auto a = e->begin(); a != e->end(); ++a)
        sum += static_cast<NetworkEdge<FlowType>*>(*a)->getFlow();
    stream << sum << std::endl;
    for(auto a = (*edges).begin(); a != (*edges).end(); ++a)
        stream << static_cast<NetworkEdge<FlowType>*>(graph->getEdge((*a).From, (*a).To, (*a).getId()))->getFlow() << std::endl;
}
}


#endif
