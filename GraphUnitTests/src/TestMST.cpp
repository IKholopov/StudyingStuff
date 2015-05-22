#include "TestMST.h"
#include "CustomGenerator.h"
#include "Kruskal.h"

void TestMST()
{
    GraphValuedEdge<double>* g = GenerateGraph(1000, 30);
    GraphValuedEdge<double>* t = Kruskal(g);
}
