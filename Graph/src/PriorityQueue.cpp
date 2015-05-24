#if TRUE
#include"PriorityQueue.h"

typedef struct QueueItem{
    PriorityQueue* Queue;
    void* Item;
    void* Priority;
}QueueItem;

int CompareQueueItems(const void* a, const void* b)
{
    QueueItem* itemA = (QueueItem*)a;
    QueueItem* itemB = (QueueItem*)b;
    if(itemA->Queue->CompareFunction(itemA->Priority, itemB->Priority) > 0)
        return 1;
    if(itemA->Queue->CompareFunction(itemA->Priority, itemB->Priority) == 0)
        return 0;
    return -1;
}

PriorityQueue* NewQueue(int (*compare)(const void* a, const void* b))
{
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->Heap = NewHeap(sizeof(QueueItem), &CompareQueueItems);
    queue->CompareFunction = compare;
    return queue;
}

void DeleteQueue(PriorityQueue* queue)
{
    DeleteHeap(queue->Heap);
    free(queue);
}

void AddItem(PriorityQueue* queue, void* item, void* priority)
{
    QueueItem* queueItem = (QueueItem*)malloc(sizeof(QueueItem));
    queueItem->Item = item;
    queueItem->Priority = priority;
    queueItem->Queue = queue;
    AddToHeap(queue->Heap, queueItem);
}

size_t GetQueueSize(PriorityQueue* queue)
{
    return queue->Heap->Size;
}

void* GetNextItem(PriorityQueue* queue)
{
    return ((QueueItem*)GetTop(queue->Heap))->Item;
}

void* PopNextItem(PriorityQueue* queue)
{
    QueueItem* queueItem = (QueueItem*)PopTop(queue->Heap);
    if(queueItem == NULL)
        return NULL;
    char* item = (char*)queueItem->Item;
    free(queueItem);
    return item;
}

void *GetNextItemPriority(PriorityQueue *queue)
{
    return ((QueueItem*)GetTop(queue->Heap))->Priority;
}
#endif
