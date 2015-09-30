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
    unsigned int size, edgeSz;
    file >> size;
    this->graph->InitializeNewGraph(size);
    file >> edgeSz;
    for(int i = 0; i < edgeSz; ++i)
    {
        unsigned int from, to;
        file >> from;
        file >> to;
        this->AddEdge(from, to);
    }
}
void OrientedGraph::WriteToFile(std::ofstream &file)
{
    std::vector<Edge*> edges = this->graph->GetAllEdges();
    file << this->Size() << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << std::endl;
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
    for(int i = 0; i < this->Size(); ++i)
        for(int j = 0; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddEdge(i, j);
            }
        }
}
void OrientedGraph::BFS(unsigned int source, std::function<void(unsigned int, unsigned int)> operation)
{
    enum Color{White, Grey, Black};
    std::vector<Color> vertexes (this->Size(), Color::White);
    std::queue<unsigned int> q;
    q.push(source);
    while(!q.empty())
    {
        unsigned int u = q.front();
        q.pop();
        if(vertexes[u] == Color::Black)
            continue;
        vertexes[u] = Color::Grey;
        auto childs = this->GetChilds(u);
        for(auto v: childs)
        {
            operation(u, v);
            q.push(v);
        }
    }
}
