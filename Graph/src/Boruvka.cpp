#include "Boruvka.h"

#include <iostream>
#include "MinDSU.h"

UnorientedGraphValuedEdge<double>* Boruvka(UnorientedGraphValuedEdge<double> *original)
{
    UnorientedGraphValuedEdge<double>* mst = new UnorientedGraphValuedEdge<double>(original->Size());
    MinDSU dsu(mst->Size());
    std::vector<ValuedEdge<double>*> minEdge;
    while(dsu.SetCount() > 1)
    {
        minEdge.clear();
        minEdge.resize(original->Size());
        for(int i = 0; i < minEdge.size(); ++i)
            minEdge[i] = NULL;
        std::vector<Edge*> edges =  original->GetAllEdges();
        for(int i = 0; i < edges.size(); ++i)
        {
            if(!dsu.Find(edges[i]->From, edges[i]->To))
            {
                unsigned int from = dsu.GetParentId(edges[i]->From);
                unsigned int to = dsu.GetParentId(edges[i]->To);
                if(minEdge[from] == NULL || minEdge[from]->GetValue() - ((ValuedEdge<double>*)edges[i])->GetValue() > 0)
                    minEdge[from] = (ValuedEdge<double>*)edges[i];
                if(minEdge[to] == NULL || minEdge[to]->GetValue() - ((ValuedEdge<double>*)edges[i])->GetValue() > 0)
                    minEdge[to] = (ValuedEdge<double>*)edges[i];
            }
        }
        for(int i = 0; i < original->Size(); ++i)
        {
            if(minEdge[i] != NULL)
            {
                mst->AddEdge(minEdge[i]->From, minEdge[i]->To, minEdge[i]->GetValue());
                dsu.Merge(minEdge[i]->From, minEdge[i]->To);
            }
        }
    }
    mst->NormalizeEdges();
    return mst;
}
void Boruvka()
{
    unsigned int n, m;
    std::cin >> n;
    std::cin >> m;
    UnorientedGraphValuedEdge<double> graph(n);
    for(int i = 0; i < m; ++i)
    {
        unsigned int u, v;
        double val;
        std::cin >> u >> v >> val;
        graph.AddEdge(u, v, val);
    }
    UnorientedGraphValuedEdge<double>* mst = Boruvka(&graph);
    std::vector<Edge*> edges = mst->GetAllEdgesSorted();
    for(int i = 0; i < edges.size(); ++i)
        std::cout << edges[i]->From << " " << edges[i]->To << " " << ((ValuedEdge<double>*)edges[i])->GetValue() << std::endl;
    delete mst;
}
