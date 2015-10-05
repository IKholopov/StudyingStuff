#ifndef __GRAPH_VALUED_EDGE_HPP__
#define __GRAPH_VALUED_EDGE_HPP__

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "OrientedGraph.h"
#include "ValuedEdge.hpp"
#include "GraphFileFormat.h"

template <class EdgeValueTupe>
class OrientedGraphValuedEdge: public OrientedGraph
{
    public:
    OrientedGraphValuedEdge(IGraph& graph): OrientedGraph(graph) {}
    OrientedGraphValuedEdge(unsigned long long size, IGraph& graph):OrientedGraph(size, graph) {};
    OrientedGraphValuedEdge(IGraph* graph): OrientedGraph(graph) {}
    OrientedGraphValuedEdge(unsigned long long size, IGraph* graph):OrientedGraph(size, graph) {};
    virtual ~OrientedGraphValuedEdge();

    using OrientedGraph::WriteToFile;
    virtual void ReadFromFile(std::istream &file);
    virtual void WriteToFile(std::ostream &file);
    virtual void RandomizeGraph(double probability, EdgeValueTupe (*randFunc)());
    void GenerateAccurateGraph(long long percentage, EdgeValueTupe (*randFunc)());
    bool AddEdge(long long from, long long to, EdgeValueTupe value);
    bool CheckConnection();
    void DFS(unsigned long long  vertex, std::vector<bool>*visited);
    EdgeValueTupe GetEdgeValue(long long from, long long to);
};

template <class T>
OrientedGraphValuedEdge<T>::~OrientedGraphValuedEdge()
{
}

template <class T>
void OrientedGraphValuedEdge<T>::ReadFromFile(std::istream &file)
{
    unsigned long long size, edgeSz;
    file >> size;
    this->OrientedGraph::InitializeNewGraph(size);
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
void OrientedGraphValuedEdge<T>::WriteToFile(std::ostream &file)
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
bool OrientedGraphValuedEdge<T>::CheckConnection()
{
    std::vector<bool> visited;
    visited.resize(this->size);
    std::fill(visited.begin(), visited.end(), false);
    DFS(0, &visited);
    for(long long i = 0; i < visited.size(); ++i)
        if(!visited[i])
            return false;
    return true;
}
template <class T>
void OrientedGraphValuedEdge<T>::DFS(unsigned long long vertex, std::vector<bool>* visited)
{
    std::vector<unsigned long long> vs = this->GetChilds(vertex);
    for(long long i = 0; i < vs.size(); ++i)
        if(!visited->at(vs[i]))
        {
            visited->at(vs[i]) = true;
            DFS(vs[i], visited);
        }
}
template <class T>
void OrientedGraphValuedEdge<T>::RandomizeGraph(double probability, T (*randFunc)())
{
    this->graph->InitializeNewGraph(this->Size());
    for(long long i = 0; i < this->Size() - 1; ++i)
        for(long long j = 0; j < this->Size(); ++j)
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
bool OrientedGraphValuedEdge<T>::AddEdge(long long from, long long to, T value)
{
    return this->OrientedGraph::AddEdge(new ValuedEdge<T>(from, to, value));
}
template <class T>
T OrientedGraphValuedEdge<T>::GetEdgeValue(long long from, long long to)
{
    Edge* e = this->GetEdge(from, to);
    if(e == NULL)
        throw std::exception();
    return static_cast<ValuedEdge<T>*>(e)->GetValue();
}
#endif
