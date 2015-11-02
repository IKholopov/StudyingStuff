#include "Strings.h"

Strings::Strings()
{

}

Strings& Strings::lib()
{
    static Strings lib;
    return lib;
}

std::vector<long long> Strings::Prefix(std::string s)
{
    std::vector<long long> prefix;
    prefix.push_back(0);
    for(long long i = 1; i < s.size(); ++i)
    {
        long long last = prefix.at(i - 1);
        while(last > 0 && s[i] != s[last])
            last = prefix[last - 1];
        if(s[i] == s[last])
            ++last;
        prefix.push_back(last);
    }
    return prefix;
}
void Strings::PrefixTemplate(std::istream& input, std::ostream& output)
{
    std::string pattern = "";
    input >> pattern;
    pattern += '#';
    std::vector<long long> prefix = this->Prefix(pattern);
    char c;
    long long prev = prefix.at(prefix.size() - 1);
    long long counter = 0;
    while(input.get(c) && (counter == 0 || (c != '\n' && c != ' ')))
    {
        long long last = prev;
        while(last > 0 && c != pattern[last])
            last = prefix[last - 1];
        if(c == pattern[last])
            ++last;
        prev = last;
        if(last == pattern.size() - 1)
            output << (counter - (pattern.size() - 1)) << " ";
        ++counter;
    }
}
