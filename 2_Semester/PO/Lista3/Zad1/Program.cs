/*
 * PO lista 3, zad 1 
 * Artur Jankowski
 * indeks : 317928
 */
using System;
using ListyLib.Listy;

namespace zad1
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Lista<int> list1 = new Lista<int>();
                list1.addBack(2);
                list1.addBack(3);
                list1.addFront(5);
                list1.printList();
                Console.WriteLine("----");
                Console.WriteLine(list1.popBack());
                Console.WriteLine(list1.popBack());
                Console.WriteLine(list1.popBack());
                //Console.WriteLine(list1.popBack());//throws exception
                list1.printList();

                Console.WriteLine("----");
                list1.addFront(42);
                Console.WriteLine(list1.popFront());
                //list1.popFront();//exception 

                Console.WriteLine("----");
                Lista<string> list2 = new Lista<string>();
                list2.addBack("test");
                list2.addBack("drugi");
                list2.printList();
                Console.WriteLine(list2.popFront());
                Console.WriteLine(list2.popBack());
                //Console.WriteLine(list2.popFront());throws exception

                Console.Readline();
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        
    }
}
