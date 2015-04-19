#include "PSTree.h"

#include <iostream>
#include <algorithm>

NodeData::NodeData(int added, int data)
{
    this->added = added;
    this->data = data;
}

PSTreeNode::PSTreeNode(size_t leftLim, size_t rightLim)
{
    this->leftLim = leftLim;
    this->rightLim = rightLim;
    if(leftLim == rightLim)
    {
        sums.Add(0, NodeData(0,0));
        left = NULL;
        right = NULL;
    }
    else
    {
        left = new PSTreeNode(leftLim, (leftLim + rightLim) /  2);
        right = new PSTreeNode((leftLim + rightLim) /  2 + 1, rightLim);
        sums.Add(0, NodeData(left->sums[0].added + right->sums[0].added, 0));
    }
}
int PSTreeNode::GetSum(int l, int r)
{
    if(l > rightLim || r < leftLim)
        return 0;
    if(leftLim >= l && rightLim <= r)
        return this->sums.back().data;
    return this->left->GetSum(l, r) + this->right->GetSum(l, r);
}
int PSTreeNode::GetSumAdded(int version, int l, int r)
{
    if(l > rightLim || r < leftLim)
        return 0;
    if(leftLim >= l && rightLim <= r)
        return this->sums[version].added;
    return this->left->GetSumAdded(version, l, r) + this->right->GetSumAdded(version, l, r);
}
void PSTreeNode::Add(int version, size_t position, int value, int data)
{
    if(this->leftLim == this->rightLim)
        this->sums.Add(version + 1, NodeData(value, data));
    else
    {
        if(position <= (this->leftLim + this->rightLim) / 2)
        {
            this->left->Add(version, position, value, data);
        }
        else
        {
            this->right->Add(version, position, value, data);
        }
        this->sums.Add(version + 1, NodeData(this->left->sums.back().added + this->right->sums.back().added,
                                             this->left->sums.back().data + this->right->sums.back().data));
    }
}
int PSTreeNode::GetKthStatistic(size_t l, size_t r, size_t k)
{
    if(this->leftLim == this->rightLim)
        return leftLim;
    if(this->left->sums[r].added - this->left->sums[l].added >= k)
    {
        return this->left->GetKthStatistic(l, r, k);
    }
    return this->right->GetKthStatistic(l, r,
                     k - (this->left->sums[r].added - this->left->sums[l].added));
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
        int value = this->GetSumAdded(i, indexes[i], indexes[i]);
        this->Add(i, indexes[i], value + 1, sorted[i]);
    }
}

int PSTree::GetSum(int l, int r)
{
    return this->root->GetSum(l, r);
}
int PSTree::GetSumAdded(int version, int l, int r)
{
    return root->GetSumAdded(version, l, r);
}
size_t PSTree::GetSize()
{
    return this->size;
}
void PSTree::Add(int version, size_t position, int value, int data)
{
    root->Add(version, position, value, data);
}
int PSTree::GetKthStatistics(size_t l, size_t r, size_t k)
{
    return sorted[root->GetKthStatistic(l, r, k + 1)];
}

/*void PSTreeNode::VersionSum::Add(int version, int sum)
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
*/
