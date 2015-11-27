#include "SuffixTree.h"
#include "EnglishAlphabetConfig.h"
#include <iostream>


int main()
{
    std::string s1, s2;
    std::cin >> s1;
    std::cin >> s2;
    EnglishAlphabetConfig conf;
    SuffixTree tree(conf, s1);
    std::cout << tree.LCSWith(s2) << std::endl;
    return 0;
}

