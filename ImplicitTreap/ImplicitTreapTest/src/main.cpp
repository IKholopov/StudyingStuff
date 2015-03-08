#include<stdio.h>
#include"ImplicitTreapTree.h"

int main()
{
    int keys[] = {8, 14, 14, 2, 9, 14, 12, 6, 1, 13,
                  5, 7, 14, 7, 12, 2, 5, 1, 12, 11};
    int values[] = {8, 14, 14, 2, 9, 14, 12, 6, 1, 13,
                    5, 7, 14, 7, 12, 2, 5, 1, 12, 11};
    srand(4393);
    ImplicitTreapTree<int>* t = new ImplicitTreapTree<int>(rand(), 8);
    t->Remove(0);
    t->Add(0, 88);
    t->Add(1, 14);
    t->Add(2, 16);
    t->Add(0, 10);
    t->Add(0, 2);
    t->Remove(1);
    t->Add(2, 100);
    t->Add(3, 39);
    t->Add(3, 45);
    ImplicitTreapNode<int>* t1 = t->GetPosition(0);
    t->GetPosition(2)->SetData(1000000);
    delete t;
    return 0;
}
