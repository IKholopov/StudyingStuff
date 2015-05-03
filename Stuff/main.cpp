#include <iostream>
#include <vector>
#include "Graph.h"
#include "GraphValuedEdge.h"
#include "GraphManager.h"


int main()
{

    /*GraphValuedEdge* g = new GraphValuedEdge(10000);
    g->RandomizeUnorientedGraph(0.02);
    g->Graph::WriteToFile("graph.gr");*/
    GraphValuedEdge* g = (GraphValuedEdge*)GraphManager::ReadFromFile("graph.gr");
    std::cout << g->BFS(2,42) << std::endl;
    return 0;
}
