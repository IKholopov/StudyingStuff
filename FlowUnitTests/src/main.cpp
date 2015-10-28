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
    auto in = NetworkManager<long long>::instance().readGraph(std::cin, new ParentChildListOriented());
    auto edges = in.first;
    auto graph = in.second;
    NetworkManager<long long>::instance().threeIndiansAlgorithm(*graph, 0, graph->size() - 1);
    NetworkManager<long long>::instance().writeGraphFlow(std::cout, graph, edges);
    delete graph;
    delete edges;
    return 0;
}
