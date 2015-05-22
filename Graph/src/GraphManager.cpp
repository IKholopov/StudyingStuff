#include "GraphManager.h"
#include "GraphFileFormat.h"
#include "GraphValuedEdge.hpp"

Graph* GraphManager::GetRandomUnorientedGraph(unsigned int size)
{
    return GetRandomUnorientedGraph(size, 0.5);
}
Graph *GraphManager::GetRandomUnorientedGraph(unsigned int size, double probability)
{
    Graph* g = new Graph(size, false);
    g->RandomizeUnorientedGraph(probability);
    return g;
}
Graph* GraphManager::GetRandomGraph(unsigned int size)
{
    return GetRandomGraph(size, 0.5);
}
Graph *GraphManager::GetRandomGraph(unsigned int size, double probability)
{
    Graph* g = new Graph(size, false);
    g->RandomizeGraph(probability);
    return g;
}
Graph* GraphManager::ReadFromFile(std::string path)
{
    std::ifstream file(path.c_str());
    std::string s;
    std::getline(file, s);
    Graph* g;
    if(s == GR_TYPE_GRAPH_REGULAR)
    {
        g = GraphManager::ReadFromFileGraphRegular(file);
        file.close();
        return g;
    }
    if(s == GR_TYPE_GRAPH_VALUED_EDGE)
    {
        g = GraphManager::ReadFromFileGraphIntValuedEdge(file);
        file.close();
        return g;
    }
    throw std::exception();
    return NULL;
}
Graph* GraphManager::ReadFromFileGraphRegular(std::ifstream& file)
{
    Graph* g = new Graph(1, false);
    g->ReadFromFile(file);
    return g;
}
GraphValuedEdge<int>* GraphManager::ReadFromFileGraphIntValuedEdge(std::ifstream& file)
{
    GraphValuedEdge<int>* g = new GraphValuedEdge<int>(1, false);
    g->ReadFromFile(file);
    return g;
}
