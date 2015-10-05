#ifndef FLOW_NETWORKEDGE_H
#define FLOW_NETWORKEDGE_H

#include "Edge.h"
#include <assert.h>
#include <istream>
#include <ostream>

template <class FlowType>
class NetworkEdge: public Edge
{
    public:
        NetworkEdge() {}
        NetworkEdge(unsigned long long id, unsigned long long from, unsigned long long to,
                    FlowType capacity, FlowType flow):Edge(from, to)
        {
            this->id = id;
            this->capacity = capacity;
            this->flow = flow;
        }
        NetworkEdge* Clone()
        {
            return new NetworkEdge(id, From, To, capacity, flow);
        }
        FlowType GetCapacity()
        {
            return capacity;
        }
        FlowType SetCapacity(long long capacity)
        {
            assert(capacity >= 0);
            this->capacity = capacity;
        }
        FlowType GetFlow()
        {
            return flow;
        }
        FlowType SetFlow(long long flow)
        {
            assert(flow <= capacity);
            this->flow = flow;
        }

    private:
        FlowType capacity;
        FlowType flow;
};

#endif
