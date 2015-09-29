#ifndef GRAPH_ADJACENCYMATRIXUNORIENTED_H
#define GRAPH_ADJACENCYMATRIXUNORIENTED_H

#include "IUnoriented.h"

class AdjacencyMatrixUnoriented:public IUnoriented
{
    AdjacencyMatrixUnoriented(unsigned int size, const std::vector<Edge*>& edges);
    AdjacencyMatrixUnoriented(unsigned int size);
    AdjacencyMatrixUnoriented(const AdjacencyMatrixUnoriented& graph);
    AdjacencyMatrixUnoriented& operator=(const AdjacencyMatrixUnoriented& graph);
    AdjacencyMatrixUnoriented* Clone() const;

    virtual ~AdjacencyMatrixUnoriented();

    unsigned int Size() const;
    unsigned int NumberOfEdges() const;
    std::vector<unsigned int> GetChilds(unsigned int vertex) const;
    std::vector<unsigned int> GetParents(unsigned int vertex) const;
    std::vector<Edge*> GetAllEdges() const;
    std::vector<Edge*> GetAllEdgesSorted();
    void AddNodes(size_t amount);                               //Append to and
    bool AddEdge(int from, int to);
    bool CheckEdge(int from, int to);
    Edge* GetEdge(int from, int to);
    Edge* RemoveEdge(int from, int to);
    void DeleteAllEdges();
protected:
    unsigned int size;
    std::vector< std::vector<Edge*> >* adjacencyMatrix;

    bool AddEdge(Edge *edge);
    void InitializeNewGraph(unsigned int size);
};

#endif
