#ifndef _IGRAPH_H__
#define _IGRAPH_H__

#include <vector>
#include <iostream>
#include"Edge.h"

class IGraph
{
    public:
        virtual ~IGraph() {};
        virtual unsigned int Size() const = 0;
        virtual unsigned int NumberOfEdges() const = 0;
        virtual IGraph* Clone() const = 0;
        virtual std::vector<unsigned int> GetChilds(unsigned int vertex) const = 0;
        virtual std::vector<unsigned int> GetParents(unsigned int vertex) const = 0;
        virtual void AddNodes(size_t amount) = 0;
        virtual bool AddEdge(int from, int to) = 0;
        virtual bool CheckEdge(int from, int to) = 0;
        virtual Edge* GetEdge(int from, int to) = 0;
        virtual std::vector<Edge*> GetAllEdges() const = 0;
        virtual std::vector<Edge*> GetAllEdgesSorted() = 0;
        virtual Edge* RemoveEdge(int from, int to);
        virtual void DeleteAllEdges() = 0;
    protected:
        virtual bool AddEdge(Edge *edge) = 0;
        virtual void InitializeNewGraph(unsigned int size) = 0;
};

#endif
