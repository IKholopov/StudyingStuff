#define uint unsigned int

#include <iostream>
#include <vector>
#include "Graph.h"


int main()
{
    std::vector<Edge> e;
    e.push_back(Edge(1, 5));
    Graph g(9, e);
    return 0;
}
