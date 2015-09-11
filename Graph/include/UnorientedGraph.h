#ifndef _UNORIENTED_GRAPH_H__
#define _UNORIENTED_GRAPH_H__

#include <vector>
#include <fstream>
#include"IGraph.h"

class UnorientedGraph:public IGraph
{
    public:
        UnorientedGraph(unsigned int size);
        virtual ~UnorientedGraph();

        unsigned int Size() const;
        unsigned int NumberOfEdges() const;
        virtual std::vector<unsigned int> GetChilds(unsigned int vertex) const;
        std::vector<unsigned int> GetParents(unsigned int vertex) const;
        std::vector<Edge*> GetAllEdges();
        std::vector<Edge*> GetAllEdgesSorted();
        virtual void ReadFromFile(std::ifstream& file);
        void WriteToFile(std::string filename);
        virtual void WriteToFile(std::ofstream& file);
        virtual void RandomizeGraph(double probability);
        void AddNodes(size_t amount);
        bool AddEdge(int from, int to);
        bool CheckEdge(int from, int to);
        void NormalizeEdges();
        Edge* GetEdge(int from, int to);
        void DeleteAllEdges();
    protected:
        unsigned int size;
        std::vector<Edge*> edges;
        std::vector< std::vector<Edge*> >* adjacencyMatrix;

        bool AddEdge(Edge *edge);
        void InitializeNewGraph(unsigned int size);
};

#endif
