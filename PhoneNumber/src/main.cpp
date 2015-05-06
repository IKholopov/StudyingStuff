#include <iostream>

#include "Phone.h"

int main()
{
    int N, M, L;
    std::cin >> N;
    std::cin >> M;
    std::cin >> L;
    Phone::Solve(M, N, L);

    return 0;
}
