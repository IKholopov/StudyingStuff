#include "Prim.h"

#include <limits>
#include <iostream>
#include "AdjacencyMatrixUnoriented.h"
#include "MinPQ.hpp"


UnorientedGraphValuedEdge<double>* Prim(UnorientedGraphValuedEdge<double>* original)
{
    MinPQ<double> q;
    std::vector<double> dist;
    std::vector<int> p;
    for(int i = 0; i < original->Size(); ++i)
    {
        q.push(std::pair<double, int>(std::numeric_limits<double>::infinity(), i));
        dist.push_back(std::numeric_limits<double>::infinity());
        p.push_back(-1);
    }
    dist[0] = 0;
    p[0] = -1;
    q.DecreaseKey(0, 0);
    UnorientedGraphValuedEdge<double>* mst = new UnorientedGraphValuedEdge<double>(original->Size(), new AdjacencyMatrixUnoriented());
    while(q.size() > 0)
    {
        std::pair<double, int> v = q.pop();
        for(int i = 0; i < q.size(); i++)
        {
            unsigned int u = q.GetAt(i).second;
            if(original->CheckEdge(v.second, u) && dist[u] - ((ValuedEdge<double>*)original->GetEdge(v.second, u))->GetValue() > 0)
            {
                p[u] = v.second;
                dist[u] = ((ValuedEdge<double>*)original->GetEdge(v.second, u))->GetValue();
                q.DecreaseKey(i, dist[u]);
            }
        }
        if(p[v.second] != -1)
        {
            mst->AddEdge(v.second, p[v.second], ((ValuedEdge<double>*)original->GetEdge(v.second, p[v.second]))->GetValue());
        }
    }
    mst->NormalizeEdges();
    return mst;
}

void Prim()
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
        graph.AddEdge(u, v, val);
    }
    UnorientedGraphValuedEdge<double>* mst = Prim(&graph);
    std::vector<Edge*> edges = mst->GetAllEdgesSorted();
    for(int i = 0; i < edges.size(); ++i)
        std::cout << edges[i]->From << " " << edges[i]->To << " " << ((ValuedEdge<double>*)edges[i])->GetValue() << std::endl;
    delete mst;
}
