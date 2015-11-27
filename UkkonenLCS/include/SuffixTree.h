#ifndef UKKONEN_LCS_SUFFIX_TREE_H
#define UKKONEN_LCS_SUFFIX_TREE_H

#include "IAlphabetConfig.h"
#include "ExplicitState.h"
#include <set>
#include <string>
#include <ostream>

class SuffixTree
{
    public:
        SuffixTree(IAlphabetConfig& config, std::string string);
        ~SuffixTree();

        std::string LCSWith(std::string t);
        void PrintTree(std::ostream& out);
    private:
        ExplicitState::Pass Update(ExplicitState* state, long long left, long long right);
        ExplicitState::Pass Canonize(ExplicitState* state, long long left, long long right);
        bool TestEndPointAndSplit(ExplicitState::Pass pass, char c, ExplicitState*& state);
        char Sequence(long long id);
        void PrintTree(std::ostream& out, long long max);

        IAlphabetConfig& config_;
        std::string string_;
        std::vector<ExplicitState*> states_;
        ExplicitState* notAString;  //joker
        ExplicitState* emptyString;
        const long long inf;
};

#endif
