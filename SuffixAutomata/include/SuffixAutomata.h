#ifndef SUFFIX_AUTOMATA_H_
#define SUFFIX_AUTOMATA_H_

#include "IAlphabetConfig.h"
#include <string>
#include <vector>

class SuffixAutomata
{
    public:
        SuffixAutomata(IAlphabetConfig config, std::string baseString);
        virtual ~SuffixAutomata();
    private:
        class AutomataState
        {
            public:
                AutomataState(IAlphabetConfig& config, long long length);
            private:
                IAlphabetConfig& config_;
                long long length_;
                AutomataState* suffixLink_;
                std::vector<AutomataState*> transtions_;
        };

        IAlphabetConfig config_;
        std::string baseString_;
        std::vector<AutomataState*> states_;
};

#endif
