#ifndef GRAPH_BASEGRAPH_H
#define GRAPH_BASEGRAPH_H

#include "IGraph.h"
#include <functional>

class BaseGraph //Wrapper for different IGraph implementations
{
    public:
        virtual BaseGraph* clone() const = 0;
        virtual ~BaseGraph() {}

        unsigned long long size() const;
        unsigned long long numberOfEdges() const;
        std::vector<unsigned long long>* getChilds(unsigned long long vertex) const;
        std::vector<unsigned long long>* getParents(unsigned long long vertex) const;
        std::vector<Edge*>* getAllEdges() const;
        std::vector<Edge*>* getAllEdgesSorted(); //const;
        void addNodes(size_t amount);
        bool addEdge(long long from, long long to);
        bool addEdge(Edge* edge);
        bool checkEdge(long long from, long long to);
        Edge* getEdge(long long from, long long to);
        void deleteEdge(long long from, long long to);
        void deleteNodeEdges(unsigned long long v);
        void deleteAllEdges();
        void initializeNewGraph(unsigned long long size);
    protected:
        IGraph* graph_;

        BaseGraph(IGraph& graph);
        BaseGraph(IGraph* graph);
        BaseGraph(unsigned long long size, IGraph& graph_);
        BaseGraph(unsigned long long size, IGraph* graph_);
};

#endif
