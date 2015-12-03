#include "SuffixAutomata.h"
#include "EnglishAlphabetConfig.h"
#include <iostream>


int main()
{
    std::string s1;
    std::cin >> s1;
    EnglishAlphabetConfig conf;
    SuffixAutomata automata(conf, s1);
    std::cout << automata.FindDifferentSubstrings() << std::endl;
    return 0;
}

