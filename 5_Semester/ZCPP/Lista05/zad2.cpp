#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <utility>

#include "dfa.hpp"

void testInitializerList()
{
    DFA automata({0,1,2},
               {'0', '1'},
              {{0, '0', 1}, {0, '1', 2}, {1, '0', 1}, {1, '1', 2}, {2, '0', 2}, {2, '1', 1}},
            0,
          {0, 1});

    std::string test;

    std::cout << "==================== BINARY AUTOMATA =====================";

    test = "";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "0";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "1";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "101";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "1012";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";
}

void testBinaryAutomata()
{
    std::set<state> states{0,1,2};
    std::set<symbol> alphabet{'0', '1'};
    state initial{0};
    std::set<state> F{0, 1};
    qfunc func;

    func[0]['0'] = 1;
    func[0]['1'] = 2;

    func[1]['0'] = 1;
    func[1]['1'] = 2;

    func[2]['0'] = 2;
    func[2]['1'] = 1;

    DFA automata(states, alphabet, func, initial, F);

    std::string test;

    std::cout << "==================== BINARY AUTOMATA =====================";

    test = "";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "0";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "1";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "101";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "1012";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

};

// https://imgur.com/a/bCp7cF3
// sum of digits divisble by 3
void testDecimalAutomata()
{
    std::set<state> states{0,1,2,3};
    std::set<symbol> alphabet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    state initial{0};
    std::set<state> F{0, 1};
    qfunc func;

    DFA automata(states, alphabet, func, initial, F);

    std::vector<symbol> rem0 = {'0', '3', '6', '9'};
    std::vector<symbol> rem1 = {'1', '4', '7'};
    std::vector<symbol> rem2 = {'2', '5', '8'};

    // q0 -> start
    // q1 -> remainder 0
    // q2 -> remainder 1
    // q3 -> remainder 2

    automata.addTransition(0, rem0,1);
    automata.addTransition(0, rem1,2);
    automata.addTransition(0, rem2,3);

    automata.addTransition(1, rem1,2);
    automata.addTransition(1, rem2,3);

    automata.addTransition(2, rem1,3);
    automata.addTransition(2, rem2,1);

    automata.addTransition(3, rem1,1);
    automata.addTransition(3, rem2,2);

    std::string test;

    std::cout << "==================== DECIMAL AUTOMATA =====================";
    test = "";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "0";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "1";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "2";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "3";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "30";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "301";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    test = "30a";
    std::cout << test << ":" << automata.is_accepted(test) << "\n";

    /*
    for (int i = 0; i < 100; ++i)
    {
        test = std::to_string(i);
        std::cout << test << ":" << automata.is_accepted(test) << "\n";
    }
    */
}

void testArgv(const std::string& input)
{
    DFA automata_binary({0,1,2},
                 {'0', '1'},
                 {{0, '0', 1}, {0, '1', 2}, {1, '0', 1}, {1, '1', 2}, {2, '0', 2}, {2, '1', 1}},
                 0,
                 {0, 1});

    std::string check_b = automata_binary.is_accepted(input) ? "true" : "false";
    std::cout << "[" << input << "]: has even number of 1's: " << check_b << "\n";

    DFA automata_decimal({0,1,2,3},
                       {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                      {{}},
                    0,
                  {0, 1});

    std::vector<symbol> rem0 = {'0', '3', '6', '9'};
    std::vector<symbol> rem1 = {'1', '4', '7'};
    std::vector<symbol> rem2 = {'2', '5', '8'};

    automata_decimal.addTransition(0, rem0,1);
    automata_decimal.addTransition(0, rem1,2);
    automata_decimal.addTransition(0, rem2,3);

    automata_decimal.addTransition(1, rem1,2);
    automata_decimal.addTransition(1, rem2,3);

    automata_decimal.addTransition(2, rem1,3);
    automata_decimal.addTransition(2, rem2,1);

    automata_decimal.addTransition(3, rem1,1);
    automata_decimal.addTransition(3, rem2,2);

    std::string check_d = automata_decimal.is_accepted(input) ? "true" : "false";
    std::cout << "[" << input << "]: is divisible by 3: " << check_d << "\n";
}


int main(int argc, char* argv[])
{
    //testInitializerList();
    //testBinaryAutomata();
    //testDecimalAutomata();

    if (argc == 1)
    {
        std::cerr<< "Usage: " << argv[0] << " <string to check>+";
        return 1;
    }

    for (int cnt = 1; cnt < argc; cnt++)
    {
        testArgv(argv[cnt]);
    }

    return 0;
}
