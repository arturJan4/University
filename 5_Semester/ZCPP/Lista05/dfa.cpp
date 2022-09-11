#include "dfa.hpp"

DFA::DFA(std::initializer_list<int> states,
         std::initializer_list<char> alphabet,
         std::initializer_list<std::tuple<int, char, int>> transitions,
         int starting_state,
         std::initializer_list<int> accepted_states)
{
    for (auto& state : states)
    {
        if(m_Q.contains(state))
            throw std::invalid_argument("repeating state");

        m_Q.insert(state);
    }

    for (auto& symbol : alphabet)
    {
        if(m_Sigma.contains(symbol))
            throw std::invalid_argument("repeating character in the alphabet");

        m_Sigma.insert(symbol);
    }

    for (auto& [start_state, symbol, end_state] : transitions)
    {
        this->addTransition(start_state, symbol, end_state);
    }

    if (!m_Q.contains(starting_state))
        throw std::invalid_argument("starting set not in the set of valid states");
    else
        this->setStartingState(starting_state);

    for (auto& state : accepted_states)
    {
        if(m_F.contains(state))
            throw std::invalid_argument("repeating state");
        else if (!m_Q.contains(state))
            throw std::invalid_argument("accepted state is not a valid state");

        m_F.insert(state);
    }
}

bool DFA::is_valid_alphabet(const std::string &input)
{
    for(char it : input)
    {
        if(!m_Sigma.contains(it))
            return false;
    }

    return true;
}

bool DFA::func_domain_exists(state state, symbol symbol)
{
    return m_delta.contains(state) && m_delta[state].contains(symbol);
}

bool DFA::is_accepted(const std::string &input)
{
    if(!is_valid_alphabet(input))
        return false;

    state current = m_s;

    for(char it : input)
    {
        if (!func_domain_exists(current, it)) // assume loop
            continue;

        current = m_delta[current][it];
    }

    return m_F.contains(current);
}

void DFA::setValidState(const std::set<state> &mQ)
{
    m_Q = mQ;
}

void DFA::setAlphabet(const std::set<symbol> &mSigma)
{
    m_Sigma = mSigma;
}

void DFA::setTransitionFunction(const qfunc &mDelta)
{
    m_delta = mDelta;
}

void DFA::addTransition(state st, symbol sym, state res)
{
    m_delta[st][sym] = res;
}

void DFA::addTransition(state start_state, const std::vector<symbol>& symbol_list, state result_state)
{
    for (auto symbol : symbol_list)
    {
        m_delta[start_state][symbol] = result_state;
    }
}

void DFA::setStartingState(state mS)
{
    m_s = mS;
}

void DFA::setAcceptedStates(const std::set<state> &mF)
{
    m_F = mF;
}
