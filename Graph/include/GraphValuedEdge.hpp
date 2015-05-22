#ifndef __GRAPH_VALUED_EDGE_HPP__
#define __GRAPH_VALUED_EDGE_HPP__

#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "Graph.h"
#include "ValuedEdge.hpp"
#include "MinPQ.hpp"
#include "GraphFileFormat.h"

template <class EdgeValueTupe>
class GraphValuedEdge: public Graph
{
    public:
        GraphValuedEdge(unsigned int size, bool oriented): Graph(size, oriented) {}
        virtual ~GraphValuedEdge();

        using Graph::WriteToFile;
        virtual void ReadFromFile(std::ifstream& file);
        virtual void WriteToFile(std::ofstream& file);
        virtual void RandomizeGraph(double probability, EdgeValueTupe (*randFunc)());
        virtual void RandomizeUnorientedGraph(double probability, EdgeValueTupe (*randFunc)());
        void GenerateAccurateUnorientedGraph(int percentage, EdgeValueTupe (*randFunc)());
        bool AddEdge(int from, int to, EdgeValueTupe value);
        bool AddUnorientedEdge(int from, int to, EdgeValueTupe value);                   //return false if already exists
        EdgeValueTupe GetEdgeValue(int from, int to);
        int BFS(unsigned int source, unsigned int destination);
        int Dijkstra(unsigned int source, unsigned int destination);

};

template <class T>
GraphValuedEdge<T>::~GraphValuedEdge()
{
}

template <class T>
void GraphValuedEdge<T>::ReadFromFile(std::ifstream &file)
{
    unsigned int size, edgeSz;
    file >> size;
    this->Graph::InitializeNewGraph(size);
    std::string s;
    std::getline(file, s);
    std::getline(file, s);
    if(s != "<EDGES>")
        throw std::exception();
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
    std::getline(file, s);
    std::getline(file, s);
    if(s != "</EDGES>")
        throw std::exception();
}
template <class T>
void GraphValuedEdge<T>::WriteToFile(std::ofstream &file)
{
    file << GR_TYPE_GRAPH_VALUED_EDGE<< std::endl;
    file << this->size << std::endl;
    file << "<EDGES>" << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << " " <<
                ((ValuedEdge<T>*)edges[i])->GetValue() << std::endl;
    file << "</EDGES>" << std::endl;
}
template <class T>
void GraphValuedEdge<T>::GenerateAccurateUnorientedGraph(int percentage, T (*randFunc)())
{
    this->InitializeNewGraph(this->size);
    int required = percentage * (size * (size -1) / 2) / 100;
    while(edges.size() / 2 < required)
    {
        unsigned int u = rand() % size;
        unsigned int v = rand() % size;
        if(v == u)
            if(v == size - 1)
                v = 0;
            else
                v++;
        while(adjacencyMatrix->at(u).at(v) != -1)
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
        this->AddEdge(v, u, val);
    }
}
template <class T>
void GraphValuedEdge<T>::RandomizeGraph(double probability, T (*randFunc)())
{
    this->InitializeNewGraph(this->size);
    for(int i = 0; i < this->Size(); ++i)
        for(int j = 0; j < this->Size(); ++j)
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
void GraphValuedEdge<T>::RandomizeUnorientedGraph(double probability, T (*randFunc)())
{
    this->InitializeNewGraph(this->size);
    for(int i = 0; i < this->Size() - 1; ++i)
        for(int j = i; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddUnorientedEdge(i, j, randFunc());
            }
        }
}
template <class T>
bool GraphValuedEdge<T>::AddEdge(int from, int to, T value)
{
    return this->Graph::AddEdge(new ValuedEdge<T>(from, to, value));
}
template <class T>
bool GraphValuedEdge<T>::AddUnorientedEdge(int from, int to, T value)
{
    return this->Graph::AddUnorientedEdge(new ValuedEdge<T>(from, to, value));
}
template <class T>
T GraphValuedEdge<T>::GetEdgeValue(int from, int to)
{
    Edge* e = this->GetEdge(from, to);
    if(e == NULL)
        throw std::exception();
    return ((ValuedEdge<T>*)e)->GetValue();
}
template <class T>
int GraphValuedEdge<T>::BFS(unsigned int source, unsigned int destination)
{
    //std::priority_queue< std::pair<int, int>, std::vector< std::pair<int, int> >,   //first - prioriry
      //      EdgeComparator> q;                                                     //second - vertex
    MinPQ<T> q;
    int d[this->size];
    bool visited[this->size];
    for(int i = 0; i < this->size; ++i)
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
        for(int i = 0; i < size; ++i)
        {
            unsigned int vs = adjacencyMatrix->at(u).at(i);
            if(vs == -1)
                continue;
            if(visited[i])
                continue;
            int value = ((ValuedEdge<T>*)this->GetEdge(u, i))->GetValue();
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
int GraphValuedEdge<T>::Dijkstra(unsigned int source, unsigned int destination)
{
    MinPQ<T> q;
    unsigned int d[this->size];
    for(int i = 0; i < this->size; ++i)
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
            if(this->adjacencyMatrix->at(u).at(q.GetAt(i).second) != -1)
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
