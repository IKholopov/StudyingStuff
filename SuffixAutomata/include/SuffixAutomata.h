#ifndef SUFFIX_AUTOMATA_H_
#define SUFFIX_AUTOMATA_H_

#include "IAlphabetConfig.h"
#include <string>
#include <vector>

class SuffixAutomata
{
    public:
        SuffixAutomata(IAlphabetConfig& config, std::string baseString);
        virtual ~SuffixAutomata();

        long long FindDifferentSubstrings();
    private:
        class AutomataState
        {
            public:
                AutomataState(IAlphabetConfig& config, long long id, long long length);
                AutomataState(AutomataState& state, long long id);

                long long GetId();
                long long GetLength();
                AutomataState* GetTransition(char c);
                AutomataState* GetSuffixLink();
                void SetTransition(char key, AutomataState* toState);
                void SetSuffixLink(AutomataState* toState);
                void SetLength(long long length);

            private:
                IAlphabetConfig& config_;
                long long id_;
                long long length_;
                AutomataState* suffixLink_;
                std::vector<AutomataState*> transtions_;
        };

        IAlphabetConfig& config_;
        std::string baseString_;
        std::vector<AutomataState*> states_;
        AutomataState* notAString_;
        AutomataState* root_;

        long long CalculatePathsFromNode(std::vector<long long>& paths, long long stateId);
};

#endif
