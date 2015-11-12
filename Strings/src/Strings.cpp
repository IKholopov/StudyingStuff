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
std::vector<long long> Strings::ZFunction(std::string s)
{
    unsigned long long left = 0;
    unsigned long long right = 0;
    std::vector<long long> z;
    z.push_back(s.size());
    for(long long i = 1; i < s.size(); ++i)
    {
        long long index = 0;
        if(i > right) {
            for(long long j = 0; s[j + i] == s[j] && j + i < s.size(); ++j)
                ++index;
            left = i;
            right = i + index - 1;
        }
        else {
            if(i + z.at(i - left) > right) {
                index = right - i;
                for(long long j = 0; s[j + right] == s[j + right - i] && j + right - i < s.size(); ++j)
                    ++index;
                left = i;
                right = i + index - 1;
            }
            else
                index = z.at(i - left);
        }
        z.push_back(index);
    }
    return z;
}
std::string Strings::PrefixDecode(std::vector<long long>& prefixFunc)
{
    std::string prefix = "";
    if(prefixFunc.size() > 0)
        prefix += "a";
    for(long long i = 1; i < prefixFunc.size(); ++i)
    {
        if(prefixFunc[i] == 0)
            prefix += prefix[prefixFunc[i - 1]] + 1;
        else
            prefix += prefix[prefixFunc[i] - 1];
    }
    return prefix;
}
void Strings::PrefixDecode(std::istream& input, std::ostream& output)
{
    std::ios::sync_with_stdio(false);
    long long d1, d2;
    char c;
    std::string prefix = "";
    if(!(input >> d1)) {
        output << prefix;
        std::ios::sync_with_stdio(true);
        return;
    }
    input.get(c);
    prefix += "a";
    do {
        if(!(input >> d2))
            break;
        if(d2 == 0)
            prefix += prefix[d1] + 1;
        else
            prefix += prefix[d2 - 1];
        d1 = d2;
    }while(input.get(c) && c != '\0' && c != '\n');
    output << prefix;
    std::ios::sync_with_stdio(true);
}
void Strings::ZFunctionDecode(std::istream& input, std::ostream& output)
{
    std::ios::sync_with_stdio(false);
    long long d1, d2, temp;
    char c;
    std::string prefix = "";
    if(!(input >> d1)) {
        output << prefix;
        std::ios::sync_with_stdio(true);
        return;
    }
    input.get(c);
    prefix += "a";
    d1 = 0;
    do {
        if(!(input >> d2))
            break;
        if(d2 == 0)
            prefix += prefix[d1] + 1;
        else {
            prefix += prefix[0];
            for(long long j = 1; j < d2; ++j)
            {
                prefix += prefix[j];
                input >> temp;
            }
        }
        d1 = d2;
    }while(input.get(c) && c != '\0' && c != '\n');
    output << prefix;
    std::ios::sync_with_stdio(true);
}
void Strings::ZFunctionTemplate(std::istream& input, std::ostream& output)
{
    std::string pattern = "";
    input >> pattern;
    pattern += "#";
    std::vector<long long> prefix = this->ZFunction(pattern);
    std::string string;
    input >> string;
    long long left = -1;
    long long right = -1;
    for(long long i = 0; i < string.size(); ++i)
    {
        long long index = 0;
        if(i > right) {
            for(long long j = 0; string[j + i] == pattern[j] && j + i < string.size(); ++j)
                ++index;
            left = i;
            right = i + index - 1;
        }
        else {
            if(i + prefix.at(i - left) > right) {
                index = right - i;
                for(long long j = 0; string[j + right] == pattern[j + right - i] && j + right - i < string.size(); ++j)
                    ++index;
                left = i;
                right = i + index - 1;
            }
            else
                index = prefix.at(i - left);
        }
        if(index == pattern.size() - 1)
            output << i << " ";
    }
}
void Strings::PrefixTemplate(std::istream& input, std::ostream& output)
{
    std::string pattern = "";
    input >> pattern;
    pattern += '#';
    std::vector<long long> prefix = this->Prefix(pattern);
    long long prev = prefix.at(prefix.size() - 1);
    long long counter = 0;
    std::string string;
    input >> string;
    for(long long i = 0; i < string.size(); ++i)
    {
        long long last = prev;
        while(last > 0 && string[i] != pattern[last])
            last = prefix[last - 1];
        if(string[i] == pattern[last])
            ++last;
        prev = last;
        if(last == pattern.size() - 1)
            output << (counter - (pattern.size() - 2)) << " ";
        ++counter;
    }
}
void Strings::MaxSubPalindrome(std::istream& input, std::ostream& output)
{
    std::string s;
    input >> s;
    long long left = 0;
    long long right = -1;
    long long odd[s.size()];
    for(long long i = 0; i < s.size(); ++i)
    {
        long long k = (i > right ? 0 : (odd[left + right - i] - 1 < right - i ? odd[left + right - i] - 1: right - i )) + 1;
            while(i + k  - 1 < s.size() && i + 1 >= k && s[i + k - 1] == s[i - k + 1])
                ++k;
            k -= 1;
            odd[i] = k;
            if(i + k > right) {
                left = i - k + 1;
                right = i + k - 1;
            }
    }
    long long maxOddLength = 2 * odd[0] - 1;
    long long maxOddId = 0;
    for(long long j = 0; j < s.size(); ++j)
    {
        if(2 * odd[j] - 1 > maxOddLength){
            maxOddLength = 2 * odd[j] - 1;
            maxOddId = j - odd[j] + 1;
        }
    }
    left = 0;
    right = -1;
    for(long long i = 0; i < s.size(); ++i)
        odd[i] = 0;
    for(long long i = 0; i < s.size(); ++i)
    {
        long long k = (i > right ? 0 :
                                   (odd[left + right - i] < right - i ? odd[left + right - i]  : right - i)) + 1;
            while(i + k - 1 < s.size() && i >= k && s[i + k - 1] == s[i - k])
                ++k;
            k -= 1;
            odd[i] = k;
            if(i + k > right) {
                left = i - k;
                right = i + k - 1;
            }
    }
    long long maxEvenLength = 2 * odd[0];
    long long maxEvenId = 0;
    for(long long j = 0; j < s.size(); ++j)
    {
        if(2 * odd[j] > maxEvenLength){
            maxEvenLength = 2 * odd[j];
            maxEvenId = j - odd[j];
        }
    }
    long long first, length;
    first = maxOddLength > maxEvenLength ? maxOddId : maxEvenId;
    length = maxOddLength > maxEvenLength ? maxOddLength : maxEvenLength;
    for(long long c = first; c < first + length; ++c)
        output << s[c];
}
