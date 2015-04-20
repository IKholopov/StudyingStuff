#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include <utility>
#include <vector>
#include "Graph.h"

template <class T>
class PageRank: public Graph
{
    static const double d = 0.85;

    public:
        std::vector<T> Data;

        PageRank(unsigned int size);
        ~PageRank();

        bool AddPage(T page);
        int GetIndexOfPage(T page);         //-1 - not found
        void PageRankForSteps(int steps);
        std::vector<double> GetRank()
        { return *rank; }
    private:
        std::vector<double>* oldRank;
        std::vector<double>* rank;
};

template <class T>
PageRank<T>::PageRank(unsigned int size):Graph(size)
{
    this->size = size;
    oldRank = new std::vector<double>();
    rank = new std::vector<double>();
    for(int i = 0; i < size; ++i)
    {
        rank->push_back(1.0 / size);
    }
}
template <class T>
PageRank<T>::~PageRank()
{
    delete oldRank;
    delete rank;
}
template <class T>
bool PageRank<T>::AddPage(T page)
{
        if(GetIndexOfPage(page) != -1)
            return false;
        ++size;
        Data.push_back(page);
        return true;
}
template <class T>
int PageRank<T>::GetIndexOfPage(T page)
{
    for(int i = 0; i < size; ++i)
    {
        if(Data[i] == page)
        {
            return i;
        }
    }
    return -1;
}
template <class T>
void PageRank<T>::PageRankForSteps(int steps)
{
    for(int i = 0; i < steps; ++i)
    {
        std::vector<double>* temp = oldRank;
        oldRank = rank;
        rank = temp;
        rank->clear();
        for(int j = 0; j < size; ++j)
        {
            double sum = 0;
            std::vector<unsigned int> parents = GetParents(j);
            for(int k = 0; k < parents.size(); ++k)
            {
                if(j == k)
                    continue;
                std::vector<unsigned int> childs = GetChilds(parents[k]);
                sum += oldRank->at(k) / childs.size();
            }
            rank->push_back((1.0 - d) / size + d * sum);
        }
    }
}

#endif
