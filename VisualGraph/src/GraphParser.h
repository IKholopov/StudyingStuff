#ifndef GRAPHPARSER_H
#define GRAPHPARSER_H

#include "NetworkManager.h"
#include "NetworkDelta.h"

class GraphParser
{
    public:
        static GraphParser& parser();
        std::vector<NetworkDelta>* getAlgorithmRun(const std::vector<std::vector<unsigned long long> >& graphData);
    private:
        GraphParser();
};

#endif // GRAPHPARSER_H
