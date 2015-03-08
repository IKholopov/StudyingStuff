#ifndef __IMPLICIT_TREAP_H__
#define __IMPLICIT_TREAP_H__

#include <stdlib.h>

template <class T>
class ImplicitTreapNode{
    public:
        ImplicitTreapNode<T>* right;
        ImplicitTreapNode<T>* left;

        ImplicitTreapNode(int y, T data);
        ImplicitTreapNode();
        ~ImplicitTreapNode();

        static ImplicitTreapNode<T>* Merge(ImplicitTreapNode<T>* l, ImplicitTreapNode<T>* r);
        static int GetCountOf(ImplicitTreapNode<T>* t);
        static void Push(ImplicitTreapNode<T>* t);

        virtual void UpdateCount();
        void Split(int x, ImplicitTreapNode*& l, ImplicitTreapNode*& r);
        ImplicitTreapNode<T>* Reverse(size_t i, size_t j);
        ImplicitTreapNode<T>* GetPosition(size_t i);
        virtual ImplicitTreapNode<T>* Add(int position, T data);
        ImplicitTreapNode<T>* Remove(int position);
        T GetData();
        int SetData(T data);

    protected:
        int y;
        T Data;
        int Count;
        bool shouldReverse;
    private:
        ImplicitTreapNode(int y, T data, ImplicitTreapNode<T>* l, ImplicitTreapNode<T>* r);
};

template <class T>
ImplicitTreapNode<T>::ImplicitTreapNode(int y, T data, ImplicitTreapNode<T>* l, ImplicitTreapNode<T>* r)
{
    this->y = y;
    this->left = l;
    this->right = r;
    this->Data = data;
    this->shouldReverse = false;
    UpdateCount();
}
template <class T>
ImplicitTreapNode<T>::ImplicitTreapNode(int y, T data)
{
    this->y = y;
    this->left = NULL;
    this->right = NULL;
    this->Data = data;
    this->shouldReverse = false;
    this->Count = 1;
}
template <class T>
ImplicitTreapNode<T>::ImplicitTreapNode()
{
    this->Count = 0;
}
template <class T>
ImplicitTreapNode<T>::~ImplicitTreapNode()
{
    if(this != NULL)
    {
        delete this->left;
        delete this->right;
    }
    this->Count = 0;
}
template <class T>
ImplicitTreapNode<T>* ImplicitTreapNode<T>::GetPosition(size_t i)
{
    Push(this);
    if(this->Count == 0)
        return NULL;
    int index = GetCountOf(this->left);
    if(index == i)
        return this;
    if(index < i)
    {
        if(this->right == NULL)
            return NULL;
        return this->right->GetPosition(i - index - 1);
    }
    else
    {
        if(this->left == NULL)
            return NULL;
        return this->left->GetPosition(i);
    }

}
template <class T>
ImplicitTreapNode<T>* ImplicitTreapNode<T>::Add(int position, T data)
{
    ImplicitTreapNode* result;
    if(this->Count == 0)
    {
        this->y = rand();
        this->left = NULL;
        this->right = NULL;
        this->Data = data;
        this->Count = 1;
        result = this;
    }
    else
    {
        ImplicitTreapNode *l, *r;
        Split(position, l, r);
        ImplicitTreapNode* element = new ImplicitTreapNode(rand(), data);
        result = Merge(Merge(l, element), r);
    }
    return result;
}
template <class T>
ImplicitTreapNode<T>* ImplicitTreapNode<T>::Remove(int position)
{
    ImplicitTreapNode *l, *r, *z;
    Split(position, l, r);
    r->Split(1, z, r);
    if(l != NULL || r != NULL)
        delete z;
    ImplicitTreapNode* result = Merge(l, r);
    if(result == NULL)
    {
        this->Count = 0;
        return this;
    }
    return result;
}
template <class T>
void ImplicitTreapNode<T>::Split(int x, ImplicitTreapNode*& l, ImplicitTreapNode*& r)
{
    Push(this);
    ImplicitTreapNode* tree = NULL;
    int index = GetCountOf(this->left) + 1;
    if(index <= x)
    {
        if(this->right == NULL)
            r = NULL;
        else
            this->right->Split(x - index, tree, r);
        l = this;
        this->right = tree;
        l->UpdateCount();
    }
    else
    {
        if(this->left == NULL)
            l = NULL;
        else
            this->left->Split(x, l, tree);
        r = this;
        this->left = tree;
        r->UpdateCount();
    }
}
template <class T>
ImplicitTreapNode<T> *ImplicitTreapNode<T>::Reverse(size_t i, size_t j)
{
    ImplicitTreapNode *l, *rev, *r;
    this->Split(i, l, r);
    r->Split(j - i + 1, rev, r);
    rev->shouldReverse = true;
    Merge(Merge(l, rev), r);
    return rev;
}

template <class T>
ImplicitTreapNode<T>* ImplicitTreapNode<T>::Merge(ImplicitTreapNode<T>* l, ImplicitTreapNode<T>* r)
{
    Push(l);
    Push(r);
    if(l == NULL)
    {
        if(r != NULL)
            r->UpdateCount();
        return r;
    }
    if(r == NULL)
    {
        if(l != NULL)
            l->UpdateCount();
        return l;
    }
    if(l->y > r->y)
    {
        ImplicitTreapNode<T>* right = Merge(l->right, r);
        l->right = right;
        l->UpdateCount();
        return l;
    }
    else
    {
        ImplicitTreapNode<T>* left = Merge(l, r->left);
        r->left = left;
        r->UpdateCount();
        return r;
    }
}
template<class T>
void ImplicitTreapNode<T>::Push(ImplicitTreapNode<T> *t)
{
    if(t == NULL)
        return;
    if(!t->shouldReverse)
        return;
    ImplicitTreapNode* swap = t->left;
    t->left = t->right;
    t->right = swap;
    t->shouldReverse = false;
    if(t->left != NULL)
    {
        t->left->shouldReverse ^= true;
    }
    if(t->right != NULL)
        t->right->shouldReverse ^= true;
}
template <class T>
int ImplicitTreapNode<T>::GetCountOf(ImplicitTreapNode<T>* t)
{
    if(t == NULL)
        return 0;
    return t->Count;
}
template <class T>
void ImplicitTreapNode<T>::UpdateCount()
{
    Count = GetCountOf(this->left) + GetCountOf(this->right) + 1;
}
template <class T>
T ImplicitTreapNode<T>::GetData()
{
    if(this->Count != 0)
        return this->Data;
    throw "Tree is empty";
    return 0;
}
template <class T>
int ImplicitTreapNode<T>::SetData(T data)
{
    if(this->Count != 0)
    {
        this->Data = data;
        return 0;
    }
    return 1;
}
#endif
