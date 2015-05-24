#include "MinDSU.h"

#include <stdlib.h>

MinDSU::MinDSU(unsigned int amount)
{
    for(int i = 0; i < amount; ++i)
    {
        DSUElement* e = new DSUElement(i);
        elements.push_back(e);
    }
    setsCounter = amount;
}
MinDSU::~MinDSU()
{
    for(int i = 0; i < elements.size(); ++i)
        delete elements[i];
}

DSUElement *MinDSU::GetParent(DSUElement* e)
{
    DSUElement* origin = e;
    while(e->prev != NULL)
    {
        e = e->prev;
    }
    if(origin->prev != NULL)
        origin->prev = e;
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
     e2->prev = e1;
     --setsCounter;
}
unsigned int MinDSU::GetParentId(unsigned int id)
{
    DSUElement* e = GetParent(elements[id]);
    return e->id;
}
unsigned int MinDSU::SetCount()
{
    return setsCounter;
}
