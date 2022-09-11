using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Singleton
{
    // one instance per process
    public sealed class SingletonGlobal
    {
        // current instance of singleton
        private static SingletonGlobal instance = null;
        // lock used for concurrency issues
        private static readonly object _lock = new object();

        public static SingletonGlobal Instance()
        {
            if (instance == null)
            {
                lock (_lock)
                {
                    // double checking after acquiring lock
                    if (instance == null)
                    {
                        instance = new SingletonGlobal();
                    }
                }
            }
            return instance;
        }
    }

    // one instance per thread
    public sealed class SingletonThread
    {
        [ThreadStatic]
        static SingletonThread instance;

        private SingletonThread() { }

        public static SingletonThread Instance()
        {
            if (instance == null)
            {
                instance = new SingletonThread();
            }

            return instance;

        }
    }

    // one instance for at most 5 seconds
    public sealed class SingletonTimed
    {
        /// <summary>
        /// same as first version but added timer
        /// </summary>
        // current instance of singleton
        private static SingletonTimed instance = null;
        // lock used for concurrency issues
        private static readonly object _lock = new object();

        private static DateTime time;

        public static SingletonTimed Instance()
        {
            if ((instance == null) || ((DateTime.Now - time).Seconds > 5))
            {
                lock (_lock)
                {
                    // double checking after acquiring lock
                    if ((instance == null) || ((DateTime.Now - time).Seconds > 5))
                    {
                        instance = new SingletonTimed();
                        time = DateTime.Now;
                    }
                }
            }
            return instance;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // Display the number of command line arguments.
            Console.WriteLine(args.Length);
        }
    }
}
