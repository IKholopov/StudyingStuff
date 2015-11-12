#include "AhoAutomata.h"
#include "AhoMaskAutomata.h"
#include "ConfigFactory.h"
#include <iostream>
#include <sstream>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Aho_test
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(Trie_test)
{
    std::vector<std::string> v = {"abc", "bcdc", "cccb", "bcdd", "bbbc"};
    std::stringstream string;
    string << "abcdcbcddbbbcccbbbcccbb";
    auto a = AhoAutomata(AhoConfigFactory::Config(), v);
    a.FindTemplates(string, std::cout);
}
BOOST_AUTO_TEST_CASE(Aho_test)
{
    std::stringstream pattern, string;
    pattern << "ab??aba";
    string << "ababacaba";
    auto a = AhoMaskAutomata(AhoConfigFactory::Config(), pattern);
    //a.FindTemplates(std::cin, std::cout);
    a.FindTemplate(string, std::cout);
}
