#ifndef __Palindrome_H__
#define __Palindrome_H__

#include "PalindromeTreap.h"

class Palindrome
{
    private:
        PalindromeTreapTree* t;
        std::string s;
        int n;
    public:
        Palindrome(std::string s);
        ~Palindrome();

        void Set(unsigned int i, char c);
        bool IsPalindrome(unsigned int i, unsigned int j);
};

#endif
