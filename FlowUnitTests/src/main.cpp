#include <iostream>
#include <stdlib.h>
#include "NetworkManager.h"

NetworkEdgeValue<int> randInt()
{
    return NetworkEdgeValue<int>(rand() % 25 + 1, 0);
}

int main()
{
    /*typedef ValuedEdge<NetworkEdgeValue<int>> NetEdge;
    std::vector<NetEdge*> v;
    v.push_back(new NetEdge(0, 1, NetworkEdgeValue<int>(4, 0)));
    v.push_back(new NetEdge(0, 2, NetworkEdgeValue<int>(2, 0)));
    v.push_back(new NetEdge(1, 3, NetworkEdgeValue<int>(3, 0)));
    v.push_back(new NetEdge(1, 4, NetworkEdgeValue<int>(1, 0)));
    v.push_back(new NetEdge(2, 4, NetworkEdgeValue<int>(1, 0)));
    v.push_back(new NetEdge(2, 5, NetworkEdgeValue<int>(3, 0)));
    v.push_back(new NetEdge(3, 6, NetworkEdgeValue<int>(2, 0)));
    v.push_back(new NetEdge(4, 1, NetworkEdgeValue<int>(1, 0)));
    v.push_back(new NetEdge(4, 5, NetworkEdgeValue<int>(1, 0)));
    v.push_back(new NetEdge(4, 6, NetworkEdgeValue<int>(2, 0)));
    v.push_back(new NetEdge(4, 7, NetworkEdgeValue<int>(2, 0)));
    v.push_back(new NetEdge(5, 4, NetworkEdgeValue<int>(3, 0)));
    v.push_back(new NetEdge(5, 7, NetworkEdgeValue<int>(4, 0)));
    v.push_back(new NetEdge(6, 1, NetworkEdgeValue<int>(1, 0)));
    v.push_back(new NetEdge(6, 8, NetworkEdgeValue<int>(3, 0)));
    v.push_back(new NetEdge(7, 8, NetworkEdgeValue<int>(2, 0)));
    v.push_back(new NetEdge(8, 7, NetworkEdgeValue<int>(3, 0)));
    auto flowed = NetworkManager<int>::instance().ThreeIndiansAlgorithm(9, v, 0, 8);*/
    NetworkGraph<int> graph(2, new AdjacencyMatrixOriented());
    graph.RandomizeGraph(1, &randInt);
    NetworkManager<int>::instance().ThreeIndiansAlgorithm(graph, 0, 1);

    return 0;
}
