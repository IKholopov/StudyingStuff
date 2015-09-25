#include "UnorientedGraph.h"
#include <algorithm>

UnorientedGraph::UnorientedGraph(unsigned int size)
{
#ifndef DEBUG
    srand(time(NULL));
#endif
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
    this->edges = edges;
}
UnorientedGraph::UnorientedGraph(const UnorientedGraph &graph)
{
#ifndef DEBUG
    srand(time(NULL));
#endif
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    edges = graph.GetAllEdges();
    std::vector<Edge*> edges = graph.GetAllEdges();
    for(auto edge = edges.begin(); edge != edges.end(); ++edge)
        AddEdge((*edge)->Clone());
}
UnorientedGraph &UnorientedGraph::operator=(const UnorientedGraph &graph)
{
#ifndef DEBUG
    srand(time(NULL));
#endif
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    edges = graph.GetAllEdges();
    std::vector<Edge*> edges = graph.GetAllEdges();
    for(auto edge = edges.begin(); edge != edges.end(); ++edge)
        AddEdge((*edge)->Clone());
}
UnorientedGraph::~UnorientedGraph()
{
    this->DeleteAllEdges();
    delete adjacencyMatrix;
}

unsigned int UnorientedGraph::Size() const
{
    return this->size;
}
unsigned int UnorientedGraph::NumberOfEdges() const
{
    return edges.size();
}
std::vector<unsigned int> UnorientedGraph::GetChilds(unsigned int vertex) const
{
    std::vector<unsigned int> childs;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != NULL)
            childs.push_back(adjacencyMatrix->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned int> UnorientedGraph::GetParents(unsigned int vertex) const
{
    std::vector<unsigned int> parents;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(i).at(vertex) != NULL)
            parents.push_back(adjacencyMatrix->at(i).at(vertex)->From);
    return parents;
}
std::vector<Edge *> UnorientedGraph::GetAllEdges() const
{
    return edges;
}
std::vector<Edge *> UnorientedGraph::GetAllEdgesSorted()
{
    std::sort(edges.begin(), edges.end(), [](Edge* a, Edge* b) {
            if(a->From == b->From)
                return a->To < b->To;
            return a->From < b->From;
    });
    return edges;
}
void UnorientedGraph::ReadFromFile(std::ifstream &file)
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
void UnorientedGraph::WriteToFile(std::string filename)
{
    std::ofstream file(filename.c_str());
    this->WriteToFile(file);
    file.close();
}
void UnorientedGraph::WriteToFile(std::ofstream &file)
{
    file << this->size << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << std::endl;
}
void UnorientedGraph::RandomizeGraph(double probability)
{
    this->InitializeNewGraph(this->size);
    for(int i = 0; i < this->Size() - 1; ++i)
        for(int j = i; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddEdge(i, j);
            }
        }
}
void UnorientedGraph::AddNodes(size_t amount)
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
bool UnorientedGraph::AddEdge(int from, int to)
{
    return AddEdge(new Edge(from, to));
}
bool UnorientedGraph::CheckEdge(int from, int to)
{
    if(from == to)
        return true;
    return adjacencyMatrix->at(from).at(to) != NULL;
}
void UnorientedGraph::NormalizeEdges()
{
    for(int i = 0; i < edges.size(); ++i)
        if(edges[i]->From > edges[i]->To)
        {
            unsigned int temp = edges[i]->From;
            edges[i]->From = edges[i]->To;
            edges[i]->To = temp;
        }
}
Edge *UnorientedGraph::GetEdge(int from, int to)
{
    return adjacencyMatrix->at(from).at(to);
}
void UnorientedGraph::DeleteAllEdges()
{
    for(int i = 0; i < edges.size(); ++i)
    {
            delete edges[i];
    }
    edges.clear();
    adjacencyMatrix->clear();
}

bool UnorientedGraph::AddEdge(Edge* edge)
{
    bool exists = adjacencyMatrix->at(edge->From).at(edge->To) != NULL;
    if(exists)
        return false;
    edges.push_back(edge);
    adjacencyMatrix->at(edge->From).at(edge->To) = edge;
    adjacencyMatrix->at(edge->To).at(edge->From) = edge;
    return true;
}
void UnorientedGraph::InitializeNewGraph(unsigned int size)
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
