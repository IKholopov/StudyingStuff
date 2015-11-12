#ifndef AHO_AUTOMATA_H
#define AHO_AUTOMATA_H

#include "AutomataNode.h"
#include <string>
#include <memory>
#include <vector>
#include <istream>

#define ROOT_ID 0

class AutomataNode;

class AhoAutomata
{
    public:
        AhoAutomata(IAhoAutomataConfig& config, std::vector<std::string>& strings);
        AhoAutomata(IAhoAutomataConfig& config);
        void FindTemplates(std::istream& input, std::ostream& output);
    protected:
        void AddString(std::string s);
        std::vector<std::unique_ptr<AutomataNode>> nodes_;
        AutomataNode* GetTransition(AutomataNode* node, char c);
        AutomataNode* GetFastSuffixLink(AutomataNode* node);
        std::vector<std::string> strings_;
    private:
        void AddString(std::string s, unsigned long long stringId);
        AutomataNode* GetNode(long long id);
        AutomataNode* GetSuffixLink(AutomataNode* node);
        AutomataNode* GetSuffixLink(long long nodeId);
        AutomataNode* GetTransition(long long nodeId, char c);
        IAhoAutomataConfig& config_;
        unsigned long long size_;
};

#endif
