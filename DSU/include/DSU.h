#ifndef __DSU_H__
#define __DSU_H__

#include <vector>
#include <utility>

class DataNode
{
    public:
        DataNode(int value, int size);
        int value;
        int size;
};

class DSUVersion
{
    public:
        ~DSUVersion();

        std::pair<int, DataNode*> changeset;
        DSUVersion(DSUVersion* ancestor);
        DataNode GetParent(std::vector<DataNode>* set, int element);
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
        int versionCounter;
        std::vector<DataNode> base;
        DSUVersion* InitNewVersion(int version);
        DataNode GetParent(DSUVersion* version, int element);
        std::vector<DSUVersion*> versions;
};

#endif
