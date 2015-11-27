#ifndef UKKONEN_LCS_IALPHABET_CONFIG
#define UKKONEN_LCS_IALPHABET_CONFIG

class IAlphabetConfig
{
    public:
        virtual long long GetLetterId(char c) = 0;
        virtual char GetLetter(long long id) = 0;
        virtual long long GetAlphabetSize() = 0;
        virtual bool AssertCorrectSuymbol(char c) = 0;
};

#endif
