#include "SuffixTree.h"
#include <assert.h>
#include <iostream>

SuffixTree::SuffixTree(IAlphabetConfig& config, std::string string):config_(config), string_(string), inf(string.size() + 1)
{
    string_ += "$";
    this->notAString = new ExplicitState(states_.size(), config_);
    states_.push_back(notAString);
    this->emptyString = new ExplicitState(states_.size(), config_);
    states_.push_back(emptyString);
    for(long long i = 0; i < config.GetAlphabetSize(); ++i)
        notAString->AddTransition(config.GetLetter(i), ExplicitState::Pass(- i - 1, - i - 1, emptyString));
    emptyString->AddSuffixLink(notAString);
    ExplicitState::Pass tail = ExplicitState::Pass(0, -1, emptyString);
    for(long long i = 0; i < string_.size(); ++i)
    {
        std::cout << i << std::endl;
        tail = this->Update(tail.State, tail.Left, i);
        tail = this->Canonize(tail.State, tail.Left, i);
        this->PrintTree(std::cout, i);
    }
}
SuffixTree::~SuffixTree()
{
    for(auto st = states_.begin(); st != states_.end(); ++st)
        delete *st;
}

ExplicitState::Pass SuffixTree::Update(ExplicitState* state, long long left, long long right)
{
    ExplicitState* prev = emptyString;
    ExplicitState* nextState = nullptr;
    bool isEndPoint = this->TestEndPointAndSplit(ExplicitState::Pass(left, right - 1, state), this->Sequence(right), nextState);
    while(!isEndPoint)
    {
        ExplicitState* newState = new ExplicitState(states_.size(), config_);
        states_.push_back(newState);
        nextState->AddTransition(Sequence(right), ExplicitState::Pass(right, inf, newState));
        if(prev != emptyString)
            prev->AddSuffixLink(nextState);
        prev = nextState;
        auto canonized = this->Canonize(state->GetSuffixLink(), left, right - 1);
        state = canonized.State;
        left = canonized.Left;
        isEndPoint = this->TestEndPointAndSplit(ExplicitState::Pass(left, right - 1, state), this->Sequence(right), nextState);
    }
    if(prev != emptyString)
        prev->AddSuffixLink(state);
    return ExplicitState::Pass(left, 0, state);
}
ExplicitState::Pass SuffixTree::Canonize(ExplicitState* state, long long left, long long right)
{
    if(right < left)
        return ExplicitState::Pass(left, 0, state);
    ExplicitState::Pass leftPass = state->GetTransition(this->Sequence(left));
    while(leftPass.Right - leftPass.Left <= right - left) {
        left = left + leftPass.Right - leftPass.Left + 1;
        state = leftPass.State;
        if(left <= right)
            leftPass = state->GetTransition(this->Sequence(left));
    }
    return ExplicitState::Pass(left, 0, state);
}
bool SuffixTree::TestEndPointAndSplit(ExplicitState::Pass pass, char c, ExplicitState*& state)
{
    if(pass.Left <= pass.Right) {
        ExplicitState::Pass next = pass.State->GetTransition(this->Sequence(pass.Left));
        assert(next.State != nullptr);
        if(c == Sequence(next.Left + pass.Right - pass.Left + 1)) {
            state = pass.State;
            return true;
        }
        ExplicitState* newState = new ExplicitState(states_.size(), config_);
        states_.push_back(newState);
        long long branchingPoint = next.Left + pass.Right - pass.Left;
        pass.State->AddTransition(this->Sequence(next.Left),
                                ExplicitState::Pass(next.Left, branchingPoint, newState));
        newState->AddTransition(this->Sequence(branchingPoint), ExplicitState::Pass(branchingPoint, next.Right, next.State));
        state = newState;
        return false;
    }
    else {
        state = pass.State;
        if(pass.State != nullptr) {
            return pass.State->GetTransition(c).State != nullptr;
        }
        return false;
    }
}
char SuffixTree::Sequence(long long id)
{
    assert(id < inf);
    if(id < 0)
        return config_.GetLetter(-id - 1);
    return string_[id];
}
void SuffixTree::PrintTree(std::ostream& out, long long max)
{
    std::vector<bool> isVisited;
    isVisited.resize(states_.size(), 0);
    std::vector<ExplicitState*> stack;
    stack.push_back(notAString);
    isVisited[notAString->GetId()] = 1;
    long long depth = 0;
    while(stack.size() > 0)
    {
        auto state = stack.at(stack.size() - 1);
        stack.pop_back();
        --depth;
        if(state == nullptr)
            continue;
        for(int i = 0; i < config_.GetAlphabetSize(); ++i)
        {
            auto next = state->GetTransition(config_.GetLetter(i));
            if(next.State != nullptr && isVisited[next.State->GetId()] == 0)
            {
                if(next.Left >= 0) {
                    for(int i = 0; i < depth; ++i)
                        out << '\t';
                    for(int i = next.Left; i < next.Right && i < max + 1; ++i)
                    {
                        out << string_[i];
                    }
                    out << std::endl;
                }
                if(next.State != nullptr) {
                    isVisited[next.State->GetId()] = 1;
                    stack.push_back(state);
                    ++depth;
                    stack.push_back(next.State);
                    ++depth;
                    break;
                }
            }
        }
    }

}

void SuffixTree::PrintTree(std::ostream& out)
{
    std::vector<bool> isVisited;
    isVisited.resize(states_.size(), 0);
    std::vector<ExplicitState*> stack;
    stack.push_back(notAString);
    isVisited[notAString->GetId()] = 1;
    long long depth = 0;
    while(stack.size() > 0)
    {
        auto state = stack.at(stack.size() - 1);
        stack.pop_back();
        --depth;
        if(state == nullptr)
            continue;
        for(int i = 0; i < config_.GetAlphabetSize(); ++i)
        {
            auto next = state->GetTransition(config_.GetLetter(i));
            if(next.State != nullptr && isVisited[next.State->GetId()] == 0)
            {
                if(next.Left >= 0) {
                    for(int i = 0; i < depth; ++i)
                        out << '\t';
                    for(int i = next.Left; i < next.Right && i < string_.size(); ++i)
                    {
                        out << string_[i];
                    }
                    out << std::endl;
                }
                if(next.State != nullptr) {
                    isVisited[next.State->GetId()] = 1;
                    stack.push_back(state);
                    ++depth;
                    stack.push_back(next.State);
                    ++depth;
                    break;
                }
            }
        }
    }

}
