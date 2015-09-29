#ifndef GRAPH_ADJACENCYMATRIXORIENTED_H
#define GRAPH_ADJACENCYMATRIXORIENTED_H

#include "IOriented.h"

class AdjacencyMatrixOriented:public IOriented
{
    AdjacencyMatrixOriented(unsigned int size, const std::vector<Edge*>& edges);
    AdjacencyMatrixOriented(unsigned int size);
    AdjacencyMatrixOriented(const AdjacencyMatrixOriented& graph);
    AdjacencyMatrixOriented& operator=(const AdjacencyMatrixOriented& graph);
    AdjacencyMatrixOriented* Clone() const;

    virtual ~AdjacencyMatrixOriented();

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
    void DeleteAllEdges();
protected:
    unsigned int size;
    std::vector< std::vector<Edge*> >* adjacencyMatrix;

    bool AddEdge(Edge *edge);
    void InitializeNewGraph(unsigned int size);
};

#endif
