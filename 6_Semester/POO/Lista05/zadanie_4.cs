using System;
using System.Collections;

namespace POO_Lista5
{
    class CompareAdapter<T> : IComparer
    {
        Comparison<T> _compare;
        public CompareAdapter(Comparison<T> comparer)
        {
            _compare = comparer;
        }

        public int Compare(object l, object r)
        {
            return _compare((T)l, (T)r);
        }
    }

    class Program
    {
        /* this is the Comparison<int> to be converted */
        static int IntComparer(int x, int y)
        {
            return x.CompareTo(y);
        }

        static void Main(string[] args)
        {
            ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };

            /* the ArrayList's Sort method accepts ONLY an IComparer */
            a.Sort(new CompareAdapter<int>(IntComparer));

            foreach (var i in a)
            {
                Console.WriteLine(i);
            }

            Console.ReadLine();
        }
    }
}
