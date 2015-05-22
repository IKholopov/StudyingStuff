#include "MinDSU.h"

#include <stdlib.h>

MinDSU::MinDSU(unsigned int amount)
{
    for(int i = 0; i < amount; ++i)
    {
        DSUElement* e = new DSUElement();
        elements.push_back(e);
        sets.push_back(e);
    }
}

DSUElement *MinDSU::GetParent(DSUElement* e)
{
    while(e->prev != NULL)
    {
        e = e->prev;
    }
    return e;
}
bool MinDSU::Find(unsigned int id1, unsigned int id2)
{
    if(GetParent(elements[id1]) == GetParent(elements[id2]))
        return true;
    return false;
}
void MinDSU::Merge(unsigned int id1, unsigned int id2)
{
    DSUElement* e1 = GetParent(elements[id1]);
    DSUElement* e2 = GetParent(elements[id2]);
    if(e1 == e2)
        return;
    if(e1->size - 1 >= e2->size)
    {
        e2->prev = e1;
        if(e1->size - 1 < e2->size)
            e1->size = e2->size + 1;
        sets.erase(sets.begin() + id2);
    }
    else
    {
        e1->prev = e2;
        if(e2->size - 1 < e1->size)
            e2->size = e1->size + 1;
        sets.erase(sets.begin() + id1);
    }
}
unsigned int MinDSU::SetCount()
{
    return sets.size();
}
