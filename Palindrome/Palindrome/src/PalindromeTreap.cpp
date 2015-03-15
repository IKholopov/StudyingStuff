#include"PalindromeTreap.h"

#include<vector>

std::vector<unsigned long long> PalindromeTreapTree::pows;
unsigned long long PalindromeTreapTree::Pow(unsigned long long b)
{
    if(pows.size() > b)
        return pows[b];
    else
        for(int i = pows.size() - 1; i < b; ++i)
            pows.push_back(pows[i] * P_BASE);
    return pows[b];
}

PalindromeTreapTree::PalindromeTreapTree(std::string s):ImplicitTreapTree()
{
    pows.push_back(1);
    if(s[0] == '\0')
        return;
    this->head = (ImplicitTreapNode<char>*)new PalindromeTreapNode(s[0]);
    ++size;
    int n = s.length();
    for(int i = 1; i < n; ++i)
    {
        ImplicitTreapTree<char>::Add(i, s[i]);
    }
}
void PalindromeTreapTree::SetAt(unsigned int i, char c)
{
    ((PalindromeTreapNode*)this->head)->SetAt(i, c);
}
bool PalindromeTreapTree::CheckPalindrome(unsigned int i, unsigned int j)
{
    if(j - i < 1)
        return true;
    ImplicitTreapNode<char> *l, *lz, *mz, *rz, *r;
    this->head->Split(i, l, r);
    r->Split(j + 1 - i, lz, r);
    bool result = false;
    if((j - i) % 2 == 1)
    {
        lz->Split((j - i) / 2 + 1, lz, rz);
#ifdef DEBUG
        lz->PrintTree();
        rz->PrintTree();
#endif
        if(((PalindromeTreapNode*)lz)->GetLeftHash() ==
                ((PalindromeTreapNode*)rz)->GetRightHash())
            result = true;
        lz = ImplicitTreapNode<char>::Merge(lz, rz);
    }
    else
    {
        lz->Split((j - i) / 2, lz, mz);
        mz->Split(1, mz, rz);
#ifdef DEBUG
        lz->PrintTree();
        rz->PrintTree();
#endif
        if(((PalindromeTreapNode*)lz)->GetLeftHash() ==
                ((PalindromeTreapNode*)rz)->GetRightHash())
            result = true;
        lz = ImplicitTreapNode<char>::Merge(lz, ImplicitTreapNode<char>::Merge(mz, rz));
    }
    this->head = ImplicitTreapNode<char>::Merge(l, ImplicitTreapNode<char>::Merge(lz, r));
    return result;
}


void PalindromeTreapNode::SetAt(unsigned int i, char c)
{
    if(this->Count == 0)
        return;
    int index = GetCountOf(this->left);
    if(index == i)
    {
        this->SetData(c);
        this->UpdateCount();
    }
    if(index < i)
    {
        if(this->right == NULL)
            return;
        ((PalindromeTreapNode*)this->right)->SetAt(i - index - 1, c);
        this->UpdateCount();
    }
    else
    {
        if(this->left == NULL)
            return;
        ((PalindromeTreapNode*)this->left)->SetAt(i, c);
        this->UpdateCount();
    }
}
void PalindromeTreapNode::UpdateCount()
{
    ImplicitTreapNode<char>::UpdateCount();
    unsigned int cl = 0;
    unsigned int cr = 0;
    hashLeft = 0;
    hashRight = 0;
    cl += GetCountOf(this->left);
    cr += GetCountOf(this->right);
    if(this->left != NULL)
    {
        hashLeft += ((PalindromeTreapNode*)this->left)->hashLeft;
        hashRight += ((PalindromeTreapNode*)this->left)->hashRight *
                PalindromeTreapTree::Pow(cr + 1);
    }
    if(this->right != NULL)
    {
        hashLeft += ((PalindromeTreapNode*)this->right)->hashLeft *
                PalindromeTreapTree::Pow(cl + 1);
        hashRight += ((PalindromeTreapNode*)this->right)->hashRight;
    }
    hashLeft += this->GetData() * PalindromeTreapTree::Pow(cl);
    hashRight += this->GetData() * PalindromeTreapTree::Pow(cr);
}
PalindromeTreapNode *PalindromeTreapNode::Add(int position, char data)
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
        ImplicitTreapNode<char>::Split(position, l, r);
        ImplicitTreapNode* element = new PalindromeTreapNode(rand(), data);
        result = Merge(Merge(l, element), r);
    }
    return (PalindromeTreapNode*)result;
}
