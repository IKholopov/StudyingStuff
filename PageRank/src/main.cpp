#include <iostream>
#include <vector>
#include <time.h>
#include "Graph.h"
#include "GraphManager.hpp"
#include "PageRank.hpp"

#define RANGE 7

int main()
{   
    unsigned int tests = 5;
    unsigned int steps = 20;
    for(int i = 0; i < tests; ++i)
    {
        std::cout << "Test " << i << std::endl;
        PageRank<int>* g = new PageRank<int>(10);
        GraphManager<int>::RandomizeGraph(g);
        for(int j = 0; j < steps; ++j)
        {
            g->PageRankForSteps(1);
            std::vector<double> rank = g->GetRank();
            for(int k = 0; k < rank.size(); ++k)
                std::cout << rank[k] << " ";
            std::cout << std::endl;
        }
        delete g;
    }
    std::ifstream file("input.txt");
    unsigned long long i = 0;
    std::string test[RANGE];
    PageRank<std::string>* pr = new PageRank<std::string>(0);
    for(int i = 0; i < RANGE - 1; ++i)
    {
        file >> test[i];
        pr->AddPage(test[i % RANGE]);
    }
    while(file.peek() != EOF)
    {
        file >> test[i % RANGE];
        pr->AddPage(test[i % RANGE]);
        for(int j = i - RANGE + 1; j < RANGE; ++j)
        {
            pr->AddEdge(pr->GetIndexOfPage(test))
        }
    }
    return 0;
}
