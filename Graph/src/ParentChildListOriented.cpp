#include "ParentChildListOriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

ParentChildListOriented::ParentChildListOriented()
{
    this->size_ = 0;
    initializeNewGraph(DEFAULT_NODES_AMOUNT);
}
ParentChildListOriented::ParentChildListOriented(unsigned long long size, std::vector<Edge *> &edges)
{
    this->size_ = size;
    this->edges_.resize(size);
    initializeNewGraph(size);
    for(auto edge = edges.begin(); edge != edges.end(); ++edge)
    {
        this->edges_.push_back(*edge);
        this->outgoingEdges_[(*edge)->From].push_back(*edge);
        this->ingoingEdges_[(*edge)->To].push_back(*edge);
    }
}
ParentChildListOriented::ParentChildListOriented(unsigned long long size)
{
    this->edges_.resize(size);
    initializeNewGraph(size);
}
ParentChildListOriented::ParentChildListOriented(const ParentChildListOriented &graph)
{
    this->edges_.resize(graph.size_);
    initializeNewGraph(graph.size_);
    std::vector<Edge*>* edges = graph.getAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
    {
        auto newEdge = (*edge)->clone();
        this->edges_.push_back(newEdge);
        this->outgoingEdges_[(*edge)->From].push_back(newEdge);
        this->ingoingEdges_[(*edge)->To].push_back(newEdge);
    }
    delete edges;
}
ParentChildListOriented &ParentChildListOriented::operator=(const ParentChildListOriented &graph)
{
    this->edges_.resize(graph.size_);
    initializeNewGraph(graph.size_);
    std::vector<Edge*>* edges = graph.getAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
    {
        auto newEdge = (*edge)->clone();
        this->edges_.push_back(newEdge);
        this->outgoingEdges_[(*edge)->From].push_back(newEdge);
        this->ingoingEdges_[(*edge)->To].push_back(newEdge);
    }
    delete edges;
}
ParentChildListOriented* ParentChildListOriented::clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v = edges_.begin(); v != edges_.end(); ++v)
        newEdges.push_back((*v)->clone());
    return new ParentChildListOriented(this->size_, newEdges);
}
ParentChildListOriented::~ParentChildListOriented()
{
    this->deleteAllEdges();
}
unsigned long long ParentChildListOriented::size() const
{
    return size_;
}
unsigned long long ParentChildListOriented::numberOfEdges() const
{
    return this->edges_.size();
}
std::vector<unsigned long long> *ParentChildListOriented::getChilds(unsigned long long vertex) const
{
    std::vector<unsigned long long>* childs = new std::vector<unsigned long long>();
    for(auto e = edges_.begin(); e != edges_.end(); ++e)
        if((*e)->From == vertex)
            childs->push_back((*e)->To);
    return childs;
}
std::vector<unsigned long long> *ParentChildListOriented::getParents(unsigned long long vertex) const
{
    std::vector<unsigned long long>* parents = new std::vector<unsigned long long>();
    for(auto e = edges_.begin(); e != edges_.end(); ++e)
        if((*e)->To == vertex)
            parents->push_back((*e)->From);
    return parents;
}
std::vector<Edge *> *ParentChildListOriented::getAllEdges() const
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
               edges->push_back(*u);
    return edges;
}
const std::vector<Edge *> *ParentChildListOriented::getAllEdgesConst() const
{
    return &edges_;
}
std::vector<Edge *> *ParentChildListOriented::getAllEdgesSorted()
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
void ParentChildListOriented::addNodes(size_t amount)
{
    this->size_ += amount;
}
bool ParentChildListOriented::addEdge(long long from, long long to)
{
    return addEdge(new Edge(from, to));
}
bool ParentChildListOriented::checkEdge(long long from, long long to)
{
    if(from == to)
        return true;
    for(auto u = this->outgoingEdges_[from].begin(); u != this->outgoingEdges_[from].end(); ++u)
        if((*u)->To == to)
            return true;
    return NULL;
}
Edge* ParentChildListOriented::getEdge(long long from, long long to)
{
    for(auto u = this->outgoingEdges_[from].begin(); u != this->outgoingEdges_[from].end(); ++u)
        if((*u)->To == to)
            return *u;
    return NULL;
}
Edge*ParentChildListOriented::getEdge(long long from, long long to, unsigned long long id)
{
    for(auto u = this->outgoingEdges_[from].begin(); u != this->outgoingEdges_[from].end(); ++u)
        if((*u)->To == to && (*u)->getId() == id)
            return *u;
    return NULL;
}
Edge*ParentChildListOriented::getEdge(unsigned long long id)
{
    for(auto u = this->edges_.begin(); u != edges_.end(); ++u)
        if((*u)->getId() == id)
            return *u;
    return NULL;
}
Edge* ParentChildListOriented::removeEdge(long long from, long long to)
{
    Edge* edge = NULL;
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
        if((*u)->From == from && (*u)->To == to) {
            this->edges_.erase(u);
            edge = *u;
        }
    for(auto u = this->outgoingEdges_[from].begin(); u != this->outgoingEdges_[from].end(); ++u)
        if((*u)->To == to)
            this->outgoingEdges_[from].erase(u);
    for(auto u = this->ingoingEdges_[to].begin(); u != this->ingoingEdges_[to].end(); ++u)
        if((*u)->From == from)
            this->ingoingEdges_[to].erase(u);
    return edge;
}
void ParentChildListOriented::deleteEdge(unsigned long long from, unsigned long long to)
{
    Edge* edge = NULL;
    for(auto u = this->edges_.begin(); u != this->edges_.end(); ++u)
        if((*u)->From == from && (*u)->To == to) {
            edge = *u;
            this->edges_.erase(u);
            break;
        }
    for(auto u = this->outgoingEdges_[from].begin(); u != this->outgoingEdges_[from].end(); ++u)
        if((*u)->To == to) {
            this->outgoingEdges_[from].erase(u);
            break;
        }
    for(auto u = this->ingoingEdges_[to].begin(); u != this->ingoingEdges_[to].end(); ++u)
        if((*u)->From == from) {
            this->ingoingEdges_[to].erase(u);
            break;
        }
    assert(edge != NULL);
    delete edge;
}
void ParentChildListOriented::deleteNodeEdges(unsigned long long v)
{
    for(long long i = 0; i < edges_.size(); ++i)
        if(edges_[i]->From == v || edges_[i]->To == v) {
            delete(edges_[i]);
            edges_.erase(edges_.begin() + i);
            --i;
        }
    for(int i  = 0; i < this->ingoingEdges_.size(); ++i)
    {
        for(int j = 0; j < this->ingoingEdges_[i].size(); ++j)
        {
            Edge* e = ingoingEdges_[i][j];
            if(e->From == v || e->To == v ) {
                ingoingEdges_[i].erase(ingoingEdges_[i].begin() + j);
                --j;
            }
        }
    }
    for(int i  = 0; i < this->outgoingEdges_.size(); ++i)
    {
        for(int j = 0; j < this->outgoingEdges_[i].size(); ++j)
        {
            Edge* e = outgoingEdges_[i][j];
            if(e->From == v || e->To == v ) {
                outgoingEdges_[i].erase(outgoingEdges_[i].begin() + j);
                --j;
            }
        }
    }
    this->ingoingEdges_.at(v).clear();
    this->outgoingEdges_.at(v).clear();

}
void ParentChildListOriented::deleteAllEdges()
{
    for(auto v = edges_.begin(); v != edges_.end(); ++v)
               delete *v;
    edges_.clear();
    this->ingoingEdges_.clear();
    this->ingoingEdges_.resize(this->size_);
    this->outgoingEdges_.clear();
    this->outgoingEdges_.resize(this->size_);
}
bool ParentChildListOriented::addEdge(Edge *edge)
{
    edges_.push_back(edge);
    ingoingEdges_[edge->To].push_back(edge);
    outgoingEdges_[edge->From].push_back(edge);
    return true;
}
void ParentChildListOriented::initializeNewGraph(unsigned long long size)
{
    this->deleteAllEdges();
    this->ingoingEdges_.resize(size);
    this->outgoingEdges_.resize(size);
    this->size_ = size;
}
const std::vector<Edge *> *ParentChildListOriented::getOutgoing(unsigned long long vertex) const
{
    return &(outgoingEdges_[vertex]);
}
const std::vector<Edge *> *ParentChildListOriented::getIngoing(unsigned long long vertex) const
{
    return &(ingoingEdges_[vertex]);
}
