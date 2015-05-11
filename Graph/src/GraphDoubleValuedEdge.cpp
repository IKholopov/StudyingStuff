#include "GraphDoubleValuedEdge.h"

#include <stdlib.h>
#include <queue>
#include <limits>
#include "GraphFileFormat.h"
#include "MinPQ.hpp"
#include "ValuedEdge.hpp"

GraphDoubleValuedEdge::~GraphDoubleValuedEdge()
{
}

void GraphDoubleValuedEdge::ReadFromFile(std::ifstream &file)
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
        double vlaue;
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
void GraphDoubleValuedEdge::WriteToFile(std::ofstream &file)
{
    file << GR_TYPE_GRAPH_VALUED_EDGE<< std::endl;
    file << this->size << std::endl;
    file << "<EDGES>" << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << " " <<
                ((ValuedEdge<double>*)edges[i])->GetValue() << std::endl;
    file << "</EDGES>" << std::endl;
}
void GraphDoubleValuedEdge::RandomizeGraph(double probability)
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
void GraphDoubleValuedEdge::RandomizeUnorientedGraph(double probability)
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
bool GraphDoubleValuedEdge::AddEdge(int from, int to, int value)
{
    return this->Graph::AddEdge(new ValuedEdge<int>(from, to, value));
}
bool GraphDoubleValuedEdge::AddUnorientedEdge(int from, int to, int value)
{
    return this->Graph::AddUnorientedEdge(new ValuedEdge<int>(from, to, value));
}
int GraphDoubleValuedEdge::GetEdgeValue(int from, int to)
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
int GraphDoubleValuedEdge::BFS(unsigned int source, unsigned int destination)
{
    //std::priority_queue< std::pair<int, int>, std::vector< std::pair<int, int> >,   //first - prioriry
      //      EdgeComparator> q;                                                     //second - vertex
    MinPQ<double> q;
    double d[this->size];
    bool visited[this->size];
    for(int i = 0; i < this->size; ++i)
    {
        visited[i] = false;
        d[i] = -1;
    }
    d[source] = 0;
    q.push(std::pair<double, int>(0, source));
    while(q.size() > 0)
    {
        std::pair<double, int> next = q.top();
        q.pop();
        double pr = next.first;
        int u = next.second;
        if(visited[u])
            continue;
        visited[u] = true;
        std::vector<unsigned int> vs = this->GetChilds(u);
        for(int i = 0; i < vs.size(); ++i)
        {
            if(d[vs[i]] == -1 || ((ValuedEdge<double>*)this->GetEdge(u, vs[i]))->GetValue() + d[u] < d[vs[i]])
                d[vs[i]] = ((ValuedEdge<double>*)this->GetEdge(u, vs[i]))->GetValue() + d[u];


            if(!(visited[vs[i]]))
            {
                q.push(std::pair<double, int> (((ValuedEdge<double>*)this->GetEdge(u, vs[i]))->GetValue() + d[u],
                                            vs[i]));
            }
        }
    }
    return d[destination];
}
int GraphDoubleValuedEdge::Dijkstra(unsigned int source, unsigned int destination)
{
    MinPQ<double> q;
    double d[this->size];
    for(int i = 0; i < this->size; ++i)
    {
        q.push(std::pair<double, int>(INT32_MAX, i));
        d[i] = -1;
    }
    q.DecreaseKeyAt(source, 0);
    d[source] = 0;
    int u = source;
    double dist = 0;
    while (q.size() > 0) {
        for(int i = 0; i < q.size(); ++i)
            if(this->adjacencyMatrix->at(u).at(q.GetAt(i).second) != -1)
            {
                if(((ValuedEdge<double>*)this->GetEdge(u, q.GetAt(i).second))->GetValue() + dist < q.GetAt(i).first)
                    q.DecreaseKey(i, ((ValuedEdge<double>*)this->GetEdge(u, q.GetAt(i).second))->GetValue() + dist);
            }
        std::pair<double, int> next = q.pop();
        u = next.second;
        dist = next.first;
        d[u] = dist;
    }
    return d[destination];
}
