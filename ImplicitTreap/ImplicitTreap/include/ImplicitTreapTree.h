#ifndef __IMPLICIT_TREAP_TREE_H__
#define __IMPLICIT_TREAP_TREE_H__

#include "ImplicitTreapNode.h"

template <class T>
class ImplicitTreapTree
{
    public:
        ImplicitTreapTree(int y, T data);
        ImplicitTreapTree(ImplicitTreapNode<T>* head);
        ImplicitTreapTree();
        ~ImplicitTreapTree();

        ImplicitTreapNode<T>* GetPosition(unsigned int i);
        ImplicitTreapNode<T>* GetHead();
        size_t Size();
        void Add(int position, T data);
        void Remove(int position);
        void Reverse(size_t i, size_t j);
    protected:
        ImplicitTreapNode<T>* head;
        size_t size;
};

template <class T>
ImplicitTreapTree<T>::ImplicitTreapTree()
{
    size = 0;
}
template <class T>
ImplicitTreapTree<T>::ImplicitTreapTree(ImplicitTreapNode<T>* head)
{
    size = 0;
    this->head = head;
}
template <class T>
ImplicitTreapTree<T>::ImplicitTreapTree(int y, T data)
{
    size = 0;
    head = new ImplicitTreapNode<T>(y, data);
}
template <class T>
ImplicitTreapTree<T>::~ImplicitTreapTree()
{
    delete head;
}
template <class T>
ImplicitTreapNode<T>* ImplicitTreapTree<T>::GetPosition(unsigned int i)
{
    return head->GetPosition(i);
}
template <class T>
ImplicitTreapNode<T>* ImplicitTreapTree<T>::GetHead()
{
    return this->head;
}
template <class T>
size_t ImplicitTreapTree<T>::Size()
{
    return size;
}
template <class T>
void ImplicitTreapTree<T>::Add(int position, T data)
{

    head = head->Add(position, data);
    ++size;
}
template <class T>
void ImplicitTreapTree<T>::Remove(int position)
{
    head = head->Remove(position);
    if(size != 0)
        --size;
}
template <class T>
void ImplicitTreapTree<T>::Reverse(size_t i, size_t j)
{
    this->head->Reverse(i, j);
}

#endif
