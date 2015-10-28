#include "GraphManager.h"
#include "GraphFileFormat.h"
#include "UnorientedGraphValuedEdge.hpp"
#include "AdjacencyMatrixOriented.h"
#include "AdjacencyMatrixUnoriented.h"

UnorientedGraph* GraphManager::GetRandomUnorientedGraph(unsigned int size)
{
    return GetRandomUnorientedGraph(size, 0.5);
}
UnorientedGraph* GraphManager::GetRandomUnorientedGraph(unsigned int size, double probability)
{
    UnorientedGraph* g = new UnorientedGraph(*(new AdjacencyMatrixUnoriented(size)));
    g->randomizeGraph(probability);
    return g;
}
OrientedGraph* GraphManager::GetRandomGraph(unsigned int size)
{
    return GetRandomGraph(size, 0.5);
}
OrientedGraph* GraphManager::GetRandomGraph(unsigned int size, double probability)
{
    OrientedGraph* g = new OrientedGraph(*(new AdjacencyMatrixOriented(size)));
    g->RandomizeGraph(probability);
    return g;
}
BaseGraph *GraphManager::ReadFromFile(std::string path)
{
    std::ifstream file(path.c_str());
    std::string s;
    std::getline(file, s);
    BaseGraph* g;
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
OrientedGraph* GraphManager::ReadFromFileGraphRegular(std::ifstream& file)
{
    OrientedGraph* g = new OrientedGraph(*(new AdjacencyMatrixOriented(1)));
    g->ReadFromFile(file);
    return g;
}
UnorientedGraphValuedEdge<int>* GraphManager::ReadFromFileGraphIntValuedEdge(std::ifstream& file)
{
    UnorientedGraphValuedEdge<int>* g = new UnorientedGraphValuedEdge<int>(1, *(new AdjacencyMatrixUnoriented()));
    g->readFromFile(file);
    return g;
}
