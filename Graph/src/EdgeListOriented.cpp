#include "EdgeListOriented.h"

#include<assert.h>
#include<algorithm>

#define DEFAULT_NODES_AMOUNT 1

EdgeListOriented::EdgeListOriented()
{
    this->size = 0;
    InitializeNewGraph(DEFAULT_NODES_AMOUNT);
}
EdgeListOriented::EdgeListOriented(unsigned long long size, std::vector<Edge *> &edges)
{
    this->edges.resize(size);
    InitializeNewGraph(size);
    for(auto edge = edges.begin(); edge != edges.end(); ++edge)
    {
        this->edges.push_back(*edge);
    }
}
EdgeListOriented::EdgeListOriented(unsigned long long size)
{
    this->edges.resize(size);
    InitializeNewGraph(size);
}
EdgeListOriented::EdgeListOriented(const EdgeListOriented &graph)
{
    this->edges.resize(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*>* edges = graph.GetAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
        this->edges.push_back((*edge)->Clone());
    delete edges;
}
EdgeListOriented &EdgeListOriented::operator=(const EdgeListOriented &graph)
{
    this->edges.resize(graph.size);
    InitializeNewGraph(graph.size);
    std::vector<Edge*>* edges = graph.GetAllEdges();
    for(auto edge = edges->begin(); edge != edges->end(); ++edge)
        this->edges.push_back((*edge)->Clone());
    delete edges;
}
EdgeListOriented *EdgeListOriented::Clone() const
{
    std::vector<Edge*> newEdges;
    for(auto v = edges.begin(); v != edges.end(); ++v)
            if(*v != NULL)
                newEdges.push_back((*v)->Clone());
    return new EdgeListOriented(this->size, newEdges);
}
EdgeListOriented::~EdgeListOriented()
{
    this->DeleteAllEdges();
}
unsigned long long EdgeListOriented::Size() const
{
    return size;
}
unsigned long long EdgeListOriented::NumberOfEdges() const
{
    return this->edges.size();
}
std::vector<unsigned long long> *EdgeListOriented::GetChilds(unsigned long long vertex) const
{
    std::vector<unsigned long long>* childs = new std::vector<unsigned long long>();
    for(auto e = edges.begin(); e != edges.end(); ++e)
        if((*e)->From == vertex)
            childs->push_back((*e)->To);
    return childs;
}
std::vector<unsigned long long> *EdgeListOriented::GetParents(unsigned long long vertex) const
{
    std::vector<unsigned long long>* parents = new std::vector<unsigned long long>();
    for(auto e = edges.begin(); e != edges.end(); ++e)
        if((*e)->To == vertex)
            parents->push_back((*e)->From);
    return parents;
}
std::vector<Edge *> *EdgeListOriented::GetAllEdges() const
{
    std::vector<Edge*>* edges = new std::vector<Edge*>();
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
               edges->push_back(*u);
    return edges;
}
std::vector<Edge *> *EdgeListOriented::GetAllEdgesSorted()
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
void EdgeListOriented::AddNodes(size_t amount)
{
    this->size += amount;
}
bool EdgeListOriented::AddEdge(long long from, long long to)
{
    return AddEdge(new Edge(from, to));
}
bool EdgeListOriented::CheckEdge(long long from, long long to)
{
    if(from == to)
        return true;
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
            return true;
    return NULL;
}
Edge* EdgeListOriented::GetEdge(long long from, long long to)
{
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
            return *u;
    return NULL;
}
Edge* EdgeListOriented::RemoveEdge(long long from, long long to)
{
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
        {
            this->edges.erase(u);
            return *u;
        }
    return NULL;
}
void EdgeListOriented::DeleteEdge(unsigned long long from, unsigned long long to)
{
    auto edgeToDelete = this->edges.begin();
    for(auto u = this->edges.begin(); u != this->edges.end(); ++u)
        if((*u)->From == from && (*u)->To == to)
        {
            delete *u;
            edgeToDelete = u;
        }
    this->edges.erase(edgeToDelete);
}
void EdgeListOriented::DeleteNodeEdges(unsigned long long v)
{
    for(long long i = 0; i < edges.size(); ++i)
        if(edges[i]->From == v || edges[i]->To == v)
        {
            delete edges[i];
            edges.erase(edges.begin() + i);
            --i;
        }
}
void EdgeListOriented::DeleteAllEdges()
{
    for(auto v = edges.begin(); v != edges.end(); ++v)
               delete *v;
    edges.clear();
}
bool EdgeListOriented::AddEdge(Edge *edge)
{
    edges.push_back(edge);
    return true;
}
void EdgeListOriented::InitializeNewGraph(unsigned long long size)
{
    this->DeleteAllEdges();
    this->size = size;
}
