#ifndef __DSU_H__
#define __DSU_H__

#include <vector>

class DSUElement
{
    public:
        DSUElement(int value);
        DSUElement* GetParent(int version);
        void SetParent(DSUElement* parent, int version);
        int length;
    private:
        int LocateParentIdAt(int version);
        int value;
        std::vector<DSUElement*> parent;
        std::vector<int> versions;
};

class DSU
{
    public:
        DSU(std::vector<int> values);
        bool Find(int version, int a, int b);
        void Merge(int version, int a, int b);
    private:
        int versions;
        std::vector<DSUElement*> elements;
};

#endif
