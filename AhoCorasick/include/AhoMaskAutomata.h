#ifndef AHOMASKAUTOMATA_H
#define AHOMASKAUTOMATA_H

#include "AhoAutomata.h"

class AhoMaskAutomata: public AhoAutomata
{
    public:
        AhoMaskAutomata(IAhoAutomataConfig& config, std::istream& input);
        void FindTemplate(std::istream& input, std::ostream& output);
    private:
        long long patternCounter_;
        long long patternSize_;
};

#endif