#include "SuffixAutomata.h"
#include "EnglishAlphabetConfig.h"
#include <iostream>
#include <sstream>
#include <random>
#include <unordered_map>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Aho_test
#include <boost/test/unit_test.hpp>


long long GetAllSubstrings(std::string s)
{
    std::unordered_map<std::string , long long> substr;
    for(int i = 0; i < s.size(); ++i)
    {
        for(int j = 0; j < s.size() - i; ++j)
            substr.insert(std::pair<std::string, long long>(s.substr(j, i + 1), 0));
    }
    return substr.size();
}

BOOST_AUTO_TEST_CASE(suffixTree)
{
    EnglishAlphabetConfig conf;
    int length = 100;
    for(int i = 0; i < 10000; ++i)
    {
        std::string s = "";
        for(int j = 0; j < length; ++j)
            s += rand() % 26 + 'a';
        auto x = GetAllSubstrings(s);
        SuffixAutomata tree0(conf, s);
        int a = tree0.FindDifferentSubstrings();
        if(a != x)
            std::cout << s <<std::endl;
        BOOST_CHECK(tree0.FindDifferentSubstrings() == x);
    }
    auto x = GetAllSubstrings("kppa");
    SuffixAutomata tree0(conf, "kppa");
    int a = tree0.FindDifferentSubstrings();
}
