#ifndef __PSTree_H__
#define __PSTree_H__

#include <stdlib.h>
#include <vector>

class PSTreeNode
{
    public:
        PSTreeNode(size_t leftLim, size_t rightLim);
        int GetSum(int version, int l, int r);
        void Add(int version, size_t position, int value);
        int GetKthStatistic(size_t l, size_t r, size_t k);

        //DEBUG
        static void TestVSum();

    private:
        class VersionSum
        {
            public:
                void Add(int version, int sum);
                int back();
                int operator [](int i) const;
            private:
                std::vector<int> versions;
                std::vector<int> sums;
        };

        PSTreeNode* left;
        PSTreeNode* right;
        size_t leftLim;
        size_t rightLim;
        VersionSum sums;
};

class PSTree
{
    public:
        PSTree(int* data, size_t size);
        int GetSum(int version, int l, int r);
        int GetKthStatistics(size_t l, size_t r, size_t k);
    private:
        std::vector<int> sorted;
        void Add(int version, size_t position, int value);
        PSTreeNode* root;
        size_t size;
};

#endif
