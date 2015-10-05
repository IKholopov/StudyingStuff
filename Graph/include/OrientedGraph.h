#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "BaseGraph.h"

class OrientedGraph: public BaseGraph
{
    public:
        OrientedGraph(IGraph& graph):BaseGraph(graph) {};
        OrientedGraph(unsigned long long size, IGraph& graph):BaseGraph(size, graph) {};
        OrientedGraph(IGraph* graph):BaseGraph(graph) {};
        OrientedGraph(unsigned long long size, IGraph* graph):BaseGraph(size, graph) {};
        BaseGraph* Clone() const;

        virtual ~OrientedGraph();

        virtual void ReadFromFile(std::ifstream& file);
        void WriteToFile(std::string filename);
        virtual void WriteToFile(std::ofstream& file);
        virtual void RandomizeGraph(double probability);
        virtual void BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* e)> operation,
                         std::function<bool(Edge* edge)> edgeCondition);
};

#endif
