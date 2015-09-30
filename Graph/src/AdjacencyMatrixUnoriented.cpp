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
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(unsigned int size, const std::vector<Edge *> &edges)
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
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(unsigned int size)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(size);
    InitializeNewGraph(size);
}
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(const AdjacencyMatrixUnoriented &graph)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*> edges = graph.GetAllEdges();
    for(auto edge: edges)
        adjacencyMatrix->at(edge->From).at(edge->To) = edge->Clone();
}
AdjacencyMatrixUnoriented &AdjacencyMatrixUnoriented::operator=(const AdjacencyMatrixUnoriented &graph)
{
    adjacencyMatrix = new std::vector< std::vector<Edge*> >(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*> edges = graph.GetAllEdges();
    for(auto edge: edges)
        adjacencyMatrix->at(edge->From).at(edge->To) = edge->Clone();
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
unsigned int AdjacencyMatrixUnoriented::Size() const
{
    return size;
}
unsigned int AdjacencyMatrixUnoriented::NumberOfEdges() const
{
    unsigned long counter = 0;
    for(int i = 0; i < size; ++i)
        for(int j = i + 1; j < size; ++j)
            if(this->adjacencyMatrix->at(i).at(j) != NULL)
               ++counter;
    return counter;
}
std::vector<unsigned int> AdjacencyMatrixUnoriented::GetChilds(unsigned int vertex) const
{
    std::vector<unsigned int> childs;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(vertex).at(i) != NULL)
            childs.push_back(adjacencyMatrix->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned int> AdjacencyMatrixUnoriented::GetParents(unsigned int vertex) const
{
    std::vector<unsigned int> parents;
    for(int i = 0; i < size; ++i)
        if(adjacencyMatrix->at(i).at(vertex) != NULL)
            parents.push_back(adjacencyMatrix->at(i).at(vertex)->From);
    return parents;
}
std::vector<Edge*> AdjacencyMatrixUnoriented::GetAllEdges() const
{
    std::vector<Edge*> edges;
    for(int i = 0; i < size; ++i)
        for(int j = i + 1; j < size; ++j)
            if(this->adjacencyMatrix->at(i).at(j) != NULL)
               edges.push_back(this->adjacencyMatrix->at(i).at(j));
    return edges;
}
std::vector<Edge*> AdjacencyMatrixUnoriented::GetAllEdgesSorted()
{
    std::vector<Edge*> edges;
    for(int i = 0; i < size; ++i)
        for(int j = i + 1; j < size; ++j)
            if(this->adjacencyMatrix->at(i).at(j) != NULL)
               edges.push_back(this->adjacencyMatrix->at(i).at(j));
    std::sort(edges.begin(), edges.end(), [](Edge* a, Edge* b) {
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
    for(int i = 0; i < size; ++i)
        adjacencyMatrix->at(i).resize(size);
    for(int i = 0; i < oldSize; ++i)
        for(int j = oldSize; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = NULL;
    for(int i = oldSize; i < size; ++i)
        for(int j = 0; j < size; ++j)
            adjacencyMatrix->at(i).at(j) = NULL;
}
bool AdjacencyMatrixUnoriented::AddEdge(int from, int to)
{
    return AddEdge(new Edge(from, to));
}
bool AdjacencyMatrixUnoriented::CheckEdge(int from, int to)
{
    if(from == to)
        return true;
    return adjacencyMatrix->at(from).at(to) != NULL;
}
Edge* AdjacencyMatrixUnoriented::GetEdge(int from, int to)
{
    return adjacencyMatrix->at(from).at(to);
}
Edge* AdjacencyMatrixUnoriented::RemoveEdge(int from, int to)
{
    Edge* e = this->adjacencyMatrix->at(from).at(to);
    this->adjacencyMatrix->at(from).at(to) = NULL;
    this->adjacencyMatrix->at(to).at(from) = NULL;
    return e;
}
void AdjacencyMatrixUnoriented::DeleteEdge(unsigned int from, unsigned int to)
{
    if(this->adjacencyMatrix->at(from).at(to) != NULL)
        delete this->adjacencyMatrix->at(from).at(to);
}
void AdjacencyMatrixUnoriented::DeleteNodeEdges(unsigned int v)
{
    for(auto a: *(this->adjacencyMatrix))
    {
        if(a.at(v) != NULL)
            delete a.at(v);
    }
    for(auto a: this->adjacencyMatrix->at(v))
    {
        if(a != NULL)
             delete a;
    }
}
void AdjacencyMatrixUnoriented::DeleteAllEdges()
{
    for(int i = 0; i < size; ++i)
        for(int j = i + 1; j < size; ++j)
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
void AdjacencyMatrixUnoriented::InitializeNewGraph(unsigned int size)
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
