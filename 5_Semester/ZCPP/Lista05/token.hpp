#ifndef LISTA5_TOKEN_HPP
#define LISTA5_TOKEN_HPP

#include <queue>
#include <variant>
#include <string>
#include <stdexcept>

enum class token_operator : char
{
    plus = '+',
    minus = '-',
    mult = '*',
    div = '/',
    pow = '^'
};
bool is_token_operator(char c);   // check whether a symbol is in our operators enum class

enum class token_paranthesis : char
{
    left_p = '(',
    right_p = ')'
};
bool is_token_paranthesis(char c);

int operator_precedence(token_operator token);                           // precedence interpreted numerically (higher binds)

using token_type = std::variant<token_operator, token_paranthesis, int>; // final token type
std::queue<token_type> tokenize_str(const std::string& inp);             // takes input string and tokenizes it into a queue
std::string token_queue_to_str(std::queue<token_type> tokens);           // return string representing token equation

#endif //LISTA5_TOKEN_HPP
