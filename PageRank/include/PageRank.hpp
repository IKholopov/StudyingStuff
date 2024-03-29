#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include <utility>
#include <vector>
#include <map>
#include <cmath>
#include "OrientedGraph.h"
#include "AdjacencyMatrixOriented.h"

template <class T>
class PageRank: public OrientedGraph
{
    public:
        std::map<T, unsigned int> Data;

        PageRank(unsigned int size, double d);
        ~PageRank();

        bool AddPage(T page);
        void InitRank();
        int GetIndexOfPage(const T& page);         //-1 - not found
        void PageRankForSteps(int steps);
        void PageRankToConverge();
        std::vector<double> GetRank()
        { return *rank; }
    private:
        double d;
        std::vector<double>* oldRank;
        std::vector<double>* rank;
};

template <class T>
PageRank<T>::PageRank(unsigned int size, double d):OrientedGraph(size, new AdjacencyMatrixOriented())
{
    this->d = d;
    oldRank = new std::vector<double>();
    rank = new std::vector<double>();
    for(int i = 0; i < this->size(); ++i)
    {
        rank->push_back(1.0 / this->size());
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
        this->addNodes(1);
        Data[page] = this->size() - 1;
        return true;
}
template <class T>
void PageRank<T>::InitRank()
{
    oldRank->clear();
    rank->clear();
    for(int i = 0; i < size(); ++i)
    {
        rank->push_back(1.0 / size());
    }
}
template <class T>
int PageRank<T>::GetIndexOfPage(const T& page)
{
    if(Data.find(page) == Data.end())
        return -1;
    return Data[page];
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
        for(int j = 0; j < size(); ++j)
        {
            double sum = 0;
            auto parents = getParents(j);
                for(int k = 0; k < parents->size(); ++k)
            {
                if(j == k)
                    continue;
                auto childs = getChilds(parents->at(k));
                sum += oldRank->at(k) / childs->size();
                delete childs;
            }
            rank->push_back((1.0 - d) / size() + d * sum);
            delete parents;
        }
    }
}
template <class T>
void PageRank<T>::PageRankToConverge()
{
    double error = 0.001;
    bool converge = false;
    while(!converge)
    {
            PageRankForSteps(1);
            converge = true;
            for(int i = 0; i < this->size(); ++i)
                if(std::abs(oldRank->at(i) - rank->at(i)) > error)
                {
                    converge = false;
                    break;
                }
    }
}

#endif
