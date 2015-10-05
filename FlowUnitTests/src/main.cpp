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
    auto in = NetworkManager<long long>::instance().ReadGraph(std::cin, new ParentChildListOriented());
    auto edges = in.first;
    auto graph = in.second;
    NetworkManager<long long>::instance().ThreeIndiansAlgorithm(*graph, 0, graph->Size() - 1);
    NetworkManager<long long>::instance().WriteGraphFlow(std::cout, graph, edges);
    delete graph;
    delete edges;
    return 0;
}
