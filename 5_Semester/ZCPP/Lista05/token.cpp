#include "token.hpp"

// using switch char-cast trick
bool is_token_operator(char c)
{
    switch (c)
    {
        case static_cast<char>(token_operator::plus):
            return true;
        case static_cast<char>(token_operator::minus):
            return true;
        case static_cast<char>(token_operator::mult):
            return true;
        case static_cast<char>(token_operator::div):
            return true;
        case static_cast<char>(token_operator::pow):
            return true;
        default:
            return false;
    }
};

// using switch char-cast trick
bool is_token_paranthesis(char c)
{
    switch (c)
    {
        case static_cast<char>(token_paranthesis::left_p):
            return true;
        case static_cast<char>(token_paranthesis::right_p):
            return true;
        default:
            return false;
    }
};

int operator_precedence(token_operator token)
{
    // making use of fallback here!
    switch(token)
    {
        case token_operator::plus:
        case token_operator::minus:
            return 1;
        case token_operator::mult:
        case token_operator::div:
            return 2;
        case token_operator::pow:
            return 3;
    }

    return -1;
}

std::queue<token_type> tokenize_str(const std::string& inp)
{
    std::queue<token_type> tokens;

    std::string::const_iterator end = inp.cend();
    for(std::string::const_iterator it = inp.cbegin(); it != end; it++)
    {
        char c = *it;

        if (c == '\0')     // null terminated string
            continue;

        if(std::isdigit(c))
        {
            int value = c - '0'; // number as char -> int ASCII conversion trick

            // number can be more then one digit e.g. 123 -> is '1' + '2' + '3' in terms of characters
            while((it+1) != end && std::isdigit(*(it+1)))
            {
                // build decimal number
                value *= 10;
                value += (*it - '0');
                it++;
            }

            tokens.push(value);
        }
        else if (is_token_operator(c))
        {
            tokens.push(token_operator(c));
        }
        else if (is_token_paranthesis(c))
        {
            tokens.push(token_paranthesis(c));
        }
        else if (isspace(c))
        {
            // ignore whitespaces
            continue;
        }
        else
        {
            throw std::invalid_argument("unknown symbol in the expression: " + std::to_string(c));
        }
    }

    return tokens;
}

std::string token_queue_to_str(std::queue<token_type> tokens)
{
    std::string output;
    output.reserve(tokens.size() * 2 + 1);

    while(!tokens.empty())
    {
        auto fr = tokens.front();

        if(std::holds_alternative<int>(fr))
            output += std::to_string(std::get<int>(fr));
        else if(std::holds_alternative<token_operator>(fr))
            output += static_cast<char>(get<token_operator>(fr));
        else if(std::holds_alternative<token_paranthesis>(fr))
            output += static_cast<char>(get<token_paranthesis>(fr));

        output += " ";

        tokens.pop();
    }
    return output;
}