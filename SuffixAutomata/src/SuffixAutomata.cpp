#include "SuffixAutomata.h"

#include<assert.h>

SuffixAutomata::SuffixAutomata(IAlphabetConfig& config, std::string baseString):config_(config), baseString_(baseString)
{
    this->notAString_ = new AutomataState(config_, 0, 0);
    states_.push_back(notAString_);
    this->root_ = new AutomataState(config_, 1, 0);
    root_->SetSuffixLink(notAString_);
    states_.push_back(root_);
    AutomataState* tail = root_;
    for(long long i = 0; i < baseString_.size(); ++i)
    {
        char c = baseString_[i];
        auto newState = new AutomataState(config, states_.size(), tail->GetLength() + 1);
        states_.push_back(newState);
        AutomataState* state;
        for(state = tail; state != notAString_ && state->GetTransition(c) == nullptr; state = state->GetSuffixLink())
        {
            assert(state != nullptr);
            state->SetTransition(c, newState);
        }
        if(state == notAString_) {
            newState->SetSuffixLink(root_);
            tail = newState;
            continue;
        }
        auto nextState = state->GetTransition(c);
        if(nextState->GetLength() == state->GetLength() + 1) {
            newState->SetSuffixLink(nextState);
            tail = newState;
            continue;
        }
        auto clone = new AutomataState(*nextState, states_.size());
        clone->SetLength(state->GetLength() + 1);
        states_.push_back(clone);
        newState->SetSuffixLink(clone);
        nextState->SetSuffixLink(clone);
        for(auto st = state; st->GetTransition(c) == nextState; st = st->GetSuffixLink())
        {
            assert(st != nullptr);
            st->SetTransition(c, clone);
        }
        tail = newState;
    }
}

SuffixAutomata::~SuffixAutomata()
{
    for(auto state = states_.begin(); state != states_.end(); ++state)
        delete *state;
}
long long SuffixAutomata::FindDifferentSubstrings()
{
    std::vector<long long> numberOfPaths;
    numberOfPaths.resize(states_.size(), -1);
    for(long long i = 0; i < states_.size(); ++i)
    {
        this->CalculatePathsFromNode(numberOfPaths, i);
    }
    return numberOfPaths[1] - 1;
}
long long SuffixAutomata::CalculatePathsFromNode(std::vector<long long>& paths, long long stateId)
{
    if(paths.at(stateId) != -1)
        return paths.at(stateId);
    paths[stateId] = 0;
    auto state = states_.at(stateId);
    for(long long i = 0; i < config_.GetAlphabetSize(); ++i)
    {
        auto nextState = state->GetTransition(config_.GetLetter(i));
        if(nextState == nullptr)
            continue;
        auto next = nextState->GetId();
        paths[stateId] += paths.at(next) == -1 ? CalculatePathsFromNode(paths, next) : paths.at(next);
    }
    ++paths[stateId];
    return paths.at(stateId);
}

SuffixAutomata::AutomataState::AutomataState(IAlphabetConfig& config, long long id, long long length): config_(config), id_(id), length_(length)
{
    transtions_.resize(config_.GetAlphabetSize(), nullptr);
    suffixLink_ = nullptr;
}
SuffixAutomata::AutomataState::AutomataState(SuffixAutomata::AutomataState& state, long long id):config_(state.config_), id_(id),
                                                                                   length_(state.length_),
                                                                                   suffixLink_(state.suffixLink_),
                                                                                   transtions_(state.transtions_)
{
}

long long SuffixAutomata::AutomataState::GetId()
{
    return this->id_;
}
long long SuffixAutomata::AutomataState::GetLength()
{
    return length_;
}
SuffixAutomata::AutomataState*SuffixAutomata::AutomataState::GetTransition(char c)
{
    return transtions_.at(config_.GetLetterId(c));
}
SuffixAutomata::AutomataState*SuffixAutomata::AutomataState::GetSuffixLink()
{
    return this->suffixLink_;
}
void SuffixAutomata::AutomataState::SetTransition(char key, SuffixAutomata::AutomataState* toState)
{
    this->transtions_[config_.GetLetterId(key)] = toState;
}
void SuffixAutomata::AutomataState::SetSuffixLink(SuffixAutomata::AutomataState* toState)
{
    this->suffixLink_ = toState;
}
void SuffixAutomata::AutomataState::SetLength(long long length)
{
    this->length_ = length;
}
