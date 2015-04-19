#include <iostream>
#include "PermutationTreap.hpp"

int main()
{
    int n;
    std::cin >> n;
    int m;
    PermutationTreapTree a, b;
    for(int i = 0; i < n; ++i)
    {
        std::cin >> m;
        a.Add(i, m);
    }
    for(int i = 0; i < n; ++i)
    {
        std::cin >> m;
        b.Add(i, m);
    }
    std::cin >> m;
    for(int i = 0; i < m; ++i)
    {
        char c;
        int l, r;
        std::cin >> c;
        while(c == '\n')
            std::cin >> c;
        std::cin >> l;
        std::cin >> r;
        switch (c) {
        case '+':
            for(int i = l; i <= r; ++i)
                a.SetAt(i, a.GetPosition(i)->GetData() + b.GetPosition(i)->GetData());
            break;
        case '?':
            std::cout << a.GetSum(l, r) << std::endl;
            break;
        default:
            throw "Invalid input";
            break;
        }
    }
}
