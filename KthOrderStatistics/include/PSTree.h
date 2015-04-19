#ifndef __PSTree_H__
#define __PSTree_H__

#include <stdlib.h>
#include <vector>
#include "PersistentData.hpp"

class NodeData{
    public:
        NodeData(int added, int data);
        int added;
        int data;
};

class PSTreeNode
{
    public:
        PSTreeNode(size_t leftLim, size_t rightLim);
        int GetSum(int l, int r);
        int GetSumAdded(int version, int l, int r);
        void Add(int version, size_t position, int value, int data);
        int GetKthStatistic(size_t l, size_t r, size_t k);

        //DEBUG
        static void TestVSum();

    private:
        PSTreeNode* left;
        PSTreeNode* right;
        size_t leftLim;
        size_t rightLim;
        PersistentData<NodeData> sums;
};

class PSTree
{
    public:
        PSTree(int* data, size_t size);
        int GetSum(int l, int r);
        int GetSumAdded(int version, int l, int r);
        size_t GetSize();
        int GetKthStatistics(size_t l, size_t r, size_t k);
    private:
        std::vector<int> sorted;
        void Add(int version, size_t position, int value, int data);
        PSTreeNode* root;
        size_t size;
};

#endif
