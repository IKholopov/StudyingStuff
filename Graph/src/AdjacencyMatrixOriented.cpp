#include"AdjacencyMatrixOriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

AdjacencyMatrixOriented::AdjacencyMatrixOriented()
{
    this->size = 0;
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(DEFAULT_NODES_AMOUNT);
    InitializeNewGraph(DEFAULT_NODES_AMOUNT);
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(unsigned int size, const std::vector<Edge *> &edges)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
    for(auto edge: edges)
    {
        assert(adjacencyMatrix->at(edge->From).at(edge->To) == NULL);
        adjacencyMatrix->at(edge->From).at(edge->To) = edge;
    }
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(unsigned int size)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(const AdjacencyMatrixOriented &graph)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*> edges = graph.GetAllEdges();
    for(auto edge: edges)
        adjacencyMatrix->at(edge->From).at(edge->To) = edge->Clone();
}
AdjacencyMatrixOriented &AdjacencyMatrixOriented::operator=(const AdjacencyMatrixOriented &graph)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*> edges = graph.GetAllEdges();
    for(auto edge: edges)
        adjacencyMatrix->at(edge->From).at(edge->To) = edge->Clone();
}
AdjacencyMatrixOriented *AdjacencyMatrixOriented::Clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v: *(this->adjacencyMatrix))
        for(auto u: v)
            if(u != NULL)
                newEdges.push_back(u->Clone());
    return new AdjacencyMatrixOriented(this->size, newEdges);
}
AdjacencyMatrixOriented::~AdjacencyMatrixOriented()
{
    this->DeleteAllEdges();
    delete adjacencyMatrix;
}
unsigned int AdjacencyMatrixOriented::Size() const
{
    return size;
}
unsigned int AdjacencyMatrixOriented::NumberOfEdges() const
{
    unsigned long counter = 0;
    for(auto v: *(this->adjacencyMatrix))
        for(auto u: v)
            if(u != NULL)
               ++counter;
    return counter;
}
std::vector<unsigned int> AdjacencyMatrixOriented::GetChilds(unsigned int vertex) const
{
    std::vector<unsigned int> childs;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != NULL)
            childs.push_back(adjacencyMatrix->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned int> AdjacencyMatrixOriented::GetParents(unsigned int vertex) const
{
    std::vector<unsigned int> parents;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(i).at(vertex) != NULL)
            parents.push_back(adjacencyMatrix->at(i).at(vertex)->From);
    return parents;
}
std::vector<Edge*> AdjacencyMatrixOriented::GetAllEdges() const
{
    std::vector<Edge*> edges;
    for(auto v: *(this->adjacencyMatrix))
        for(auto u: v)
            if(u != NULL)
               edges.push_back(u);
    return edges;
}
std::vector<Edge*> AdjacencyMatrixOriented::GetAllEdgesSorted()
{
    std::vector<Edge*> edges;
    for(auto v: *(this->adjacencyMatrix))
        for(auto u: v)
            if(u != NULL)
               edges.push_back(u);
    std::sort(edges.begin(), edges.end(), [](Edge* a, Edge* b) {
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
    for(int i = 0; i < size; ++i)
        adjacencyMatrix->at(i).resize(size);
    for(int i = 0; i < oldSize; ++i)
        for(int j = oldSize; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = NULL;
    for(int i = oldSize; i < size; ++i)
        for(int j = 0; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = NULL;
}
bool AdjacencyMatrixOriented::AddEdge(int from, int to)
{
    return AddEdge(new Edge(from, to));
}
bool AdjacencyMatrixOriented::CheckEdge(int from, int to)
{
    if(from == to)
        return true;
    return adjacencyMatrix->at(from).at(to) != NULL;
}
Edge* AdjacencyMatrixOriented::GetEdge(int from, int to)
{
    return adjacencyMatrix->at(from).at(to);
}
Edge* AdjacencyMatrixOriented::RemoveEdge(int from, int to)
{
    Edge* e = this->adjacencyMatrix->at(from).at(to);
    this->adjacencyMatrix->at(from).at(to) = NULL;
    return e;
}
void AdjacencyMatrixOriented::DeleteAllEdges()
{
    for(auto v: *(this->adjacencyMatrix))
        for(auto u: v)
            if(u != NULL)
               delete u;
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
void AdjacencyMatrixOriented::InitializeNewGraph(unsigned int size)
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
