#include <iostream>
#include <stdlib.h>
#include "NetworkManager.h"

template <long long T>
NetworkEdgeValue<long long> randInt()
{
    return NetworkEdgeValue<long long>(rand() % T + 1, 0);
}

int Validate(NetworkGraph<long long>& graph)
{
    std::vector<Edge*> edges =  graph.GetAllEdges();
    for(auto a: edges)
    {
        auto b = static_cast<ValuedEdge<NetworkEdgeValue<long long>>*>(a);
        if(b->GetValue().Capacity < b->GetValue().Flow)
        {
            std::cerr << "Test failed - overflowing" << std::endl;
            return 1;
        }
    }
    for(long long i = 1; i < graph.Size() - 1; ++i)
    {
        std::vector<unsigned long long> parents = graph.GetParents(i);
        std::vector<unsigned long long> childs = graph.GetChilds(i);
        unsigned long long sumP = 0;
        for(auto a: parents)
            sumP += static_cast<ValuedEdge<NetworkEdgeValue<long long>>*>(graph.GetEdge(a, i))->GetValue().Flow;
        unsigned long long sumC = 0;
        for(auto a: childs)
            sumC += static_cast<ValuedEdge<NetworkEdgeValue<long long>>*>(graph.GetEdge(i, a))->GetValue().Flow;
        if(sumP != sumC)
        {
            std::cerr << "Test failed - invalid ins and outs" << std::endl;
            return 1;
        }
    }
    std::cout << "All passed" << std::endl;
    return 0;
}

int main()
{
    /*typedef ValuedEdge<NetworkEdgeValue<long long>> NetEdge;
    std::vector<NetEdge*> v;
    v.push_back(new NetEdge(0, 1, NetworkEdgeValue<long long>(4, 0)));
    v.push_back(new NetEdge(0, 2, NetworkEdgeValue<long long>(2, 0)));
    v.push_back(new NetEdge(1, 3, NetworkEdgeValue<long long>(3, 0)));
    v.push_back(new NetEdge(1, 4, NetworkEdgeValue<long long>(1, 0)));
    v.push_back(new NetEdge(2, 4, NetworkEdgeValue<long long>(1, 0)));
    v.push_back(new NetEdge(2, 5, NetworkEdgeValue<long long>(3, 0)));
    v.push_back(new NetEdge(3, 6, NetworkEdgeValue<long long>(2, 0)));
    v.push_back(new NetEdge(4, 1, NetworkEdgeValue<long long>(1, 0)));
    v.push_back(new NetEdge(4, 5, NetworkEdgeValue<long long>(1, 0)));
    v.push_back(new NetEdge(4, 6, NetworkEdgeValue<long long>(2, 0)));
    v.push_back(new NetEdge(4, 7, NetworkEdgeValue<long long>(2, 0)));
    v.push_back(new NetEdge(5, 4, NetworkEdgeValue<long long>(3, 0)));
    v.push_back(new NetEdge(5, 7, NetworkEdgeValue<long long>(4, 0)));
    v.push_back(new NetEdge(6, 1, NetworkEdgeValue<long long>(1, 0)));
    v.push_back(new NetEdge(6, 8, NetworkEdgeValue<long long>(3, 0)));
    v.push_back(new NetEdge(7, 8, NetworkEdgeValue<long long>(2, 0)));
    v.push_back(new NetEdge(8, 7, NetworkEdgeValue<long long>(3, 0)));
    auto flowed = NetworkManager<long long>::instance().ThreeIndiansAlgorithm(9, v, 0, 8);
    NetworkGraph<long long> graph(500, new AdjacencyMatrixOriented());
    graph.RandomizeGraph(0.04, &randInt);
    NetworkManager<long long>::instance().ThreeIndiansAlgorithm(graph, 0, 1);*/
    //auto in = NetworkManager<long long>::instance().ReadGraph(std::cin, new AdjacencyMatrixOriented());
    //auto edges = in.first;
    //auto graph = in.second;
    //NetworkManager<long long>::instance().ThreeIndiansAlgorithm(*graph, 0, graph->Size() - 1);
    for(int i = 0; i < 1000; ++i)
    {
        auto graph = new NetworkGraph<long long>(rand() % 500 + 2, new AdjacencyMatrixOriented());
        graph->RandomizeGraph(((double)(rand() % 40))/100, &randInt<1000>);
        NetworkManager<long long>::instance().ThreeIndiansAlgorithm(*graph, 0, graph->Size() - 1);

        if(Validate(*graph))
            break;
    }
    //NetworkManager<long long>::instance().WriteGraphFlow(std::cout, graph, edges);
    //delete graph;
    //delete edges;
    return 0;
}
