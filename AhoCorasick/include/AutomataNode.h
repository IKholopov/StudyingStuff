#ifndef AUTOMATA_NODE_H
#define AUTOMATA_NODE_H

#include "IAhoAutomataConfig.h"
#include "AhoAutomata.h"
#include <vector>
#include <memory>

class AhoAutomata;

class AutomataNode
{
    public:
        AutomataNode(AhoAutomata& automata, long long id, long long parentId, IAhoAutomataConfig& config, char symbol = '\0',
                     long long stringId = NO_NODE);
        long long GetChildId(char c);
        long long GetId();
        char GetSymbol();
        bool IsString();
        std::vector<long long>& GetStrings();
        long long GetTransition(char c);
        long long GetSuffixLinkId();
        long long GetFastLinkId();
        long long GetParentId();
        void SetSuffixLinkId(long long id);
        void SetFastLinkId(long long id);
        void SetTransition(char c, long long transition);
        void AddChild(char c, long long childId);
        void MarkAsString(long long stringId);
    private:
        long long id_;
        char symbol_;
        long long parentId_;
        long long suffix_;
        std::vector<long long> childs_;
        std::vector<long long> transitions_;
        std::vector<long long> string_;
        long long fastSuffix_;
        IAhoAutomataConfig& config_;
        AhoAutomata& automata_;
};

#endif
