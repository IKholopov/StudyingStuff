#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
#include "GraphValuedEdge.h"
#include "GraphManager.h"

const int numberOfTests = 1;
const int graphSize= 1000;

void TestBFS()
{
    GraphValuedEdge* g = new GraphValuedEdge(graphSize);
    std::cout << numberOfTests << " tests" << std::endl;
    std::cout << "0.01 p: ";
    g->RandomizeUnorientedGraph(0.01);
    clock_t start_t, end_t;
    start_t = clock();
    for(int i = 0; i < numberOfTests; ++i)
        g->BFS(rand() % graphSize, rand() % graphSize);
    end_t = clock();
    std::cout << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
    printf("P1\n");
    std::cout << "0.05 p: ";
    g->RandomizeUnorientedGraph(0.05);
    start_t = clock();
    for(int i = 0; i < numberOfTests; ++i)
        g->BFS(rand() % graphSize, rand() % graphSize);
    end_t = clock();
    std::cout << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
    std::cout << "0.1 p: ";
    g->RandomizeUnorientedGraph(0.1);
    start_t = clock();
    for(int i = 0; i < numberOfTests; ++i)
        g->BFS(rand() % graphSize, rand() % graphSize);
    end_t = clock();
    std::cout << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
    std::cout << "0.5 p: ";
    g->RandomizeUnorientedGraph(0.5);
    start_t = clock();
    for(int i = 0; i < numberOfTests; ++i)
        g->BFS(rand() % graphSize, rand() % graphSize);
    end_t = clock();
    std::cout << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
    delete g;
}

int main()
{
    TestBFS();
    return 0;
}
