#ifndef FLOW_NETWORKMANAGER_H
#define FLOW_NETWORKMANAGER_H

#include <vector>
#include <queue>
#include <istream>
#include <ostream>
#include "LayerNetwork.h"
#include "ParentChildListOriented.h"

template <class FlowType>
class NetworkManager
{
    public:
        static NetworkManager<FlowType>& instance();
        void  ThreeIndiansAlgorithm(NetworkGraph<FlowType>& graph,
                                                      unsigned long long source, unsigned long long sink,
                                                      IMultiGraph *residualImpl = new ParentChildListOriented(),
                                   IMultiGraph *layeredImpl = new ParentChildListOriented());
        std::pair<std::vector<Edge>*,NetworkGraph<FlowType>*> ReadGraph(std::istream& stream, IMultiGraph *realization);
        void WriteGraphFlow(std::ostream& stream, NetworkGraph<FlowType>* graph, std::vector<Edge>* edges);

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
void NetworkManager<FlowType>::ThreeIndiansAlgorithm(NetworkGraph<FlowType> &graph,
                                                                       unsigned long long source, unsigned long long sink,
                                                     IMultiGraph* residualImpl, IMultiGraph* layeredImpl)
{

    assert(source < graph.Size() && sink < graph.Size());
    ResidualNetwork<FlowType>* residualNetwork = new ResidualNetwork<FlowType>(*residualImpl, graph);
    while(true)
    {
        auto layeredNetwork = new LayerNetwork<FlowType>(source, sink, *residualNetwork, *static_cast<IMultiGraph*>((*layeredImpl).Clone()));
        if(layeredNetwork->GetDistances()->at(sink) == 0)
        {
            delete layeredNetwork;
            break;
        }
        layeredNetwork->FindBlockingPath(*residualNetwork);
        delete layeredNetwork;
    }
    graph.FlowFromResidual(*residualNetwork);
    delete residualNetwork;
    delete layeredImpl;
}
template <class FlowType>
std::pair<std::vector<Edge> *, NetworkGraph<FlowType> *> NetworkManager<FlowType>::ReadGraph(std::istream &stream, IMultiGraph* realization)
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
        graph->AddEdge(new NetworkEdge<FlowType>(i, from - 1, to - 1, val, 0));
    }
    return std::pair<std::vector<Edge>*, NetworkGraph<FlowType>*>(edges, graph);
}
template <class FlowType>
void NetworkManager<FlowType>::WriteGraphFlow(std::ostream &stream, NetworkGraph<FlowType> *graph, std::vector<Edge> *edges)
{
    auto e = graph->GetOutgoing(0);
    FlowType sum = 0;
    for(auto a = e->begin(); a != e->end(); ++a)
        sum += static_cast<NetworkEdge<FlowType>*>(*a)->GetFlow();
    stream << sum << std::endl;
    for(auto a = (*edges).begin(); a != (*edges).end(); ++a)
        stream << static_cast<NetworkEdge<FlowType>*>(graph->GetEdge((*a).From, (*a).To, (*a).GetId()))->GetFlow() << std::endl;
}

#endif
