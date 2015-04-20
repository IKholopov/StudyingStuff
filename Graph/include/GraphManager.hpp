#ifndef __GRAPH_MANAGER_H__
#define __GRAPH_MANAGER_H__

#include <vector>
#include <string>
#include <utility>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>

#include "Graph.h"

template <class T>
class GraphManager
{
    public:
        static Graph* GetRandomUnorientedGraph(unsigned int size);
        static Graph* GetRandomGraph(unsigned int size);
        static void RandomizeGraph(Graph* g);
        static Graph* ReadFromFile(std::string path);
};

/*      File format:
 *          SIZE FLAGS //Flags ve - valued edge
 *          from to (value)
 *          ...
*/
template <class T>
Graph* GraphManager<T>::GetRandomUnorientedGraph(unsigned int size)
{
    std::vector<Edge> e;
    for(int i = 0; i < size - 1; ++i)
        for(int j = i + 1; j < size; ++j)
        {
            if(rand() % 2)
            {
                e.push_back(Edge(i, j));
                e.push_back(Edge(j, i));
            }
        }
    Graph* g = new Graph(size, e);
    return g;
}
template <class T>
Graph* GraphManager<T>::GetRandomGraph(unsigned int size)
{
    std::vector<Edge> e;
    for(int i = 0; i < size - 1; ++i)
        for(int j = 0; j < size; ++j)
        {
            if(j == i)
                continue;
            if(rand() % 2)
            {
                e.push_back(Edge(i, j));
            }
        }
    Graph* g = new Graph(size, e);
    return g;
}
template <class T>
void GraphManager<T>::RandomizeGraph(Graph *g)
{
    g->DeleteAllEdges();
    for(int i = 0; i < g->Size() - 1; ++i)
        for(int j = 0; j < g->Size(); ++j)
        {
            if(j == i)
                continue;
            if(rand() % 2)
            {
                g->AddEdge(i, j);
            }
        }
}
template <class T>
Graph *GraphManager<T>::ReadFromFile(std::string path)
{
    /*std::ifstream file(path, std::ifstream::in);
    size_t size;
    bool valuedEdges = false;
    scanf("%d", &size);
    Graph *g = new Graph(size);
    std::string line;
    std::getline(file, line);
    bool v = false;
    for(int i = 0; i < line.length(); ++i)
        switch(line[i])
        {
            case 'v':
                v = true;
                break;
            case 'e':
                if(v)
                {
                    valuedEdges = true;
                    v = false;
                }
                break;
            default:
                break;
        }
    while(file.peek() != EOF)
    {
        int from, to;
        T value;
        file >> from;
        file >> to;
        if(valuedEdges)
        {
            file >> value;
            g->AddEdge(ValuedEdge<T>(from, to, value));
        }
        else
            g->AddEdge(from, to);

    }
    file.close();
    return g;*/
}
#endif
