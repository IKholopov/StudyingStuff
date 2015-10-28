#ifndef GRAPH_ADJACENCYMATRIXORIENTED_H
#define GRAPH_ADJACENCYMATRIXORIENTED_H

#include "IOriented.h"

class AdjacencyMatrixOriented:public IOriented
{
    public:
        AdjacencyMatrixOriented();
        AdjacencyMatrixOriented(unsigned long long size_, std::vector<Edge*>& edges);
        AdjacencyMatrixOriented(unsigned long long size_);
        AdjacencyMatrixOriented(const AdjacencyMatrixOriented& graph);
        AdjacencyMatrixOriented& operator=(const AdjacencyMatrixOriented& graph);
        AdjacencyMatrixOriented* clone() const;

        ~AdjacencyMatrixOriented();

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
