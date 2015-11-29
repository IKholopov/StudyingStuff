#ifndef UKKONEN_LCS_EXPLICIT_STATE
#define UKKONEN_LCS_EXPLICIT_STATE

#include "IAlphabetConfig.h"
#include <vector>

class ExplicitState
{
    public:
        struct Pass
        {
                Pass(long long left = 0, long long right = 0, ExplicitState* state = nullptr ):
                    Left(left), Right(right), State(state) {}
                long long Left;
                long long Right;
                ExplicitState* State;
        };
        ExplicitState(long long id, IAlphabetConfig& config);

        long long GetId();
        Pass GetTransition(char c);
        ExplicitState* GetSuffixLink();
        void AddTransition(char c, Pass pass);
        void AddSuffixLink(ExplicitState* link);
    private:
        long long id_;
        IAlphabetConfig& config_;
        ExplicitState* suffixLink_;
        std::vector<Pass> transitions_;
};

#endif
