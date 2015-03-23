#include "PSTree.h"

#include <algorithm>

PSTreeNode::PSTreeNode(size_t leftLim, size_t rightLim)
{
    this->leftLim = leftLim;
    this->rightLim = rightLim;
    if(leftLim == rightLim)
    {
        sums.push_back(0);
        left = NULL;
        right = NULL;
    }
    else
    {
        left = new PSTreeNode(leftLim, (leftLim + rightLim) /  2);
        right = new PSTreeNode((leftLim + rightLim) /  2 + 1, rightLim);
        sums.push_back(left->sums[0] + right->sums[0]);
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
        this->sums.push_back(value);
    else
    {
        if(position <= (this->leftLim + this->rightLim) / 2)
        {
            this->right->ProcessNoChanges();
            this->left->Add(version, position, value);
        }
        else
        {
            this->left->ProcessNoChanges();
            this->right->Add(version, position, value);
        }
        this->sums.push_back(this->left->sums.back() + this->right->sums.back());
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
void PSTreeNode::ProcessNoChanges()
{
    this->sums.push_back(this->sums.back());
    if(this->leftLim != this->rightLim)
    {
        this->left->ProcessNoChanges();
        this->right->ProcessNoChanges();
    }
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
