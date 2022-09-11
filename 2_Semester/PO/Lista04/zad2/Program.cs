using System;
namespace zad2
{
    class Program
    {
        static void Main(string[] args)
        {
            PrimeCollection kolekcja = new PrimeCollection();
            kolekcja.setMaximum(97);
            foreach(int i in kolekcja)
            {
                Console.WriteLine(i);
            }
        }
    }
}
