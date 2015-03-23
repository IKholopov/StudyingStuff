#ifndef __DSU_H__
#define __DSU_H__

#include <vector>

class DSUElement
{
    public:
        DSUElement(int value);
        DSUElement* GetParent(int version);
        void SetParent(DSUElement* parent);
        int versions;
        DSUElement* GetLastParent() { return parent.back(); }
    private:
        int value;
        std::vector<DSUElement*> parent;
};

class DSU
{
    public:
        DSU(std::vector<int> values);
        bool Find(int version, int a, int b);
        void Merge(int version, int a, int b);
    private:
        int versions;
        std::vector< std::vector<DSUElement*> > units;
        std::vector<DSUElement*> elements;
        void InitNewVersion();
};

#endif
