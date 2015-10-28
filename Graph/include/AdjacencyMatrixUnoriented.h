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
        AdjacencyMatrixUnoriented* clone() const;

        ~AdjacencyMatrixUnoriented();

        unsigned long long size() const;
        unsigned long long numberOfEdges() const;
        std::vector<unsigned long long>* getChilds(unsigned long long vertex) const;
        std::vector<unsigned long long>* getParents(unsigned long long vertex) const;
        std::vector<Edge*>* getAllEdges() const;
        std::vector<Edge*>* getAllEdgesSorted();
        void addNodes(size_t amount);                               //Append to and
        bool addEdge(long long from, long long to);
        bool addEdge(Edge* edge);
        bool checkEdge(long long from, long long to);
        Edge* getEdge(long long from, long long to);
        Edge* removeEdge(long long from, long long to);
        void deleteEdge(unsigned long long from, unsigned long long to);
        void deleteNodeEdges(unsigned long long v);
        void deleteAllEdges();
        void initializeNewGraph(unsigned long long size_);
    protected:
        unsigned long long size_;
        std::vector< std::vector<Edge*> >* adjacencyMatrix_;
};

#endif
