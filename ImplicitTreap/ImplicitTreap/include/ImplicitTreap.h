#ifndef __IMPLICIT_TREAP_H__
#define __IMPLICIT_TREAP_H__

#include<stdlib.h>

template <class T>
class ImplicitTreap{
    private:
        int y;
        T Data;
        int Count;
        ImplicitTreap(int y, T data, ImplicitTreap<T>* l, ImplicitTreap<T>* r);
    public:
        T sum;
        ImplicitTreap<T>* right;
        ImplicitTreap<T>* left;

        ImplicitTreap(int y, T data);
        ImplicitTreap();
        ~ImplicitTreap();

        static ImplicitTreap<T>* Merge(ImplicitTreap<T>* l, ImplicitTreap<T>* r);
        static int GetCountOf(ImplicitTreap<T>* treap);

        void UpdateCount();
        void Split(int x, ImplicitTreap*& l, ImplicitTreap*& r);
        ImplicitTreap<T>* GetPosition(unsigned int i);
        ImplicitTreap<T>* Add(int position, T data);
        ImplicitTreap<T>* Remove(int position);
        T GetSum();
        T GetSum(int i, int j);
        void NextPermutation(int i, int j);
        T GetData();
        int SetData(T data);
};

template <class T>
ImplicitTreap<T>::ImplicitTreap(int y, T data, ImplicitTreap<T>* l, ImplicitTreap<T>* r)
{
    this->y = y;
    this->left = l;
    this->right = r;
    this->Data = data;
    UpdateCount();
}
template <class T>
ImplicitTreap<T>::ImplicitTreap(int y, T data)
{
    this->y = y;
    this->left = NULL;
    this->right = NULL;
    this->Data = data;
    this->Count = 1;
}
template <class T>
ImplicitTreap<T>::ImplicitTreap()
{
    this->Count = 0;
}
template <class T>
ImplicitTreap<T>::~ImplicitTreap()
{
    if(this != NULL)
    {
        delete this->left;
        delete this->right;
    }
    this->Count = 0;
}

template <class T>
ImplicitTreap<T>* ImplicitTreap<T>::GetPosition(unsigned int i)
{
    ImplicitTreap *l, *r, *z;
    Split(i, l, r);
    r->Split(1, z, r);
    Merge(Merge(l, z), r);
    return z;
}
template <class T>
ImplicitTreap<T>* ImplicitTreap<T>::Add(int position, T data)
{
    ImplicitTreap* result;
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
        ImplicitTreap *l, *r;
        Split(position, l, r);
        ImplicitTreap* element = new ImplicitTreap(rand(), data);
        result = Merge(Merge(l, element), r);
    }
    return result;
}
template <class T>
ImplicitTreap<T>* ImplicitTreap<T>::Remove(int position)
{
    ImplicitTreap *l, *r, *z;
    Split(position, l, r);
    r->Split(1, z, r);
    if(l != NULL || r != NULL)
        delete z;
    ImplicitTreap* result = Merge(l, r);
    if(result == NULL)
    {
        this->Count = 0;
        return this;
    }
    return result;
}
template <class T>
void ImplicitTreap<T>::Split(int x, ImplicitTreap*& l, ImplicitTreap*& r)
{
    ImplicitTreap* tree = NULL;
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
ImplicitTreap<T>* ImplicitTreap<T>::Merge(ImplicitTreap<T>* l, ImplicitTreap<T>* r)
{
    if(l == NULL)
        return r;
    if(r == NULL)
        return l;
    if(l->y > r->y)
    {
        ImplicitTreap<T>* right = Merge(l->right, r);
        l->right = right;
        l->UpdateCount();
        return l;
    }
    else
    {
        ImplicitTreap<T>* left = Merge(l, r->left);
        r->left = left;
        r->UpdateCount();
        return r;
    }
}
template <class T>
int ImplicitTreap<T>::GetCountOf(ImplicitTreap<T>* treap)
{
    if(treap == NULL)
        return 0;
    return treap->Count;
}
template <class T>
void ImplicitTreap<T>::UpdateCount()
{
    Count = GetCountOf(this->left) + GetCountOf(this->right) + 1;
    sum = Data;
    if(left != NULL)
        sum += left->sum;
    if(right != NULL)
        sum += right->sum;
}
template <class T>
T ImplicitTreap<T>::GetData()
{
    if(this->Count != 0)
        return this->Data;
    return NULL;
}
template <class T>
T ImplicitTreap<T>::GetSum()
{
    return sum;
}

template <class T>
T ImplicitTreap<T>::GetSum(int i, int j)
{
    ImplicitTreap<T> *l, *z, *r;
    Split(i, l, r);
    Split(j - i, z, r);
    T sum = z->GetSum();
    Merge(Merge(l, z), r);
    return sum;
}
template <class T>
void ImplicitTreap<T>::NextPermutation(int i, int j)
{
    ImplicitTreap<T> *l, *z, *r;
    Split(i, l, r);
    Split(j - i, z, r);
    for(int k = j - i; k > 0; k--)
    {
        if(z->GetPosition(k)->GetData() > z->GetPosition(k - 1)->GetData())
        {
            ImplicitTreap<T>* b = z->GetPosition(k - 1);
            for(int m = j - i; m >= k; m--)
            {
                ImplicitTreap<T>* a = z->GetPosition(m);
                if(a->Data > b->Data)
                {
                    T temp = a->Data;
                    a->Data = b->Data;
                    b->Data = temp;
                    //Fell asleep here .....ZZZZ....ZZ.......
                }
            }
        }
    }
    Merge(Merge(l, z), r);
}
template <class T>
int ImplicitTreap<T>::SetData(T data)
{
    if(this->Count != 0)
    {
        this->Data = data;
        return 0;
    }
    return 1;
}

#endif
