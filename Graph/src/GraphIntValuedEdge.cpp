#include "GraphIntValuedEdge.h"

#include <stdlib.h>
#include <queue>
#include <limits>
#include "GraphFileFormat.h"
#include "MinPQ.hpp"
#include "ValuedEdge.hpp"

GraphIntValuedEdge::~GraphIntValuedEdge()
{
}

void GraphIntValuedEdge::ReadFromFile(std::ifstream &file)
{
    unsigned int size, edgeSz;
    file >> size;
    this->Graph::InitializeNewGraph(size);
    std::string s;
    std::getline(file, s);
    std::getline(file, s);
    if(s != "<EDGES>")
        throw std::exception();
    file >> edgeSz;
    for(int i = 0; i < edgeSz; ++i)
    {
        unsigned int from, to;
        int vlaue;
        file >> from;
        file >> to;
        file >> vlaue;
        this->AddEdge(from, to, vlaue);
    }
    std::getline(file, s);
    std::getline(file, s);
    if(s != "</EDGES>")
        throw std::exception();
}
void GraphIntValuedEdge::WriteToFile(std::ofstream &file)
{
    file << GR_TYPE_GRAPH_VALUED_EDGE<< std::endl;
    file << this->size << std::endl;
    file << "<EDGES>" << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << " " <<
                ((ValuedEdge<int>*)edges[i])->GetValue() << std::endl;
    file << "</EDGES>" << std::endl;
}
void GraphIntValuedEdge::RandomizeGraph(double probability)
{
    this->InitializeNewGraph(this->size);
    for(int i = 0; i < this->Size(); ++i)
        for(int j = 0; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddEdge(i, j, rand() % 256);
            }
        }
}
void GraphIntValuedEdge::RandomizeUnorientedGraph(double probability)
{
    this->InitializeNewGraph(this->size);
    for(int i = 0; i < this->Size() - 1; ++i)
        for(int j = i; j < this->Size(); ++j)
        {
            if(j == i)
                continue;
            if(!(rand() % (int)(1.0 / probability)))
            {
                this->AddUnorientedEdge(i, j, rand() % 256);
            }
        }
}
bool GraphIntValuedEdge::AddEdge(int from, int to, int value)
{
    return this->Graph::AddEdge(new ValuedEdge<int>(from, to, value));
}
bool GraphIntValuedEdge::AddUnorientedEdge(int from, int to, int value)
{
    return this->Graph::AddUnorientedEdge(new ValuedEdge<int>(from, to, value));
}
int GraphIntValuedEdge::GetEdgeValue(int from, int to)
{
    Edge* e = this->GetEdge(from, to);
    if(e == NULL)
        throw std::exception();
    return ((ValuedEdge<int>*)e)->GetValue();
}
int ValuedEdgeComparator(const void* a, const void* b)
{
    int* eA = (int*)a;
    int* eB = (int*)b;
    if(eA > eB)
        return 1;
    if(eA == eB)
        return 0;
    return -1;
}
int GraphIntValuedEdge::BFS(unsigned int source, unsigned int destination)
{
    //std::priority_queue< std::pair<int, int>, std::vector< std::pair<int, int> >,   //first - prioriry
      //      EdgeComparator> q;                                                     //second - vertex
    MinPQ<unsigned int> q;
    int d[this->size];
    bool visited[this->size];
    for(int i = 0; i < this->size; ++i)
    {
        visited[i] = false;
        d[i] = -1;
    }
    d[source] = 0;
    q.push(std::pair<unsigned int, int>(0, source));
    while(q.size() > 0)
    {
        std::pair<int, int> next = q.top();
        q.pop();
        int pr = next.first;
        int u = next.second;
        if(visited[u])
            continue;
        visited[u] = true;
        std::vector<unsigned int> vs = this->GetChilds(u);
        for(int i = 0; i < vs.size(); ++i)
        {
            if(d[vs[i]] == -1 || ((ValuedEdge<int>*)this->GetEdge(u, vs[i]))->GetValue() + d[u] < d[vs[i]])
                d[vs[i]] = ((ValuedEdge<int>*)this->GetEdge(u, vs[i]))->GetValue() + d[u];


            if(!(visited[vs[i]]))
            {
                q.push(std::pair<unsigned int, int> (((ValuedEdge<int>*)this->GetEdge(u, vs[i]))->GetValue() + d[u],
                                            vs[i]));
            }
        }
    }
    return d[destination];
}
int GraphIntValuedEdge::Dijkstra(unsigned int source, unsigned int destination)
{
    MinPQ<unsigned int> q;
    unsigned int d[this->size];
    for(int i = 0; i < this->size; ++i)
    {
        q.push(std::pair<unsigned int, int>(INT32_MAX, i));
        d[i] = -1;
    }
    q.DecreaseKeyAt(source, 0);
    d[source] = 0;
    int u = source;
    int dist = 0;
    while (q.size() > 0) {
        for(int i = 0; i < q.size(); ++i)
            if(this->adjacencyMatrix->at(u).at(q.GetAt(i).second) != -1)
            {
                if(((ValuedEdge<int>*)this->GetEdge(u, q.GetAt(i).second))->GetValue() + dist < q.GetAt(i).first)
                    q.DecreaseKey(i, ((ValuedEdge<int>*)this->GetEdge(u, q.GetAt(i).second))->GetValue() + dist);
            }
        std::pair<unsigned int, int> next = q.pop();
        u = next.second;
        dist = next.first;
        d[u] = dist;
    }
    return d[destination];
}
