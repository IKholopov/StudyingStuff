#ifndef __GRAPH_DOUBLE_VALUED_EDGE_H__
#define __GRAPH_DOUBLE_VALUED_EDGE_H__

#include "Graph.h"

class GraphDoubleValuedEdge: public Graph
{
    public:
        GraphDoubleValuedEdge(unsigned int size): Graph(size) {}
        virtual ~GraphDoubleValuedEdge();

        virtual void ReadFromFile(std::ifstream& file);
        virtual void WriteToFile(std::ofstream& file);
        virtual void RandomizeGraph(double probability);
        virtual void RandomizeUnorientedGraph(double probability);
        bool AddEdge(int from, int to, int value);
        bool AddUnorientedEdge(int from, int to, int value);                   //return false if already exists
        int GetEdgeValue(int from, int to);
        int BFS(unsigned int source, unsigned int destination);
        int Dijkstra(unsigned int source, unsigned int destination);
};

#endif
