#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "IGraph.h"

class Graph: public IGraph
{
    public:
        Graph(unsigned int size, const std::vector<Edge*>& edges);
        Graph(unsigned int size);
        virtual ~Graph();

        unsigned int Size();
        unsigned int NumberOfEdges();
        std::vector<unsigned int> GetChilds(unsigned int vertex);
        std::vector<unsigned int> GetParents(unsigned int vertex);
        std::vector<Edge*> GetAllEdges();
        //std::vector<Edge*> GetSortedUnorientedEdges();
        virtual void ReadFromFile(std::ifstream& file);
        void WriteToFile(std::string filename);
        virtual void WriteToFile(std::ofstream& file);
        virtual void RandomizeGraph(double probability);
        //virtual void RandomizeUnorientedGraph(double probability);
        void AddNodes(size_t amount);                               //Append to and
        //bool AddUnorientedEdge(int from, int to);                   //return false if already exists
        bool AddEdge(int from, int to);
        bool CheckEdge(int from, int to);
        Edge* GetEdge(int from, int to);
        void DeleteAllEdges();
    protected:
        unsigned int size;
        std::vector<Edge*> edges;
        std::vector< std::vector<Edge*> >* adjacencyMatrix;           //index in 'edges', -1 == doesn't exist

        bool AddEdge(Edge *edge);
        //bool AddUnorientedEdge(Edge *edge);
        void InitializeNewGraph(unsigned int size);
};

#endif
