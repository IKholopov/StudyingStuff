#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include <istream>

namespace GraphLibrary {

class Edge
{
    public:
        Edge(unsigned long long from, unsigned long long to);

        //TODOstatic  Edge* ReadEdge(std::istream& stream);
        virtual Edge* GetReversed();
        virtual Edge* Clone();
        unsigned long long GetId();
        unsigned long long From;
        unsigned long long To;
        void SetId(unsigned long long id);
    protected:
        unsigned long long id;
};

}


#endif
