#ifndef __VALUED_EDGE_H__
#define __VALUED_EDGE_H__

#include <type_traits>
#include "Edge.h"

template <class ValueType>
class ValuedEdge: public Edge
{
    public:
        ValuedEdge(unsigned int from, unsigned int to, ValueType value):Edge(from, to)
        {
            this->value = value;
        }
        ~ValuedEdge()
        {
        }

        ValueType GetValue()
        {
            return value;
        }
        void SetValue(ValueType value)
        {
            this->value = value;
        }
        virtual Edge* GetReversed()
        {
            return new ValuedEdge(To, From, value);
        }
        virtual Edge* Clone()
        {
            return new ValuedEdge(*this);
        }

    protected:
        ValueType value;
};

#endif
