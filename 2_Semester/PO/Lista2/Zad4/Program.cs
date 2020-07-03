using System;
using System.Collections.Generic;
using Stream;

namespace Zad4
{
    class ListaLeniwa
    {
        protected int m_size;
        protected Random m_next;
        protected List<int> m_lista;
        public ListaLeniwa()
        {
            m_size = 0;
            m_next = new Random();
            m_lista = new List<int>();
        }
        public int size()
        {
            return m_size;
        }
        public int element(int i)
        {
            if (i > m_size)
            {
                for (int k = m_size; k < i; ++k)
                {
                    m_lista.Add(this.generator());
                }
                m_size = i;
            }
            if (i < 1)
                throw new System.IndexOutOfRangeException("podano indeks poza zakresem");
            else
                return m_lista[i - 1];
        }
        virtual protected int generator()
        {
            return (m_next.Next());
        }
       
    }

    class Pierwsze : ListaLeniwa
    {
        Stream.PrimeStream primes;
        public Pierwsze()
        {
            m_size = 0;
            primes = new Stream.PrimeStream();
            m_lista = new List<int>();
        }
        protected override int generator()
        {
            return primes.Next();
        }
    }

    class Test
    {
        public void testLeniwa()
        {
            Console.WriteLine("======LENIWA=====");
            ListaLeniwa lista = new ListaLeniwa(); // lista.size() == 0

            Console.WriteLine("poczatkowy rozmiar listy: " + lista.size());
            Console.WriteLine("element nr.40: " + lista.element(40)); // lista.size() == 40
            Console.WriteLine("element nr.38: " + lista.element(38)); // lista.size() == 40
            Console.WriteLine("element nr.38: " + lista.element(38)); // lista.size() == 40
        }

        public void testPierwsze()
        {
            Console.WriteLine("======PIERWSZE=====");
            Pierwsze pierwsze = new Pierwsze();

            Console.WriteLine("liczba pierwsza nr.1: " + pierwsze.element(1));
            pierwsze.element(100);
            Console.WriteLine("liczba pierwsza nr.99: " + pierwsze.element(99));
            Console.WriteLine("liczba pierwsza nr.100: " + pierwsze.element(100));//541
            Console.WriteLine("liczba pierwsza nr.1000: " + pierwsze.element(1000));//7919
            Console.WriteLine("rozmiar listy: " + pierwsze.size());
        }

        public void testInteractive()
        {
            ListaLeniwa lista = new ListaLeniwa();
            Pierwsze pierwsze = new Pierwsze();

            while (1 != 0)
            {
                try
                {
                    Console.WriteLine("chcesz uzyc listy Leniwej(1) czy listy liczb pierwszych(2)?: ");
                    int choice = Convert.ToInt32(Console.ReadLine());
                    if (choice != 1 && choice != 2)
                    {
                        Console.WriteLine("podana zla cyfre");
                        return;
                    }
                    else if (choice == 1)
                    {
                        Console.WriteLine("ktory indeks listy chcesz zobaczyc");
                        int index = Convert.ToInt32(Console.ReadLine());
                        Console.WriteLine(lista.element(index));
                    }
                    else
                    {
                        Console.WriteLine("ktory indeks listy chcesz zobaczyc");
                        int index = Convert.ToInt32(Console.ReadLine());
                        Console.WriteLine(pierwsze.element(index));

                    }
                }
                catch (System.FormatException ex)
                {
                    Console.WriteLine(ex.Message);
                }
                catch (System.IndexOutOfRangeException ex)
                {
                    Console.WriteLine(ex.Message);
                }

            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Test nowyTest = new Test();

            nowyTest.testLeniwa();
            nowyTest.testPierwsze();
            nowyTest.testInteractive();
            Console.ReadLine();
        }
    }
}
