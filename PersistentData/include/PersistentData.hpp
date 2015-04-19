#ifndef __PERSISTENT_DATA_H__
#define __PERSISTENT_DATA_H__

#include <vector>
#include <stdlib.h>

template <class T>
class PersistentData
{
    public:
        void Add(size_t version, T element);
        T back();
        T operator [](int i) const;
    private:
        std::vector<int> versions;
        std::vector<T> elements;
};

#endif

template <class T>
void PersistentData<T>::Add(size_t version, T element)
{
    if(versions.size() != 0 && version < versions.back())
        throw std::exception();
    versions.push_back(version);
    elements.push_back(element);
}
template <class T>
T PersistentData<T>::back()
{
    return elements.back();
}
template <class T>
T PersistentData<T>::operator [](int i) const
{
    if(versions.size() == 0 || i < 0)
        throw std::exception();
    for(int j = versions.size() - 1; j >= 0; j--)
        if(versions[j] <= i)
            return elements[j];
}
