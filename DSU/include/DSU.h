#ifndef __DSU_H__
#define __DSU_H__

#include <vector>
#include <utility>

class DSUVersion
{
    public:
        std::pair<int, int> Changeset;

        DSUVersion(DSUVersion* ancestor);

        int GetLinkAt(int element, std::vector<int>* base);
    private:
        DSUVersion* ancestor;
};

class DSU
{
    public:
        DSU(int size);
        ~DSU();

        bool Find(int version, int a, int b);
        void Merge(int version, int a, int b);
    private:
        int GetParent(DSUVersion* version, int element);
        int versionCounter;
        std::vector<int> base;
        DSUVersion* InitNewVersion(int version);
        std::vector<DSUVersion*> versions;
};

#endif
