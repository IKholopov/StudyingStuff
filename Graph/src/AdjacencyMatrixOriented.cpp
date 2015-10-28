#include "AdjacencyMatrixOriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

AdjacencyMatrixOriented::AdjacencyMatrixOriented()
{
    this->size_ = 0;
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(DEFAULT_NODES_AMOUNT);
    initializeNewGraph(DEFAULT_NODES_AMOUNT);
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(unsigned long long size, std::vector<Edge *> &edges)
{
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(size);
    initializeNewGraph(size);
    for(auto edge = edges.begin(); edge != edges.end(); ++edge)
    {
        assert(adjacencyMatrix_->at((*edge)->From).at((*edge)->To) == NULL);
        adjacencyMatrix_->at((*edge)->From).at((*edge)->To) = (*edge);
    }
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(unsigned long long size)
{
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(size);
    initializeNewGraph(size);
}
AdjacencyMatrixOriented::AdjacencyMatrixOriented(const AdjacencyMatrixOriented &graph)
{
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(graph.size_);
    initializeNewGraph(graph.size_);
    std::vector<Edge*>* edges = graph.getAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
        adjacencyMatrix_->at((*edge)->From).at((*edge)->To) = (*edge)->clone();
    delete edges;
}
AdjacencyMatrixOriented &AdjacencyMatrixOriented::operator=(const AdjacencyMatrixOriented &graph)
{
    adjacencyMatrix_ = new std::vector< std::vector<Edge*> >(graph.size_);
    initializeNewGraph(graph.size_);
    std::vector<Edge*>* edges = graph.getAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
        adjacencyMatrix_->at((*edge)->From).at((*edge)->To) = (*edge)->clone();
    delete edges;
}
AdjacencyMatrixOriented *AdjacencyMatrixOriented::clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v = this->adjacencyMatrix_->begin(); v != this->adjacencyMatrix_->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
                newEdges.push_back((*u)->clone());
    return new AdjacencyMatrixOriented(this->size_, newEdges);
}
AdjacencyMatrixOriented::~AdjacencyMatrixOriented()
{
    this->deleteAllEdges();
    delete adjacencyMatrix_;
}
unsigned long long AdjacencyMatrixOriented::size() const
{
    return size_;
}
unsigned long long AdjacencyMatrixOriented::numberOfEdges() const
{
    unsigned long counter = 0;
    for(auto v = this->adjacencyMatrix_->begin(); v != this->adjacencyMatrix_->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
               ++counter;
    return counter;
}
std::vector<unsigned long long> *AdjacencyMatrixOriented::getChilds(unsigned long long vertex) const
{
    std::vector<unsigned long long>* childs = new std::vector<unsigned long long>();
    for(long long i = 0; i < size_; ++i)
        if(adjacencyMatrix_->at(vertex).at(i) != NULL)
            childs->push_back(adjacencyMatrix_->at(vertex).at(i)->To);
    return childs;
}
std::vector<unsigned long long> *AdjacencyMatrixOriented::getParents(unsigned long long vertex) const
{
    std::vector<unsigned long long>* parents = new std::vector<unsigned long long>();
    for(long long i = 0; i < size_; ++i)
        if(adjacencyMatrix_->at(i).at(vertex) != NULL)
            parents->push_back(adjacencyMatrix_->at(i).at(vertex)->From);
    return parents;
}
std::vector<Edge *> *AdjacencyMatrixOriented::getAllEdges() const
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto v = this->adjacencyMatrix_->begin(); v != this->adjacencyMatrix_->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
               edges->push_back(*u);
    return edges;
}
std::vector<Edge *> *AdjacencyMatrixOriented::getAllEdgesSorted()
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto v = this->adjacencyMatrix_->begin(); v != this->adjacencyMatrix_->end(); ++v)
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
void AdjacencyMatrixOriented::addNodes(size_t amount)
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
bool AdjacencyMatrixOriented::addEdge(long long from, long long to)
{
    return addEdge(new Edge(from, to));
}
bool AdjacencyMatrixOriented::checkEdge(long long from, long long to)
{
    if(from == to)
        return true;
    return adjacencyMatrix_->at(from).at(to) != NULL;
}
Edge* AdjacencyMatrixOriented::getEdge(long long from, long long to)
{
    return adjacencyMatrix_->at(from).at(to);
}
Edge* AdjacencyMatrixOriented::removeEdge(long long from, long long to)
{
    Edge* e = this->adjacencyMatrix_->at(from).at(to);
    this->adjacencyMatrix_->at(from).at(to) = NULL;
    return e;
}
void AdjacencyMatrixOriented::deleteEdge(unsigned long long from, unsigned long long to)
{
    if(this->adjacencyMatrix_->at(from).at(to) != NULL) {
        delete this->adjacencyMatrix_->at(from).at(to);
        this->adjacencyMatrix_->at(from).at(to) = NULL;
    }
}
void AdjacencyMatrixOriented::deleteNodeEdges(unsigned long long v)
{
    for(auto a = this->adjacencyMatrix_->begin(); a != this->adjacencyMatrix_->end(); ++a)
    {
        if(a->at(v) != NULL)
        {
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
void AdjacencyMatrixOriented::deleteAllEdges()
{
    for(auto v = this->adjacencyMatrix_->begin(); v != this->adjacencyMatrix_->end(); ++v)
        for(auto u = v->begin(); u != v->end(); ++u)
            if(*u != NULL)
               delete *u;
    adjacencyMatrix_->clear();
}
bool AdjacencyMatrixOriented::addEdge(Edge *edge)
{
    bool exists = adjacencyMatrix_->at(edge->From).at(edge->To) != NULL;
    if(exists)
        return false;
    adjacencyMatrix_->at(edge->From).at(edge->To) = edge;
    return true;
}
void AdjacencyMatrixOriented::initializeNewGraph(unsigned long long size)
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
