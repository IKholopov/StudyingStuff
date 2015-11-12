#ifndef STRINGS_H
#define STRINGS_H

#include <istream>
#include <ostream>
#include <vector>

class Strings
{
    public:
        static Strings& lib();

        std::vector<long long> Prefix(std::string s);
        std::vector<long long> ZFunction(std::string s);
        std::string PrefixDecode(std::vector<long long>& prefixFunc);
        void PrefixDecode(std::istream& input, std::ostream& output);
        void ZFunctionDecode(std::istream& input, std::ostream& output);
        void ZFunctionTemplate(std::istream& input, std::ostream& output);
        void PrefixTemplate(std::istream& input, std::ostream& output);
        std::string MaxSubPalindrome(std::string s);
        void MaxSubPalindrome(std::istream& input, std::ostream& output);
    private:
        Strings();
};

#endif
