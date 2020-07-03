using System;
using System.Collections.Generic;

namespace Stream
{
    class IntStream
    {
        protected int value;

        public IntStream()
        {
            this.value = -1;
        }

        virtual public int Next()
        {
            this.value++;
            return this.value;
        }

        virtual public bool eos()
        {
            if (int.MaxValue == this.value)
                return true;
            else return false;
        }

        virtual public void reset()
        {
            this.value = -1;
        }
    }

    class PrimeStream : IntStream
    {
        public override int Next()
        {
            while (!base.eos())
            {
                base.Next();
                if (isPrime(this.value))
                    break;
            }
            return this.value;
        }

        private bool isPrime(int number)
        {
            if (number <= 0) return false;
            if (number == 2 || number == 3) return true;
            if (number == 1 || number % 2 == 0 || number % 3 == 0) return false;

            for (int i = 5; i * i <= number; i += 6)
            {
                if (i < 5) break;
                if ((number % i == 0) || number % (i + 2) == 0)
                    return false;
            }
            return true;
        }
    }
}
