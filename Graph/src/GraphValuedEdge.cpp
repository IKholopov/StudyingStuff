#include "GraphValuedEdge.h"

#include <stdlib.h>
#include "PriorityQueue.h"
#include "GraphFileFormat.h"


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
    /*PriorityQueue* q = NewQueue(&ValuedEdgeComparator);
    int d[this->size];
    bool visited[this->size];
    int nodes[this->size];
    for(int i = 0; i < this->size; ++i)
    {
        visited[i] = false;
        d[i] = -1;
        nodes[i] = i;
    }
    d[source] = 0;
    int* paste = new int(0);
    AddItem(q, nodes + source, 0);
    while(GetQueueSize(q) > 0)
    {
        int u = *(int*)PopNextItem(q);
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
                *paste = ((ValuedEdge*)this->GetEdge(u, vs[i]))->GetValue() + d[u];
                AddItem(q, nodes + vs[i], paste);
            }
        }
    }
    delete paste;
    //DeleteQueue(q);*/
    return 0;//d[destination];
}
