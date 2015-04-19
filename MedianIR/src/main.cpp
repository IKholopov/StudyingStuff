#include <iostream>
#include <cstdlib>
#include "IR.h"

int main()
{
    int n, m;
    std::cin >> n;
    std::cin >> m;
    int data[n];
    for(int i = 0; i < n; ++i)
        std::cin >> data[i];
    IR ir(data, n);
    int l, r;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> l;
        std::cin >> r;
        int roman = ir.Roman(l, r);
        int ilona = ir.Ilona(l, r);
        std::cout << "Rm "<< roman << " Il " << ilona << " ABS " << std::abs(roman - ilona) << std::endl;
        std::cout << std::abs(roman - ilona) << std::endl;
    }
    return 0;
}
