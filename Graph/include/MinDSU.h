#ifndef _MINDSU_H__
#define _MINDSU_H__

#include <vector>
#include <stdlib.h>

class DSUElement
{
    public:
        DSUElement* prev;
        unsigned int size;

        DSUElement()
        {
            prev = NULL;
            size = 1;
        }
};

class MinDSU
{
    public:
        MinDSU(unsigned int amount);

        bool Find(unsigned int id1, unsigned int id2);
        void Merge(unsigned int id1, unsigned int id2);
        unsigned int SetCount();
    private:
        DSUElement* GetParent(DSUElement* e);
        std::vector<DSUElement*> elements;
        std::vector<DSUElement*> sets;
};

#endif
