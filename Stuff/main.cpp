#define uint unsigned int

#include <iostream>
#include <list>

class DSU
{
    public:
        std::list<uint> Roots;
};
class DSUTree
{
    public:
        int index;
        DSU value;
        DSUTree* l;
        DSUTree* r;
        void Append( );//
};

int main()
{
    return 0;
}
