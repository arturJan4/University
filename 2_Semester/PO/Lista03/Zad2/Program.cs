/*
 * PO lista 3, zad 2 
 * Artur Jankowski
 * indeks : 317928
 */
using System;
using MyDictionary;

namespace zad2
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Slownik<string, int> test = new Slownik<string, int>();
                test.insert("jeden", 1);
                test.insert("dwa", 2);
                test.insert("trzy", 3);
                test.print();

                Console.WriteLine(test.searchValue("dwa"));
                //Console.WriteLine(test.searchValue("cztery"));//throws exception
                test.delete("dwa");//usuwanie ze srodka
                test.print();

                test.delete("trzy");//usuwanie z poczatku
                test.insert("cztery", 4);
                test.print();

                test.delete("jeden");//usuwanie z konca
                test.print();

                test.delete("cztery");//uswanie ostatniego elemetnu
                test.print();
                //test.delete("x");// throws exception

                Console.WriteLine("TEST 2==========");
                Slownik<string, string> bazaStudentow = new Slownik<string, string>();
                bazaStudentow.insert("312314", "Aleksandra Malinowska");
                bazaStudentow.insert("311512", "Hubert Andrzejewski");
                bazaStudentow.insert("312551", "Zuzanna Szymanska");
                bazaStudentow.print();
              
                Console.WriteLine(bazaStudentow.searchValue("312551"));
                bazaStudentow.delete("312551");
                
                //Console.WriteLine(bazaStudentow.searchValue("312551"));//throws exception

                Console.ReadLine();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
