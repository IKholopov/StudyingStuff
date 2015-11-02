#ifndef GRAPH_PARENT_CHILD_LIST_ORIENTED
#define GRAPH_PARENT_CHILD_LIST_ORIENTED

#include "IOriented.h"
#include "IMultiGraph.h"

class ParentChildListOriented: public IMultiGraph
{
    public:
        ParentChildListOriented();
        ParentChildListOriented(unsigned long long size_, std::vector<Edge*>& edges_);
        ParentChildListOriented(unsigned long long size_);
        ParentChildListOriented(const ParentChildListOriented& graph);
        ParentChildListOriented& operator=(const ParentChildListOriented& graph);
        ParentChildListOriented* clone() const;

        ~ParentChildListOriented();

        unsigned long long size() const;
        unsigned long long numberOfEdges() const;
        std::vector<unsigned long long>* getChilds(unsigned long long vertex) const;
        std::vector<unsigned long long>* getParents(unsigned long long vertex) const;
        std::vector<Edge*>* getAllEdges() const;
        const std::vector<Edge*>* getAllEdgesConst() const;
        std::vector<Edge*>* getAllEdgesSorted();
        void addNodes(size_t amount);                               //Append to and
        bool addEdge(long long from, long long to);
        bool addEdge(Edge* edge);
        bool checkEdge(long long from, long long to);
        Edge* getEdge(long long from, long long to);
        Edge* getEdge(long long from, long long to, unsigned long long id);
        Edge* getEdge(unsigned long long id);
        Edge* removeEdge(long long from, long long to);
        void deleteEdge(unsigned long long from, unsigned long long to);
        void deleteNodeEdges(unsigned long long v);
        void deleteAllEdges();
        void initializeNewGraph(unsigned long long size_);
        const std::vector<Edge*>* getOutgoing(unsigned long long vertex) const;
        const std::vector<Edge*>* getIngoing(unsigned long long vertex) const;
    protected:
        unsigned long long idCounter_;
        unsigned long long size_;
        std::vector<Edge*> edges_;
        std::vector<std::vector<Edge*>> ingoingEdges_;
        std::vector<std::vector<Edge*>> outgoingEdges_;
};

#endif
