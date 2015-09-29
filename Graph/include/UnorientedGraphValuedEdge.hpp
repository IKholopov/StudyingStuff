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
        UnorientedGraphValuedEdge(unsigned int size, IGraph& graph):UnorientedGraph(size, graph) {};
        UnorientedGraphValuedEdge(IGraph* graph): UnorientedGraph(graph) {}
        UnorientedGraphValuedEdge(unsigned int size, IGraph* graph):UnorientedGraph(size, graph) {};
        virtual ~UnorientedGraphValuedEdge();

        using UnorientedGraph::WriteToFile;
        virtual void ReadFromFile(std::ifstream& file);
        virtual void WriteToFile(std::ostream &file);
        virtual void RandomizeGraph(double probability, EdgeValueTupe (*randFunc)());
        void GenerateAccurateUnorientedGraph(int percentage, EdgeValueTupe (*randFunc)());
        bool AddEdge(int from, int to, EdgeValueTupe value);
        bool CheckConnection();
        void DFS(unsigned int  vertex, std::vector<bool>*visited);
        EdgeValueTupe GetEdgeValue(int from, int to);
        int BFS(unsigned int source, unsigned int destination);
        int Dijkstra(unsigned int source, unsigned int destination);
};
template <class T>
UnorientedGraphValuedEdge<T>::~UnorientedGraphValuedEdge()
{
}

template <class T>
void UnorientedGraphValuedEdge<T>::ReadFromFile(std::ifstream &file)
{
    unsigned int size, edgeSz;
    file >> size;
    this->graph->InitializeNewGraph(size);
    file >> edgeSz;
    for(int i = 0; i < edgeSz; ++i)
    {
        unsigned int from, to;
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
    std::vector<Edge*> sorted = this->GetAllEdgesSorted();
    file << this->Size() << std::endl;
    file << sorted.size() << std::endl;
    for(int i = 0; i < sorted.size(); ++i)
        file << sorted[i]->From << " " << sorted[i]->To << " " <<
                ((ValuedEdge<T>*)sorted[i])->GetValue() << std::endl;
}
template <class T>
bool UnorientedGraphValuedEdge<T>::CheckConnection()
{
    std::vector<bool> visited;
    visited.resize(this->Size());
    std::fill(visited.begin(), visited.end(), false);
    DFS(0, &visited);
    for(int i = 0; i < visited.size(); ++i)
        if(!visited[i])
            return false;
    return true;
}
template <class T>
void UnorientedGraphValuedEdge<T>::DFS(unsigned int vertex, std::vector<bool>* visited)
{
    std::vector<unsigned int> vs = this->GetChilds(vertex);
    for(int i = 0; i < vs.size(); ++i)
        if(!visited->at(vs[i]))
        {
            visited->at(vs[i]) = true;
            DFS(vs[i], visited);
        }
}
template <class T>
void UnorientedGraphValuedEdge<T>::GenerateAccurateUnorientedGraph(int percentage, T (*randFunc)())
{
    unsigned int size = this->Size();
    this->graph->InitializeNewGraph(this->Size());
    int required = percentage * (Size() * (Size() - 1) / 2) / 100;
    int edgesCounter = 0;
    while(edgesCounter < required)
    {
        unsigned int u = rand() % size;
        unsigned int v = rand() % size;
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
        unsigned int u = rand() % size;
        unsigned int v = rand() % size;
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
    for(int i = 0; i < this->Size() - 1; ++i)
        for(int j = i; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddEdge(i, j, randFunc());
            }
        }
}
template <class T>
bool UnorientedGraphValuedEdge<T>::AddEdge(int from, int to, T value)
{
    return this->UnorientedGraph::AddEdge(new ValuedEdge<T>(from, to, value));
}
template <class T>
T UnorientedGraphValuedEdge<T>::GetEdgeValue(int from, int to)
{
    Edge* e = this->GetEdge(from, to);
    if(e == NULL)
        throw std::exception();
    return ((ValuedEdge<T>*)e)->GetValue();
}
template <class T>
int UnorientedGraphValuedEdge<T>::BFS(unsigned int source, unsigned int destination)
{
    //std::priority_queue< std::pair<int, int>, std::vector< std::pair<int, int> >,   //first - prioriry
      //      EdgeComparator> q;                                                     //second - vertex
    MinPQ<T> q;
    int d[this->Size()];
    bool visited[this->Size()];
    for(int i = 0; i < this->Size(); ++i)
    {
        visited[i] = false;
        d[i] = -1;
    }
    d[source] = 0;
    q.push(std::pair<T, unsigned int>(0, source));
    while(q.size() > 0)
    {
        std::pair<T, unsigned int> next = q.top();
        q.pop();
        int u = next.second;
        if(visited[u])
            continue;
        visited[u] = true;
        //std::vector<unsigned int> vs = this->GetChilds(u);
        for(int i = 0; i < this->Size(); ++i)
        {
            ValuedEdge<T>* vs = static_cast<ValuedEdge<T>*>(graph->GetEdge(u, i));
            if(vs == NULL)
                continue;
            if(visited[i])
                continue;
            int value = vs->GetValue();
            if(d[i] == -1 || value + d[u] < d[i])
                d[i] = value + d[u];
            if(!(visited[i]))
            {
                q.push(std::pair<T, unsigned int> (value + d[u], i));
            }
        }
    }
    return d[destination];
}
template <class T>
int UnorientedGraphValuedEdge<T>::Dijkstra(unsigned int source, unsigned int destination)
{
    MinPQ<T> q;
    unsigned int d[this->Size()];
    for(int i = 0; i < this->Size(); ++i)
    {
        q.push(std::pair<T, unsigned int>(INT32_MAX, i));
        d[i] = -1;
    }
    q.DecreaseKeyAt(source, 0);
    d[source] = 0;
    int u = source;
    int dist = 0;
    while (q.size() > 0) {
        for(int i = 0; i < q.size(); ++i)
            if(this->graph->GetEdge(u, q.GetAt(i).second) != NULL)
            {
                if(((ValuedEdge<T>*)this->GetEdge(u, q.GetAt(i).second))->GetValue() + dist < q.GetAt(i).first)
                    q.DecreaseKey(i, ((ValuedEdge<T>*)this->GetEdge(u, q.GetAt(i).second))->GetValue() + dist);
            }
        std::pair<unsigned int, int> next = q.pop();
        u = next.second;
        dist = next.first;
        d[u] = dist;
    }
    return d[destination];
}


#endif
