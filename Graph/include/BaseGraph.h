#ifndef GRAPH_BASEGRAPH_H
#define GRAPH_BASEGRAPH_H

#include"IGraph.h"

class BaseGraph //Wrapper for different IGraph implementations
{
    public:
        virtual BaseGraph* Clone() const = 0;
        virtual ~BaseGraph() {}

        unsigned int Size() const;
        unsigned int NumberOfEdges() const;
        std::vector<unsigned int> GetChilds(unsigned int vertex) const;
        std::vector<unsigned int> GetParents(unsigned int vertex) const;
        std::vector<Edge*> GetAllEdges() const;
        std::vector<Edge*> GetAllEdgesSorted(); //const;
        void AddNodes(size_t amount);
        bool AddEdge(int from, int to);
        bool AddEdge(Edge* edge);
        bool CheckEdge(int from, int to);
        Edge* GetEdge(int from, int to);
        void DeleteAllEdges();
        void InitializeNewGraph(unsigned int size);
    protected:
        IGraph* graph;

        BaseGraph(IGraph& graph);
        BaseGraph(IGraph* graph);
        BaseGraph(unsigned int size, IGraph& graph);
        BaseGraph(unsigned int size, IGraph* graph);
};

#endif
