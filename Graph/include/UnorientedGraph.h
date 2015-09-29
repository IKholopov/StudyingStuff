#ifndef _UNORIENTED_GRAPH_H__
#define _UNORIENTED_GRAPH_H__

#include <vector>
#include <fstream>
#include"BaseGraph.h"

class UnorientedGraph: public BaseGraph
{
    public:
        UnorientedGraph(IGraph& graph):BaseGraph(graph) {};
        UnorientedGraph(unsigned int size, IGraph& graph):BaseGraph(size, graph) {};
        UnorientedGraph(IGraph* graph):BaseGraph(graph) {};
        UnorientedGraph(unsigned int size, IGraph* graph):BaseGraph(size, graph) {};
        UnorientedGraph* Clone() const;
        virtual ~UnorientedGraph();

        virtual void ReadFromFile(std::ifstream& file);
        void WriteToFile(std::string filename);
        virtual void WriteToFile(std::ofstream& file);
        virtual void RandomizeGraph(double probability);
        void NormalizeEdges();
};

#endif
