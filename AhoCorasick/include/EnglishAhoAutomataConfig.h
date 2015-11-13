#ifndef ENGLISH_AHO_AUTOMATA_CONFIG
#define ENGLISH_AHO_AUTOMATA_CONFIG

#include "IAhoAutomataConfig.h"

#include <unordered_map>

class EnglishAhoAutomataConfig: public IAhoAutomataConfig
{
    public:
        EnglishAhoAutomataConfig();
        unsigned long long GetLetterId(char c);
        unsigned long long GetAlphabetSize();
        bool AssertCorrectSymbol(char c);
    private:
        unsigned long long alphabetSize_;
        std::unordered_map<char, unsigned long long> lettersCodes_;
};

#endif
