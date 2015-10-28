#include "EdgeListOriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

EdgeListOriented::EdgeListOriented()
{
    this->size_ = 0;
    initializeNewGraph(DEFAULT_NODES_AMOUNT);
}
EdgeListOriented::EdgeListOriented(unsigned long long size, std::vector<Edge *> &edges)
{
    this->edges_.resize(size);
    initializeNewGraph(size);
    for(auto edge = edges.begin(); edge != edges.end(); ++edge)
    {
        this->edges_.push_back(*edge);
    }
}
EdgeListOriented::EdgeListOriented(unsigned long long size)
{
    this->edges_.resize(size);
    initializeNewGraph(size);
}
EdgeListOriented::EdgeListOriented(const EdgeListOriented &graph)
{
    this->edges_.resize(graph.size_);
    initializeNewGraph(graph.size_);
    std::vector<Edge*>* edges = graph.getAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
        this->edges_.push_back((*edge)->clone());
    delete edges;
}
EdgeListOriented &EdgeListOriented::operator=(const EdgeListOriented &graph)
{
    this->edges_.resize(graph.size_);
    initializeNewGraph(graph.size_);
    std::vector<Edge*>* edges = graph.getAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
        this->edges_.push_back((*edge)->clone());
    delete edges;
}
EdgeListOriented *EdgeListOriented::clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v = edges_.begin(); v != edges_.end(); ++v)
            if(*v != NULL)
                newEdges.push_back((*v)->clone());
    return new EdgeListOriented(this->size_, newEdges);
}
EdgeListOriented::~EdgeListOriented()
{
    this->deleteAllEdges();
}
unsigned long long EdgeListOriented::size() const
{
    return size_;
}
unsigned long long EdgeListOriented::numberOfEdges() const
{
    return this->edges_.size();
}
std::vector<unsigned long long> *EdgeListOriented::getChilds(unsigned long long vertex) const
{
    std::vector<unsigned long long>* childs = new std::vector<unsigned long long>();
    for(auto e = edges_.begin(); e != edges_.end(); ++e)
        if((*e)->From == vertex)
            childs->push_back((*e)->To);
    return childs;
}
std::vector<unsigned long long> *EdgeListOriented::getParents(unsigned long long vertex) const
{
    std::vector<unsigned long long>* parents = new std::vector<unsigned long long>();
    for(auto e = edges_.begin(); e != edges_.end(); ++e)
        if((*e)->To == vertex)
            parents->push_back((*e)->From);
    return parents;
}
std::vector<Edge *> *EdgeListOriented::getAllEdges() const
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
               edges->push_back(*u);
    return edges;
}
std::vector<Edge *> *EdgeListOriented::getAllEdgesSorted()
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
               edges->push_back(*u);
    std::sort(edges->begin(), edges->end(), [](Edge* a, Edge* b) {
        if(a->From == b->From)
            return a->To < b->To;
        return a->From < b->From;
    });
    return edges;
}
void EdgeListOriented::addNodes(size_t amount)
{
    this->size_ += amount;
}
bool EdgeListOriented::addEdge(long long from, long long to)
{
    return addEdge(new Edge(from, to));
}
bool EdgeListOriented::checkEdge(long long from, long long to)
{
    if(from == to)
        return true;
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
            return true;
    return NULL;
}
Edge* EdgeListOriented::getEdge(long long from, long long to)
{
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
            return *u;
    return NULL;
}
Edge* EdgeListOriented::removeEdge(long long from, long long to)
{
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
        {
            this->edges_.erase(u);
            return *u;
        }
    return NULL;
}
void EdgeListOriented::deleteEdge(unsigned long long from, unsigned long long to)
{
    auto edgeToDelete = this->edges_.begin();
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
        {
            delete *u;
            edgeToDelete = u;
        }
    this->edges_.erase(edgeToDelete);
}
void EdgeListOriented::deleteNodeEdges(unsigned long long v)
{
    for(long long i = 0; i < edges_.size(); ++i)
        if(edges_[i]->From == v || edges_[i]->To == v)
        {
            delete edges_[i];
            edges_.erase(edges_.begin() + i);
            --i;
        }
}
void EdgeListOriented::deleteAllEdges()
{
    for(auto v = edges_.begin(); v != edges_.end(); ++v)
               delete *v;
    edges_.clear();
}
bool EdgeListOriented::addEdge(Edge *edge)
{
    edges_.push_back(edge);
    return true;
}
void EdgeListOriented::initializeNewGraph(unsigned long long size)
{
    this->deleteAllEdges();
    this->size_ = size;
}
