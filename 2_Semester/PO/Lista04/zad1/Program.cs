//PO lista 4 - zad1
//Artur Jankowski
//indeks 317928

using System;
using System.Collections;
using Streams;

namespace zad1
{
    public class Tests
    {
        public void printAllInts()//very long loop
        {
            Console.WriteLine("===Testy foreach===");
            IntStream stream = new IntStream();
            foreach (int e in stream)
            {
                Console.WriteLine(e);
            }
        }
        public void testToString()
        {
            Console.WriteLine("===Testy metody ToString()===");
            IntStream stream = new IntStream();
            Console.WriteLine(stream);
            stream.next();
            Console.WriteLine(stream);
        }
        public void testIndexedAcces()
        {
            Console.WriteLine("===Testy dostepu indeksowanego===");
            IntStream stream = new IntStream();
            Console.WriteLine(stream[10]);
            Console.WriteLine(stream[9]);
        }
        public void testLengthProperty()
        {
            Console.WriteLine("===Testy wlasciwosci Length===");
            IntStream stream = new IntStream();
            Console.WriteLine(stream.Length);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Tests testy = new Tests();
            //commented out, because it takes a long time to finish printing
            //testy.printAllInts();
            testy.testToString();
            testy.testIndexedAcces();
            testy.testLengthProperty();
        }
    }
}
