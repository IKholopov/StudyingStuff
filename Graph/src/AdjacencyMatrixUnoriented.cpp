#include"AdjacencyMatrixUnoriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented()
{
    this->size_ = 0;
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(DEFAULT_NODES_AMOUNT);
    initializeNewGraph(DEFAULT_NODES_AMOUNT);
}
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(unsigned long long size, const std::vector<Edge *> &edges)
{
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(size);
    initializeNewGraph(size);
    for(auto edge: edges)
    {
        assert(adjacencyMatrix_->at(edge->From).at(edge->To) == NULL);
        adjacencyMatrix_->at(edge->From).at(edge->To) = edge;
        adjacencyMatrix_->at(edge->To).at(edge->From) = edge;
    }
}
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(unsigned long long size)
{
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(size);
    initializeNewGraph(size);
}
AdjacencyMatrixUnoriented::AdjacencyMatrixUnoriented(const AdjacencyMatrixUnoriented &graph)
{
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(graph.size_);
    initializeNewGraph(graph.size_);
    std::vector<Edge*>* edges = graph.getAllEdges();
    for(auto edge: *edges)
        adjacencyMatrix_->at(edge->From).at(edge->To) = edge->clone();
    delete edges;
}
AdjacencyMatrixUnoriented &AdjacencyMatrixUnoriented::operator=(const AdjacencyMatrixUnoriented &graph)
{
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(graph.size_);
    initializeNewGraph(graph.size_);
    std::vector<Edge*>* edges = graph.getAllEdges();
    for(auto edge: *edges)
        adjacencyMatrix_->at(edge->From).at(edge->To) = edge->clone();
    delete edges;
}
AdjacencyMatrixUnoriented *AdjacencyMatrixUnoriented::clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v: *(this->adjacencyMatrix_))
        for(auto u: v)
            if(u != NULL)
                newEdges.push_back(u->clone());
    return new AdjacencyMatrixUnoriented(this->size_, newEdges);
}
AdjacencyMatrixUnoriented::~AdjacencyMatrixUnoriented()
{
    this->deleteAllEdges();
    delete adjacencyMatrix_;
}
unsigned long long AdjacencyMatrixUnoriented::size() const
{
    return size_;
}
unsigned long long AdjacencyMatrixUnoriented::numberOfEdges() const
{
    unsigned long counter = 0;
    for(long long i = 0; i < size_; ++i)
        for(long long j = i + 1; j < size_; ++j)
            if(this->adjacencyMatrix_->at(i).at(j) != NULL)
               ++counter;
    return counter;
}
std::vector<unsigned long long> *AdjacencyMatrixUnoriented::getChilds(unsigned long long vertex) const
{
    std::vector<unsigned long long>* childs = new std::vector<unsigned long long>();
    for(long long i = 0; i < size_; ++i)
        if(adjacencyMatrix_->at(vertex).at(i) != NULL)
            childs->push_back(adjacencyMatrix_->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned long long> *AdjacencyMatrixUnoriented::getParents(unsigned long long vertex) const
{
    std::vector<unsigned long long>* parents = new std::vector<unsigned long long>();
    for(long long i = 0; i < size_; ++i)
        if(adjacencyMatrix_->at(i).at(vertex) != NULL)
            parents->push_back(adjacencyMatrix_->at(i).at(vertex)->From);
    return parents;
}
std::vector<Edge *> *AdjacencyMatrixUnoriented::getAllEdges() const
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(long long i = 0; i < size_; ++i)
        for(long long j = i + 1; j < size_; ++j)
            if(this->adjacencyMatrix_->at(i).at(j) != NULL)
               edges->push_back(this->adjacencyMatrix_->at(i).at(j));
    return edges;
}
std::vector<Edge *> *AdjacencyMatrixUnoriented::getAllEdgesSorted()
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(long long i = 0; i < size_; ++i)
        for(long long j = i + 1; j < size_; ++j)
            if(this->adjacencyMatrix_->at(i).at(j) != NULL)
               edges->push_back(this->adjacencyMatrix_->at(i).at(j));
    std::sort(edges->begin(), edges->end(), [](Edge* a, Edge* b) {
        if(a->From == b->From)
            return a->To < b->To;
        return a->From < b->From;
    });
    return edges;
}
void AdjacencyMatrixUnoriented::addNodes(size_t amount)
{
    size_t oldSize = this->size_;
    this->size_ += amount;
    adjacencyMatrix_->resize(size_);
    for(long long i = 0; i < size_; ++i)
        adjacencyMatrix_->at(i).resize(size_);
    for(long long i = 0; i < oldSize; ++i)
        for(long long j = oldSize; j < size_; ++j)
            adjacencyMatrix_->at(i).at(j) = NULL;
    for(long long i = oldSize; i < size_; ++i)
        for(long long j = 0; j < size_; ++j)
            adjacencyMatrix_->at(i).at(j) = NULL;
}
bool AdjacencyMatrixUnoriented::addEdge(long long from, long long to)
{
    return addEdge(new Edge(from, to));
}
bool AdjacencyMatrixUnoriented::checkEdge(long long from, long long to)
{
    if(from == to)
        return true;
    return adjacencyMatrix_->at(from).at(to) != NULL;
}
Edge* AdjacencyMatrixUnoriented::getEdge(long long from, long long to)
{
    return adjacencyMatrix_->at(from).at(to);
}
Edge* AdjacencyMatrixUnoriented::removeEdge(long long from, long long to)
{
    Edge* e = this->adjacencyMatrix_->at(from).at(to);
    this->adjacencyMatrix_->at(from).at(to) = NULL;
    this->adjacencyMatrix_->at(to).at(from) = NULL;
    return e;
}
void AdjacencyMatrixUnoriented::deleteEdge(unsigned long long from, unsigned long long to)
{
    if(this->adjacencyMatrix_->at(from).at(to) != NULL) {
        delete this->adjacencyMatrix_->at(from).at(to);
        this->adjacencyMatrix_->at(from).at(to) = NULL;
    }
}
void AdjacencyMatrixUnoriented::deleteNodeEdges(unsigned long long v)
{
    for(auto a = this->adjacencyMatrix_->begin(); a != this->adjacencyMatrix_->end(); ++a)
    {
        if(a->at(v) != NULL) {
            delete a->at(v);
            a->at(v) = NULL;
        }
    }
    for(auto a = this->adjacencyMatrix_->at(v).begin(); a != this->adjacencyMatrix_->at(v).end(); ++a)
    {
        if(*a != NULL) {
            delete *a;
            *a = NULL;
        }
    }
}
void AdjacencyMatrixUnoriented::deleteAllEdges()
{
    for(long long i = 0; i < size_; ++i)
        for(long long j = i + 1; j < size_; ++j)
            if(this->adjacencyMatrix_->at(i).at(j) != NULL)
               delete this->adjacencyMatrix_->at(i).at(j);
    adjacencyMatrix_->clear();
}
bool AdjacencyMatrixUnoriented::addEdge(Edge *edge)
{
    bool exists = adjacencyMatrix_->at(edge->From).at(edge->To) != NULL;
    if(exists)
        return false;
    adjacencyMatrix_->at(edge->From).at(edge->To) = edge;
    adjacencyMatrix_->at(edge->To).at(edge->From) = edge;
    return true;
}
void AdjacencyMatrixUnoriented::initializeNewGraph(unsigned long long size)
{
    this->deleteAllEdges();
    this->size_ = size;
    adjacencyMatrix_->resize(size);
    for(long long i = 0; i < size; ++i)
    {
        adjacencyMatrix_->at(i).resize(size);
        for(long long j = 0; j < size; ++j)
            adjacencyMatrix_->at(i).at(j)= NULL;
    }
}
