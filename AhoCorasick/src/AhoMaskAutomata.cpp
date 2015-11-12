#include "AhoMaskAutomata.h"
#include <assert.h>

AhoMaskAutomata::AhoMaskAutomata(IAhoAutomataConfig& config, std::istream& input):AhoAutomata(config)
{
        std::ios::sync_with_stdio(false);
        std::string s = "";
        long long subPatternStartPosition = 0;
        char c;
        while(input.get(c) && c != '\n' && c != ' ')
        {
            if(c == '?') {
                if(s.compare("") != 0) {
                    this->AddString(s);
                    s = "";
                }
            }
            else
            {
                if(s.compare("") == 0)
                    subPatternStartPosition_.push_back(subPatternStartPosition);
                s += c;
            }
            ++subPatternStartPosition;
        }
        if(s.compare("") != 0)
            this->AddString(s);
        patternSize_ = subPatternStartPosition;
        std::ios::sync_with_stdio(true);
}
void AhoMaskAutomata::FindTemplate(std::istream& input, std::ostream& output)
{
    std::ios::sync_with_stdio(false);
    char c;
    long long position = 0;
    auto state = this->nodes_.at(ROOT_ID).get();
    std::vector<long long> subPatternCounter;
    long long patternCounter = 0;
    while(input.get(c) && c != '\n')
    {
        subPatternCounter.push_back(0);
        ++position;
        state = this->GetTransition(state, c);
        for(auto st = state; st->GetId() != ROOT_ID; st = GetFastSuffixLink(st))
        {
            if(st->IsString())
                for(auto s = st->GetStrings().begin(); s != st->GetStrings().end(); ++s)
                {
                    auto index = position - (long long)strings_.at(*s).length()
                            - (long long)subPatternStartPosition_.at(*s);
                    if(index > 0)
                        ++subPatternCounter[index];
                }
        }
    }
    for(long long i = 0; patternSize_ - 1 +  i < subPatternCounter.size(); ++i)
        if(subPatternCounter[i] >= subPatternStartPosition_.size()) {
            output << i << " ";
            ++patternCounter;
        }
    std::ios::sync_with_stdio(true);
}
