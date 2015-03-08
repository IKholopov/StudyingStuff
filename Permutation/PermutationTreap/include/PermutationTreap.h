#ifndef __PERMUTATIONTREAP_H__
#define __PERMUTATIONTREAP_H__

#include "ImplicitTreapTree.h"

class PermutationTreapNode: public ImplicitTreapNode<int>
{
    public:
        PermutationTreapNode():ImplicitTreapNode<int>(){}
        PermutationTreapNode(int y, int data):ImplicitTreapNode<int>(y, data) {};

        long GetSum();
        long GetSum(int i, int j);                  //Section [i;j]
        PermutationTreapNode* Add(int position, int data);
        virtual void UpdateCount();
        void Split(int x, ImplicitTreapNode*& l, ImplicitTreapNode*& r);
        bool NextPermutation(size_t i, size_t j);

        //move to private after tests
    private:
        long sum;
        PermutationTreapNode* subLeft;
        PermutationTreapNode* subRight;
        size_t GetFirstOfLastDecrease();
        bool isUnstrictDecrease;               //>= for subtree
};
class PermutationTreapTree: public ImplicitTreapTree<int>
{
    public:
        PermutationTreapTree();
        PermutationTreapTree(int y, int data);

        long GetSum(){ return ((PermutationTreapNode*)head)->GetSum(); }
        long GetSum(int i, int j){ return ((PermutationTreapNode*)head)->GetSum(i, j);}
        bool NextPermutation(size_t i, size_t j);
};

PermutationTreapNode* PermutationTreapNode::Add(int position, int data)
{
    ImplicitTreapNode* result;
    if(this->Count == 0)
    {
        this->y = rand();
        this->left = NULL;
        this->right = NULL;
        this->Data = data;
        this->shouldReverse = false;
        this->Count = 1;
        result = this;
        UpdateCount();
    }
    else
    {
        ImplicitTreapNode *l, *r;
        ImplicitTreapNode<int>::Split(position, l, r);
        ImplicitTreapNode* element = new PermutationTreapNode(rand(), data);
        result = Merge(Merge(l, element), r);
    }
    return (PermutationTreapNode*)result;
}
void PermutationTreapNode::UpdateCount()
{
    ImplicitTreapNode<int>::UpdateCount();

    isUnstrictDecrease = true;
    if(left != NULL)
    {
        subLeft = ((PermutationTreapNode*)left)->subLeft;
        if(!((PermutationTreapNode*)left)->isUnstrictDecrease ||
                ((PermutationTreapNode*)left)->subRight->GetData() < GetData())
            isUnstrictDecrease = false;
    }
    else
        subLeft = this;
    if(right != NULL)
    {
        subRight = ((PermutationTreapNode*)right)->subRight;
        if(!((PermutationTreapNode*)right)->isUnstrictDecrease ||
                GetData() < ((PermutationTreapNode*)right)->subLeft->GetData())
            isUnstrictDecrease = false;
    }
    else
        subRight = this;

    sum = Data;
    if(left != NULL)
        sum += ((PermutationTreapNode*)left)->sum;
    if(right != NULL)
        sum += ((PermutationTreapNode*)right)->sum;
}
bool PermutationTreapNode::NextPermutation(size_t i, size_t j)
{
    ImplicitTreapNode *l, *set, *r;
    ImplicitTreapNode<int>::Split(i, l, r);
    r->Split(j - i + 1, set, r);
    int a = ((PermutationTreapNode*)set)->GetFirstOfLastDecrease();
    bool result = true;
    if(a != 0)
    {
        ImplicitTreapNode* t = set->Reverse(a, j - i + 1);
        int toChange = set->GetPosition(a - 1)->GetData();
        while(t->left != NULL || t->right != NULL)
        {
            Push(t);
            if(t->GetData() >= toChange)
            {
                if(t->left != NULL && ((PermutationTreapNode*)t->left)->subRight->GetData() > toChange)
                    t = t->left;
                else break;
            }
            else
                if(t )
                t = t->right;
        }
        int oldT = t->GetData();
        t->SetData(toChange);
        set->GetPosition(a - 1)->SetData(oldT);
    }
    else
    {
        set->Reverse(a, j - i + 1);
        result = false;
    }
    Merge(Merge(l, set), r);
    return result;
}

size_t PermutationTreapNode::GetFirstOfLastDecrease()
{
    Push(this);
    size_t count = 0;
    PermutationTreapNode* t = this;
    while(t->right != NULL && !((PermutationTreapNode*)t->right)->isUnstrictDecrease)
    {
        if(t->left != NULL)
            count += t->GetCountOf(t->left);
        count += 1;
        t =(PermutationTreapNode*)t->right;
    }
    if(t->right != NULL &&
            t->GetData() < ((PermutationTreapNode*)t->right)->subLeft->GetData())
    {
        if(t->left != NULL)
            count += t->GetCountOf(t->left);
        count += 1;
        return count;//(PermutationTreapNode*)t->right)->subLeft;
    }
    if(t->left != NULL &&
            ((PermutationTreapNode*)t->left)->subRight->GetData() >= t->GetData())
        return ((PermutationTreapNode*)t->left)->GetFirstOfLastDecrease();
    if(left != NULL)
        count += t->GetCountOf(t->left);
    return count;
}
long PermutationTreapNode::GetSum()
{
    return sum;
}
long PermutationTreapNode::GetSum(int i, int j)
{
    ImplicitTreapNode<int> *l, *z, *r;
    ImplicitTreapNode<int>::Split(i, l, r);
    r->Split(j + 1 - i, z, r);
    long sum = ((PermutationTreapNode*)z)->GetSum();
    Merge(Merge(l, z), r);
    return sum;
}

PermutationTreapTree::PermutationTreapTree()
{
    this->head = new PermutationTreapNode();
}
PermutationTreapTree::PermutationTreapTree(int y, int data)
{
    this->head = new PermutationTreapNode(y, data);
}
bool PermutationTreapTree::NextPermutation(size_t i, size_t j)
{
    return ((PermutationTreapNode*)this->head)->NextPermutation(i, j);
}

#endif
