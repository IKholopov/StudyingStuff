#ifndef GRAPH_ADJACENCYMATRIXUNORIENTED_H
#define GRAPH_ADJACENCYMATRIXUNORIENTED_H

#include "IUnoriented.h"

class AdjacencyMatrixUnoriented:public IUnoriented
{
    public:
        AdjacencyMatrixUnoriented();
        AdjacencyMatrixUnoriented(unsigned int size, const std::vector<Edge*>& edges);
        AdjacencyMatrixUnoriented(unsigned int size);
        AdjacencyMatrixUnoriented(const AdjacencyMatrixUnoriented& graph);
        AdjacencyMatrixUnoriented& operator=(const AdjacencyMatrixUnoriented& graph);
        AdjacencyMatrixUnoriented* Clone() const;

        ~AdjacencyMatrixUnoriented();

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
