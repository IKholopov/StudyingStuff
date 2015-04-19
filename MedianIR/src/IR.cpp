#include "IR.h"

IR::IR(int* data, size_t size)
{
    t = new PSTree(data, size);
    treap = new PermutationTreapTree();
    for(int i = 0; i < size; ++i)
        treap->Add(i, data[i]);
}
IR::~IR()
{
    delete t;
}

int IR::Roman(unsigned int l, unsigned int r)
{
     unsigned int median = (r - l) / 2;
     return t->GetKthStatistics(l - 1, r, median);
}
int IR::Ilona(unsigned int l, unsigned int r)
{
    int diff = (int)(0.1 * (r - l + 1));
    int lDiff = 0;
    int rDiff = 0;
    for(int i = 0; i < diff; ++i)
    {
        lDiff += t->GetKthStatistics(l - 1, r - 1, i);
        rDiff += t->GetKthStatistics(l - 1, r - 1, r - l - i);
    }
    return ((treap->GetSum(l - 1, r - 1) - lDiff - rDiff) / (r - l + 1 - 2 * diff));
}
