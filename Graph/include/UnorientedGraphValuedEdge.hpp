#ifndef __GRAPH_VALUED_EDGE_HPP__
#define __GRAPH_VALUED_EDGE_HPP__

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "UnorientedGraph.h"
#include "ValuedEdge.hpp"
#include "MinPQ.hpp"
#include "GraphFileFormat.h"

template <class EdgeValueTupe>
class UnorientedGraphValuedEdge: public UnorientedGraph
{
    public:
        UnorientedGraphValuedEdge(IGraph& graph): UnorientedGraph(graph) {}
        UnorientedGraphValuedEdge(unsigned long long size, IGraph& graph):UnorientedGraph(size, graph) {};
        UnorientedGraphValuedEdge(IGraph* graph): UnorientedGraph(graph) {}
        UnorientedGraphValuedEdge(unsigned long long size, IGraph* graph):UnorientedGraph(size, graph) {};
        virtual ~UnorientedGraphValuedEdge();

        using UnorientedGraph::WriteToFile;
        virtual void ReadFromFile(std::ifstream& file);
        virtual void WriteToFile(std::ostream &file);
        virtual void RandomizeGraph(double probability, EdgeValueTupe (*randFunc)());
        void GenerateAccurateUnorientedGraph(long long percentage, EdgeValueTupe (*randFunc)());
        bool AddEdge(long long from, long long to, EdgeValueTupe value);
        bool CheckConnection();
        void DFS(unsigned long long  vertex, std::vector<bool>*visited);
        EdgeValueTupe GetEdgeValue(long long from, long long to);
        long long BFS(unsigned long long source, unsigned long long destination);
        long long Dijkstra(unsigned long long source, unsigned long long destination);
};
template <class T>
UnorientedGraphValuedEdge<T>::~UnorientedGraphValuedEdge()
{
}

template <class T>
void UnorientedGraphValuedEdge<T>::ReadFromFile(std::ifstream &file)
{
    unsigned long long size, edgeSz;
    file >> size;
    this->graph->InitializeNewGraph(size);
    file >> edgeSz;
    for(long long i = 0; i < edgeSz; ++i)
    {
        unsigned long long from, to;
        T vlaue;
        file >> from;
        file >> to;
        file >> vlaue;
        this->AddEdge(from, to, vlaue);
    }
}
template <class T>
void UnorientedGraphValuedEdge<T>::WriteToFile(std::ostream &file)
{
    std::vector<Edge*>* sorted = this->GetAllEdgesSorted();
    file << this->Size() << std::endl;
    file << sorted->size() << std::endl;
    for(long long i = 0; i < sorted->size(); ++i)
        file << sorted->at(i)->From << " " << sorted->at(i)->To << " " <<
                ((ValuedEdge<T>*)sorted->at(i))->GetValue() << std::endl;
    delete sorted;
}
template <class T>
bool UnorientedGraphValuedEdge<T>::CheckConnection()
{
    std::vector<bool> visited;
    visited.resize(this->Size());
    std::fill(visited.begin(), visited.end(), false);
    DFS(0, &visited);
    for(long long i = 0; i < visited.size(); ++i)
        if(!visited[i])
            return false;
    return true;
}
template <class T>
void UnorientedGraphValuedEdge<T>::DFS(unsigned long long vertex, std::vector<bool>* visited)
{
    std::vector<unsigned long long>* vs = this->GetChilds(vertex);
    for(long long i = 0; i < vs->size(); ++i)
        if(!visited->at(vs->at(i)))
        {
            visited->at(vs->at(i)) = true;
            DFS(vs->at(i), visited);
        }
    delete vs;
}
template <class T>
void UnorientedGraphValuedEdge<T>::GenerateAccurateUnorientedGraph(long long percentage, T (*randFunc)())
{
    unsigned long long size = this->Size();
    this->graph->InitializeNewGraph(this->Size());
    long long required = percentage * (Size() * (Size() - 1) / 2) / 100;
    long long edgesCounter = 0;
    while(edgesCounter < required)
    {
        unsigned long long u = rand() % size;
        unsigned long long v = rand() % size;
        if(v == u)
            if(v == size - 1)
                v = 0;
            else
                v++;
        while(graph->GetEdge(u,v) != NULL)
        {
            if(v == size - 1)
            {
                v = 0;
                if(u == size - 1)
                {
                    u = 0;
                    v = 1;
                }
                else u++;
            }
            else
                v++;
            if(v == u)
                v++;
            if(v == size)
            {
                v = 0;
                if(u == size - 1)
                {
                    u = 0;
                    v = 1;
                }
                else u++;
            }
        }
        T val = randFunc();
        this->AddEdge(u, v, val);
        ++edgesCounter;
    }
    while(!CheckConnection())
    {
        unsigned long long u = rand() % size;
        unsigned long long v = rand() % size;
        if(v == u)
            if(v == size - 1)
                v = 0;
            else
                v++;
        while(this->graph->GetEdge(u,v) != NULL)
        {
            if(v == size - 1)
            {
                v = 0;
                if(u == size - 1)
                {
                    u = 0;
                    v = 1;
                }
                else u++;
            }
            else
                v++;
            if(v == u)
                v++;
            if(v == size)
            {
                v = 0;
                if(u == size - 1)
                {
                    u = 0;
                    v = 1;
                }
                else u++;
            }
        }
        T val = randFunc();
        this->AddEdge(u, v, val);
        ++edgesCounter;
    }
}
template <class T>
void UnorientedGraphValuedEdge<T>::RandomizeGraph(double probability, T (*randFunc)())
{
    this->graph->InitializeNewGraph(this->Size());
    for(long long i = 0; i < this->Size() - 1; ++i)
        for(long long j = i; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (long long)(1.0 / probability)))
            {
                this->AddEdge(i, j, randFunc());
            }
        }
}
template <class T>
bool UnorientedGraphValuedEdge<T>::AddEdge(long long from, long long to, T value)
{
    return this->UnorientedGraph::AddEdge(new ValuedEdge<T>(from, to, value));
}
template <class T>
T UnorientedGraphValuedEdge<T>::GetEdgeValue(long long from, long long to)
{
    Edge* e = this->GetEdge(from, to);
    if(e == NULL)
        throw std::exception();
    return ((ValuedEdge<T>*)e)->GetValue();
}
template <class T>
long long UnorientedGraphValuedEdge<T>::BFS(unsigned long long source, unsigned long long destination)
{
    //std::priority_queue< std::pair<long long, long long>, std::vector< std::pair<long long, long long> >,   //first - prioriry
      //      EdgeComparator> q;                                                     //second - vertex
    MinPQ<T> q;
    long long d[this->Size()];
    bool visited[this->Size()];
    for(long long i = 0; i < this->Size(); ++i)
    {
        visited[i] = false;
        d[i] = -1;
    }
    d[source] = 0;
    q.push(std::pair<T, unsigned long long>(0, source));
    while(q.size() > 0)
    {
        std::pair<T, unsigned long long> next = q.top();
        q.pop();
        long long u = next.second;
        if(visited[u])
            continue;
        visited[u] = true;
        //std::vector<unsigned long long> vs = this->GetChilds(u);
        for(long long i = 0; i < this->Size(); ++i)
        {
            ValuedEdge<T>* vs = static_cast<ValuedEdge<T>*>(graph->GetEdge(u, i));
            if(vs == NULL)
                continue;
            if(visited[i])
                continue;
            long long value = vs->GetValue();
            if(d[i] == -1 || value + d[u] < d[i])
                d[i] = value + d[u];
            if(!(visited[i]))
            {
                q.push(std::pair<T, unsigned long long> (value + d[u], i));
            }
        }
    }
    return d[destination];
}
template <class T>
long long UnorientedGraphValuedEdge<T>::Dijkstra(unsigned long long source, unsigned long long destination)
{
    MinPQ<T> q;
    unsigned long long d[this->Size()];
    for(long long i = 0; i < this->Size(); ++i)
    {
        q.push(std::pair<T, unsigned long long>(INT32_MAX, i));
        d[i] = -1;
    }
    q.DecreaseKeyAt(source, 0);
    d[source] = 0;
    long long u = source;
    long long dist = 0;
    while (q.size() > 0) {
        for(long long i = 0; i < q.size(); ++i)
            if(this->graph->GetEdge(u, q.GetAt(i).second) != NULL)
            {
                if(((ValuedEdge<T>*)this->GetEdge(u, q.GetAt(i).second))->GetValue() + dist < q.GetAt(i).first)
                    q.DecreaseKey(i, ((ValuedEdge<T>*)this->GetEdge(u, q.GetAt(i).second))->GetValue() + dist);
            }
        std::pair<unsigned long long, long long> next = q.pop();
        u = next.second;
        dist = next.first;
        d[u] = dist;
    }
    return d[destination];
}


#endif
