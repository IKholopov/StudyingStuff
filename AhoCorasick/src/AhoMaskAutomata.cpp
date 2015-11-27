#include "AhoMaskAutomata.h"
#include <assert.h>

AhoMaskAutomata::AhoMaskAutomata(IAhoAutomataConfig& config, std::istream& input):AhoAutomata(config)
{
        std::ios::sync_with_stdio(false);
        std::string s = "";
        long long subPatternStartPosition = 0;
        long long positionCounter = 0;
        patternCounter_ = 0;
        char c;
        while(input.get(c) && c != '\n')
        {
            if(!(config_.AssertCorrectSymbol(c) || c == '?'))
                continue;
            if(c == '?') {
                if(s.compare("") != 0) {
                    this->AddString(s, s.length() + subPatternStartPosition);
                    ++patternCounter_;
                    s = "";
                }
            }
            else
            {
                if(s.compare("") == 0) {
                    subPatternStartPosition = positionCounter;
                }
                s += c;
            }
            ++positionCounter;
        }
        if(s.compare("") != 0) {
            this->AddString(s, s.length() + subPatternStartPosition);
            ++patternCounter_;
        }
        patternSize_ = positionCounter;
        std::ios::sync_with_stdio(true);
}
void AhoMaskAutomata::FindTemplate(std::istream& input, std::ostream& output)
{
    std::ios::sync_with_stdio(false);
    char c;
    long long position = 0;
    auto state = this->nodes_.at(ROOT_ID);
    std::vector<long long> subPatternCounter;
    while(input.get(c))
    {
        if(!config_.AssertCorrectSymbol(c))
            continue;
        subPatternCounter.push_back(0);
        ++position;
        state = this->GetTransition(state, c);
        for(auto st = state; st->GetId() != ROOT_ID; st = GetFastSuffixLink(st))
        {
            if(st->IsString()) {
                auto str = st->GetStrings();
                for(long long i = 0; i < str.size(); ++i)
                {
                    auto index = position - str[i];
                    if(index >= 0)
                        ++subPatternCounter[index];
                }
            }
        }
    }
    for(long long i = 0; patternSize_ - 1 +  i < subPatternCounter.size(); ++i)
        if(subPatternCounter[i] >= patternCounter_) {
            output << i << " ";
        }
    std::ios::sync_with_stdio(true);
}
