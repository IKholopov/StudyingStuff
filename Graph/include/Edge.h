#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

class Edge
{
    public:
        Edge(unsigned long long from, unsigned long long to)
        {
            this->From = from;
            this->To = to;
        }
        virtual Edge* GetReversed()
        {
            return new Edge(To, From);
        }
        virtual Edge* Clone()
        {
            return new Edge(*this);
        }

        unsigned long long From;
        unsigned long long To;
};

#endif
