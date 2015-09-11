#include "Graph.h"

#include <stdlib.h>
#include "GraphFileFormat.h"

Graph::Graph(unsigned int size, const std::vector<Edge*> &edges)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
    this->edges = edges;
}
Graph::Graph(unsigned int size)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
}
Graph::~Graph()
{
    this->DeleteAllEdges();
    delete adjacencyMatrix;
}
unsigned int Graph::Size() const
{
    return size;
}
std::vector<unsigned int> Graph::GetChilds(unsigned int vertex) const
{
    std::vector<unsigned int> childs;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != NULL)
            childs.push_back(adjacencyMatrix->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned int> Graph::GetParents(unsigned int vertex) const
{
    std::vector<unsigned int> parents;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(i).at(vertex) != NULL)
            parents.push_back(adjacencyMatrix->at(i).at(vertex)->From);
    return parents;
}
void Graph::ReadFromFile(std::ifstream& file)
{
    unsigned int size, edgeSz;
    file >> size;
    this->InitializeNewGraph(size);
    file >> edgeSz;
    for(int i = 0; i < edgeSz; ++i)
    {
        unsigned int from, to;
        file >> from;
        file >> to;
        this->AddEdge(from, to);
    }
}
void Graph::WriteToFile(std::ofstream &file)
{
    file << this->size << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << std::endl;
}
void Graph::WriteToFile(std::string filename)
{
    std::ofstream file(filename.c_str());
    this->WriteToFile(file);
    file.close();
}
void Graph::RandomizeGraph(double probability)
{
    this->InitializeNewGraph(this->size);
    for(int i = 0; i < this->Size(); ++i)
        for(int j = 0; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddEdge(i, j);
            }
        }
}
/*void Graph::RandomizeUnorientedGraph(double probability)
{
    this->InitializeNewGraph(this->size);
    for(int i = 0; i < this->Size() - 1; ++i)
        for(int j = i; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddUnorientedEdge(i, j);
            }
        }
}*/
void Graph::AddNodes(size_t amount)
{
    size_t oldSize = this->size;
    this->size += amount;
    adjacencyMatrix->resize(size);
    for(int i = 0; i < size; ++i)
        adjacencyMatrix->at(i).resize(size);
    for(int i = 0; i < oldSize; ++i)
        for(int j = oldSize; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = NULL;
    for(int i = oldSize; i < size; ++i)
        for(int j = 0; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = NULL;
}
/*bool Graph::AddUnorientedEdge(int from, int to)
{
    return AddUnorientedEdge(new Edge(from, to));
}*/
bool Graph::AddEdge(int from, int to)
{
    return AddEdge(new Edge(from, to));
}
bool Graph::CheckEdge(int from, int to)
{
    if(from == to)
        return true;
    return adjacencyMatrix->at(from).at(to) != NULL;
}
Edge *Graph::GetEdge(int from, int to)
{
    return adjacencyMatrix->at(from).at(to);
}
void Graph::DeleteAllEdges()
{
    for(int i = 0; i < edges.size(); ++i)
    {
            delete edges[i];
    }
    edges.clear();
    adjacencyMatrix->clear();
}
unsigned int Graph::NumberOfEdges() const
{
    return edges.size();
}
void Graph::InitializeNewGraph(unsigned int size)
{
    this->DeleteAllEdges();
    this->size = size;
    adjacencyMatrix->resize(size);
    for(int i = 0; i < size; ++i)
    {
        adjacencyMatrix->at(i).resize(size);
        for(int j = 0; j < size; ++j)
            adjacencyMatrix->at(i).at(j)= NULL;
    }
}
bool Graph::AddEdge(Edge* edge)
{
    bool exists = adjacencyMatrix->at(edge->From).at(edge->To) != NULL;
    if(exists)
        return false;
    edges.push_back(edge);
    adjacencyMatrix->at(edge->From).at(edge->To) = edge;
    return true;
}
std::vector<Edge *> Graph::GetAllEdges()
{
    return edges;
}

