#include "ExplicitState.h"
#include <assert.h>

ExplicitState::ExplicitState(long long id, IAlphabetConfig& config):id_(id), config_(config), suffixLink_(nullptr)
{
    transitions_.resize(config.GetAlphabetSize(), Pass(0, 04, nullptr));
}

long long ExplicitState::GetId()
{
    return id_;
}
ExplicitState::Pass ExplicitState::GetTransition(char c)
{
    assert(config_.AssertCorrectSuymbol(c));
    return transitions_[config_.GetLetterId(c)];
}
ExplicitState*ExplicitState::GetSuffixLink()
{
    return suffixLink_;
}
void ExplicitState::AddTransition(char c, ExplicitState::Pass pass)
{
    auto letterId = config_.GetLetterId(c);
    transitions_[letterId] = pass;
}
void ExplicitState::AddSuffixLink(ExplicitState* link)
{
    assert(link != nullptr);
    this->suffixLink_ = link;
}
