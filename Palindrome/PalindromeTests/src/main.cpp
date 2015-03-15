#include<vector>
#include<iostream>

#include "Palindrome.h"

void TestPalindrome()
{
    int amount = 100000;
    int tests = 1000;
    bool clear = true;
    std::string s = " ";
    std::vector<char> v;
    for(int i = 1; i < amount; ++i)
        s = s + " ";
    Palindrome p(s);
    for(int i = 0; i < tests; ++i)
    {        
        int sz = rand() % (amount / 3);
        for(int j = 0; j < sz; j++)
            v.push_back(rand() % 82 + 40);
        int pos = rand() % (amount - 2 * sz - 1);
        bool isOdd = rand() % 2;
        for(int j = 0; j < sz; j++)
        {
            p.Set(pos + j, v[j]);
        }
        if(isOdd)
            p.Set(pos++ + sz, rand() % 82 + 40);
        for(int j = 0; j < sz; j++)
        {
            p.Set(pos + sz+ j, v[sz - 1 - j]);
        }
        if(isOdd)
            --pos;
        if(!p.IsPalindrome(pos, (sz == 0 ? pos : pos + 2 * sz + (isOdd ? 0 : -1))))
        {
            for(int k = pos; k <= (sz == 0 ? pos : pos + 2 * sz + (isOdd ? 0 : -1)); ++k)
                std::cout << p.Get(k) << " ";
            std::cout << std::endl;
            clear = false;
            break;
        }
        if(sz != 0)
        {
            int dr = rand() % (sz == 1 ? sz : sz / 2);
            p.Set(pos + dr, p.Get(pos + dr) + 1);
            if(p.IsPalindrome(pos, pos + 2 * sz + (isOdd ? 0 : -1)))
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
    for(int i = 1; i < amount; ++i)
        s += " ";
    Palindrome t(s);
    for(int i = 0; i < 100000; ++i)
        if(rand() % 2 == 0)
        {
            t.Set(rand() % amount, rand() % 82 + 40);
        }
        else
        {
            unsigned int a = rand() % amount;
            t.IsPalindrome(a, rand() % (amount - a) + a);
        }
}

int main()
{
    TestPalindrome();
    TestLimits();
    return 0;
}
