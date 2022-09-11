//PO lista 4 - zad1
//Artur Jankowski
//indeks 317928

using System;
using System.Collections;

namespace Streams
{
    public interface IStreams
    {
        public int next();
        public bool eos();
        public void reset();
    }

    class IntStreamEnum : IEnumerator
    {
        protected int value;
        public IntStreamEnum(int value)
        {
            this.value = value;
        }
        public bool MoveNext()
        {
            this.value++;

            return (this.value < int.MaxValue);
        }
        public void Reset()
        {
            value = -1;
        }
        public object Current
        {
            get
            {
                return value;
            }
        }
    }
    class IntStream : IEnumerable, IStreams
    {
        protected int value;

        public IntStream()
        {
            this.value = -1;
        }

        virtual public int next()
        {
            if (this.eos()) return this.value;

            this.value++;
            return this.value;
        }

        virtual public bool eos()
        {
            if (int.MaxValue == this.value)
                return true;
            else return false;
        }

        public void reset()
        {
            this.value = -1;
        }
        //nowe rzeczy
        IEnumerator IEnumerable.GetEnumerator()
        {
            return (IEnumerator)GetEnumerator();
        }
        public IntStreamEnum GetEnumerator()//implementacja IEnumerable
        {
            return new IntStreamEnum(value);
        }
        public override string ToString()
        {
            return String.Format("obecna wartosc kolekcji to: {0}", this.value);
        }
        public int this[int indeks]//dostep indeksowany
        {
            get
            {
                if (indeks < 0 || indeks > int.MaxValue)
                    return -1;

                var test = new IntStream();
                while (test.value != indeks)
                    test.next();

                return test.value;
            }
        }
        public int Length//wlaściwość length
        {
            get;
        }

    }

    class RandomStream : IntStream, IStreams
    {
        private Random rand;
        public RandomStream()
        {
            value = -1;
            rand = new Random();
        }
        public override bool eos()
        {
            return false;
        }
        public override int next()
        {
            this.value = rand.Next(0, (int.MaxValue - 1));
            return this.value;
        }
    }
}

