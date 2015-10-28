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

        using UnorientedGraph::writeToFile;
        virtual void readFromFile(std::ifstream& file);
        virtual void writeToFile(std::ostream &file);
        virtual void randomizeGraph(double probability, EdgeValueTupe (*randFunc)());
        void generateAccurateUnorientedGraph(long long percentage, EdgeValueTupe (*randFunc)());
        bool addEdge(long long from, long long to, EdgeValueTupe value);
        bool checkConnection();
        void DFS(unsigned long long  vertex, std::vector<bool>*visited);
        EdgeValueTupe getEdgeValue(long long from, long long to);
        long long BFS(unsigned long long source, unsigned long long destination);
        long long dijkstra(unsigned long long source, unsigned long long destination);
};
template <class T>
UnorientedGraphValuedEdge<T>::~UnorientedGraphValuedEdge()
{
}

template <class T>
void UnorientedGraphValuedEdge<T>::readFromFile(std::ifstream &file)
{
    unsigned long long size, edgeSz;
    file >> size;
    this->graph_->initializeNewGraph(size);
    file >> edgeSz;
    for(long long i = 0; i < edgeSz; ++i)
    {
        unsigned long long from, to;
        T vlaue;
        file >> from;
        file >> to;
        file >> vlaue;
        this->addEdge(from, to, vlaue);
    }
}
template <class T>
void UnorientedGraphValuedEdge<T>::writeToFile(std::ostream &file)
{
    std::vector<Edge*>* sorted = this->getAllEdgesSorted();
    file << this->size() << std::endl;
    file << sorted->size() << std::endl;
    for(long long i = 0; i < sorted->size(); ++i)
        file << sorted->at(i)->From << " " << sorted->at(i)->To << " " <<
                ((ValuedEdge<T>*)sorted->at(i))->GetValue() << std::endl;
    delete sorted;
}
template <class T>
bool UnorientedGraphValuedEdge<T>::checkConnection()
{
    std::vector<bool> visited;
    visited.resize(this->size());
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
    std::vector<unsigned long long>* vs = this->getChilds(vertex);
    for(long long i = 0; i < vs->size(); ++i)
        if(!visited->at(vs->at(i)))
        {
            visited->at(vs->at(i)) = true;
            DFS(vs->at(i), visited);
        }
    delete vs;
}
template <class T>
void UnorientedGraphValuedEdge<T>::generateAccurateUnorientedGraph(long long percentage, T (*randFunc)())
{
    unsigned long long size = this->size();
    this->graph_->initializeNewGraph(this->size());
    long long required = percentage * (this->size() * (this->size() - 1) / 2) / 100;
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
        while(graph_->getEdge(u,v) != NULL)
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
        this->addEdge(u, v, val);
        ++edgesCounter;
    }
    while(!checkConnection())
    {
        unsigned long long u = rand() % size;
        unsigned long long v = rand() % size;
        if(v == u)
            if(v == size - 1)
                v = 0;
            else
                v++;
        while(this->graph_->getEdge(u,v) != NULL)
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
        this->addEdge(u, v, val);
        ++edgesCounter;
    }
}
template <class T>
void UnorientedGraphValuedEdge<T>::randomizeGraph(double probability, T (*randFunc)())
{
    this->graph_->initializeNewGraph(this->size());
    for(long long i = 0; i < this->size() - 1; ++i)
        for(long long j = i; j < this->size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (long long)(1.0 / probability)))
            {
                this->addEdge(i, j, randFunc());
            }
        }
}
template <class T>
bool UnorientedGraphValuedEdge<T>::addEdge(long long from, long long to, T value)
{
    return this->UnorientedGraph::addEdge(new ValuedEdge<T>(from, to, value));
}
template <class T>
T UnorientedGraphValuedEdge<T>::getEdgeValue(long long from, long long to)
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
    long long d[this->size()];
    bool visited[this->size()];
    for(long long i = 0; i < this->size(); ++i)
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
        for(long long i = 0; i < this->size(); ++i)
        {
            ValuedEdge<T>* vs = static_cast<ValuedEdge<T>*>(graph_->getEdge(u, i));
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
long long UnorientedGraphValuedEdge<T>::dijkstra(unsigned long long source, unsigned long long destination)
{
    MinPQ<T> q;
    unsigned long long d[this->size()];
    for(long long i = 0; i < this->size(); ++i)
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
            if(this->graph->getEdge(u, q.GetAt(i).second) != NULL)
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
