#include <iostream>
#include <vector>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <time.h>
#include <stdlib.h>
#include "Graph.h"
#include "GraphIntValuedEdge.h"
#include "GraphManager.h"


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property,
                               boost::property<boost::edge_weight_t,int> > BoostGraph;
typename BoostGraph::vertex_descriptor u, v;
typedef typename BoostGraph ::edge_property_type Weight;

void GrandTest(double probability)
{
    GraphIntValuedEdge* g = new GraphIntValuedEdge(100);
    g->RandomizeUnorientedGraph(probability);
    clock_t start_t, end_t;
    std::cout << "Probability: " << probability << std::endl;
    double sumBFS = 0;
    double sumDj = 0;
    double sumBDj = 0;
    std::vector<int> requests;
    for(int i = 0; i < 20; ++i)
    {
        int u = rand() % 100;
        int v = rand() % 100;
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
    GraphIntValuedEdge* g = new GraphIntValuedEdge(10000);
    g->RandomizeUnorientedGraph(0.05);
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
    GraphIntValuedEdge* g = new GraphIntValuedEdge(10000);
    g->RandomizeUnorientedGraph(0.05);
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
    GraphIntValuedEdge* g = new GraphIntValuedEdge(10000);
    g->RandomizeUnorientedGraph(0.05);
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

int main()
{
    //GrandTest(0.01);
    //GrandTest(0.05);
    //GrandTest(0.1);
    GrandTest(0.5);
    return 0;
}

