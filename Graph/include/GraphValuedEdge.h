#ifndef __GRAPH_VALUED_EDGE_H__
#define __GRAPH_VALUED_EDGE_H__

#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "Graph.h"

class ValuedEdge: public Edge
{
    public:
        ValuedEdge(unsigned int from, unsigned int to, int value):Edge(from, to)
        {
            this->value = value;
        }
        int GetValue()
        {
            return value;
        }
        virtual Edge* GetReversed()
        {
            return new ValuedEdge(To, From, value);
        }

    private:
        int value;
};

class GraphValuedEdge: public Graph
{
    public:
        GraphValuedEdge(unsigned int size): Graph(size) {}
        virtual ~GraphValuedEdge();

        virtual void ReadFromFile(std::ifstream& file);
        virtual void WriteToFile(std::ofstream& file);
        virtual void RandomizeGraph(double probability);
        virtual void RandomizeUnorientedGraph(double probability);
        bool AddEdge(int from, int to, int value);
        bool AddUnorientedEdge(int from, int to, int value);                   //return false if already exists
        int BFS(unsigned int source, unsigned int destination);
};

#endif

