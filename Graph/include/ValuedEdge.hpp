#ifndef __VALUED_EDGE_H__
#define __VALUED_EDGE_H__
template <class ValueType>
class ValuedEdge: public Edge
{
    public:
        ValuedEdge(unsigned int from, unsigned int to, ValueType value):Edge(from, to)
        {
            this->value = value;
        }
        ValueType GetValue()
        {
            return value;
        }
        virtual Edge* GetReversed()
        {
            return new ValuedEdge(To, From, value);
        }
        virtual Edge* Clone()
        {
            return new ValuedEdge(*this);
        }

    private:
        ValueType value;
};

#endif
