#include <iostream>
#include <stdio.h>
#include <vector>

#include "DSU.h"

int main()
{
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
