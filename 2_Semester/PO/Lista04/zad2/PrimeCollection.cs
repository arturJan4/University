using System;
using System.Collections;
 class PrimeCollection : IEnumerable
    {
        private int value = 1;
        private int maximum = int.MaxValue;
        IEnumerator IEnumerable.GetEnumerator()
        {
            return (IEnumerator)GetEnumerator();
        }

        public PrimeEnumerator GetEnumerator()
        {
            return new PrimeEnumerator(this);
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

        virtual public bool eos()
        {
            if (maximum == this.value)
                return true;
            else return false;
        }

        public void reset()
        {
            this.value = 1;
        }
        public int getValue()
        {
            return this.value;
        }
        public int getMaximum()
        {
            return this.maximum;
        }
        public void setMaximum(int max)
        {
            maximum = max;
        }
        public int next()
        {
            if(this.value == maximum)
            {
                this.value = -1;
                return this.value;
            }

             while (!this.eos())
             {
                this.value++;
                if (isPrime(this.value))
                {
                    return this.value;
                }
             }
            if (this.value < 0 || (!isPrime(this.value)))
                 this.value = -1;

            return this.value;
        }
    }
    class PrimeEnumerator : IEnumerator
    {
        PrimeCollection m_collection;
        public PrimeEnumerator(PrimeCollection o)
        {
            m_collection = o;
        }

        public bool MoveNext()
        {
            m_collection.next();

            return (this.m_collection.getValue() > -1 && 
                    this.m_collection.getValue() <= m_collection.getMaximum());
        }
        public void Reset()
        {
            m_collection.reset();
        }
        public object Current
        {
            get
            {
                return m_collection.getValue();
            }
        }
    }

