#ifndef GRAPH_ADJACENCYMATRIXUNORIENTED_H
#define GRAPH_ADJACENCYMATRIXUNORIENTED_H

#include "IUnoriented.h"

class AdjacencyMatrixUnoriented:public IUnoriented
{
    public:
        AdjacencyMatrixUnoriented();
        AdjacencyMatrixUnoriented(unsigned long long size, const std::vector<Edge*>& edges);
        AdjacencyMatrixUnoriented(unsigned long long size);
        AdjacencyMatrixUnoriented(const AdjacencyMatrixUnoriented& graph);
        AdjacencyMatrixUnoriented& operator=(const AdjacencyMatrixUnoriented& graph);
        AdjacencyMatrixUnoriented* Clone() const;

        ~AdjacencyMatrixUnoriented();

        unsigned long long Size() const;
        unsigned long long NumberOfEdges() const;
        std::vector<unsigned long long> GetChilds(unsigned long long vertex) const;
        std::vector<unsigned long long> GetParents(unsigned long long vertex) const;
        std::vector<Edge*> GetAllEdges() const;
        std::vector<Edge*> GetAllEdgesSorted();
        void AddNodes(size_t amount);                               //Append to and
        bool AddEdge(long long from, long long to);
        bool AddEdge(Edge* edge);
        bool CheckEdge(long long from, long long to);
        Edge* GetEdge(long long from, long long to);
        Edge* RemoveEdge(long long from, long long to);
        void DeleteEdge(unsigned long long from, unsigned long long to);
        void DeleteNodeEdges(unsigned long long v);
        void DeleteAllEdges();
        void InitializeNewGraph(unsigned long long size);
    protected:
        unsigned long long size;
        std::vector< std::vector<Edge*> >* adjacencyMatrix;
};

#endif
