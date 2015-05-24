#include "CustomGenerator.h"
#include <limits>

double randVal()
{
    return (double)rand() / RAND_MAX;
}
GraphValuedEdge<double>* GenerateGraphFromCin()
{
    return GenerateGraphFrom(std::cin);
}
GraphValuedEdge<double>* GenerateGraphFrom(std::istream& str)
{
    int n, t;
    str >> n;
    str >> t;
    return GenerateGraph(n, t);
}
GraphValuedEdge<double>* GenerateGraph(unsigned int size, int percentage)
{
    GraphValuedEdge<double>* g = new GraphValuedEdge<double>(size);
    g->GenerateAccurateUnorientedGraph(percentage, &randVal);
    return g;
}
