#include"Hamilton.h"

#ifdef DEBUG
#include <fstream>
#include <bitset>
#endif

#define MAX_GRAPH_SIZE 20

bool HamiltonVerify::CheckIfHamilton(Graph *g)
{
    static int table[1 << MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
    if(g->Size() == 1)
        return true;
    for(int i = 0; i < g->Size(); ++i)
    {
        table[(1 << i) | 1][i] = g->CheckEdge(0, i);
    }
    for(int i = 0; i < (1 << g->Size()); ++i)
    {
        int edges = 0;
        int set = i;
        for(int j = 0; j < g->Size(); ++j)
        {
            edges += set % 2;
            if(edges > 1)
                break;
            set >>= 1;
        }
        if(edges == 1)
            continue;
        for(int j = 0; j < g->Size(); ++j)
            if(((1 << j) & i) != 0)
                for(int l = 0; l < g->Size(); ++l)
                    if(l != j && (((1 << l) & i) != 0))
                    {
                        table[i][j] = table[(1 << j) ^ i][l] && g->CheckEdge(l, j);
                        if(table[i][j])
                            break;
                    }
    }
    bool hamil = false;

#ifdef DEBUG
    std::ofstream output;
    output.open("debugGraph.txt");
    for(int i = 0; i < (1 << g->Size()); ++i)
    {
        std::bitset<20> set(i);
        output << set << std::endl;
        for(int j = 0; j < g->Size(); ++j)
        {
            output << "  " << table[i][j];
        }
        output << std::endl;
    }
    output.close();
#endif
    for(int i = 1; i < g->Size(); ++i)
        if(table[(1 << g->Size()) - 1][i] && g->CheckEdge(i, 0))
        {
            hamil = true;
            break;
        }
        /*if(table[(1 << g->Size()) - 1][i])
        {
            for(int j = i + 1; j < g->Size(); ++j)
                if(table[(1 << g->Size()) - 1][j] && g->CheckEdge(i, j))
                    hamil = true;
        }*/
    for(int i = 0; i < (1 << g->Size()); ++i)
        for(int j = 0; j < g->Size(); ++j)
            table[i][j] = 0;
    return hamil;
}
