#include "GraphManager.h"
#include "GraphFileFormat.h"
#include "GraphValuedEdge.hpp"

UnorientedGraph* GraphManager::GetRandomUnorientedGraph(unsigned int size)
{
    return GetRandomUnorientedGraph(size, 0.5);
}
UnorientedGraph* GraphManager::GetRandomUnorientedGraph(unsigned int size, double probability)
{
    UnorientedGraph* g = new UnorientedGraph(size);
    g->RandomizeGraph(probability);
    return g;
}
Graph* GraphManager::GetRandomGraph(unsigned int size)
{
    return GetRandomGraph(size, 0.5);
}
Graph* GraphManager::GetRandomGraph(unsigned int size, double probability)
{
    Graph* g = new Graph(size);
    g->RandomizeGraph(probability);
    return g;
}
IGraph* GraphManager::ReadFromFile(std::string path)
{
    std::ifstream file(path.c_str());
    std::string s;
    std::getline(file, s);
    IGraph* g;
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
    Graph* g = new Graph(1);
    g->ReadFromFile(file);
    return g;
}
GraphValuedEdge<int>* GraphManager::ReadFromFileGraphIntValuedEdge(std::ifstream& file)
{
    GraphValuedEdge<int>* g = new GraphValuedEdge<int>(1);
    g->ReadFromFile(file);
    return g;
}
