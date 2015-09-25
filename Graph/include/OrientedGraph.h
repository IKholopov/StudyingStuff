#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "IGraph.h"

class OrientedGraph: public IGraph
{
    public:
        OrientedGraph(unsigned int size, const std::vector<Edge*>& edges);
        OrientedGraph(unsigned int size);
        OrientedGraph(const OrientedGraph& graph);
        OrientedGraph& operator=(const OrientedGraph& graph);
        virtual ~OrientedGraph();

        unsigned int Size() const;
        unsigned int NumberOfEdges() const;
        std::vector<unsigned int> GetChilds(unsigned int vertex) const;
        std::vector<unsigned int> GetParents(unsigned int vertex) const;
        std::vector<Edge*> GetAllEdges() const;
        std::vector<Edge*> GetAllEdgesSorted();
        virtual void ReadFromFile(std::ifstream& file);
        void WriteToFile(std::string filename);
        virtual void WriteToFile(std::ofstream& file);
        virtual void RandomizeGraph(double probability);
        void AddNodes(size_t amount);                               //Append to and
        bool AddEdge(int from, int to);
        bool CheckEdge(int from, int to);
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
