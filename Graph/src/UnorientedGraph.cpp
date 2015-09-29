#include "UnorientedGraph.h"
#include <algorithm>

UnorientedGraph *UnorientedGraph::Clone() const
{
    return new UnorientedGraph(this->graph->Clone());
}
UnorientedGraph::~UnorientedGraph()
{
    delete graph;
}

void UnorientedGraph::ReadFromFile(std::ifstream &file)
{
    unsigned int size, edgeSz;
    file >> size;
    this->InitializeNewGraph(size);
    file >> edgeSz;
    for(int i = 0; i < edgeSz; ++i)
    {
        unsigned int from, to;
        file >> from;
        file >> to;
        this->AddEdge(from, to);
    }
}
void UnorientedGraph::WriteToFile(std::string filename)
{
    std::ofstream file(filename.c_str());
    this->WriteToFile(file);
    file.close();
}
void UnorientedGraph::WriteToFile(std::ofstream &file)
{
    std::vector<Edge*> edges = this->graph->GetAllEdges();
    file << this->Size() << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << std::endl;
}
void UnorientedGraph::RandomizeGraph(double probability)
{
    this->InitializeNewGraph(this->Size());
    for(int i = 0; i < this->Size() - 1; ++i)
        for(int j = i; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddEdge(i, j);
            }
        }
}
void UnorientedGraph::NormalizeEdges()
{
    std::vector<Edge*> edges = this->graph->GetAllEdges();
    for(int i = 0; i < edges.size(); ++i)
        if(edges[i]->From > edges[i]->To)
        {
            unsigned int temp = edges[i]->From;
            edges[i]->From = edges[i]->To;
            edges[i]->To = temp;
        }
}
