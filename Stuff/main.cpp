#include <iostream>
#include <vector>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <time.h>
#include <stdlib.h>
#include "OrientedGraph.h"
#include "GraphManager.h"
#include "CustomGenerator.h"


int main()
{
    IGraph* g = GenerateGraphFromCin();
    delete g;
    return 0;
}

