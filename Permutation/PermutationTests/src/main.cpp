#include <iostream>
#include <vector>
#include <stdlib.h>
#include "PermutationTreap.h"

void TestAdd()
{
    const size_t amount = 100;
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
    const size_t amount = 101;
    std::vector<int> v;
    PermutationTreapTree t;
    for(int i = 0; i < amount; ++i)
    {
        int k = rand()/1000;
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
    const size_t amount = 101;
    std::vector<int> v;
    PermutationTreapTree t;
    long sum = 0;
    long sum20_40 = 0;
    for(int i = 0; i < amount; ++i)
    {
        int k = rand()/1000000;
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

void Test()
{
    TestAdd();
    TestRemove();
    TestSum();
}

int main()
{
    Test();

    PermutationTreapTree* t = new PermutationTreapTree(100, 10);
    t->Remove(0);
    int values[] = {90, 24, 10, 83, 83, 83, 83, 14, 15, 13, 12, 10, 8, 7, 6, 4, 2, 1};
    for(int i = 0; i < 18; ++i)
    {
        t->Add(i, values[i]);
    }

    t->NextPermutation(0, 17);
    for(int i = 0; i < 18; ++i)
    {
        std::cout << t->GetPosition(i)->GetData() << " ";
    }
    t->GetPosition(2)->SetData(1000000);
    delete t;
    return 0;
}
