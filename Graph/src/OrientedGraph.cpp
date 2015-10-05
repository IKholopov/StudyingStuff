#include "OrientedGraph.h"

#include <stdlib.h>
#include <algorithm>
#include <queue>
#include "GraphFileFormat.h"

BaseGraph* OrientedGraph::Clone() const
{
        return new OrientedGraph(this->graph->Clone());
}
OrientedGraph::~OrientedGraph()
{
    delete graph;
}
void OrientedGraph::ReadFromFile(std::ifstream& file)
{
    unsigned long long size, edgeSz;
    file >> size;
    this->graph->InitializeNewGraph(size);
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
    std::vector<Edge*>* edges = this->graph->GetAllEdges();
    file << this->Size() << std::endl;
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
    this->InitializeNewGraph(this->Size());
    for(long long i = 0; i < this->Size(); ++i)
        for(long long j = 0; j < this->Size(); ++j)
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
    std::vector<Color> vertexes (this->Size(), Color::White);
    std::queue<unsigned long long> q;
    q.push(source);
    while(!q.empty())
    {
        unsigned long long u = q.front();
        q.pop();
        if(vertexes[u] == Color::Black)
            continue;
        vertexes[u] = Color::Grey;
        auto childs = this->GetChilds(u);
        for(auto v = childs->begin(); v != childs->end(); ++v)
        {
            if(!edgeCondition(this->GetEdge(u, *v)))
                continue;
            if(!operation(u, *v, this->GetEdge(u, *v)))
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
