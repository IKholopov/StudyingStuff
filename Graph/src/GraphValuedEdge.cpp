#include "GraphValuedEdge.h"

#include <stdlib.h>
#include <queue>
#include "GraphFileFormat.h"

struct EdgeComparator: public std::binary_function<std::pair<int, int>, std::pair<int, int>, bool>
  {
    bool operator()(const std::pair<int, int>& __x, const std::pair<int, int>& __y) const
    {
        return __x.first > __y.first;
    }
  };

GraphValuedEdge::~GraphValuedEdge()
{
}

void GraphValuedEdge::ReadFromFile(std::ifstream &file)
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
void GraphValuedEdge::WriteToFile(std::ofstream &file)
{
    file << GR_TYPE_GRAPH_VALUED_EDGE<< std::endl;
    file << this->size << std::endl;
    file << "<EDGES>" << std::endl;
    file << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
        file << edges[i]->From << " " << edges[i]->To << " " <<
                ((ValuedEdge*)edges[i])->GetValue() << std::endl;
    file << "</EDGES>" << std::endl;
}
void GraphValuedEdge::RandomizeGraph(double probability)
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
void GraphValuedEdge::RandomizeUnorientedGraph(double probability)
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
bool GraphValuedEdge::AddEdge(int from, int to, int value)
{
    return this->Graph::AddEdge(new ValuedEdge(from, to, value));
}
bool GraphValuedEdge::AddUnorientedEdge(int from, int to, int value)
{
    return this->Graph::AddUnorientedEdge(new ValuedEdge(from, to, value));
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
int GraphValuedEdge::BFS(unsigned int source, unsigned int destination)
{
    std::priority_queue< std::pair<int, int>, std::vector< std::pair<int, int> >,   //first - prioriry
            EdgeComparator> q;                                                     //second - vertex
    int d[this->size];
    bool visited[this->size];
    for(int i = 0; i < this->size; ++i)
    {
        visited[i] = false;
        d[i] = -1;
    }
    d[source] = 0;
    q.push(std::pair<int, int>(0, source));
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
            if(d[vs[i]] == -1 || ((ValuedEdge*)this->GetEdge(u, vs[i]))->GetValue() + d[u] < d[vs[i]])
                d[vs[i]] = ((ValuedEdge*)this->GetEdge(u, vs[i]))->GetValue() + d[u];


            if(!(visited[vs[i]]))
            {
                q.push(std::pair<int, int> (((ValuedEdge*)this->GetEdge(u, vs[i]))->GetValue() + d[u],
                                            vs[i]));
            }
        }
    }
    return d[destination];
}
