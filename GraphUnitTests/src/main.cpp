#include <iostream>
#include "TestShortestPath.hpp"
#include "TestMST.h"

int main()
{
    //TestMy1KBFS(1, 10);
    TestShortestPaths(0.01);
    TestShortestPaths(0.05);
    TestShortestPaths(0.1);
    //GrandTest(0.5);
    return 0;
}
