#ifndef _TESTSHP_CPP__
#define _TESTSHP_CPP__

#include <iostream>
#include <vector>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <time.h>
#include <stdlib.h>
#include "OrientedGraph.h"
#include "UnorientedGraphValuedEdge.hpp"
#include "GraphManager.h"


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property,
                               boost::property<boost::edge_weight_t,int> > BoostGraph;
typename BoostGraph::vertex_descriptor u, v;
typedef typename BoostGraph ::edge_property_type Weight;

int randInt()
{
    return rand() % 256;
}

void TestShortestPaths(double probability)
{
    const int SIZE = 10000;
    UnorientedGraphValuedEdge<int>* g = new UnorientedGraphValuedEdge<int>(SIZE);
    g->RandomizeGraph(probability, &randInt);
    clock_t start_t, end_t;
    std::cout << "Probability: " << probability << std::endl;
    double sumBFS = 0;
    double sumDj = 0;
    double sumBDj = 0;
    std::vector<int> requests;
    for(int i = 0; i < 20; ++i)
    {
        int u = rand() % SIZE;
        int v = rand() % SIZE;
        requests.push_back(u);
        start_t = clock();
        g->BFS(u, v);
        end_t = clock();
        sumBFS += (float)(end_t - start_t)/CLOCKS_PER_SEC;

        start_t = clock();
        g->Dijkstra(u, v);
        end_t = clock();
        sumDj += (float)(end_t - start_t)/CLOCKS_PER_SEC;
    }
    BoostGraph gb(g->Size());
    for(int i = 0; i < g->Size(); ++i)
        for(int j = i + 1; j < g->Size(); ++j)
            if(g->CheckEdge(i, j))
            {
                boost::add_edge(boost::vertex(i, gb), boost::vertex(j,gb), Weight(g->GetEdgeValue(i, j)), gb);
            }

    std::vector<BoostGraph::vertex_descriptor> p(boost::num_vertices(gb));
    std::vector<int> d(boost::num_vertices(gb));

    auto bgl = boost::predecessor_map(boost::make_iterator_property_map(p.begin(),
                            boost::get(boost::vertex_index, gb))).
                            distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, gb)));
    delete g;
    for(int i = 0; i < 20; ++i)
    {
        BoostGraph::vertex_descriptor s = boost::vertex(u, gb);
        start_t = clock();
        boost::dijkstra_shortest_paths(gb, s, bgl);
        end_t = clock();
        sumBDj += (float)(end_t - start_t)/CLOCKS_PER_SEC;
    }
    std::cout << "\tBFS 1-K " << sumBFS << std::endl;
    std::cout << "\tDijkstra " << sumDj << std::endl;
    std::cout << "\tboost::Dijkstra " << sumBDj << std::endl;
}

void TestMy1KBFS(int u, int v)
{
    /*GraphValuedEdge* g = new GraphValuedEdge(10000);
    g->RandomizeUnorientedGraph(0.02);
    g->Graph::WriteToFile("graph.gr");*/
    UnorientedGraphValuedEdge<int>* g = new UnorientedGraphValuedEdge<int>(1000);
    g->RandomizeGraph(0.05, &randInt);
    std::cout << g->BFS(u, v) << std::endl;
    delete g;
}
void TestMy1KBFS()
{
    unsigned int u, v;
    std::cin >> u;
    std::cin >> v;
    TestMy1KBFS(u, v);
}
void TestMyDijkstra(int u, int v)
{
    UnorientedGraphValuedEdge<int>* g = new UnorientedGraphValuedEdge<int>(10000);
    g->RandomizeGraph(0.05, &randInt);
    std::cout << g->Dijkstra(u,v) << std::endl;
    delete g;
}
void TestMyDijkstra()
{
    unsigned int u, v;
    std::cin >> u;
    std::cin >> v;
    TestMyDijkstra(u, v);
}
void TestBoostDijkstra(int u, int v)
{
    UnorientedGraphValuedEdge<int>* g = new UnorientedGraphValuedEdge<int>(10000);
    g->RandomizeGraph(0.05, &randInt);
    BoostGraph gb(g->Size());
    for(int i = 0; i < g->Size(); ++i)
        for(int j = i + 1; j < g->Size(); ++j)
            if(g->CheckEdge(i, j))
            {
                boost::add_edge(boost::vertex(i, gb), boost::vertex(j,gb), Weight(g->GetEdgeValue(i, j)), gb);
            }

    std::vector<BoostGraph::vertex_descriptor> p(boost::num_vertices(gb));
    std::vector<int> d(boost::num_vertices(gb));
    BoostGraph::vertex_descriptor s = boost::vertex(u, gb);
    boost::dijkstra_shortest_paths(gb, s,
                                                boost::predecessor_map(boost::make_iterator_property_map(p.begin(),
                                                                                                         boost::get(boost::vertex_index, gb))).
                                   distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, gb))));
    std::cout << d[v] << std::endl;
    delete g;
}
void TestBoostDijkstra()
{
    unsigned int u, v;
    std::cin >> u;
    std::cin >> v;
    TestBoostDijkstra(u, v);
}

#endif
