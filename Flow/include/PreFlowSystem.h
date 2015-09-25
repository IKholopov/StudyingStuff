#ifndef _PREFLOWSYSTEM_H__
#define _PREFLOWSYSTEM_H__

#include <vector>
#include "OrientedGraphValuedEdge.hpp"

class PreFlowSystem
{
    public:
        PreFlowSystem() = delete;
        ~PreFlowSystem();
        PreFlowSystem(const OrientedGraphValuedEdge<int>& graph);
        std::vector<ValuedEdge<int>> ToBegining(int source, int sink);
    private:
        OrientedGraphValuedEdge<int>* graph;
        std::vector<int> excess;
        std::vector<int> heights;
};

#endif
