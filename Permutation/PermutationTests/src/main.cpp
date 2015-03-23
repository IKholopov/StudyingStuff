#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "PermutationTreap.hpp"

void TestAdd()
{
    const size_t amount = 1000;
    std::vector<int> v;
    PermutationTreapTree t;
    for(int i = 0; i < amount; ++i)
    {
        int k = rand()/1000;
        int pos = i == 0 ? 0 : rand() % i;
        v.insert(v.begin() + pos, k);
        t.Add(pos, k);
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
    const int amount = 10100;
    const int tests = 500;
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
void TestAll()
{
    const size_t tests = 100000;
    const size_t testSums = 100;
    const size_t amount = 100000;
    std::vector<int> v;
    PermutationTreapTree t;
    for(int i = 0; i < amount; ++i)
    {
        int k = (rand() % 100);//* (rand() % 2 == 0 ? 1 : -1);
        int pos = i == 0 ? 0 : rand() % i;
        v.insert(v.begin() + pos, k);
        t.Add(pos, k);
    }
    clock_t start_t, end_t;
    for(int i = 0; i < tests; ++i)
    {
        start_t = clock();
        for(int k = 0; k < tests; ++k)
        {
            int ops = rand() % 4;
            switch (ops) {
            case 0: //ADD
            {
                int pos = rand() % t.Size();
                int k = (rand() % 100) * (rand() % 2 == 0 ? 1 : -1);
                v.insert(v.begin() + pos, k);
                t.Add(pos, k);
                break;
            }
            case 1: //REPLACE
            {
                int pos = rand() % t.Size();
                int k = (rand() % 100) * (rand() % 2 == 0 ? 1 : -1);
                v[pos] = k;
                t.SetAt(pos, k);
                break;
            }
            case 2: //REMOVE
            {
                if(t.Size() != 1)
                {
                    int pos = rand() % t.Size();
                    v.erase(v.begin() + pos);
                    t.Remove(pos);
                }
                break;
            }
            case 3: //PERMUTATION
            {
                int a = rand() % t.Size();
                int b = rand() % (t.Size() - a) + a;
                std::next_permutation(v.begin() + a, v.begin() + b + 1);
                t.NextPermutation(a, b);
#ifdef DEBUG
                //((PermutationTreapNode*)t.GetHead())->VerifySubs();
                //t.GetHead()-> PrintTree();
                for(int l = 0; l < t.Size(); ++l)
                {
                    if(v[l] != t.GetPosition(l)->GetData())
                        throw "Tree corrupted!";
                }
                /*if(!((PermutationTreapNode*)t.GetHead())->VerifySum())
                    throw "Sum corrupted!";*/
#endif
                break;
            }
            default:
                throw "WTF?";
                break;
            }
#ifdef DEBUG
           for(int l = 0; l < t.Size(); ++l)
            {
                if(v[l] != t.GetPosition(l)->GetData())
                    throw "Tree corrupted!";
            }
            /*if(!((PermutationTreapNode*)t.GetHead())->VerifySum())
                throw "Sum corrupted!";*/

#endif
        }
        end_t = clock();
        std::cout << (float)(end_t - start_t)/CLOCKS_PER_SEC << std::endl;
        for(int j = 0; j < testSums; ++j)
        {
            unsigned long long sum = 0;
            int a = rand() % (1000 < t.Size() ? 1000 : t.Size());
            int b = rand() % ((1000 < t.Size() ? 1000 : t.Size()) - a) + a;
            for(int k = a; k <= b; ++k)
                sum += v[k];
            long long sumTree = t.GetSum(a, b);
            if(sum != sumTree)
                throw "Too bad!";
        }
    }
}

void Test()
{
    TestAdd();
    TestRemove();
    TestSum();
    TestPermutation();
    TestAll();
}

int main()
{
    Test();
    return 0;
}
