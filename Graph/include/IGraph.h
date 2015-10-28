#ifndef _IGRAPH_H__
#define _IGRAPH_H__

#include <vector>
#include <iostream>
#include "Edge.h"

using namespace GraphLibrary;

class IGraph
{
    public:
        virtual ~IGraph() {}
        virtual unsigned long long size() const = 0;
        virtual unsigned long long numberOfEdges() const = 0;
        virtual IGraph* clone() const = 0;
        virtual std::vector<unsigned long long>* getChilds(unsigned long long vertex) const = 0;
        virtual std::vector<unsigned long long>* getParents(unsigned long long vertex) const = 0;
        virtual void addNodes(size_t amount) = 0;
        virtual bool checkEdge(long long from, long long to) = 0;
        virtual Edge* getEdge(long long from, long long to) = 0;
        virtual std::vector<Edge*>* getAllEdges() const = 0;
        virtual std::vector<Edge*>* getAllEdgesSorted() = 0;
        virtual Edge* removeEdge(long long from, long long to) = 0;
        virtual void deleteEdge(unsigned long long from, unsigned long long to) = 0;
        virtual void deleteNodeEdges(unsigned long long v) = 0;
        virtual void deleteAllEdges() = 0;
        virtual void initializeNewGraph(unsigned long long size_) = 0;
        virtual bool addEdge(Edge *edge) = 0;
};

#endif
