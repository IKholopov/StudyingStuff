#include "CustomGenerator.h"
#include "AdjacencyMatrixUnoriented.h"
#include <limits>

double randVal()
{
    return (double)rand() / RAND_MAX;
}
UnorientedGraphValuedEdge<double>* GenerateGraphFromCin()
{
    return GenerateGraphFrom(std::cin);
}
UnorientedGraphValuedEdge<double>* GenerateGraphFrom(std::istream& str)
{
    int n, t;
    str >> n;
    str >> t;
    return GenerateGraph(n, t);
}
UnorientedGraphValuedEdge<double>* GenerateGraph(unsigned int size, int percentage)
{
    UnorientedGraphValuedEdge<double>* g = new UnorientedGraphValuedEdge<double>(size, *(new AdjacencyMatrixUnoriented()));
    g->generateAccurateUnorientedGraph(percentage, &randVal);
    return g;
}
void GenerateToStream(std::ostream &outstr, std::istream &instr)
{
    int n, t;
    instr >> n;
    instr >> t;
    UnorientedGraphValuedEdge<double>* g = GenerateGraph(n, t);
    g->normalizeEdges();
    g->writeToFile(outstr);
}
void GenerateToStream()
{
    GenerateToStream(std::cout, std::cin);
}
