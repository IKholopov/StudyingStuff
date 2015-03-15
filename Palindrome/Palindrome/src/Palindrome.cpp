#include "Palindrome.h"

Palindrome::Palindrome(std::string s)
{
    t = new PalindromeTreapTree(s);
    this->s = s;
    n = s.size();
}
Palindrome::~Palindrome()
{
    delete t;
}

void Palindrome::Set(unsigned int i, char c)
{
    if(i >= n)
        throw "Out of range";
    t->SetAt(i, c);
}
bool Palindrome::IsPalindrome(unsigned int i, unsigned int j)
{
    if(j >= n || j < i)
        throw "Invalid range";
    return t->CheckPalindrome(i, j);
}
