#ifndef __MedIR_H__
#define __MedIR_H__

#include <vector>
#include <stdlib.h>
#include "PSTree.h"
#include "PermutationTreap.hpp"

class IR
{
    public:
        IR(int* data, size_t size);
        ~IR();
        int Roman(unsigned int l, unsigned int r);
        int Ilona(unsigned int l, unsigned int r);
    private:
        PSTree* t;
        PermutationTreapTree* treap;
};

#endif
