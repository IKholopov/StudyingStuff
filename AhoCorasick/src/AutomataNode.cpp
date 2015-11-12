#include "AutomataNode.h"

#include <assert.h>

AutomataNode::AutomataNode(AhoAutomata& automata, long long id, long long parentId, IAhoAutomataConfig& config, char symbol,
                           long long stringId):id_(id), symbol_(symbol), parentId_(parentId), suffix_(NO_NODE),
                           fastSuffix_(NO_NODE), config_(config), automata_(automata)
{
    this->childs_.assign(config.GetAlphabetSize(), NO_NODE);
    this->transitions_.assign(config.GetAlphabetSize(), NO_NODE);
    if(stringId != NO_NODE)
        string_.push_back(stringId);
}

long long AutomataNode::GetChildId(char c)
{
    return childs_.at(config_.GetLetterId(c));
}
long long AutomataNode::GetId()
{
    return this->id_;

}
char AutomataNode::GetSymbol()
{
    return symbol_;
}
bool AutomataNode::IsString()
{
    return string_.size() > 0;
}
std::vector<long long>& AutomataNode::GetStrings()
{
    return string_;
}
long long AutomataNode::GetTransition(char c)
{
    auto letterId = config_.GetLetterId(c);
    return this->transitions_.at(letterId);
}

long long AutomataNode::GetSuffixLinkId()
{
    return this->suffix_;
}
long long AutomataNode::GetFastLinkId()
{
    return this->fastSuffix_;
}
long long AutomataNode::GetParentId()
{
    return this->parentId_;
}
void AutomataNode::SetSuffixLinkId(long long id)
{
    this->suffix_ = id;
}
void AutomataNode::SetFastLinkId(long long id)
{
    this->fastSuffix_ = id;
}
void AutomataNode::SetTransition(char c, long long transition)
{
    this->transitions_[config_.GetLetterId(c)] = transition;
}
void AutomataNode::AddChild(char c, long long childId)
{
    assert(this->childs_.at(config_.GetLetterId(c)) == NO_NODE);
    this->childs_[config_.GetLetterId(c)] = childId;
}
void AutomataNode::MarkAsString(long long stringId)
{
    this->string_.push_back(stringId);
}
