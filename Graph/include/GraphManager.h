#ifndef __GRAPH_MANAGER_H__
#define __GRAPH_MANAGER_H__

#include <vector>
#include <string>
#include <utility>

#include "Graph.h"

class GraphManager
{
    public:
        static Graph* GetRandomGraph(unsigned int size);
};

#endif
