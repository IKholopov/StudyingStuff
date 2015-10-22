#include "GraphParser.h"
#include "NetworkEdge.h"

GraphParser& GraphParser::parser()
{
    static GraphParser parser;
    return parser;
}

std::vector<NetworkDelta>* GraphParser::GetAlgorithmRun(const std::vector<std::vector<unsigned long long> >& graphData)
{
    unsigned long long size = 1;
    for(auto e: graphData)
    {
        if(e.at(0) > size - 1)
            size = e.at(0) + 1;
        if(e.at(1) > size - 1)
            size = e.at(1) + 1;
    }
    NetworkGraph<long long> graph(size, new ParentChildListOriented());
    for(unsigned long long i = 0; i < graphData.size(); ++i)
    {
        graph.AddEdge(new GraphLibrary::NetworkEdge<long long>(i, graphData.at(i).at(0),graphData.at(i).at(1), graphData.at(i).at(2), 0));
    }
    return NetworkManager<long long>::instance().ThreeIndiansAlgorithmDelta(graph, 0, size - 1);
}

GraphParser::GraphParser()
{

}

