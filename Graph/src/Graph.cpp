#include "Graph.h"

#include <stdlib.h>
#include "GraphFileFormat.h"

Graph::Graph(unsigned int size, const std::vector<Edge *> &edges, bool oriented)
{
    this->oriented = oriented;
    adjacencyMatrix = new std::vector< std::vector<int> >(size);
    InitializeNewGraph(size);
    this->edges = edges;
    for(int i = 0; i < edges.size(); ++i)
    {
        adjacencyMatrix->at(edges[i]->From).at(edges[i]->To) = 1;
    }
}
Graph::Graph(unsigned int size, bool oriented)
{
    this->oriented = oriented;
    adjacencyMatrix = new std::vector< std::vector<int> >(size);
    InitializeNewGraph(size);
}
Graph::~Graph()
{
    this->DeleteAllEdges();
    delete adjacencyMatrix;
}
unsigned int Graph::Size()
{
    return size;
}
std::vector<unsigned int> Graph::GetChilds(unsigned int vertex)
{
    std::vector<unsigned int> childs;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != -1)
            childs.push_back(edges[adjacencyMatrix->at(vertex).at(i)]->To);
    return childs;
}
std::vector<unsigned int> Graph::GetParents(unsigned int vertex)
{
    std::vector<unsigned int> parents;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(i).at(vertex) != -1)
            parents.push_back(edges[adjacencyMatrix->at(i).at(vertex)]->From);
    return parents;
}
void Graph::ReadFromFile(std::ifstream& file)
{
    unsigned int size, edgeSz;
    file >> size;
    this->InitializeNewGraph(size);
    std::string s;
    std::getline(file, s);
    std::getline(file, s);
    if(s != "<EDGES>")
        throw std::exception();
    file >> edgeSz;
    for(int i = 0; i < edgeSz; ++i)
    {
        unsigned int from, to;
        file >> from;
        file >> to;
        this->AddEdge(from, to);
    }
    std::getline(file, s);
    std::getline(file, s);
    if(s != "</EDGES>")
        throw std::exception();
}
void Graph::WriteToFile(std::ofstream &file)
{
    file << GR_TYPE_GRAPH_REGULAR  << std::endl;
    file << this->size << std::endl;
    file << "<EDGES>" << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << std::endl;
    file << "</EDGES>" << std::endl;
}
void Graph::WriteToFile(std::string filename)
{
    std::ofstream file(filename.c_str());
    this->WriteToFile(file);
    file.close();
}
void Graph::RandomizeGraph(double probability)
{
    if(!oriented)
        throw std::exception();
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
void Graph::RandomizeUnorientedGraph(double probability)
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
}
void Graph::AddNodes(size_t amount)
{
    size_t oldSize = this->size;
    this->size += amount;
    adjacencyMatrix->resize(size);
    for(int i = 0; i < size; ++i)
        adjacencyMatrix->at(i).resize(size);
    for(int i = 0; i < oldSize; ++i)
        for(int j = oldSize; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = -1;
    for(int i = oldSize; i < size; ++i)
        for(int j = 0; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = -1;
}
bool Graph::AddUnorientedEdge(int from, int to)
{
    return AddUnorientedEdge(new Edge(from, to));
}
bool Graph::AddEdge(int from, int to)
{
    if(!oriented)
        throw std::exception();
    return AddEdge(new Edge(from, to));
}
bool Graph::CheckEdge(int from, int to)
{
    if(from == to)
        return true;
    return adjacencyMatrix->at(from).at(to) != -1;
}
Edge *Graph::GetEdge(int from, int to)
{
    if(adjacencyMatrix->at(from).at(to) == -1)
        return NULL;
    return edges[adjacencyMatrix->at(from).at(to)];
}
void Graph::DeleteAllEdges()
{
    for(int i = 0; i < edges.size(); ++i)
    {
        delete edges[i];
    }
    edges.clear();
}
size_t Graph::NumberOfEdges()
{
    return edges.size();
}
bool Graph::IsOriented()
{
    return oriented;
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
            adjacencyMatrix->at(i).at(j)= -1;
    }
}
bool Graph::AddEdge(Edge* edge)
{
    if(!oriented)
        throw std::exception();
    bool exists = adjacencyMatrix->at(edge->From).at(edge->To) != -1;
    if(exists)
        return false;
    edges.push_back(edge);
    adjacencyMatrix->at(edge->From).at(edge->To) = edges.size() - 1;
    return true;
}
bool Graph::AddUnorientedEdge(Edge* edge)
{
    bool straight = adjacencyMatrix->at(edge->From).at(edge->To) != -1;
    bool reverse = adjacencyMatrix->at(edge->To).at(edge->From) != -1;
    if(!straight)
    {
        edges.push_back(edge);
        adjacencyMatrix->at(edge->From).at(edge->To) = edges.size() - 1;
    }
    if(!reverse)
    {
        edges.push_back(edge->GetReversed());
        adjacencyMatrix->at(edge->To).at(edge->From) = edges.size() - 1;
    }
    if(straight && reverse)
        return false;
    return true;
}
unsigned int Graph::EdgesCount()
{
    return edges.size();
}
std::vector<Edge *> Graph::GetAllEdges()
{
    return edges;
}
std::vector<Edge *> Graph::GetSortedUnorientedEdges()
{
    if(oriented)
        throw std::exception();
    for(int i = 0; i < size; ++i)
        for(int j = i + 1; j < size; ++j)
            if(adjacencyMatrix)
}
