#include "DSU.h"

#include <stdlib.h>

DSU::DSU(int size)
{
    for(int i = 0; i < size; ++i)
    {
        base.push_back(i + 1);
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
    if(GetParent(newVer, a) == GetParent(newVer, b))
        return true;
    return false;
}
void DSU::Merge(int version, int a, int b)
{
    DSUVersion* newVer = InitNewVersion(version);
    int parentA = GetParent(newVer, a);
    int parentB = GetParent(newVer, b);
    if(!(parentA == parentB))
    {
            newVer->Changeset.first = b;
            newVer->Changeset.second = a;
    }
}
int DSU::GetParent(DSUVersion* version, int element)
{
     int ancestor = version->GetLinkAt(element, &base);
     while(ancestor != element)
     {
         element = ancestor;
         ancestor = version->GetLinkAt(element, &base);
     }
     return element;
}

DSUVersion::DSUVersion(DSUVersion* ancestor)
{
    this->ancestor = ancestor;
    this->Changeset = std::make_pair(0, 0);
}

int DSUVersion::GetLinkAt(int element, std::vector<int>* base)
{
    if(this->ancestor == NULL)
        return base->at(element - 1);
    if(this->Changeset.first == element)
        return this->Changeset.second;
    return this->ancestor->GetLinkAt(element, base);
}
