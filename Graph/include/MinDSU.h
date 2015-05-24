#ifndef _MINDSU_H__
#define _MINDSU_H__

#include <vector>
#include <stdlib.h>

class DSUElement
{
    public:
        DSUElement* prev;
        unsigned int id;

        DSUElement(unsigned int id)
        {
            this->id = id;
            prev = NULL;
        }
};

class MinDSU
{
    public:
        MinDSU(unsigned int amount);
        ~MinDSU();

        bool Find(unsigned int id1, unsigned int id2);
        void Merge(unsigned int id1, unsigned int id2);
        unsigned int GetParentId(unsigned int id);
        unsigned int SetCount();
    private:
        DSUElement* GetParent(DSUElement* e);
        std::vector<DSUElement*> elements;
        unsigned int setsCounter;
};

#endif
