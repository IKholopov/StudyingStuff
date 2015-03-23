#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

#include "PSTree.h"


void TestTime()
{
    int k = 1;
    for(int i = 0; i < 5; ++i)
    {
        k *= 10;
        int data[k];
        for(int j = 0; j < k; ++j)
        {
            data[j] = rand();
        }
        PSTree t(data, k);
        std::vector<int> pst;
        std::vector<int> lv, rv ,stv;
        clock_t start_t, end_t;
        start_t = clock();
        for(int j = 0; j < 100; ++j)
        {
            int l = rand() % k;
            lv.push_back(l);
            int r = rand() % (k - l) + l;
            rv.push_back(r);
            int st = rand() % (r - l + 1) - 1;
            stv.push_back(st);
            pst.push_back( t.GetKthStatistics(l, r + 1, st));
        }
        end_t = clock();
        std::cout << "PST:" << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
        std::vector<int> stdSort;
        start_t = clock();
        for(int j = 0; j < 100; ++j)
        {
            int sub[rv[i] - lv[i]];
            memcpy(sub, data, k * sizeof(int));
            std::sort(sub, sub + k);
            stdSort.push_back(sub[stv[i]]);
        }
        end_t = clock();
        std::cout << "STD:" << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
        for(int j = 0; j < 100; ++j)
        {
            if(stdSort[j] != pst[j])
                throw "Error!";
        }
    }
}

int main()
{
    //TestTime();
    int data[] = { 6, 1, 2, 8, 7, 9, 5, 3, 2};
    PSTree t(data, 9);
    for(int i = 0; i < 6; ++i)
        std::cout << t.GetKthStatistics(2, 8, i) << std::endl;
    std::cout << std::endl;
    return 0;
}
