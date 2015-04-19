#ifndef __PERMUTATIONTREAP_H__
#define __PERMUTATIONTREAP_H__

#include "ImplicitTreapTree.h"

class PermutationTreapNode: public ImplicitTreapNode<int>
{
    public:
        PermutationTreapNode():ImplicitTreapNode<int>(){}
        PermutationTreapNode(int y, int data):ImplicitTreapNode<int>(y, data) {};



        long long GetSum();
        long long GetSum(int i, int j);                  //Section [i;j]
        PermutationTreapNode* Add(int position, int data);
        virtual void UpdateCount();
        void Split(int x, ImplicitTreapNode*& l, ImplicitTreapNode*& r);
        bool NextPermutation(size_t i, size_t j);
        size_t GetFirstOfLastDecrease();
        void Push();
        PermutationTreapNode*  GetSubLeft();
        PermutationTreapNode*  GetSubRight();

    private:
        long long sum;
        bool isUnstrictDecrease;               //>= for subtree
};

class PermutationTreapTree: public ImplicitTreapTree<int>
{
    public:
        PermutationTreapTree();
        PermutationTreapTree(int y, int data);

        long long GetSum(){ return ((PermutationTreapNode*)head)->GetSum(); }
        long long GetSum(int i, int j){ return ((PermutationTreapNode*)head)->GetSum(i, j);}
        bool NextPermutation(size_t i, size_t j);
};

#endif
