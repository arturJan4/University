#ifndef LISTA5_DFA_HPP
#define LISTA5_DFA_HPP

#include <set>
#include <vector>
#include <unordered_map>

using state = uint64_t;
using symbol = char;
using qfunc = std::unordered_map<state, std::unordered_map<symbol, state>>;

/*
* Finite state automata consists of:
* M = <Q, Sigma, Delta, s, F>
* where:
* Q - set of states
* Sigma - input alphabet
* Delta - Q:Sigma -> Q function
* s - starting state
* F - accepted states
*/

class DFA
{
private:
    std::set<state> m_Q;
    std::set<symbol> m_Sigma;
    qfunc m_delta;
    state m_s;
    std::set<state> m_F;

    bool is_valid_alphabet(const std::string &input);      // checks if there are symbols outside of the alphabet

    // check if there exists a transition between state and some another state when symbol is received
    bool func_domain_exists(state state, symbol symbol);

public:
    DFA(std::set<state> mQ, std::set<symbol> mSigma,
        qfunc mDelta, state mS, std::set<state> mF)
            : m_Q(std::move(mQ)), m_Sigma(std::move(mSigma)), m_delta(std::move(mDelta)), m_s(mS), m_F(std::move(mF))
    {}

    DFA(std::initializer_list<int> states,
        std::initializer_list<char> alphabet,
        std::initializer_list<std::tuple<int, char, int>> transitions,
        int starting_state,
        std::initializer_list<int> accepted_states);

    bool is_accepted(const std::string &input);            // checks if DFA accepts given input

    void setValidState(const std::set<state> &mQ);
    void setAlphabet(const std::set<symbol> &mSigma);
    void setTransitionFunction(const qfunc &mDelta);
    void setStartingState(state mS);
    void setAcceptedStates(const std::set<state> &mF);

    void addTransition(state st, symbol sym, state res);   // add one transitions

    // add multiple transitions from start_state to result_state given a list of symbols
    void addTransition(state start_state, const std::vector<symbol>& symbol_list, state result_state);


    ~DFA() = default;
};


#endif //LISTA5_DFA_HPP
