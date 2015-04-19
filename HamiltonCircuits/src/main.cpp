#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
#include "GraphManager.h"
#include "Hamilton.h"

int CheckGraphsOfSize(int n)
{
    unsigned long long total = 0;

}

int main()
{
        srand(time(NULL));
        const int amount = 1000;
        for(int i = 1; i <= 20; ++i){
            int counter = 0;
            for(int j = 0; j < amount; ++j)
            {
                Graph* g = GraphManager::GetRandomGraph(i);
                if(HamiltonVerify::CheckIfHamilton(g))
                {
                    ++counter;
                }

                delete g;
            }
            std::cout << i << "  " << (double)counter / (double)amount;
            std::cout  << std::endl;
        }
   /* std::vector<Edge> edges;
    for(;;)
    {
    Graph* g = new Graph(20, edges);
            g->AddUnorientedEdge(0, 1);
            g->AddUnorientedEdge(2, 1);
            g->AddUnorientedEdge(2, 3);
            g->AddUnorientedEdge(3, 4);
            g->AddUnorientedEdge(0, 4);
            g->AddUnorientedEdge(0, 5);
            g->AddUnorientedEdge(1, 6);
            g->AddUnorientedEdge(2, 7);
            g->AddUnorientedEdge(3, 8);
            g->AddUnorientedEdge(4, 9);
            g->AddUnorientedEdge(9, 10);
            g->AddUnorientedEdge(10, 5);
            g->AddUnorientedEdge(11, 5);
            g->AddUnorientedEdge(11, 6);
            g->AddUnorientedEdge(12, 6);
            g->AddUnorientedEdge(12, 7);
            g->AddUnorientedEdge(13, 7);
            g->AddUnorientedEdge(13, 8);
            g->AddUnorientedEdge(14, 8);
            g->AddUnorientedEdge(14, 9);
            g->AddUnorientedEdge(15, 10);
            g->AddUnorientedEdge(15, 16);
            g->AddUnorientedEdge(15, 19);
            g->AddUnorientedEdge(16, 11);
            g->AddUnorientedEdge(17, 16);
            g->AddUnorientedEdge(17, 12);
            g->AddUnorientedEdge(17, 18);
            g->AddUnorientedEdge(13, 18);
            g->AddUnorientedEdge(19, 18);
            g->AddUnorientedEdge(19, 14);
            HamiltonVerify::CheckIfHamilton(g);
            delete g;
}*/
    return 0;
}
