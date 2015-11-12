#include "AhoMaskAutomata.h"
#include "ConfigFactory.h"
#include <iostream>


int main()
{
    auto a = AhoMaskAutomata(AhoConfigFactory::Config(), std::cin);
    a.FindTemplate(std::cin, std::cout);
    return 0;
}

