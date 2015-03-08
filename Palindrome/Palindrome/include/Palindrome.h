#ifndef __Palindrome_H__
#define __Palindrome_H__

class Palindrome
{
    private:
        int p;
        string s;
        int n;
    public:
        Palindrome(string s);
        void Set(int i);
        bool IsPalindrome(int i, int j);
};

#endif
