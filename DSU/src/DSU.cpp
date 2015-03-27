#include "DSU.h"


DSUElement::DSUElement(int value)
{
    this->value = value;
    this->parent.push_back(this);
    this->versions.push_back(0);
}

DSUElement* DSUElement::GetParent(int version)
{
    int v = LocateParentIdAt(version);
    if(parent[v] == this)
        return parent[v];
    return parent[v]->GetParent(version);
}
void DSUElement::SetParent(DSUElement* parent, int version)
{
    this->parent.push_back(parent);
    versions.push_back(version);
}
int DSUElement::LocateParentIdAt(int version)
{
    for(int i = versions.size() - 1; i >= 0; --i)
        if(this->versions[i] <= version)
            return i;
}

DSU::DSU(std::vector<int> values)
{
    for(int i = 0; i < values.size(); ++i)
    {
        DSUElement* element = new DSUElement(values[i]);
        elements.push_back(element);
    }
    versions = 0;
}

bool DSU::Find(int version, int a, int b)
{
    ++versions;
    if(elements[a - 1]->GetParent(version) ==
            elements[b - 1]->GetParent(version))
        return true;
    return false;
}
void DSU::Merge(int version, int a, int b)
{
    ++versions;
    if(!(elements[a - 1]->GetParent(version) ==
          elements[b - 1]->GetParent(version)))
    {
        elements[a - 1]->SetParent(elements[b - 1]->GetParent(version), versions);
    }
}
