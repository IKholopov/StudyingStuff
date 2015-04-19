#include "PermutationTreap.hpp"

void PermutationTreapNode::Push()
{
    if(!this->IsShouldReverse())
        return;
    this->UpdateCount();
    ImplicitTreapNode* swap = this->left;
    this->left = this->right;
    this->right = swap;
    this->shouldReverse = false;
    if(this->isUnstrictDecrease == true && this->GetSubLeft() != this->GetSubRight())
        this->isUnstrictDecrease = false;
    if(this->left != NULL)
    {
        ((PermutationTreapNode*)this->left)->shouldReverse ^= true;
    }
    if(this->right != NULL)
    {
        ((PermutationTreapNode*)this->right)->shouldReverse ^= true;
    }

}
PermutationTreapNode *PermutationTreapNode::GetSubLeft()
{
    if(this->GetLeft() == NULL)
        return this;
    return ((PermutationTreapNode*)this->GetLeft())->GetSubLeft();
}
PermutationTreapNode *PermutationTreapNode::GetSubRight()
{
    if(this->GetRight() == NULL)
        return this;
    return ((PermutationTreapNode*)this->GetRight())->GetSubRight();
}

PermutationTreapNode* PermutationTreapNode::Add(int position, int data)
{
    ImplicitTreapNode* result;
    if(this->Count == 0)
    {
        this->y = rand();
        this->left = NULL;
        this->right = NULL;
        this->Data = data;
        this->shouldReverse = false;
        this->Count = 1;
        result = this;
        UpdateCount();
    }
    else
    {
        ImplicitTreapNode *l, *r;
        ImplicitTreapNode<int>::Split(position, l, r);
        ImplicitTreapNode* element = new PermutationTreapNode(rand(), data);
        result = Merge(Merge(l, element), r);
    }
    return (PermutationTreapNode*)result;
}
void PermutationTreapNode::UpdateCount()
{
    ImplicitTreapNode<int>::UpdateCount();

    isUnstrictDecrease = true;
    if(GetLeft() != NULL)
    {
        if(!((PermutationTreapNode*)GetLeft())->isUnstrictDecrease ||
                ((PermutationTreapNode*)GetLeft())->GetSubRight()->GetData() < GetData())
            isUnstrictDecrease = false;
    }
    if(GetRight() != NULL)
    {
        if(!((PermutationTreapNode*)GetRight())->isUnstrictDecrease ||
                GetData() < ((PermutationTreapNode*)GetRight())->GetSubLeft()->GetData())
            isUnstrictDecrease = false;
    }

    sum = Data;
    if(left != NULL)
        sum += ((PermutationTreapNode*)left)->sum;
    if(right != NULL)
        sum += ((PermutationTreapNode*)right)->sum;
}

size_t PermutationTreapNode::GetFirstOfLastDecrease()
{
    this->Push();
    size_t count = 0;
    PermutationTreapNode* t = this;

    while(t->GetRight() != NULL && !((PermutationTreapNode*)t->right)->isUnstrictDecrease)
    {
        if(t->left != NULL)
            count += t->GetCountOf(t->left);
        count += 1;
        t =(PermutationTreapNode*)t->right;
        t->Push();
    }
    if(t->right != NULL)
        t->right->UpdateCount();
    if(t->right != NULL &&
            t->GetData() < ((PermutationTreapNode*)t->right)->GetSubLeft()->GetData())
    {
        if(t->left != NULL)
            count += t->GetCountOf(t->left);
        count += 1;
        return count;
    }
    if(t->left != NULL)
        t->left->UpdateCount();
    if(t->left != NULL &&
            ((PermutationTreapNode*)t->left)->GetSubRight()->GetData() >= t->GetData())
        return count + ((PermutationTreapNode*)t->left)->GetFirstOfLastDecrease();
    if(t->left != NULL)
        count += t->GetCountOf(t->left);
    return count;
}
long long PermutationTreapNode::GetSum()
{
    return sum;
}
long long PermutationTreapNode::GetSum(int i, int j)
{
    ImplicitTreapNode<int> *l, *z, *r;
    ImplicitTreapNode<int>::Split(i, l, r);
    r->Split(j + 1 - i, z, r);
    long long sum = ((PermutationTreapNode*)z)->GetSum();
    Merge(Merge(l, z), r);
    return sum;
}

PermutationTreapTree::PermutationTreapTree()
{
    this->head = new PermutationTreapNode();
}
PermutationTreapTree::PermutationTreapTree(int y, int data)
{
    this->head = new PermutationTreapNode(y, data);
}
bool PermutationTreapTree::NextPermutation(size_t i, size_t j)
{
    ImplicitTreapNode<int> *l, *set, *r;
    this->head->Split(i, l, r);
    r->Split(j - i + 1, set, r);
    int a = ((PermutationTreapNode*)set)->GetFirstOfLastDecrease();
    bool result = true;
    if(a != 0)
    {
        ImplicitTreapNode<int> *t, *setL, *setR;
        set->Split(a, setL, setR);
        setR->Reverse(0, j - i + 1 - a);
        int toChange = setL->GetPosition(a - 1)->GetData();
        t = setR;
        int count = 0;
        while(t->GetLeft() != NULL || t->GetRight() != NULL)
        {
            t->Push();
            if(t->GetData() > toChange)
            {
                if(t->GetLeft() != NULL)
                    t->GetLeft()->Push();
                if(t->GetLeft() != NULL && ((PermutationTreapNode*)t->GetLeft())->GetSubRight()->GetData() > toChange)
                    t = t->GetLeft();
                else
                {
                    count += ImplicitTreapNode<int>::GetCountOf(t->GetLeft());
                    break;
                }
            }
            else
            {
                    count += ImplicitTreapNode<int>::GetCountOf(t->GetLeft()) + 1;
                    t = t->GetRight();
            }
        }

        int oldT = t->GetData();
        setR->SetAt(count, toChange);
        set = ImplicitTreapNode<int>::Merge(setL, setR);
        set->SetAt(a - 1, oldT);
    }
    else
    {
        set->Reverse(a, j - i + 1);
        result = false;
    }
    this->head = ImplicitTreapNode<int>::Merge(
                ImplicitTreapNode<int>::Merge(l, set),
                r);
    return result;
}
