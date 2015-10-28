#ifndef _UNORIENTED_GRAPH_H__
#define _UNORIENTED_GRAPH_H__

#include <vector>
#include <fstream>
#include"BaseGraph.h"

class UnorientedGraph: public BaseGraph
{
    public:
        UnorientedGraph(IGraph& graph):BaseGraph(graph) {};
        UnorientedGraph(unsigned long long size, IGraph& graph):BaseGraph(size, graph) {};
        UnorientedGraph(IGraph* graph):BaseGraph(graph) {};
        UnorientedGraph(unsigned long long size, IGraph* graph):BaseGraph(size, graph) {};
        UnorientedGraph* clone() const;
        virtual ~UnorientedGraph();

        virtual void readFromFile(std::ifstream& file);
        void writeToFile(std::string filename);
        virtual void writeToFile(std::ofstream& file);
        virtual void randomizeGraph(double probability);
        void normalizeEdges();
};

#endif
