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
        void PrefixTemplate(std::istream& input, std::ostream& output);
    private:
        Strings();
};

#endif
