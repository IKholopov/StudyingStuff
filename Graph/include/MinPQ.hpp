#ifndef __MIN_PQ_H__
#define __MIN_PQ_H__

#include <vector>
#include <utility>

template <class PriorityType>
class MinPQ
{
    public:
        void push(const std::pair<PriorityType, int> &item);
        std::pair<PriorityType, int> pop();
        std::pair<PriorityType, int> top();
        const std::pair<PriorityType, int>& GetAt(unsigned int i);
        void DecreaseKey(unsigned int i, PriorityType key);
        void DecreaseKeyAt(unsigned int i, PriorityType key);
        unsigned int size();
    private:
        std::vector< std::pair<PriorityType, int> > heap;                    //first - priority, second - vertex
        void SiftUp(unsigned int i);
        void SiftDown(unsigned int i);
};

template <class PriorityType>
void MinPQ<PriorityType>::push(const std::pair<PriorityType, int> &item)
{
    heap.push_back(item);
    SiftUp(heap.size() - 1);
}
template <class PriorityType>
std::pair<PriorityType, int> MinPQ<PriorityType>::pop()
{
    std::pair<int, int> min = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    SiftDown(0);
    return min;
}
template <class PriorityType>
std::pair<PriorityType, int> MinPQ<PriorityType>::top()
{
    return heap[0];
}
template <class PriorityType>
const std::pair<PriorityType, int> &MinPQ<PriorityType>::GetAt(unsigned int i)
{
    return heap[i];
}
template <class PriorityType>
void MinPQ<PriorityType>::DecreaseKey(unsigned int i, PriorityType key)
{
    if(heap[i].first < key)
        throw std::exception();
    heap[i].first = key;
    SiftUp(i);
}
template <class PriorityType>
void MinPQ<PriorityType>::DecreaseKeyAt(unsigned int i, PriorityType key)
{
    for(int j = 0; j < heap.size(); ++j)
        if(heap[j].second == i)
        {
            DecreaseKey(j, key);
            return;
        }
}
template <class PriorityType>
unsigned int MinPQ<PriorityType>::size()
{
    return heap.size();
}
template <class PriorityType>
void MinPQ<PriorityType>::SiftUp(unsigned int i)
{
    while(i != 0 && heap[i].first < heap[(i-1)/2].first)
    {
        std::pair<int, int> temp = heap[(i-1)/2];
        heap[(i-1)/2] = heap[i];
        heap[i] = temp;
        i = (i-1)/2;
    }
}
template <class PriorityType>
void MinPQ<PriorityType>::SiftDown(unsigned int i)
{
    while (2 * i + 1 < heap.size())
    {
           int left = 2 * i + 1;
           int right = 2 * i + 2;
           int j = left;
           if (right < heap.size() && heap[right].first < heap[left].first)
               j = right;
           if (heap[i].first <= heap[j].first)
               break;
           std::pair<int, int> temp = heap[j];
           heap[j] = heap[i];
           heap[i] = temp;
           i = j;
    }
}
#endif
