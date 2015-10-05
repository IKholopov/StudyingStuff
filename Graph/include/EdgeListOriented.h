#ifndef GRAPH_EDGELISTORIENTED_H
#define GRAPH_EDGELISTORIENTED_H

#include "IOriented.h"

class EdgeListOriented:public IOriented
{
    public:
        EdgeListOriented();
        EdgeListOriented(unsigned long long size, std::vector<Edge*>& edges);
        EdgeListOriented(unsigned long long size);
        EdgeListOriented(const EdgeListOriented& graph);
        EdgeListOriented& operator=(const EdgeListOriented& graph);
        EdgeListOriented* Clone() const;

        ~EdgeListOriented();

        unsigned long long Size() const;
        unsigned long long NumberOfEdges() const;
        std::vector<unsigned long long>* GetChilds(unsigned long long vertex) const;
        std::vector<unsigned long long>* GetParents(unsigned long long vertex) const;
        std::vector<Edge*>* GetAllEdges() const;
        std::vector<Edge*>* GetAllEdgesSorted();
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
        std::vector<Edge*> edges;
};

#endif
