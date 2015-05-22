#include "Kruskal.h"
#include "MinDSU.h"

#include <iostream>
#include <algorithm>

GraphValuedEdge<double>* Kruskal(GraphValuedEdge<double>* original)
{
    GraphValuedEdge<double>* T = new GraphValuedEdge<double>(original->Size(), false);
    std::vector<Edge*> allEdges = original->GetAllEdges();
    std::vector<ValuedEdge<double>*> edges(allEdges.size() / 2);
    for(int i = 0; i < allEdges.size(); ++i)
        edges[i] = (ValuedEdge<double>*)allEdges[2 * i];
    std::sort(edges.begin(), edges.end(),
              [](ValuedEdge<double>* a, ValuedEdge<double>* b)
              {
                  return a->GetValue() < b->GetValue();
              }
    );
    MinDSU dsu (original->Size());
    for(int i = 0; i < edges.size(); ++i)
    {
        if(!dsu.Find(edges[i]->From, edges[i]->To))
        {
            dsu.Merge(edges[i]->From, edges[i]->To);
            T->AddUnorientedEdge(edges[i]->From, edges[i]->To, edges[i]->GetValue());
        }
        if(dsu.SetCount() == 1)
            break;
    }
    return T;
}
void Kruskal()
{
    unsigned int n, m;
    std::cin >> n;
    std::cin >> m;
    GraphValuedEdge<double> graph(n, false);
    for(int i = 0; i < m; ++i)
    {
        unsigned int u, v;
        double val;
        std::cin >> u;
    }
}
