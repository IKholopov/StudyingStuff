#include "Graph.h"

Graph::Graph(unsigned int size, std::vector<Edge> edges)
{
    this->size = size;
    this->edges = edges;
    adjacencyMatrix = new std::vector< std::vector<int> >(size);
    for(int i = 0; i < size; ++i)
    {
        adjacencyMatrix[i].resize(size);
        for(int j = 0; j < size; ++j)
            adjacencyMatrix->at(i).at(j)= -1;
    }
}
Graph::Graph(unsigned int size)
{
    this->size = size;
}
Graph::~Graph()
{

}
unsigned int Graph::Size()
{
    return size;
}
std::vector<unsigned int> Graph::GetChilds(unsigned int vertex)
{
    std::vector<unsigned int> childs;
    /*for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != -1)
            childs.push_back(edges[adjacencyMatrix->at(vertex).at(i)].To);*/
    for(int i = 0; i < edges.size(); ++i)
        if(edges[i].From == vertex)
            childs.push_back(edges[i].To);
    return childs;
}
std::vector<unsigned int> Graph::GetParents(unsigned int vertex)
{
    std::vector<unsigned int> parents;
    for(int i = 0; i < edges.size(); ++i)
        if(edges[i].To == vertex)
            parents.push_back(edges[i].From);
    return parents;
}
bool Graph::AddUnorientedEdge(int from, int to)
{
    bool straight = false;
    bool reverse = false;
    for(int i = 0; i < edges.size(); ++i)
    {
        if(edges[i].From == from && edges[i].To == to)
        {
            straight = true;
            if(reverse)
                break;
        }
        if(edges[i].To == from && edges[i].From == to)
        {
            reverse = true;
            if(straight)
                break;
        }
    }
    if(!straight)
        edges.push_back(Edge(from, to));
    if(!reverse)
        edges.push_back(Edge(to, from));
    if(straight && reverse)
        return false;
    return true;
}
bool Graph::AddEdge(const Edge& edge)
{
    bool exists = false;
    for(int i = 0; i < edges.size(); ++i)
    {
        if(edges[i].From == edge.From && edges[i].To == edge.To)
        {
            exists = true;
            if(exists)
                break;
        }
    }
    if(exists)
        return false;
    edges.push_back(edge);
    return true;
}
bool Graph::AddEdge(int from, int to)
{
    return AddEdge(Edge(from, to));
}
bool Graph::CheckEdge(int from, int to)
{
    if(from == to)
        return true;
    for(int i = 0; i < edges.size(); ++i)
        if(edges[i].To == to && edges[i].From == from)
            return true;
    return false;
}
void Graph::DeleteAllEdges()
{
    edges.clear();
}
size_t Graph::NumberOfEdges()
{
    return edges.size();
}
