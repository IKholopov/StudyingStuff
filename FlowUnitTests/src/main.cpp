#include <iostream>
#include <stdlib.h>
#include "NetworkManager.h"
#include "EdgeListOriented.h"
#include "ParentChildListOriented.h"

long long randInt()
{
    return rand() % 25 + 1;
}

int main()
{
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
