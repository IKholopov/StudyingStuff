#if TRUE
#ifndef __PRIORITYQUEUE_H_
#define __PRIORITYQUEUE_H_

#include<stdlib.h>
#include"BinaryHeap.h"

typedef struct PriorityQueue{
    BinaryHeap* Heap;
    int (*CompareFunction)(const void* a, const void* b);
}PriorityQueue;

PriorityQueue* NewQueue(int (*compare)(const void* a, const void* b));
void DeleteQueue(PriorityQueue* queue);
void AddItem(PriorityQueue* queue, void* item, void* priority);
size_t GetQueueSize(PriorityQueue* queue);
void* GetNextItem(PriorityQueue* queue);
void* GetNextItemPriority(PriorityQueue* queue);
void* PopNextItem(PriorityQueue* queue);

#endif
#endif
