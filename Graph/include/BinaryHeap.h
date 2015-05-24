#ifndef __BINARYHEAP_H_
#define __BINARYHEAP_H_

#include <stdlib.h>
#include <vector>

class BinaryIntHeap
{
    public:
        BinaryIntHeap();

        std::vector<int>  Data;
        size_t TypeSize;
        size_t Size;
        size_t Allocated;
};

/*void AddToHeap(BinaryHeap* heap, void* new_data);
void* GetTop(BinaryHeap* heap);
void* PopTop(BinaryHeap* heap);             // Allocated dynammicly, free() required!!!
void DeleteHeap(BinaryHeap* heap);
void PrintIntHeap(BinaryHeap* heap);*/

#endif
