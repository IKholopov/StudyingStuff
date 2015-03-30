#include <iostream>
#include <vector>
#include <stdlib.h>

#include "DSU.h"

void TestAll()
{
    int amount = 100;
    int tests = 100;
    DSU d(amount);
    for(int i = 0; i < tests; ++i)
    {
        if(rand() % 2 == 0)
            d.Merge(rand() % (i + 1), rand() % amount + 1, rand() % amount + 1);
        else
            d.Find(rand() % (i + 1), rand() % amount + 1, rand() % amount + 1);
    }
    return;
}

int main()
{
    TestAll();
    int n, m;
    std::cin >> n;
    std::cin >> m;
    DSU d(n);
    for(int i = 0; i < m; ++i)
    {
        char c;
        int v, a, b;
        std::cin >> c;
        while(c == '\n')
            std::cin >> c;
        std::cin >> v;
        std::cin >> a;
        std::cin >> b;
        switch (c) {
        case '+':
            d.Merge(v, a, b);
            break;
        case '?':
            if(d.Find(v, a, b))
                std::cout << "YES" << std::endl;
            else
                std::cout << "NO" << std::endl;
            break;
        default:
            throw "Invalid input";
            break;
        }
    }
}
