#ifndef __GRAPH_HAM_H__
#define __GRAPH_HAM_H__

#include <utility>
#include <vector>
#include "OrientedGraph.h"

class HamiltonVerify
{
    public:
        static bool CheckIfHamilton(IGraph* g);
};

#endif
