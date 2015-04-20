

#include <iostream>
#include <vector>
#include "Graph.h"
#include "GraphManager.hpp"


int main()
{
    Graph* g = GraphManager<int>::ReadFromFile("graph.gr");
    return 0;
}
