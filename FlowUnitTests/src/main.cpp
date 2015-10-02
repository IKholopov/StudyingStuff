#include <iostream>
#include <stdlib.h>
#include "NetworkManager.h"
#include "EdgeListOriented.h"
#include "ParentChildListOriented.h"

NetworkEdgeValue<long long> randInt()
{
    return NetworkEdgeValue<long long>(rand() % 25 + 1, 0);
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
    auto in = NetworkManager<long long>::instance().ReadGraph(std::cin, new ParentChildListOriented());
    auto edges = in.first;
    auto graph = in.second;
    NetworkManager<long long>::instance().ThreeIndiansAlgorithm(*graph, 0, graph->Size() - 1);
    NetworkManager<long long>::instance().WriteGraphFlow(std::cout, graph, edges);
    delete graph;
    delete edges;
    return 0;
}
