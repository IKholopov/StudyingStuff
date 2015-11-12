#include "AhoAutomata.h"

#include <assert.h>

AhoAutomata::AhoAutomata(IAhoAutomataConfig& config, std::vector<std::string>& strings): config_(config), size_(1), strings_(strings)
{
    this->nodes_.push_back(std::unique_ptr<AutomataNode>({new AutomataNode(*this, 0, NO_NODE, config_)}));
    for(unsigned long long i = 0; i < strings.size(); ++i)
        this->AddString(strings[i], i);
}
AhoAutomata::AhoAutomata(IAhoAutomataConfig& config):config_(config), size_(1)
{
    this->nodes_.push_back(std::unique_ptr<AutomataNode>({new AutomataNode(*this, 0, NO_NODE, config_)}));
}

void AhoAutomata::FindTemplates(std::istream& input, std::ostream& output)
{
    std::ios::sync_with_stdio(false);
    char c;
    long long position = 0;
    auto state = this->nodes_.at(ROOT_ID).get();
    while(input.get(c) && c != '\n')
    {
        ++position;
        state = this->GetTransition(state, c);
        for(auto st = state; st->GetId() != ROOT_ID; st = GetFastSuffixLink(st))
        {
            if(st->IsString())
                for(auto s = st->GetStrings().begin(); s != st->GetStrings().end(); ++s)
                    output << position - strings_.at(*s).length() << strings_.at(*s) << std::endl;
        }
    }
    std::ios::sync_with_stdio(true);
}
void AhoAutomata::AddString(std::string s)
{
    strings_.push_back(s);
    this->AddString(s, strings_.size() - 1);
}
void AhoAutomata::AddString(std::string s, unsigned long long stringId)
{
    long long current = 0;
    assert(s.size() != 0);
    for(long long i = 0 ; i < s.size(); ++i)
    {
        auto next = nodes_.at(current).get()->GetChildId(s[i]);
        if(next == NO_NODE) {
            nodes_.push_back(std::unique_ptr<AutomataNode>({new AutomataNode(*this, size_, current, config_, s[i])}));
            nodes_.at(current).get()->AddChild(s[i], size_);
            current = size_;
            ++size_;
        }
        else
            current = next;
    }
    this->nodes_.at(current).get()->MarkAsString(stringId);
}
AutomataNode* AhoAutomata::GetNode(long long id)
{
    assert(id >= 0 && id < nodes_.size());
    return nodes_.at(id).get();
}
AutomataNode*AhoAutomata::GetSuffixLink(AutomataNode* node)
{
    if(node->GetSuffixLinkId() == NO_NODE)
        if(node->GetId() == ROOT_ID || node->GetParentId() == ROOT_ID)
            node->SetSuffixLinkId(ROOT_ID);
        else
            node->SetSuffixLinkId(this->GetTransition(GetSuffixLink(node->GetParentId()), node->GetSymbol())->GetId());
    assert(node->GetSuffixLinkId() != NO_NODE);
    return nodes_.at(node->GetSuffixLinkId()).get();
}
AutomataNode* AhoAutomata::GetFastSuffixLink(AutomataNode* node)
{
    if(node->GetFastLinkId() == NO_NODE) {
        auto link = GetSuffixLink(node);
        if(link->GetId() == ROOT_ID)
            node->SetFastLinkId(ROOT_ID);
        else
            node->SetFastLinkId(link->IsString() ? link->GetId() : GetSuffixLink(link)->GetId());
    }
    assert(node->GetSuffixLinkId() != NO_NODE);
    return nodes_.at(node->GetFastLinkId()).get();
}
AutomataNode* AhoAutomata::GetTransition(AutomataNode* node, char c)
{
    if(node->GetTransition(c) == NO_NODE)
        if(node->GetChildId(c) != NO_NODE)
            node->SetTransition(c, node->GetChildId(c));
        else
            if(node->GetId() == ROOT_ID)
                node->SetTransition(c, ROOT_ID);
            else
                node->SetTransition(c, this->GetTransition(this->GetSuffixLink(node), c)->GetId());
    assert(node->GetTransition(c) != NO_NODE);
    return this->nodes_.at(node->GetTransition(c)).get();
}
AutomataNode* AhoAutomata::GetSuffixLink(long long nodeId)
{
    assert(nodeId < nodes_.size());
    return this->GetSuffixLink(nodes_.at(nodeId).get());
}
AutomataNode*AhoAutomata::GetTransition(long long nodeId, char c)
{
    assert(nodeId < nodes_.size());
    return this->GetTransition(nodes_.at(nodeId).get(), c);
}
