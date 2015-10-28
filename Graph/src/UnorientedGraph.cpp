#include "UnorientedGraph.h"
#include <algorithm>

UnorientedGraph *UnorientedGraph::clone() const
{
    return new UnorientedGraph(this->graph_->clone());
}
UnorientedGraph::~UnorientedGraph()
{
    delete graph_;
}

void UnorientedGraph::readFromFile(std::ifstream &file)
{
    unsigned long long size, edgeSz;
    file >> size;
    this->initializeNewGraph(size);
    file >> edgeSz;
    for(long long i = 0; i < edgeSz; ++i)
    {
        unsigned long long from, to;
        file >> from;
        file >> to;
        //TODO: this->AddEdge(from, to);
    }
}
void UnorientedGraph::writeToFile(std::string filename)
{
    std::ofstream file(filename.c_str());
    this->writeToFile(file);
    file.close();
}
void UnorientedGraph::writeToFile(std::ofstream &file)
{
    std::vector<Edge*>* edges = this->graph_->getAllEdges();
    file << this->size() << std::endl;
    file << edges->size() << std::endl;
    for(long long i = 0; i < edges->size(); ++i)
        file << edges->at(i)->From << " " << edges->at(i)->To << std::endl;
}
void UnorientedGraph::randomizeGraph(double probability)
{
    this->initializeNewGraph(this->size());
    for(long long i = 0; i < this->size() - 1; ++i)
        for(long long j = i; j < this->size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (long long)(1.0 / probability)))
            {
                //TODO: this->AddEdge(i, j);
            }
        }
}
void UnorientedGraph::normalizeEdges()
{
    std::vector<Edge*>* edges = this->graph_->getAllEdges();
    for(long long i = 0; i < edges->size(); ++i)
        if(edges->at(i)->From > edges->at(i)->To)
        {
            unsigned long long temp = edges->at(i)->From;
            edges->at(i)->From = edges->at(i)->To;
            edges->at(i)->To = temp;
        }
    delete edges;
}
