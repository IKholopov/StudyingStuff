#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

class Edge
{
    public:
        Edge(unsigned int from, unsigned int to)
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

        unsigned int From;
        unsigned int To;
};

#endif
