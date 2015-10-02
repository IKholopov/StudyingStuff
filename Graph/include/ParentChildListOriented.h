#ifndef GRAPH_PARENT_CHILD_LIST_ORIENTED
#define GRAPH_PARENT_CHILD_LIST_ORIENTED

#include "IOriented.h"
#include "IMultiGraph.h"

class ParentChildListOriented: public IMultiGraph
{
    public:
        ParentChildListOriented();
        ParentChildListOriented(unsigned long long size, std::vector<Edge*>& edges);
        ParentChildListOriented(unsigned long long size);
        ParentChildListOriented(const ParentChildListOriented& graph);
        ParentChildListOriented& operator=(const ParentChildListOriented& graph);
        ParentChildListOriented* Clone() const;

        ~ParentChildListOriented();

        unsigned long long Size() const;
        unsigned long long NumberOfEdges() const;
        std::vector<unsigned long long>* GetChilds(unsigned long long vertex) const;
        std::vector<unsigned long long>* GetParents(unsigned long long vertex) const;
        std::vector<Edge*>* GetAllEdges() const;
        const std::vector<Edge*>* GetAllEdgesConst() const;
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
        const std::vector<Edge *> *GetOutgoing(unsigned long long vertex) const;
        const std::vector<Edge *> *GetIngoing(unsigned long long vertex) const;
    protected:
        unsigned long long size;
        std::vector<Edge*> edges;
        std::vector<std::vector<Edge*>> ingoingEdges;
        std::vector<std::vector<Edge*>> outgoingEdges;
};

#endif
