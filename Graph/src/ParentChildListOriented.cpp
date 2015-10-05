#include "ParentChildListOriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

ParentChildListOriented::ParentChildListOriented()
{
    this->size = 0;
    InitializeNewGraph(DEFAULT_NODES_AMOUNT);
}
ParentChildListOriented::ParentChildListOriented(unsigned long long size, std::vector<Edge *> &edges)
{
    this->size = size;
    this->edges.resize(size);
    InitializeNewGraph(size);
    for(auto edge = edges.begin(); edge != edges.end(); ++edge)
    {
        this->edges.push_back(*edge);
        this->outgoingEdges[(*edge)->From].push_back(*edge);
        this->ingoingEdges[(*edge)->To].push_back(*edge);
    }
}
ParentChildListOriented::ParentChildListOriented(unsigned long long size)
{
    this->edges.resize(size);
    InitializeNewGraph(size);
}
ParentChildListOriented::ParentChildListOriented(const ParentChildListOriented &graph)
{
    this->edges.resize(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*>* edges = graph.GetAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
    {
        auto newEdge = (*edge)->Clone();
        this->edges.push_back(newEdge);
        this->outgoingEdges[(*edge)->From].push_back(newEdge);
        this->ingoingEdges[(*edge)->To].push_back(newEdge);
    }
    delete edges;
}
ParentChildListOriented &ParentChildListOriented::operator=(const ParentChildListOriented &graph)
{
    this->edges.resize(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*>* edges = graph.GetAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
    {
        auto newEdge = (*edge)->Clone();
        this->edges.push_back(newEdge);
        this->outgoingEdges[(*edge)->From].push_back(newEdge);
        this->ingoingEdges[(*edge)->To].push_back(newEdge);
    }
    delete edges;
}
ParentChildListOriented* ParentChildListOriented::Clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v = edges.begin(); v != edges.end(); ++v)
        newEdges.push_back((*v)->Clone());
    return new ParentChildListOriented(this->size, newEdges);
}
ParentChildListOriented::~ParentChildListOriented()
{
    this->DeleteAllEdges();
}
unsigned long long ParentChildListOriented::Size() const
{
    return size;
}
unsigned long long ParentChildListOriented::NumberOfEdges() const
{
    return this->edges.size();
}
std::vector<unsigned long long> *ParentChildListOriented::GetChilds(unsigned long long vertex) const
{
    std::vector<unsigned long long>* childs = new std::vector<unsigned long long>();
    for(auto e = edges.begin(); e != edges.end(); ++e)
        if((*e)->From == vertex)
            childs->push_back((*e)->To);
    return childs;
}
std::vector<unsigned long long> *ParentChildListOriented::GetParents(unsigned long long vertex) const
{
    std::vector<unsigned long long>* parents = new std::vector<unsigned long long>();
    for(auto e = edges.begin(); e != edges.end(); ++e)
        if((*e)->To == vertex)
            parents->push_back((*e)->From);
    return parents;
}
std::vector<Edge *> *ParentChildListOriented::GetAllEdges() const
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
               edges->push_back(*u);
    return edges;
}
const std::vector<Edge *> *ParentChildListOriented::GetAllEdgesConst() const
{
    return &edges;
}
std::vector<Edge *> *ParentChildListOriented::GetAllEdgesSorted()
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
               edges->push_back(*u);
    std::sort(edges->begin(), edges->end(), [](Edge* a, Edge* b) {
        if(a->From == b->From)
            return a->To < b->To;
        return a->From < b->From;
    });
    return edges;
}
void ParentChildListOriented::AddNodes(size_t amount)
{
    this->size += amount;
}
bool ParentChildListOriented::AddEdge(long long from, long long to)
{
    return AddEdge(new Edge(from, to));
}
bool ParentChildListOriented::CheckEdge(long long from, long long to)
{
    if(from == to)
        return true;
    for(auto u = this->outgoingEdges[from].begin(); u != this->outgoingEdges[from].end(); ++u)
        if((*u)->To == to)
            return true;
    return NULL;
}
Edge* ParentChildListOriented::GetEdge(long long from, long long to)
{
    for(auto u = this->outgoingEdges[from].begin(); u != this->outgoingEdges[from].end(); ++u)
        if((*u)->To == to)
            return *u;
    return NULL;
}
Edge*ParentChildListOriented::GetEdge(long long from, long long to, unsigned long long id)
{
    for(auto u = this->outgoingEdges[from].begin(); u != this->outgoingEdges[from].end(); ++u)
        if((*u)->To == to && (*u)->GetId() == id)
            return *u;
    return NULL;
}
Edge*ParentChildListOriented::GetEdge(unsigned long long id)
{
    for(auto u = this->edges.begin(); u != edges.end(); ++u)
        if((*u)->GetId() == id)
            return *u;
    return NULL;
}
Edge* ParentChildListOriented::RemoveEdge(long long from, long long to)
{
    Edge* edge = NULL;
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
        {
            this->edges.erase(u);
            edge = *u;
        }
    for(auto u = this->outgoingEdges[from].begin(); u != this->outgoingEdges[from].end(); ++u)
        if((*u)->To == to)
            this->outgoingEdges[from].erase(u);
    for(auto u = this->ingoingEdges[to].begin(); u != this->ingoingEdges[to].end(); ++u)
        if((*u)->From == from)
            this->ingoingEdges[to].erase(u);
    return edge;
}
void ParentChildListOriented::DeleteEdge(unsigned long long from, unsigned long long to)
{
    Edge* edge = NULL;
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
        {
            edge = *u;
            this->edges.erase(u);
            break;
        }
    for(auto u = this->outgoingEdges[from].begin(); u != this->outgoingEdges[from].end(); ++u)
        if((*u)->To == to)
        {
            this->outgoingEdges[from].erase(u);
            break;
        }
    for(auto u = this->ingoingEdges[to].begin(); u != this->ingoingEdges[to].end(); ++u)
        if((*u)->From == from)
        {
            this->ingoingEdges[to].erase(u);
            break;
        }
    assert(edge != NULL);
    delete edge;
}
void ParentChildListOriented::DeleteNodeEdges(unsigned long long v)
{
    for(long long i = 0; i < edges.size(); ++i)
        if(edges[i]->From == v || edges[i]->To == v)
        {
            delete(edges[i]);
            edges.erase(edges.begin() + i);
            --i;
        }
    for(int i  = 0; i < this->ingoingEdges.size(); ++i)
    {
        for(int j = 0; j < this->ingoingEdges[i].size(); ++j)
        {
            Edge* e = ingoingEdges[i][j];
            if(e->From == v || e->To == v )
            {
                ingoingEdges[i].erase(ingoingEdges[i].begin() + j);
                --j;
            }
        }
    }
    for(int i  = 0; i < this->outgoingEdges.size(); ++i)
    {
        for(int j = 0; j < this->outgoingEdges[i].size(); ++j)
        {
            Edge* e = outgoingEdges[i][j];
            if(e->From == v || e->To == v )
            {
                outgoingEdges[i].erase(outgoingEdges[i].begin() + j);
                --j;
            }
        }
    }
    this->ingoingEdges.at(v).clear();
    this->outgoingEdges.at(v).clear();

}
void ParentChildListOriented::DeleteAllEdges()
{
    for(auto v = edges.begin(); v != edges.end(); ++v)
               delete *v;
    edges.clear();
    this->ingoingEdges.clear();
    this->ingoingEdges.resize(this->size);
    this->outgoingEdges.clear();
    this->outgoingEdges.resize(this->size);
}
bool ParentChildListOriented::AddEdge(Edge *edge)
{
    edges.push_back(edge);
    ingoingEdges[edge->To].push_back(edge);
    outgoingEdges[edge->From].push_back(edge);
    return true;
}
void ParentChildListOriented::InitializeNewGraph(unsigned long long size)
{
    this->DeleteAllEdges();
    this->ingoingEdges.resize(size);
    this->outgoingEdges.resize(size);
    this->size = size;
}
const std::vector<Edge *> *ParentChildListOriented::GetOutgoing(unsigned long long vertex) const
{
    return &(outgoingEdges[vertex]);
}
const std::vector<Edge *> *ParentChildListOriented::GetIngoing(unsigned long long vertex) const
{
    return &(ingoingEdges[vertex]);
}
