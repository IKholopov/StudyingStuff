#include "DSU.h"


DSUElement::DSUElement(int value)
{
    this->value = value;
    this->parent.push_back(this);
    versions = 0;
}

DSUElement* DSUElement::GetParent(int version)
{
    if(parent[version] == this)
        return parent[version];
    return parent[version]->GetParent(version);
}
void DSUElement::SetParent(DSUElement* parent)
{
    this->parent.push_back(parent);
    versions++;
}

DSU::DSU(std::vector<int> values)
{
    for(int i = 0; i < values.size(); ++i)
    {
        DSUElement* element = new DSUElement(values[i]);
        elements.push_back(element);
    }
    units.push_back(elements);
    versions = 0;
}

bool DSU::Find(int version, int a, int b)
{
    if(elements[a - 1]->GetParent(version) ==
            elements[b - 1]->GetParent(version))
    {
        InitNewVersion();
        units.push_back(units.back());
        return true;
    }
    InitNewVersion();
    return false;
}
void DSU::InitNewVersion()
{
    ++versions;
    for(int i = 0; i < elements.size(); ++i)
        if(elements[i]->versions != versions)
        {
            elements[i]->SetParent(elements[i]->GetLastParent());
        }
}
void DSU::Merge(int version, int a, int b)
{
    if(!(elements[a - 1]->GetParent(version) ==
          elements[b - 1]->GetParent(version)))
    {
        std::vector<DSUElement*> unit = units.back();
        DSUElement* oldParent = elements[a - 1]->GetParent(version);
        for(int i = 0; i < unit.size(); ++i)
            if(oldParent == unit[i])
            {
                unit.erase(unit.begin() + i);
                break;
            }
        elements[a - 1]->SetParent(elements[b - 1]->GetParent(version));
        units.push_back(unit);
    }
    InitNewVersion();
}
