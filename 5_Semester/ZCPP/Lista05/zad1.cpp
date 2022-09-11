#include <iostream>
#include <string>
#include <queue>
#include <variant>
#include <stack>
#include <cassert>

#include "token.hpp"

/*
 * we want to convert arithmetic expressions from INFIX to POSTFIX (RPN)
 * (x (+ 2 3) 5) -> 2 3 + 5 x
 */

// Dijkstra algorithm for conversion:
/*
 * 1) read symbol:
 *  a) number -> output queue
 *  b) operator op1 ->
 *   I) while stack has other operator op2 where precedence(op) <= precedence(op2)
 *      take of o2, put it to output queue, repeat I
 *   II) put op2 on stack
 *  c) left parenthesis -> put on stack
 *  d) right parenthesis -> take operators from stack and add to queue until top() is not '('
 *     when top is '(' -> take it off stack without adding to queue
 * 2) put all symbols from stack to queue (there should be only operators now)
 */

//https://pl.wikipedia.org/wiki/Odwrotna_notacja_polska -> algorithm steps
std::queue<token_type> infix_to_rpn(std::queue<token_type> input_tokens)
{
    std::queue<token_type> out_queue;           // output queue
    std::stack<token_type> stack;               // internal stack

    while(!input_tokens.empty())
    {
        token_type token = input_tokens.front();
        input_tokens.pop();

        if(std::holds_alternative<int>(token)) // digit -> push to queue
        {
            out_queue.push(token);
        }
        else if(std::holds_alternative<token_operator>(token)) // operator
        {
            token_operator op1 = std::get<token_operator>(token);
            int precedence1 = operator_precedence(op1);

            // while there is an operator on top of the stack
            // if it has higher or equal precedence to current operator then push it to output queue
            while (!stack.empty() && std::holds_alternative<token_operator>(stack.top()))
            {
                token_operator op2 = std::get<token_operator>(stack.top());
                int precedence2 = operator_precedence(op2);

                if (precedence1 > precedence2)
                    break;

                out_queue.push(stack.top());
                stack.pop();
            }

            stack.push(token); // finally push the operator to output queue
        }
        else if(std::holds_alternative<token_paranthesis>(token)) // paranthesis
        {
            // if it is the right paranthesis
            if(std::get<token_paranthesis>(token) == token_paranthesis::right_p)
            {
                bool foundLeft = false;
                // empty stack to queue till you find a left paranthesis
                while(!stack.empty())
                {
                    token_type top = stack.top();

                    if(std::holds_alternative<token_paranthesis>(top) &&
                       std::get<token_paranthesis>(top) == token_paranthesis::left_p)
                    {
                        stack.pop();
                        foundLeft = true;
                        break;
                    }

                    out_queue.push(top);
                    stack.pop();
                }

                if(!foundLeft)
                {
                    throw std::invalid_argument("wrong infix expression - no matching paranthesis found");
                }
            }
            else if(std::get<token_paranthesis>(token) == token_paranthesis::left_p)
            {
                // if it is the left paranthesis then push it on the stack
                stack.push(token);
            }
        }
        else
        {
            throw std::invalid_argument("wrong token received when converting to rpn");
        }
    }

    // the input has finished, but stack is nonempty
    // then push everything (should be only operators) to the output queue
    while(!stack.empty())
    {
        token_type top = stack.top();

        if(!std::holds_alternative<token_operator>(top))
            throw std::invalid_argument("wrong parantheses placement, invalid infix expresssion");

        out_queue.push(top);
        stack.pop();
    }

    return out_queue;
}

// asserts expected and actual value of conversion
void run_test(const std::string& input, const std::string& expected)
{
    std::string infix_val(input);

    std::queue<token_type> tokens = tokenize_str(infix_val);
    std::cout << token_queue_to_str(tokens) << "== ";

    std::queue<token_type> converted = infix_to_rpn(tokens);
    std::string actual = token_queue_to_str(converted);
    std::cout << actual << "\n";

    assert(actual == expected);
}

void test_basic()
{
    run_test("4 + 2 ", "4 2 + ");
}

void test_paranthesis()
{
    run_test("( 1 + 2 ) * ( 3 / 4 ) ^ ( 5 + 6 ) ", "1 2 + 3 4 / 5 6 + ^ * ");
}

void test_precedence()
{
    run_test("( ( 1  + 2 ) / 3 ) ^ 4 ", "1 2 + 3 / 4 ^ ");
}

void test_wiki()
{
    //// example from polish Wikipedia, expected result: (3 4 2 × 1 5 − 2 ^ / +)
    run_test("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ", "3 4 2 * 1 5 - 2 ^ / + ");
}


int main()
{
    test_basic();
    test_paranthesis();
    test_precedence();
    test_wiki();

    return 0;
}

