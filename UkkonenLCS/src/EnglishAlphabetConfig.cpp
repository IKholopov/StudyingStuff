#include "EnglishAlphabetConfig.h"
#include <assert.h>

EnglishAlphabetConfig::EnglishAlphabetConfig():alphabetSize_(37)
{
}

long long EnglishAlphabetConfig::GetLetterId(char c)
{
    assert(AssertCorrectSuymbol(c));
    if(c == '$')
        return 26;
    if(c >= '0' && c <= '9')
        return 27 + (c - '0');
    return c - 'a';
}
char EnglishAlphabetConfig::GetLetter(long long id)
{
    assert(id >= 0 && id < 37);
    if(id == 26)
        return '$';
    if(id >= 27)
        return '0' + id - 27;
    return 'a' + id;
}
long long EnglishAlphabetConfig::GetAlphabetSize()
{
    return alphabetSize_;
}
bool EnglishAlphabetConfig::AssertCorrectSuymbol(char c)
{
    return (c >='a' && c <= 'z') || (c == '$') || (c >= '0' && c <= '9');
}

