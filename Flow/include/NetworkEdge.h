#ifndef FLOW_NETWORKEDGE_H
#define FLOW_NETWORKEDGE_H

#include "Edge.h"

#include <assert.h>
#include <istream>
#include <ostream>

namespace GraphLibrary {

template <class FlowType>
class NetworkEdge: public Edge
{
    public:
        NetworkEdge() {}
        NetworkEdge(unsigned long long id, unsigned long long from, unsigned long long to,
                    FlowType capacity, FlowType flow):Edge(from, to)
        {
            this->id_ = id;
            this->capacity_ = capacity;
            this->flow_ = flow;
        }
        NetworkEdge* clone()
        {
            return new NetworkEdge(this->id_, this->From, this->To, capacity_, flow_);
        }
        FlowType getCapacity()
        {
            return capacity_;
        }
        void setCapacity(long long capacity)
        {
            assert(capacity >= 0);
            this->capacity_ = capacity;
        }
        FlowType getFlow()
        {
            return flow_;
        }
        void setFlow(long long flow)
        {
            assert(flow <= capacity_);
            this->flow_ = flow;
        }

    private:
        FlowType capacity_;
        FlowType flow_;
};

}

#endif
