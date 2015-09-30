#include <iostream>
#include "NetworkManager.h"

int main()
{
    std::vector<ValuedEdge<NetworkEdgeValue<int>*>*> v;
    NetworkManager<int>::instance().ThreeIndiansAlgorithm(10, v, 0, 9);
    return 0;
}
