#include "Kruskal.h"
#include "MinDSU.h"

#include <iostream>
#include <algorithm>
#include "AdjacencyMatrixUnoriented.h"

UnorientedGraphValuedEdge<double>* Kruskal(UnorientedGraphValuedEdge<double>* original)
{
    UnorientedGraphValuedEdge<double>* T = new UnorientedGraphValuedEdge<double>(original->Size(), *(new AdjacencyMatrixUnoriented));
    std::vector<Edge*> edges = original->GetAllEdges();
    std::sort(edges.begin(), edges.end(),
              [](Edge* a, Edge* b)
              {
                  return ((ValuedEdge<double>*)a)->GetValue() - ((ValuedEdge<double>*)b)->GetValue() < 0;
              }
    );
    MinDSU dsu (original->Size());
    for(int i = 0; i < edges.size(); ++i)
    {
        if(!dsu.Find(edges[i]->From, edges[i]->To))
        {
            dsu.Merge(edges[i]->From, edges[i]->To);
            T->AddEdge(edges[i]->From, edges[i]->To, ((ValuedEdge<double>*)edges[i])->GetValue());
        }
        if(dsu.SetCount() == 1)
            break;
    }
    T->NormalizeEdges();
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
        graph.AddEdge(u, v, val);
    }
    UnorientedGraphValuedEdge<double>* mst = Kruskal(&graph);
    std::vector<Edge*> edges = mst->GetAllEdgesSorted();
    for(int i = 0; i < edges.size(); ++i)
        std::cout << edges[i]->From << " " << edges[i]->To << " " << ((ValuedEdge<double>*)edges[i])->GetValue() << std::endl;
    delete mst;
}
