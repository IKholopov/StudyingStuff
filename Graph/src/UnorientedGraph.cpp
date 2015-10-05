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
    unsigned long long size, edgeSz;
    file >> size;
    this->InitializeNewGraph(size);
    file >> edgeSz;
    for(long long i = 0; i < edgeSz; ++i)
    {
        unsigned long long from, to;
        file >> from;
        file >> to;
        //TODO: this->AddEdge(from, to);
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
    std::vector<Edge*>* edges = this->graph->GetAllEdges();
    file << this->Size() << std::endl;
    file << edges->size() << std::endl;
    for(long long i = 0; i < edges->size(); ++i)
        file << edges->at(i)->From << " " << edges->at(i)->To << std::endl;
}
void UnorientedGraph::RandomizeGraph(double probability)
{
    this->InitializeNewGraph(this->Size());
    for(long long i = 0; i < this->Size() - 1; ++i)
        for(long long j = i; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (long long)(1.0 / probability)))
            {
                //TODO: this->AddEdge(i, j);
            }
        }
}
void UnorientedGraph::NormalizeEdges()
{
    std::vector<Edge*>* edges = this->graph->GetAllEdges();
    for(long long i = 0; i < edges->size(); ++i)
        if(edges->at(i)->From > edges->at(i)->To)
        {
            unsigned long long temp = edges->at(i)->From;
            edges->at(i)->From = edges->at(i)->To;
            edges->at(i)->To = temp;
        }
    delete edges;
}
