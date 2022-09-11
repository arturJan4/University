/*
 *  Artur Jankowski
 *  CPP - zad 10 kalkulator ONP
 *  indeks : 317928
 */
#include "kalkulator.hpp"
#include "testy.hpp"

// interactive RPN calculator

using namespace Kalkulator;

int main()
{
    /*
     * Przykladowa interakcja :
     * assign 2 -4.5 + 3 * floor abs to x  //mozna uzywac ',' lub '.' do odzielenia dziesietnych
     * print x
     * > 8
     * print 0 x 2 pow -
     * > -64
     * clear
     * print x
     * > nieznane wyrazenie: x
     * print 10 100 log
     * > 2
     * print e pi pow
     * > 23.1407
     * exit
     */

    //testSuite(); //odkomentuj by uruchomic testy
    //w operandy.hpp odkomentuj //#define DEBUG, by wyswietlac wiecej komunikatow

    interactiveCalc calc;
    calc.loop();
    return 0;
}
