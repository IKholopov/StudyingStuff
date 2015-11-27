#include "AhoAutomata.h"
#include "AhoMaskAutomata.h"
#include "ConfigFactory.h"
#include <iostream>
#include <sstream>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Aho_test
#include <boost/test/unit_test.hpp>

int AhoTest(std::string pattern, std::string input, std::string result)
{
    std::stringstream patternstream, string, out;
    patternstream << pattern;
    string << input;
    auto a = AhoMaskAutomata(AhoConfigFactory::Config(), patternstream);
    a.FindTemplate(string, out);
    std::string res;
    res = out.str();
    std::cout << res <<std::endl;
    return res.compare(result);
}

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
    BOOST_CHECK(AhoTest("ab??aba??", "ababacabad", "") == 0);
    BOOST_CHECK(AhoTest("", "", "") == 0);
    BOOST_CHECK(AhoTest("a?a?a?a?a?a   ", "ababababababababababababababab  ", "0 2 4 6 8 10 12 14 16 18 ") == 0);
    BOOST_CHECK(AhoTest("ab??aba?", "ababacabad", "2 ") == 0);
    BOOST_CHECK(AhoTest("ab??aba", "ababacabad", "2 ") == 0);
    BOOST_CHECK(AhoTest("?ab???ab????ab", "abccabccabccabvvvabbbbbabv", "11 ") == 0);
}
