#include "GraphManager.h"

#include <string>
#include <stdlib.h>
#include <vector>


Graph* GraphManager::GetRandomGraph(unsigned int size)
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

    /*if(size < 2)
        edges = 0;
    else
        edges =  rand() % size;
    for(int i = 0; i < edges; ++i)
    {
        int index1 = rand() % size;
        int index2;
        do
            index2 = (index1 + (rand() % (size - 1))) % size;
        while(index1 == index2);
        bool exist;
        do
        {
            exist = false;
            for(int j = 0; j < e.size(); ++j)
                if(e[j].From == index1 && e[j].To == index2)
                    exist = true;
            if(exist)
            {
                if(++index2 == index1)
                {
                    if(++index1 == size)
                        index1 = 0;
                    ++index2;
                }
                if(++index2 >= size)
                    index2 = size - index2;
            }
        }while(exist);
        e.push_back(Edge(index1, index2));
        e.push_back(Edge(index2, index1));
    }*/
    Graph* g = new Graph(size, e);
    return g;
}
