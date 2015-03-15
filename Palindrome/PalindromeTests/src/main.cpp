#include<vector>
#include<iostream>

#include "PalindromeTreap.h"

void TestPalindrome()
{
    int amount = 100000;
    int tests = 100;
    bool clear = true;
    std::string s = " ";
    PalindromeTreapTree t(s);
    std::vector<char> v;
    for(int i = 1; i < amount; ++i)
        t.Add(t.Size(), ' ');
    for(int i = 0; i < tests; ++i)
    {        
        int sz = rand() % (amount / 3);
        for(int j = 0; j < sz; j++)
            v.push_back(rand() % 82 + 40);
        int pos = rand() % (amount - 2 * sz - 1);
        bool isOdd = rand() % 2;
        for(int j = 0; j < sz; j++)
        {
            t.SetAt(pos + j, v[j]);
        }
        if(isOdd)
            t.SetAt(pos++ + sz, rand() % 82 + 40);
        for(int j = 0; j < sz; j++)
        {
            t.SetAt(pos + sz+ j, v[sz - 1 - j]);
        }
        if(isOdd)
            --pos;
        if(!t.CheckPalindrome(pos, (sz == 0 ? pos : pos + 2 * sz + (isOdd ? 0 : -1))))
        {
            for(int k = pos; k <= (sz == 0 ? pos : pos + 2 * sz + (isOdd ? 0 : -1)); ++k)
                std::cout << t.GetPosition(k)->GetData() << " ";
            std::cout << std::endl;
            clear = false;
            break;
        }
        if(sz != 0)
        {
            int dr= rand() % (sz == 1 ? sz : sz - 1);
            pos += dr;
            t.SetAt(pos, t.GetPosition(pos)->GetData() + 1);
            if(t.CheckPalindrome(pos, pos + 2 * sz + (isOdd ? 0 : -1)))
            {
                clear = false;
                break;
            }
        }
        v.clear();
    }
    if(!clear)
    {
        std::cout << "Test failed!\n" << std::endl;
        throw std::exception();
    }

}
void TestLimits()
{
    int amount = 100000;
    std::string s = " ";
    PalindromeTreapTree t(s);
    for(int i = 1; i < amount; ++i)
        t.Add(t.Size(), ' ');
    for(int i = 0; i < 100000; ++i)
        if(rand() % 2 == 0)
        {
            t.SetAt(rand() % amount, rand() % 82 + 40);
        }
        else
        {
            unsigned int a = rand() % amount;
            t.CheckPalindrome(a, rand() % (amount - a) + a);
        }
}

int main()
{
    //TestPalindrome();
    TestLimits();
    return 0;
}
