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

class Graph
{
    public:
        Graph(unsigned int size, std::vector<Edge> edges);
        Graph(unsigned int size, std::string matrix);

        unsigned int Size();
        std::vector<unsigned int> GetChilds(unsigned int vertex);
        bool AddUnorientedEdge(int from, int to); //return false if already exists
        bool CheckEdge(int from, int to);
        size_t NumberOfEdges();
    private:
        unsigned int size;
        std::vector<Edge> edges;
};

#endif
