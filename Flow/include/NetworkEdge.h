#ifndef FLOW_NETWORKEDGE_H
#define FLOW_NETWORKEDGE_H

#include "ValuedEdge.hpp"
#include <assert.h>
#include <istream>
#include <ostream>

template <class FlowType>
class NetworkEdgeValue
{
    public:
        NetworkEdgeValue() {}
        NetworkEdgeValue(FlowType capacity, FlowType flow)
        {
            this->Capacity = capacity;
            this->Flow = flow;
        }

        FlowType Capacity;
        FlowType Flow;

        friend std::istream &operator>>(std::istream  &input, NetworkEdgeValue& value)
        {
            input >> value.Capacity;
            return input;
        }
        friend std::ostream &operator<<(std::ostream  &output, const NetworkEdgeValue& value)
        {
            output << value.Flow << " " << value.Flow;
            return output;
        }
        friend std::istream &operator>>(std::istream  &input, NetworkEdgeValue* value)
        {
            input >> value->Capacity;
            return input;
        }
        friend std::ostream &operator<<(std::ostream  &output, const NetworkEdgeValue* value)
        {
            output << value->Flow << " " << value->Flow;
            return output;
        }
};

#endif
