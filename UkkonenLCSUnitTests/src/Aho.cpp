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
    SuffixTree tree(conf, "cacao");
    tree.PrintTree(std::cout);
    int a = 0;
}
