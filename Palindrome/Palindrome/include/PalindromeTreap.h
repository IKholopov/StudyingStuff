#ifndef __PalindromeTreap_H_
#define __PalindromeTreap_H_

#include <string>
#include <vector>
#include "ImplicitTreapTree.h"

const unsigned int P_BASE = 53;

class PalindromeTreapNode;

class PalindromeTreapTree:public ImplicitTreapTree<char>
{
    public:
        PalindromeTreapTree(std::string s);

        static unsigned long long Pow(unsigned long long b);

        void SetAt(unsigned int i, char c);
        bool CheckPalindrome(unsigned int i, unsigned int j);
    private:
        static std::vector<unsigned long long> pows;
};

class PalindromeTreapNode:public ImplicitTreapNode<char>
{
    public:
        PalindromeTreapNode(char c):ImplicitTreapNode<char>(rand(), c) {};
        PalindromeTreapNode(int y, char c):ImplicitTreapNode<char>(y, c) {};
        void SetAt(unsigned int i, char c);
        void UpdateCount();
        PalindromeTreapNode* Add(int position, char data);
        unsigned long long GetLeftHash()
            { return hashLeft; }
        unsigned long long GetRightHash()
            { return hashRight; }
    private:
        unsigned long long hashLeft;
        unsigned long long hashRight;
};
#endif

