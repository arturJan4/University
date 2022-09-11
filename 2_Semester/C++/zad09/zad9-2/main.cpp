/*
 *  Artur Jankowski
 *  CPP; zad9-2 Pliki
 *  indeks: 317928
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "wejscie.hpp"
#include "wyjscie.hpp"

const std::string INPUTFILE = "input2";
const std::string OUTPUTFILE = "output2";

void prepareInput(const std::string &inputText)
{
    wyjscie output(INPUTFILE);
    std::string in = inputText;
    for(auto i : in)
    {
        output << i;
    }
}

void testReadSave()
{
    //zapisuje do pliku INPUTFILE argument prepareInput
    //odczytuje bajt po bajcie
    //i przepisuje do pliku OUTPUTFILE

    prepareInput("przykladowy tekst");

    wejscie input(INPUTFILE);
    wyjscie output(OUTPUTFILE);

    int x;

    while(!input.eof()) //przepisywanie bajt po bajcie
    {
        input >> x;
        output << x;
    }
 }

 void addRandom(std::string filepath)
 {
     srand((int)time(0));

     wyjscie output(filepath);
     for(int i = 0; i < 10; ++i)
     {
         output << rand();
     }
 }

 void testRandom()
 {
    //generuje pare losowych liczb calkowitcch
    //zapisuje je do pliku
    //odczytuje je z pliku i wyswietla na ekran
     addRandom(INPUTFILE);

     int x;
     wejscie input(INPUTFILE);
     while(!input.eof())
     {
         input >> x;
         std::cout << (int)x << "\n";
     }
 }

 void addToFile(std::string filepath)
 {
     wyjscie output(filepath);
     output << 255;
     output << 0;
     output << (int)'x';
     output << 12;
 }

 void testByteByByte()
 {
     //zapisuje do pliku i
     //odczytuje bajt po bajcie i wypisuje te bajty na ekran
    addToFile(INPUTFILE);
     int x;
     wejscie input(INPUTFILE);
     while(!input.eof())
     {
         input >> x;
         std::cout << x << " ";
     }
 }

int main()
{
    testReadSave();
    //testByteByByte();
    testRandom();
    return 0;
}
