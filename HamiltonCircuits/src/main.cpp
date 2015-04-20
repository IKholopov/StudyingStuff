#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
#include "GraphManager.hpp"
#include "Hamilton.h"

int main()
{
        srand(time(NULL));
        const int amount = 1000;
        for(int i = 1; i <= 20; ++i){
            int counter = 0;
            for(int j = 0; j < amount; ++j)
            {
                Graph* g = GraphManager<int>::GetRandomUnorientedGraph(i);
                if(HamiltonVerify::CheckIfHamilton(g))
                {
                    ++counter;
                }
                delete g;
            }
            std::cout << i << "  " << (double)counter / (double)amount;
            std::cout  << std::endl;
        }
    return 0;
}
