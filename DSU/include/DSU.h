#ifndef __DSU_H__
#define __DSU_H__

#include <vector>

class DSU
{
    public:
        DSU(int size);
        bool Find(int version, int a, int b);
        void Merge(int version, int a, int b);
    private:
        int versions;
        std::vector<int>* InitNewVersion(int version);
        int GetParent(std::vector<int>* version, int element);
        std::vector< std::vector<int> > elements;                        //version[elements]
};

#endif
