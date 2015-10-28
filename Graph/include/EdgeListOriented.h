#ifndef GRAPH_EDGELISTORIENTED_H
#define GRAPH_EDGELISTORIENTED_H

#include "IOriented.h"

class EdgeListOriented:public IOriented
{
    public:
        EdgeListOriented();
        EdgeListOriented(unsigned long long size_, std::vector<Edge*>& edges_);
        EdgeListOriented(unsigned long long size_);
        EdgeListOriented(const EdgeListOriented& graph);
        EdgeListOriented& operator=(const EdgeListOriented& graph);
        EdgeListOriented* clone() const;

        ~EdgeListOriented();

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
        std::vector<Edge*> edges_;
};

#endif
