#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "PermutationTreap.h"

void TestAdd()
{
    const size_t amount = 1000;
    std::vector<int> v;
    PermutationTreapTree t;
    for(int i = 0; i < amount; ++i)
    {
        int k = rand()/1000;
        v.push_back(k);
        t.Add(t.Size(), k);
    }
    bool clear = true;
    for(int i = 0; i < amount; ++i)
    {
        if(v[i] != t.GetPosition(i)->GetData())
            clear = false;
    }
    if(clear)
        std::cout << "Test Add passed." << std::endl;
    else
        std::cout << "Test Add failed!" << std::endl;
}
void TestRemove()
{
    const size_t amount = 1010;
    std::vector<int> v;
    PermutationTreapTree t;
    for(int i = 0; i < amount; ++i)
    {
        int k = rand() % 1000;
        v.push_back(k);
        t.Add(t.Size(), k);
    }
    bool clear = true;
    for(int i = amount - 1; i >= 0; i -= 2)
    {
        t.Remove(i);
    }
    for(int i = amount/2 - 1; i >= 0; i--)
    {
        if(v[2*i + amount % 2 ] != t.GetPosition(i)->GetData())
            clear = false;
    }
    if(clear)
        std::cout << "Test Remove passed." << std::endl;
    else
        std::cout << "Test Remove failed!" << std::endl;
}
void TestSum()
{
    const size_t amount = 1010;
    std::vector<int> v;
    PermutationTreapTree t;
    long sum = 0;
    long sum20_40 = 0;
    for(int i = 0; i < amount; ++i)
    {
        int k = rand() % 10000;
        v.push_back(k);
        t.Add(t.Size(), k);
        sum += k;
        if(i >= 20 && i <= 40)
            sum20_40 += k;
    }
    bool clear = true;
    if(sum20_40 != t.GetSum(20, 40))
        clear = false;
    for(int i = amount - 1; i >= 0; i -= 2)
    {
        sum -= t.GetPosition(i)->GetData();
        t.Remove(i);
    }
    if(sum != t.GetSum())
        clear = false;
    if(clear)
        std::cout << "Test Sum passed." << std::endl;
    else
        std::cout << "Test Sum failed!" << std::endl;
}
void TestPermutation()
{
    const int amount = 1010;
    const int tests = 50;
    int v[amount];
    PermutationTreapTree t;
    bool clear = true;
    for(int i = 0; i < amount; ++i)
    {
        v[i] = rand() % 1000;
        t.Add(i, v[i]);
    }
    for(int i = 0; i < tests; ++i)
    {
        int a = rand() % amount;
        int b = rand() % (amount - a) + a;
        std::next_permutation(v + a, v + b + 1);
        t.NextPermutation(a, b);
#ifdef DEBUG
        for(int j = 0; j < amount; ++j)
            std::cout << t.GetPosition(j)->GetData() << " ";
        std::cout << std::endl;
#endif
        for(int j = 0; j < amount; ++j)
        {
            if(t.GetPosition(j)->GetData() != v[j])
            {
                throw "Test Failed!";
                clear = false;
            }
        }
    }
    if(clear)
        std::cout << "Test Permutation passed." << std::endl;
    else
        std::cout << "Test Permutation failed!" << std::endl;
}

void Test()
{
    TestAdd();
    TestRemove();
    TestSum();
    TestPermutation();
}

int main()
{
    Test();
    return 0;
}
