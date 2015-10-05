#ifndef _IGRAPH_H__
#define _IGRAPH_H__

#include <vector>
#include <iostream>
#include "Edge.h"

class IGraph
{
    public:
        virtual ~IGraph() {}
        virtual unsigned long long Size() const = 0;
        virtual unsigned long long NumberOfEdges() const = 0;
        virtual IGraph* Clone() const = 0;
        virtual std::vector<unsigned long long>* GetChilds(unsigned long long vertex) const = 0;
        virtual std::vector<unsigned long long>* GetParents(unsigned long long vertex) const = 0;
        virtual void AddNodes(size_t amount) = 0;
        virtual bool CheckEdge(long long from, long long to) = 0;
        virtual Edge* GetEdge(long long from, long long to) = 0;
        virtual std::vector<Edge*>* GetAllEdges() const = 0;
        virtual std::vector<Edge*>* GetAllEdgesSorted() = 0;
        virtual Edge* RemoveEdge(long long from, long long to) = 0;
        virtual void DeleteEdge(unsigned long long from, unsigned long long to) = 0;
        virtual void DeleteNodeEdges(unsigned long long v) = 0;
        virtual void DeleteAllEdges() = 0;
        virtual void InitializeNewGraph(unsigned long long size) = 0;
        virtual bool AddEdge(Edge *edge) = 0;
};

#endif
