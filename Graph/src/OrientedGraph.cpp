#include "OrientedGraph.h"

#include <stdlib.h>
#include <algorithm>
#include "GraphFileFormat.h"

OrientedGraph::OrientedGraph(unsigned int size, const std::vector<Edge*> &edges)
{
    srand(time(NULL));
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
    this->edges = edges;
}
OrientedGraph::OrientedGraph(unsigned int size)
{
    srand(time(NULL));
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
}
OrientedGraph::OrientedGraph(const OrientedGraph &graph)
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
OrientedGraph &OrientedGraph::operator=(const OrientedGraph &graph)
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

OrientedGraph *OrientedGraph::Clone() const
{
    std::vector<Edge*> newEdges;
    for(auto e: this->edges)
        newEdges.push_back(e->Clone());
    return new OrientedGraph(this->size, newEdges);
}
OrientedGraph::~OrientedGraph()
{
    this->DeleteAllEdges();
    delete adjacencyMatrix;
}
unsigned int OrientedGraph::Size() const
{
    return size;
}
std::vector<unsigned int> OrientedGraph::GetChilds(unsigned int vertex) const
{
    std::vector<unsigned int> childs;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != NULL)
            childs.push_back(adjacencyMatrix->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned int> OrientedGraph::GetParents(unsigned int vertex) const
{
    std::vector<unsigned int> parents;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(i).at(vertex) != NULL)
            parents.push_back(adjacencyMatrix->at(i).at(vertex)->From);
    return parents;
}
void OrientedGraph::ReadFromFile(std::ifstream& file)
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
void OrientedGraph::WriteToFile(std::ofstream &file)
{
    file << this->size << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << std::endl;
}
void OrientedGraph::WriteToFile(std::string filename)
{
    std::ofstream file(filename.c_str());
    this->WriteToFile(file);
    file.close();
}
void OrientedGraph::RandomizeGraph(double probability)
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
void OrientedGraph::AddNodes(size_t amount)
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
/*bool OrientedGraph::AddUnorientedEdge(int from, int to)
{
    return AddUnorientedEdge(new Edge(from, to));
}*/
bool OrientedGraph::AddEdge(int from, int to)
{
    return AddEdge(new Edge(from, to));
}
bool OrientedGraph::CheckEdge(int from, int to)
{
    if(from == to)
        return true;
    return adjacencyMatrix->at(from).at(to) != NULL;
}
Edge *OrientedGraph::GetEdge(int from, int to)
{
    return adjacencyMatrix->at(from).at(to);
}
void OrientedGraph::DeleteAllEdges()
{
    for(int i = 0; i < edges.size(); ++i)
    {
            delete edges[i];
    }
    edges.clear();
    adjacencyMatrix->clear();
}
unsigned int OrientedGraph::NumberOfEdges() const
{
    return edges.size();
}
void OrientedGraph::InitializeNewGraph(unsigned int size)
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
bool OrientedGraph::AddEdge(Edge* edge)
{
    bool exists = adjacencyMatrix->at(edge->From).at(edge->To) != NULL;
    if(exists)
        return false;
    edges.push_back(edge);
    adjacencyMatrix->at(edge->From).at(edge->To) = edge;
    return true;
}
std::vector<Edge *> OrientedGraph::GetAllEdges() const
{
    return edges;
}
std::vector<Edge *> OrientedGraph::GetAllEdgesSorted()
{
    std::sort(edges.begin(), edges.end(), [](Edge* a, Edge* b) {
            if(a->From == b->From)
                return a->To < b->To;
            return a->From < b->From;
    });
    return edges;
}

