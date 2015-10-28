#include "Boruvka.h"

#include <iostream>
#include "MinDSU.h"
#include "AdjacencyMatrixUnoriented.h"

UnorientedGraphValuedEdge<double>* Boruvka(UnorientedGraphValuedEdge<double> *original)
{
    UnorientedGraphValuedEdge<double>* mst = new UnorientedGraphValuedEdge<double>(original->size(), new AdjacencyMatrixUnoriented());
    MinDSU dsu(mst->size());
    std::vector<ValuedEdge<double>*> minEdge;
    while(dsu.SetCount() > 1)
    {
        minEdge.clear();
        minEdge.resize(original->size());
        for(int i = 0; i < minEdge.size(); ++i)
            minEdge[i] = NULL;
        std::vector<Edge*>* edges =  original->getAllEdges();
        for(int i = 0; i < edges->size(); ++i)
        {
            if(!dsu.Find(edges->at(i)->From, edges->at(i)->To))
            {
                unsigned int from = dsu.GetParentId(edges->at(i)->From);
                unsigned int to = dsu.GetParentId(edges->at(i)->To);
                if(minEdge[from] == NULL || minEdge[from]->GetValue() - ((ValuedEdge<double>*)edges->at(i))->GetValue() > 0)
                    minEdge[from] = (ValuedEdge<double>*)edges->at(i);
                if(minEdge[to] == NULL || minEdge[to]->GetValue() - ((ValuedEdge<double>*)edges->at(i))->GetValue() > 0)
                    minEdge[to] = (ValuedEdge<double>*)edges->at(i);
            }
        }
        delete edges;
        for(int i = 0; i < original->size(); ++i)
        {
            if(minEdge[i] != NULL)
            {
                mst->addEdge(minEdge[i]->From, minEdge[i]->To, minEdge[i]->GetValue());
                dsu.Merge(minEdge[i]->From, minEdge[i]->To);
            }
        }
    }
    mst->normalizeEdges();
    return mst;
}
void Boruvka()
{
    unsigned int n, m;
    std::cin >> n;
    std::cin >> m;
    UnorientedGraphValuedEdge<double> graph(n, new AdjacencyMatrixUnoriented());
    for(int i = 0; i < m; ++i)
    {
        unsigned int u, v;
        double val;
        std::cin >> u >> v >> val;
        graph.addEdge(u, v, val);
    }
    UnorientedGraphValuedEdge<double>* mst = Boruvka(&graph);
    std::vector<Edge*>* edges = mst->getAllEdgesSorted();
    for(int i = 0; i < edges->size(); ++i)
        std::cout << edges->at(i)->From << " " << edges->at(i)->To << " " << ((ValuedEdge<double>*)edges->at(i))->GetValue() << std::endl;
    delete edges;
    delete mst;
}
