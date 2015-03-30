#include "DSU.h"

#include <stdlib.h>

DSU::DSU(int size)
{
    for(int i = 0; i < size; ++i)
    {
        DataNode d(i + 1, 1);
        base.push_back(d);
    }
    versionCounter= 0;
    DSUVersion* v = new DSUVersion(NULL);
    versions.push_back(v);
}
DSU::~DSU()
{
    for(int i = 0; i < this->versions.size(); ++i)
        delete versions.at(i);
}

DSUVersion* DSU::InitNewVersion(int version)
{
    ++versionCounter;
    DSUVersion* newDSUv = new DSUVersion(this->versions.at(version));
    versions.push_back(newDSUv);
    return versions.back();
}
bool DSU::Find(int version, int a, int b)
{
    DSUVersion* newVer = InitNewVersion(version);
    if(GetParent(newVer, a).value == GetParent(newVer, b).value)
        return true;
    return false;
}
void DSU::Merge(int version, int a, int b)
{
    DSUVersion* newVer = InitNewVersion(version);
    DataNode parentA = GetParent(newVer, a);
    DataNode parentB = GetParent(newVer, b);
    if(!(parentA.value == parentB.value))
    {
        if(parentA.size )
        newVer->changeset.first = a;
        newVer->changeset.second->value = b;
        //newVer->changeset.second->size =
    }
}
DataNode DSU::GetParent(DSUVersion* version, int element)
{
     std::vector<DataNode> set = this->base;
     return version->GetParent(&set, element);
}

DSUVersion::DSUVersion(DSUVersion* ancestor)
{
    this->ancestor = ancestor;
    this->changeset = std::make_pair(0, new DataNode(0, 1));
}
DSUVersion::~DSUVersion()
{
    delete changeset.second;
}
DataNode DSUVersion::GetParent(std::vector<DataNode>* set, int element)
{
    if(this->ancestor == NULL)
    {
        for(;;)
        {
            int i = set->at(element - 1).value;
            if(i == element)
                return set->at(element - 1);
            element = i;
        }
    }
    if(this->changeset.first != 0)
        set->at(this->changeset.first - 1).value = this->changeset.second->value;
    return this->ancestor->GetParent(set, element);
}


DataNode::DataNode(int value, int size)
{
    this->value = value;
    this->size = size;
}
