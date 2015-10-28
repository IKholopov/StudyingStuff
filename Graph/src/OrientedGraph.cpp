#include "OrientedGraph.h"

#include <stdlib.h>
#include <algorithm>
#include <queue>
#include "GraphFileFormat.h"

BaseGraph* OrientedGraph::clone() const
{
        return new OrientedGraph(this->graph_->clone());
}
OrientedGraph::~OrientedGraph()
{
    delete graph_;
}
void OrientedGraph::ReadFromFile(std::ifstream& file)
{
    unsigned long long size, edgeSz;
    file >> size;
    this->graph_->initializeNewGraph(size);
    file >> edgeSz;
    for(long long i = 0; i < edgeSz; ++i)
    {
        unsigned long long from, to;
        file >> from;
        file >> to;
        // TODO: this->AddEdge(from, to);
    }
}
void OrientedGraph::WriteToFile(std::ofstream &file)
{
    std::vector<Edge*>* edges = this->graph_->getAllEdges();
    file << this->size() << std::endl;
    file << edges->size() << std::endl;
    for(long long i = 0; i < edges->size(); ++i)
        file << edges->at(i)->From << " " << edges->at(i)->To << std::endl;
}
void OrientedGraph::WriteToFile(std::string filename)
{
    std::ofstream file(filename.c_str());
    this->WriteToFile(file);
    file.close();
}
void OrientedGraph::RandomizeGraph(double probability)
{
    this->initializeNewGraph(this->size());
    for(long long i = 0; i < this->size(); ++i)
        for(long long j = 0; j < this->size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (long long)(1.0 / probability)))
            {
                //TODO: this->AddEdge(i, j);
            }
        }
}
void OrientedGraph::BFS(unsigned long long source, std::function<bool(unsigned long long, unsigned long long, Edge* edge)> operation,
                        std::function<bool(Edge* edge)> edgeCondition)
{
    enum Color{White, Grey, Black};
    std::vector<Color> vertexes (this->size(), Color::White);
    std::queue<unsigned long long> q;
    q.push(source);
    while(!q.empty())
    {
        unsigned long long u = q.front();
        q.pop();
        if(vertexes[u] == Color::Black)
            continue;
        vertexes[u] = Color::Grey;
        auto childs = this->getChilds(u);
        for(auto v = childs->begin(); v != childs->end(); ++v)
        {
            if(!edgeCondition(this->getEdge(u, *v)))
                continue;
            if(!operation(u, *v, this->getEdge(u, *v)))
            {
                q.push(*v);
                break;
            }
            q.push(*v);
        }
        vertexes[u] = Color::Black;
        delete childs;
    }
}
