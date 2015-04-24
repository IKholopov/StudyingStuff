#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <string>
#include <utility>

class Edge
{
    public:
        Edge(unsigned int from, unsigned int to)
        {
            this->From = from;
            this->To = to;
        }
        unsigned int From;
        unsigned int To;
};
template <class T>
class ValuedEdge: public Edge
{
    public:
        ValuedEdge(unsigned int from, unsigned int to, T value):Edge(from, to)
        {
            this->value = value;
        }

    private:
        T value;
};

class Graph
{
    public:
        Graph(unsigned int size, std::vector<Edge> edges);
        Graph(unsigned int size);
        virtual ~Graph();

        unsigned int Size();
        std::vector<unsigned int> GetChilds(unsigned int vertex);
        std::vector<unsigned int> GetParents(unsigned int vertex);
        bool AddUnorientedEdge(int from, int to); //return false if already exists
        bool AddEdge(int from, int to);
        bool CheckEdge(int from, int to);
        void DeleteAllEdges();
        size_t NumberOfEdges();
    protected:
        unsigned int size;
        std::vector<Edge> edges;
        std::vector< std::vector<int> >* adjacencyMatrix;           //index in 'edges', -1 == doesn't exist
    private:
        bool AddEdge(const Edge& edge);
};

#endif
