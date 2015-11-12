#ifndef IAHO_AUTOMATA_CONFIG_H
#define IAHO_AUTOMATA_CONFIG_H

#define NO_NODE -1

class IAhoAutomataConfig
{
    public:
        virtual unsigned long long GetLetterId(char c) = 0;
        virtual unsigned long long GetAlphabetSize() = 0;
};

#endif
