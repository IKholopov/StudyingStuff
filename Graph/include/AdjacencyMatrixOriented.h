#ifndef GRAPH_ADJACENCYMATRIXORIENTED_H
#define GRAPH_ADJACENCYMATRIXORIENTED_H

#include "IOriented.h"

class AdjacencyMatrixOriented:public IOriented
{
    public:
        AdjacencyMatrixOriented();
        AdjacencyMatrixOriented(unsigned int size, std::vector<Edge*>& edges);
        AdjacencyMatrixOriented(unsigned int size);
        AdjacencyMatrixOriented(const AdjacencyMatrixOriented& graph);
        AdjacencyMatrixOriented& operator=(const AdjacencyMatrixOriented& graph);
        AdjacencyMatrixOriented* Clone() const;

        ~AdjacencyMatrixOriented();

        unsigned int Size() const;
        unsigned int NumberOfEdges() const;
        std::vector<unsigned int> GetChilds(unsigned int vertex) const;
        std::vector<unsigned int> GetParents(unsigned int vertex) const;
        std::vector<Edge*> GetAllEdges() const;
        std::vector<Edge*> GetAllEdgesSorted();
        void AddNodes(size_t amount);                               //Append to and
        bool AddEdge(int from, int to);
        bool AddEdge(Edge* edge);
        bool CheckEdge(int from, int to);
        Edge* GetEdge(int from, int to);
        Edge* RemoveEdge(int from, int to);
        void DeleteEdge(unsigned int from, unsigned int to);
        void DeleteNodeEdges(unsigned int v);
        void DeleteAllEdges();
        void InitializeNewGraph(unsigned int size);
    protected:
        unsigned int size;
        std::vector< std::vector<Edge*> >* adjacencyMatrix;
};

#endif
