#include"AdjacencyMatrixUnoriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented()
{
    this->size = 0;
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(DEFAULT_NODES_AMOUNT);
    InitializeNewGraph(DEFAULT_NODES_AMOUNT);
}
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(unsigned long long size, const std::vector<Edge *> &edges)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
    for(auto edge: edges)
    {
        assert(adjacencyMatrix->at(edge->From).at(edge->To) == NULL);
        adjacencyMatrix->at(edge->From).at(edge->To) = edge;
        adjacencyMatrix->at(edge->To).at(edge->From) = edge;
    }
}
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(unsigned long long size)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
}
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(const AdjacencyMatrixUnoriented &graph)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*>* edges = graph.GetAllEdges();
    for(auto edge: *edges)
        adjacencyMatrix->at(edge->From).at(edge->To) = edge->Clone();
    delete edges;
}
AdjacencyMatrixUnoriented &AdjacencyMatrixUnoriented::operator=(const AdjacencyMatrixUnoriented &graph)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*>* edges = graph.GetAllEdges();
    for(auto edge: *edges)
        adjacencyMatrix->at(edge->From).at(edge->To) = edge->Clone();
    delete edges;
}
AdjacencyMatrixUnoriented *AdjacencyMatrixUnoriented::Clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v: *(this->adjacencyMatrix))
        for(auto u: v)
            if(u != NULL)
                newEdges.push_back(u->Clone());
    return new AdjacencyMatrixUnoriented(this->size, newEdges);
}
AdjacencyMatrixUnoriented::~AdjacencyMatrixUnoriented()
{
    this->DeleteAllEdges();
    delete adjacencyMatrix;
}
unsigned long long AdjacencyMatrixUnoriented::Size() const
{
    return size;
}
unsigned long long AdjacencyMatrixUnoriented::NumberOfEdges() const
{
    unsigned long counter = 0;
    for(long long i = 0; i < size; ++i)
        for(long long j = i + 1; j < size; ++j)
            if(this->adjacencyMatrix->at(i).at(j) != NULL)
               ++counter;
    return counter;
}
std::vector<unsigned long long> *AdjacencyMatrixUnoriented::GetChilds(unsigned long long vertex) const
{
    std::vector<unsigned long long>* childs = new std::vector<unsigned long long>();
    for(long long i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != NULL)
            childs->push_back(adjacencyMatrix->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned long long> *AdjacencyMatrixUnoriented::GetParents(unsigned long long vertex) const
{
    std::vector<unsigned long long>* parents = new std::vector<unsigned long long>();
    for(long long i = 0; i < size; ++i)
        if(adjacencyMatrix->at(i).at(vertex) != NULL)
            parents->push_back(adjacencyMatrix->at(i).at(vertex)->From);
    return parents;
}
std::vector<Edge *> *AdjacencyMatrixUnoriented::GetAllEdges() const
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(long long i = 0; i < size; ++i)
        for(long long j = i + 1; j < size; ++j)
            if(this->adjacencyMatrix->at(i).at(j) != NULL)
               edges->push_back(this->adjacencyMatrix->at(i).at(j));
    return edges;
}
std::vector<Edge *> *AdjacencyMatrixUnoriented::GetAllEdgesSorted()
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(long long i = 0; i < size; ++i)
        for(long long j = i + 1; j < size; ++j)
            if(this->adjacencyMatrix->at(i).at(j) != NULL)
               edges->push_back(this->adjacencyMatrix->at(i).at(j));
    std::sort(edges->begin(), edges->end(), [](Edge* a, Edge* b) {
        if(a->From == b->From)
            return a->To < b->To;
        return a->From < b->From;
    });
    return edges;
}
void AdjacencyMatrixUnoriented::AddNodes(size_t amount)
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
bool AdjacencyMatrixUnoriented::AddEdge(long long from, long long to)
{
    return AddEdge(new Edge(from, to));
}
bool AdjacencyMatrixUnoriented::CheckEdge(long long from, long long to)
{
    if(from == to)
        return true;
    return adjacencyMatrix->at(from).at(to) != NULL;
}
Edge* AdjacencyMatrixUnoriented::GetEdge(long long from, long long to)
{
    return adjacencyMatrix->at(from).at(to);
}
Edge* AdjacencyMatrixUnoriented::RemoveEdge(long long from, long long to)
{
    Edge* e = this->adjacencyMatrix->at(from).at(to);
    this->adjacencyMatrix->at(from).at(to) = NULL;
    this->adjacencyMatrix->at(to).at(from) = NULL;
    return e;
}
void AdjacencyMatrixUnoriented::DeleteEdge(unsigned long long from, unsigned long long to)
{
    if(this->adjacencyMatrix->at(from).at(to) != NULL)
    {
        delete this->adjacencyMatrix->at(from).at(to);
        this->adjacencyMatrix->at(from).at(to) = NULL;
    }
}
void AdjacencyMatrixUnoriented::DeleteNodeEdges(unsigned long long v)
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
void AdjacencyMatrixUnoriented::DeleteAllEdges()
{
    for(long long i = 0; i < size; ++i)
        for(long long j = i + 1; j < size; ++j)
            if(this->adjacencyMatrix->at(i).at(j) != NULL)
               delete this->adjacencyMatrix->at(i).at(j);
    adjacencyMatrix->clear();
}
bool AdjacencyMatrixUnoriented::AddEdge(Edge *edge)
{
    bool exists = adjacencyMatrix->at(edge->From).at(edge->To) != NULL;
    if(exists)
        return false;
    adjacencyMatrix->at(edge->From).at(edge->To) = edge;
    adjacencyMatrix->at(edge->To).at(edge->From) = edge;
    return true;
}
void AdjacencyMatrixUnoriented::InitializeNewGraph(unsigned long long size)
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
