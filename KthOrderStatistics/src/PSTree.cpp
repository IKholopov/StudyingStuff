#include "PSTree.h"

#include <iostream>
#include <algorithm>

PSTreeNode::PSTreeNode(size_t leftLim, size_t rightLim)
{
    this->leftLim = leftLim;
    this->rightLim = rightLim;
    if(leftLim == rightLim)
    {
        sums.Add(0, 0);
        left = NULL;
        right = NULL;
    }
    else
    {
        left = new PSTreeNode(leftLim, (leftLim + rightLim) /  2);
        right = new PSTreeNode((leftLim + rightLim) /  2 + 1, rightLim);
        sums.Add(0, left->sums[0] + right->sums[0]);
    }
}

int PSTreeNode::GetSum(int version, int l, int r)
{
    if(l > rightLim || r < leftLim)
        return 0;
    if(leftLim >= l && rightLim <= r)
        return this->sums[version];
    return this->left->GetSum(version, l, r) + this->right->GetSum(version, l, r);
}
void PSTreeNode::Add(int version, size_t position, int value)
{
    if(this->leftLim == this->rightLim)
        this->sums.Add(version + 1, value);
    else
    {
        if(position <= (this->leftLim + this->rightLim) / 2)
        {
            this->left->Add(version, position, value);
        }
        else
        {
            this->right->Add(version, position, value);
        }
        this->sums.Add(version + 1, this->left->sums.back() + this->right->sums.back());
    }
}
int PSTreeNode::GetKthStatistic(size_t l, size_t r, size_t k)
{
    if(this->leftLim == this->rightLim)
        return leftLim;
    if(this->left->sums[r] - this->left->sums[l] >= k)
    {
        return this->left->GetKthStatistic(l, r, k);
    }
    return this->right->GetKthStatistic(l, r,
                     k - (this->left->sums[r] - this->left->sums[l]));
}


PSTree::PSTree(int *data, size_t size)
{
    this->size = size;
    sorted.assign(data, data + size);
    std::sort(sorted.begin(), sorted.end());
    std::vector<int> indexes;
    for(int i = 0; i < size; ++i)
        indexes.push_back(std::lower_bound(sorted.begin(), sorted.end(), data[i]) - sorted.begin());
    this->root = new PSTreeNode(0, size - 1);
    for(int i = 0; i < size; ++i)
    {
        int value = this->GetSum(i, indexes[i], indexes[i]);
        this->Add(i, indexes[i], value + 1);
    }
}

int PSTree::GetSum(int version, int l, int r)
{
    return root->GetSum(version, l, r);
}
void PSTree::Add(int version, size_t position, int value)
{
    root->Add(version, position, value);
}
int PSTree::GetKthStatistics(size_t l, size_t r, size_t k)
{
    return sorted[root->GetKthStatistic(l, r, k + 1)];
}

void PSTreeNode::VersionSum::Add(int version, int sum)
{
    if(versions.size() != 0 && version < versions.back())
        throw std::exception();
    versions.push_back(version);
    sums.push_back(sum);
}
int PSTreeNode::VersionSum::back()
{
    return sums.back();
}
int PSTreeNode::VersionSum::operator [](int i) const
{
    if(versions.size() == 0 || i < 0)
        throw std::exception();
    for(int j = versions.size() - 1; j >= 0; j--)
        if(versions[j] <= i)
            return sums[j];
}


//DEBUG
void PSTreeNode::TestVSum()
{
    VersionSum v;
    for(int i = 0; i < 10; i += 2)
        v.Add(i, i);
    for(int i = 0; i < 10; ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}
