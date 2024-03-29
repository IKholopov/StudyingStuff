#ifndef GRAPH_IMULTIGRAPH_H
#define GRAPH_IMULTIGRAPH_H

#include "IOriented.h"

class IMultiGraph: public IOriented
{
    public:
        virtual Edge* getEdge(long long from, long long to, unsigned long long id) = 0;
        virtual Edge* getEdge(unsigned long long id) = 0;
        virtual const std::vector<Edge*>* getAllEdgesConst() const = 0;
        virtual const std::vector<Edge*>* getOutgoing(unsigned long long vertex) const = 0;
        virtual const std::vector<Edge*>* getIngoing(unsigned long long vertex) const = 0;
};

#endif
