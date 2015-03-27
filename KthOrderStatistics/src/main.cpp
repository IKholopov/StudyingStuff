#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

#include "PSTree.h"

void* LSD(int* data, size_t amount)
{
    int* counters = (int*)calloc(sizeof(int) * 8, sizeof(int));
    int* sorted = (int*)malloc(amount * sizeof(int));
    int mask = 1;
    int i;
    for(i = 0; i < sizeof(int) * 8 - 1; ++i)
    {
        int j;
        for(j = 0; j < amount; ++j)
        {
            int test = (mask & data[j])  >> i;
            ++counters[test];
        }
        for(j = 1; j < sizeof(int) * 8; ++j)
            counters[j] += counters[j - 1];
        for(j = amount - 1; j >= 0; --j)
        {
            sorted[--counters[(mask & data[j]) >> i]] = data[j];
        }
        mask <<= 1;
        for(j = 0; j < amount; ++j)
            data[j] = sorted[j];
        for(j = 0; j < sizeof(int) * 8; ++j)
            counters[j] = 0;
    }
    //last sign
    int j;
    for(j = 0; j < amount; ++j)
    {
        int test = (mask & data[j])  >> i;
        ++counters[!test];
    }
    for(j = 1; j < sizeof(int) * 8; ++j)
        counters[j] += counters[j - 1];
    for(j = amount - 1; j >= 0; --j)
    {
        sorted[--counters[!((mask & data[j]) >> i)]] = data[j];
    }
    mask <<= 1;
    for(j = 0; j < amount; ++j)
        data[j] = sorted[j];

}

void TestTime()
{
    int k = 1;
    int amount = 1000;
    for(int i = 0; i < 6; ++i)
    {
        k *= 10;
        std::cout << k << " elements" << std::endl;
        int data[k];
        for(int j = 0; j < k; ++j)
        {
            data[j] = rand() % 100;
        }
        PSTree t(data, k);
        std::vector<int> pst;
        std::vector<int> lv, rv ,stv;
        clock_t start_t, end_t;
        start_t = clock();
        for(int j = 0; j < amount; ++j)
        {
            int l = rand() % k;
            lv.push_back(l);
            int r = rand() % (k - l) + l;
            rv.push_back(r);
            int st = rand() % (r - l + 1);
            stv.push_back(st);
            pst.push_back( t.GetKthStatistics(l, r + 1, st));
        }
        end_t = clock();
        std::cout << "PST:" << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
        std::vector<int> stdSort;
        start_t = clock();
        for(int j = 0; j < amount; ++j)
        {
            int sub[rv[j] + 1 - lv[j]];
            memcpy(sub, data + lv[j], (rv[j] + 1 - lv[j]) * sizeof(int));
            std::sort(sub, sub + (rv[j] + 1 - lv[j]));
            stdSort.push_back(sub[stv[j]]);
        }
        end_t = clock();
        std::cout << "STD:" << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
        std::vector<int> radixSort;
        start_t = clock();
        for(int j = 0; j < amount; ++j)
        {
            int sub[rv[j] + 1 - lv[j]];
            memcpy(sub, data + lv[j], (rv[j] + 1 - lv[j]) * sizeof(int));
            LSD(sub, (size_t)(rv[j] + 1 - lv[j]));
            radixSort.push_back(sub[stv[j]]);
        }
        end_t = clock();
        std::cout << "Radix:" << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
        for(int j = 0; j < amount; ++j)
        {
            if(stdSort[j] != pst[j])
                throw "Error!";
        }
        for(int j = 0; j < amount; ++j)
        {
            if(radixSort[j] != pst[j])
                throw "Error!";
        }
    }
    std::cout << "Test passed" << std::endl;
}

int main()
{
    TestTime();
    return 0;
}
