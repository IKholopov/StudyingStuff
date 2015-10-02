#ifndef GRAPH_IMULTIGRAPH_H
#define GRAPH_IMULTIGRAPH_H

#include "IOriented.h"

class IMultiGraph: public IOriented
{
    public:
        virtual const std::vector<Edge*>* GetAllEdgesConst() const = 0;
        virtual const std::vector<Edge*>* GetOutgoing(unsigned long long vertex) const = 0;
        virtual const std::vector<Edge*>* GetIngoing(unsigned long long vertex) const = 0;
};

#endif
