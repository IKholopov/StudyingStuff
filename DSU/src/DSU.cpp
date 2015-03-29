#include "DSU.h"

DSU::DSU(int size)
{
    std::vector<int> version;
    for(int i = 0; i < size; ++i)
    {
        version.push_back(i + 1);
    }
    elements.push_back(version);
    versions = 0;
}
std::vector<int>* DSU::InitNewVersion(int version)
{
    ++versions;
    elements.push_back(elements[version]);
    return &(elements[versions]);
}
bool DSU::Find(int version, int a, int b)
{
    std::vector<int>* newVer = InitNewVersion(version);
    if(GetParent(newVer, a) == GetParent(newVer, b))
        return true;
    return false;
}
void DSU::Merge(int version, int a, int b)
{
    std::vector<int>* newVer = InitNewVersion(version);
    int parentA = GetParent(newVer, a);
    int parentB = GetParent(newVer, b);
    if(!(parentA == parentB))
    {
        newVer->at(parentA - 1) = parentB;
    }
}
int DSU::GetParent(std::vector<int> *version, int element)
{
     int v = version->at(element - 1);
     if(v == element)
         return element;
     return GetParent(version, v);
}
