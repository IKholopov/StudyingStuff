#include "AdjacencyMatrixOriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

AdjacencyMatrixOriented::AdjacencyMatrixOriented()
{
    this->size = 0;
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(DEFAULT_NODES_AMOUNT);
    InitializeNewGraph(DEFAULT_NODES_AMOUNT);
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(unsigned long long size, std::vector<Edge *> &edges)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
    for(auto edge = edges.begin(); edge != edges.end(); ++edge)
    {
        assert(adjacencyMatrix->at((*edge)->From).at((*edge)->To) == NULL);
        adjacencyMatrix->at((*edge)->From).at((*edge)->To) = (*edge);
    }
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(unsigned long long size)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(const AdjacencyMatrixOriented &graph)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*>* edges = graph.GetAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
        adjacencyMatrix->at((*edge)->From).at((*edge)->To) = (*edge)->Clone();
    delete edges;
}
AdjacencyMatrixOriented &AdjacencyMatrixOriented::operator=(const AdjacencyMatrixOriented &graph)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*>* edges = graph.GetAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
        adjacencyMatrix->at((*edge)->From).at((*edge)->To) = (*edge)->Clone();
    delete edges;
}
AdjacencyMatrixOriented *AdjacencyMatrixOriented::Clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v = this->adjacencyMatrix->begin(); v != this->adjacencyMatrix->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
                newEdges.push_back((*u)->Clone());
    return new AdjacencyMatrixOriented(this->size, newEdges);
}
AdjacencyMatrixOriented::~AdjacencyMatrixOriented()
{
    this->DeleteAllEdges();
    delete adjacencyMatrix;
}
unsigned long long AdjacencyMatrixOriented::Size() const
{
    return size;
}
unsigned long long AdjacencyMatrixOriented::NumberOfEdges() const
{
    unsigned long counter = 0;
    for(auto v = this->adjacencyMatrix->begin(); v != this->adjacencyMatrix->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
               ++counter;
    return counter;
}
std::vector<unsigned long long> *AdjacencyMatrixOriented::GetChilds(unsigned long long vertex) const
{
    std::vector<unsigned long long>* childs = new std::vector<unsigned long long>();
    for(long long i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != NULL)
            childs->push_back(adjacencyMatrix->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned long long> *AdjacencyMatrixOriented::GetParents(unsigned long long vertex) const
{
    std::vector<unsigned long long>* parents = new std::vector<unsigned long long>();
    for(long long i = 0; i < size; ++i)
        if(adjacencyMatrix->at(i).at(vertex) != NULL)
            parents->push_back(adjacencyMatrix->at(i).at(vertex)->From);
    return parents;
}
std::vector<Edge *> *AdjacencyMatrixOriented::GetAllEdges() const
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto v = this->adjacencyMatrix->begin(); v != this->adjacencyMatrix->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
               edges->push_back(*u);
    return edges;
}
std::vector<Edge *> *AdjacencyMatrixOriented::GetAllEdgesSorted()
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto v = this->adjacencyMatrix->begin(); v != this->adjacencyMatrix->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
               edges->push_back(*u);
    std::sort(edges->begin(), edges->end(), [](Edge* a, Edge* b) {
        if(a->From == b->From)
            return a->To < b->To;
        return a->From < b->From;
    });
    return edges;
}
void AdjacencyMatrixOriented::AddNodes(size_t amount)
{
    size_t oldSize = this->size;
    this->size += amount;
    adjacencyMatrix->resize(size);
    for(long long i = 0; i < size; ++i)
        adjacencyMatrix->at(i).resize(size);
    for(long long i = 0; i < oldSize; ++i)
        for(long long j = oldSize; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = NULL;
    for(long long i = oldSize; i < size; ++i)
        for(long long j = 0; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = NULL;
}
bool AdjacencyMatrixOriented::AddEdge(long long from, long long to)
{
    return AddEdge(new Edge(from, to));
}
bool AdjacencyMatrixOriented::CheckEdge(long long from, long long to)
{
    if(from == to)
        return true;
    return adjacencyMatrix->at(from).at(to) != NULL;
}
Edge* AdjacencyMatrixOriented::GetEdge(long long from, long long to)
{
    return adjacencyMatrix->at(from).at(to);
}
Edge* AdjacencyMatrixOriented::RemoveEdge(long long from, long long to)
{
    Edge* e = this->adjacencyMatrix->at(from).at(to);
    this->adjacencyMatrix->at(from).at(to) = NULL;
    return e;
}
void AdjacencyMatrixOriented::DeleteEdge(unsigned long long from, unsigned long long to)
{
    if(this->adjacencyMatrix->at(from).at(to) != NULL)
    {
        delete this->adjacencyMatrix->at(from).at(to);
        this->adjacencyMatrix->at(from).at(to) = NULL;
    }
}
void AdjacencyMatrixOriented::DeleteNodeEdges(unsigned long long v)
{
    for(auto a = this->adjacencyMatrix->begin(); a != this->adjacencyMatrix->end(); ++a)
    {
        if(a->at(v) != NULL)
        {
            delete a->at(v);
            a->at(v) = NULL;
        }
    }
    for(auto a = this->adjacencyMatrix->at(v).begin(); a != this->adjacencyMatrix->at(v).end(); ++a)
    {
        if(*a != NULL)
        {
            delete *a;
            *a = NULL;
        }
    }
}
void AdjacencyMatrixOriented::DeleteAllEdges()
{
    for(auto v = this->adjacencyMatrix->begin(); v != this->adjacencyMatrix->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
               delete *u;
    adjacencyMatrix->clear();
}
bool AdjacencyMatrixOriented::AddEdge(Edge *edge)
{
    bool exists = adjacencyMatrix->at(edge->From).at(edge->To) != NULL;
    if(exists)
        return false;
    adjacencyMatrix->at(edge->From).at(edge->To) = edge;
    return true;
}
void AdjacencyMatrixOriented::InitializeNewGraph(unsigned long long size)
{
    this->DeleteAllEdges();
    this->size = size;
    adjacencyMatrix->resize(size);
    for(long long i = 0; i < size; ++i)
    {
        adjacencyMatrix->at(i).resize(size);
        for(long long j = 0; j < size; ++j)
            adjacencyMatrix->at(i).at(j)= NULL;
    }
}
