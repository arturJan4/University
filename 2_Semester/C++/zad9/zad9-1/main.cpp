/*
 *  Artur Jankowski
 *  CPP; zad9-1 Manipulatory
 *  indeks: 317928
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "manipulator.hpp"

void testWithoutParameters()
{
    std::cout << "----TEST CLEARLINE---- \n";
    std::stringstream  ss;
    ss << "przykladowy" << std::endl << "test";
    std::string stringTest;
    ss >> clearline >> stringTest;
    std::cout << stringTest << "\n";

    std::cout << "----TEST COMMA---- \n";
    std::cout << "przykladowy" << comma << "dzialajacy test\n";

    std::cout << "----TEST COLON---- \n";
    std::cout << "przykladowy" << colon << "dzialajacy test\n";
}

void testWithParameters()
{
    std::cout << "----TEST IGNORE--- \n";
    std::stringstream  ss;
    ss << "testprzykladowy";
    std::string stringTest;
    ss >> ignore(4) >> stringTest;
    std::cout << stringTest << "\n";

    std::cout << "----TEST INDEX---- \n";
    std::cout << index(200,6) << "\n";
    std::cout << index(1200,6) << "\n";
    std::cout << index(1,6) << "\n";
    std::cout << index(15,6) << "\n";
    std::cout << index(42000,6) << "\n";
}

void testVector()
{
    std::cout << "----TEST VECTOR--- \n";
    std::fstream file("vectorin.txt");
    std::string stringobj;
    std::vector<std::pair<std::string,int>> lineNmbWithText; //para <tekst, nr linii>

    int i = 0;
    while (getline(file,stringobj))
    {
        std::pair<std::string,int> para = std::make_pair(stringobj,i);
        lineNmbWithText.push_back(para);
        ++i;
    }
    std::sort(lineNmbWithText.begin(),lineNmbWithText.end(),
            [](const std::pair<std::string,int> & a, std::pair<std::string,int> & b)
            {return a.first < b.first;});

    int length = std::to_string(i).length();
    for (auto line : lineNmbWithText)
    {
        std::cout << index(line.second, length) << colon << line.first << "\n";
    }

};

int main()
{
    testWithoutParameters();
    testWithParameters();
    testVector();
    return 0;
}
