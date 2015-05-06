#include <iostream>
#include <vector>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "Graph.h"
#include "GraphValuedEdge.h"
#include "GraphManager.h"


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> BoostGraph;

void TestMy1KBFS()
{
    GraphValuedEdge* g = new GraphValuedEdge(10000);
    g->RandomizeUnorientedGraph(0.02);
    g->Graph::WriteToFile("graph.gr");
    //GraphValuedEdge* g = (GraphValuedEdge*)GraphManager::ReadFromFile("graph.gr");
    std::cout << g->BFS(3,15) << std::endl;
}

int main()
{
    BoostGraph g;
    return 0;
}
