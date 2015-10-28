#include "Kruskal.h"
#include "MinDSU.h"

#include <iostream>
#include <algorithm>
#include "AdjacencyMatrixUnoriented.h"

UnorientedGraphValuedEdge<double>* Kruskal(UnorientedGraphValuedEdge<double>* original)
{
    UnorientedGraphValuedEdge<double>* T = new UnorientedGraphValuedEdge<double>(original->size(), *(new AdjacencyMatrixUnoriented));
    std::vector<Edge*>* edges = original->getAllEdges();
    std::sort(edges->begin(), edges->end(),
              [](Edge* a, Edge* b)
              {
                  return ((ValuedEdge<double>*)a)->GetValue() - ((ValuedEdge<double>*)b)->GetValue() < 0;
              }
    );
    MinDSU dsu (original->size());
    for(int i = 0; i < edges->size(); ++i)
    {
        if(!dsu.Find(edges->at(i)->From, edges->at(i)->To))
        {
            dsu.Merge(edges->at(i)->From, edges->at(i)->To);
            T->addEdge(edges->at(i)->From, edges->at(i)->To, ((ValuedEdge<double>*)edges->at(i))->GetValue());
        }
        if(dsu.SetCount() == 1)
            break;
    }
    T->normalizeEdges();
    delete edges;
    return T;
}
void Kruskal()
{
    unsigned int n, m;
    std::cin >> n;
    std::cin >> m;
    UnorientedGraphValuedEdge<double> graph(n, *(new AdjacencyMatrixUnoriented()));
    for(int i = 0; i < m; ++i)
    {
        unsigned int u, v;
        double val;
        std::cin >> u >> v >> val;
        graph.addEdge(u, v, val);
    }
    UnorientedGraphValuedEdge<double>* mst = Kruskal(&graph);
    std::vector<Edge*>* edges = mst->getAllEdgesSorted();
    for(int i = 0; i < edges->size(); ++i)
        std::cout << edges->at(i)->From << " " << edges->at(i)->To << " " << ((ValuedEdge<double>*)edges->at(i))->GetValue() << std::endl;
    delete edges;
    delete mst;
}
