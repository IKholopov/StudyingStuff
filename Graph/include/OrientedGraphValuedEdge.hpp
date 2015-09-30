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
    OrientedGraphValuedEdge(unsigned int size, IGraph& graph):OrientedGraph(size, graph) {};
    OrientedGraphValuedEdge(IGraph* graph): OrientedGraph(graph) {}
    OrientedGraphValuedEdge(unsigned int size, IGraph* graph):OrientedGraph(size, graph) {};
    virtual ~OrientedGraphValuedEdge();

    using OrientedGraph::WriteToFile;
    virtual void ReadFromFile(std::istream &file);
    virtual void WriteToFile(std::ostream &file);
    virtual void RandomizeGraph(double probability, EdgeValueTupe (*randFunc)());
    void GenerateAccurateGraph(int percentage, EdgeValueTupe (*randFunc)());
    bool AddEdge(int from, int to, EdgeValueTupe value);
    bool CheckConnection();
    void DFS(unsigned int  vertex, std::vector<bool>*visited);
    EdgeValueTupe GetEdgeValue(int from, int to);
};

template <class T>
OrientedGraphValuedEdge<T>::~OrientedGraphValuedEdge()
{
}

template <class T>
void OrientedGraphValuedEdge<T>::ReadFromFile(std::istream &file)
{
    unsigned int size, edgeSz;
    file >> size;
    this->OrientedGraph::InitializeNewGraph(size);
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
void OrientedGraphValuedEdge<T>::WriteToFile(std::ostream &file)
{
    std::vector<Edge*> sorted = this->GetAllEdgesSorted();
    file << this->Size() << std::endl;
    file << sorted.size() << std::endl;
    for(int i = 0; i < sorted.size(); ++i)
        file << sorted[i]->From << " " << sorted[i]->To << " " <<
                ((ValuedEdge<T>*)sorted[i])->GetValue() << std::endl;
}
template <class T>
bool OrientedGraphValuedEdge<T>::CheckConnection()
{
    std::vector<bool> visited;
    visited.resize(this->size);
    std::fill(visited.begin(), visited.end(), false);
    DFS(0, &visited);
    for(int i = 0; i < visited.size(); ++i)
        if(!visited[i])
            return false;
    return true;
}
template <class T>
void OrientedGraphValuedEdge<T>::DFS(unsigned int vertex, std::vector<bool>* visited)
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
void OrientedGraphValuedEdge<T>::RandomizeGraph(double probability, T (*randFunc)())
{
    this->graph->InitializeNewGraph(this->Size());
    for(int i = 0; i < this->Size() - 1; ++i)
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
bool OrientedGraphValuedEdge<T>::AddEdge(int from, int to, T value)
{
    return this->OrientedGraph::AddEdge(new ValuedEdge<T>(from, to, value));
}
template <class T>
T OrientedGraphValuedEdge<T>::GetEdgeValue(int from, int to)
{
    Edge* e = this->GetEdge(from, to);
    if(e == NULL)
        throw std::exception();
    return static_cast<ValuedEdge<T>*>(e)->GetValue();
}
#endif
