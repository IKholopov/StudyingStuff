#ifndef GRAPH_BASEGRAPH_H
#define GRAPH_BASEGRAPH_H

#include "IGraph.h"
#include <functional>

class BaseGraph //Wrapper for different IGraph implementations
{
    public:
        virtual BaseGraph* Clone() const = 0;
        virtual ~BaseGraph() {}

        unsigned long long Size() const;
        unsigned long long NumberOfEdges() const;
        std::vector<unsigned long long> GetChilds(unsigned long long vertex) const;
        std::vector<unsigned long long> GetParents(unsigned long long vertex) const;
        std::vector<Edge*> GetAllEdges() const;
        std::vector<Edge*> GetAllEdgesSorted(); //const;
        void AddNodes(size_t amount);
        bool AddEdge(long long from, long long to);
        bool AddEdge(Edge* edge);
        bool CheckEdge(long long from, long long to);
        Edge* GetEdge(long long from, long long to);
        void DeleteEdge(long long from, long long to);
        void DeleteNodeEdges(unsigned long long v);
        void DeleteAllEdges();
        void InitializeNewGraph(unsigned long long size);
    protected:
        IGraph* graph;

        BaseGraph(IGraph& graph);
        BaseGraph(IGraph* graph);
        BaseGraph(unsigned long long size, IGraph& graph);
        BaseGraph(unsigned long long size, IGraph* graph);
};

#endif
