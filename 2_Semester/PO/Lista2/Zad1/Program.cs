using System;
using System.Text;

class IntStream
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
}

class PrimeStream : IntStream
{
    public override int next()
    {
        while(!isPrime(this.value))
        {
            base.next();
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

class RandomStream : IntStream
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

class RandomWordStream// no inheritance (overload override problem!)
{
    private PrimeStream prime;
    private RandomStream random;

    public RandomWordStream()
    {
        prime = new PrimeStream();
        random = new RandomStream();
    }

    public bool eos()
    {
        return prime.eos();
    }

    public void reset()
    {
        prime.reset();
        random.reset();
    }

    public string next()
    {
        //string output = "";
        //zwykly string tworzy kopie przy kazdym appendzie
        int length = prime.next();
        StringBuilder myStringBuilder = new StringBuilder("",length);
        for (int i = 0; i < length; ++i)
        {
            char letter = (char)((random.next() % 93) + 33);// (space -> ~) // e.g 26 'a' for all lowercase
            myStringBuilder.Append(letter);
        }

        return myStringBuilder.ToString();
    }
    public int getValue()
    {
        return prime.next();
    }
}

class Test
{
   public void eosTEST()
    {
        IntStream ints = new IntStream();
        for(int i = 0; i < int.MaxValue; ++i)
        {
            ints.next();
        }
        if (ints.eos())
            Console.WriteLine("EOS - ints");
    }

    public void zPrzykladuPrimeStream()
    {
        PrimeStream ps = new PrimeStream();
        Console.WriteLine(ps.next()); // zwraca 2
        Console.WriteLine(ps.next()); // zwraca 3
    }
    public void zPrzykladu(RandomWordStream rws)
    {
        Console.WriteLine(rws.next()); // zwraca losowy string o dł 2
        Console.WriteLine(rws.next()); // zwraca losowy string o dł 3
        rws.reset();
    }

    public void interactive(RandomWordStream rws)
    {
        try
        {
            Console.WriteLine("write maximum length to skip (one integer): ");
            int start = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("how many strings to generate? (one integer): ");
            int howMany = Convert.ToInt32(Console.ReadLine());
            if (howMany < 0)throw new System.ArgumentException("nie da sie wygenerowac mniej niz zero ciagow :/");
            while (rws.getValue() < start) ;
            for (int i = 0; i < howMany; ++i)
            {
                Console.WriteLine(rws.next());
            }
        }
        catch(SystemException e)
        {
            Console.WriteLine(e.Message);
        }


    }
}
   
class Program
    {
    static void Main(string[] args)
        {
        Test test = new Test();
        RandomWordStream rws = new RandomWordStream();
        //test.eosTEST();//dlugo trwa
        test.zPrzykladuPrimeStream();
        test.zPrzykladu(rws);
        test.interactive(rws);

        Console.ReadLine();
        }
}
