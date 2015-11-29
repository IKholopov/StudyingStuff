#include "SuffixAutomata.h"

SuffixAutomata::SuffixAutomata(IAlphabetConfig config, std::string baseString):config_(config), baseString_(baseString)
{
    auto root = new AutomataState(config_, 0);
    states_.push_back(root);
    AutomataState* tail = root;
    for(long long i = 0; i < baseString_.size(); ++i)
    {
        cur = new
    }
}

SuffixAutomata::~SuffixAutomata()
{
    for(auto state = states_.begin(); state != states_.end(); ++state)
        delete *state;
}

SuffixAutomata::AutomataState::AutomataState(IAlphabetConfig& config, long long length): config_(config), length_(length)
{
    transtions_.resize(config_.GetAlphabetSize(), nullptr);
    suffixLink_ = nullptr;
}
