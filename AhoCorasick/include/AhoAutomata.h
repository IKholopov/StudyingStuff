#ifndef AHO_AUTOMATA_H
#define AHO_AUTOMATA_H

#include "AutomataNode.h"
#include <string>
#include <vector>
#include <istream>

#define ROOT_ID 0

class AutomataNode;

class AhoAutomata
{
    public:
        AhoAutomata(IAhoAutomataConfig& config, std::vector<std::string>& strings);
        AhoAutomata(IAhoAutomataConfig& config);
        ~AhoAutomata();
        void FindTemplates(std::istream& input, std::ostream& output);
    protected:
        void AddString(std::string s);
        std::vector<AutomataNode*> nodes_;
        AutomataNode* GetTransition(AutomataNode* node, char c);
        AutomataNode* GetFastSuffixLink(AutomataNode* node);
        std::vector<std::string> strings_;
        IAhoAutomataConfig& config_;
        void AddString(std::string s, unsigned long long stringId);
    private:
        AutomataNode* GetNode(long long id);
        AutomataNode* GetSuffixLink(AutomataNode* node);
        AutomataNode* GetSuffixLink(long long nodeId);
        AutomataNode* GetTransition(long long nodeId, char c);
        unsigned long long size_;
};

#endif
