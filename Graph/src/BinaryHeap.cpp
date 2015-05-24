
#include"BinaryHeap.h"

#include<stdio.h>

void swap(void* data, size_t a, size_t b, size_t bytes)
{

    //printf("%d %d\n", *(int*)(data + a*bytes), *(int*)(data + b*bytes));
    char* array = (char*)data;
    if(bytes == sizeof(long))
    {
        long tempL;
        long* aL = (long*)(array + bytes * a);
        long* bL = (long*)(array + bytes * b);
            tempL = *aL;
            *aL = *bL;
            *bL= tempL;
    }
    else if(bytes == sizeof(int))
    {
        int tempI;
        int* aI = (int*)(array + bytes * a);
        int* bI = (int*)(array + bytes * b);
            tempI = *aI;
            *aI = *bI;
            *bI = tempI;
    }
    else if(bytes % sizeof(long) == 0)
    {
        long tempL;
        long* aL = (long*)(array + bytes * a);
        long* bL = (long*)(array + bytes * b);
        bytes /= sizeof(long);
        while(bytes--)
        {
            tempL = *aL;
            *aL++ = *bL;
            *bL++= tempL;
        }
    }
    else
    while(bytes--)
    {
        char tempC = *(char*)(array + bytes * a);
        *(char*)(array + bytes * a++) = *(char*)(array + bytes * a);
        *(char*)(array + bytes * b++) = tempC;
    }
}
void Swap(BinaryHeap* heap, size_t a, size_t b)
{
    swap(heap->Data, a, b, sizeof(char*));
}
void PushUp(BinaryHeap* heap)
{
    int i = heap->Size - 1;
    while(i > 0)
    {
        if(heap->Compare(heap->Data[i],
                   heap->Data[((i - 1) / 2)]) < 0)
        {
            Swap(heap, i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
        else break;
    }
}
void PushDown(BinaryHeap* heap, int i)
{
    if(heap->Size <= 1)
        return;
    while(i <= (heap->Size - 2) / 2)
    {
        if(i*2 + 2 > heap->Size - 1)
        {
            if(heap->Compare(heap->Data[i],
                             heap->Data[i * 2 + 1]) > 0)
            {
                Swap(heap, i, i * 2 + 1);
                i = i * 2 + 1;
            }
            else break;
        }
        else{
            if((heap->Compare(heap->Data[i],
                             heap->Data[i * 2 + 1]) > 0) ||
                   (heap->Compare(heap->Data[i],
                                  heap->Data[i * 2 + 2])) > 0)
            {
                if(heap->Compare(heap->Data[i * 2 + 1],
                                 heap->Data[i * 2 + 2]) < 0)
                {
                    Swap(heap, i, i * 2 + 1);
                    i = i * 2 + 1;
                }
                else
                {
                    Swap(heap, i, i * 2 + 2);
                    i = i * 2 + 2;
                }
            }
            else break;
        }
    }
}

BinaryHeap* NewHeap(size_t type_size, int (*compare)(const void* a, const void* b))
{
    BinaryHeap* heap = (BinaryHeap*)malloc(sizeof(BinaryHeap));
    heap->Compare = compare;
    heap->TypeSize = type_size;
    heap->Allocated = 0;
    heap->Data = NULL;
    heap->Size = 0;
}
BinaryHeap* NewHeapFromData(void* data, size_t type_size, size_t length,
                    int (*compare)(const void* a, const void* b))
{
    char* newData = (char*)data;
    BinaryHeap* heap = (BinaryHeap*)malloc(sizeof(BinaryHeap));
    heap->Compare = compare;
    heap->TypeSize = type_size;
    heap->Data = (char**)malloc(sizeof(char**) * length);
    heap->Size = length;
    heap->Allocated = length;
    int i;
    for(i = 0; i < length; ++i)
        heap->Data[i] = &newData[i * type_size];
    int n = 1;
    int r = 1;
    i = heap->Size - 1;
    while(1)
    {
        if(i >= r)
        {
            n *= 2;
            r += n;
        }
        PushDown(heap, i);
        if(i <= 0)
            break;
        --i;
    }
    return heap;
}
void AddToHeap(BinaryHeap* heap, void* new_data)
{
    char* newData = (char*)new_data;
    if(heap->Size + 1 > heap->Allocated)
    {
        if(heap->Allocated == 0)
            heap->Allocated = 1;
        heap->Data = (char**)realloc(heap->Data, heap->Allocated *
                                    2 * sizeof(char**));
        heap->Allocated *= 2;
    }
    heap->Size += 1;
    int i = heap->Size - 1;
    heap->Data[i] = newData;
    PushUp(heap);
}
void* GetTop(BinaryHeap* heap)
{
    char** value = heap->Data;
    return *value;
}
void* PopTop(BinaryHeap* heap)
{
    if(heap->Data == NULL)
        return NULL;
    char* value = *heap->Data;
    Swap(heap, 0, heap->Size - 1);
    heap->Size -= 1;
    if(heap->Size == 0)
    {
        heap->Allocated = 0;
        free(heap->Data);
        heap->Data = NULL;
    }
    PushDown(heap, 0);
    return value;
}
void DeleteHeap(BinaryHeap* heap)
{
    free(heap->Data);
    free(heap);
}
void PrintIntHeap(BinaryHeap* heap)
{
    int i;
    int n = 1;
    int r = 1;
    for(i = 0; i < heap->Size; ++i)
    {
        if(i >= r)
        {
            printf("\n");
            n *= 2;
            r += n;
        }
        printf("%d ", **((int**)(heap->Data + i)));

    }
    printf("\n");
}


BinaryIntHeap::BinaryIntHeap()
{
    this->Allocated = 0;
    this->Size = 0;
}
