#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include <istream>

namespace GraphLibrary {

class Edge
{
    public:
        Edge(unsigned long long from, unsigned long long to);

        virtual Edge* getReversed();
        virtual Edge* clone();
        unsigned long long getId();
        unsigned long long From;
        unsigned long long To;
        void setId(unsigned long long id_);
    protected:
        unsigned long long id_;
};

}


#endif
