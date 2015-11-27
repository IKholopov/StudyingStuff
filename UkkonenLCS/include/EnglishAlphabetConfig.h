#ifndef UKKONEN_LCS_ENGLISH_ALPHABET_CONFIG
#define UKKONEN_LCS_ENGLISH_ALPHABET_CONFIG

#include "IAlphabetConfig.h"

class EnglishAlphabetConfig: public IAlphabetConfig
{
    public:
        EnglishAlphabetConfig();

        long long GetLetterId(char c);
        char GetLetter(long long id);
        long long GetAlphabetSize();
        bool AssertCorrectSuymbol(char c);
    private:
        const long long alphabetSize_;
};

#endif
