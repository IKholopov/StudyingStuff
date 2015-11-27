#include "SuffixTree.h"
#include "EnglishAlphabetConfig.h"
#include <iostream>
#include <sstream>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Aho_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(suffixTree)
{
    EnglishAlphabetConfig conf;
    SuffixTree tree(conf, "lookatmyhorsemyhorseisamazing$");
    tree.PrintTree(std::cout);
    BOOST_CHECK(tree.LCSWith("amazingsemyhorse").compare("semyhorse") == 0);
    SuffixTree tree2(conf, "abaaba$");
    tree2.PrintTree(std::cout);
    BOOST_CHECK(tree2.LCSWith("bbaa").compare("baa") == 0);
    int a = 0;
}
