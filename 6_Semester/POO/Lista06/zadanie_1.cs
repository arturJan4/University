using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POO_Lista6
{
    public interface ILogger
    {
        void Log(string Message);
    }

    public class NullLogger : ILogger
    {
        public void Log(string Message)
        {
            // empty
        }
    }

    public class ConsoleLogger : ILogger
    {
        public void Log(string Message)
        {
            Console.WriteLine(Message);
        }
    }

    public class FileLogger : ILogger
    {
        private string _path;
        public FileLogger(string path)
        {
            if (path == null)
            {
                // TODO: throw
            }

            _path = path;
        }

        public void Log(string Message)
        {
            System.IO.StreamWriter file = new System.IO.StreamWriter(_path);
            
            file.WriteLine(Message);
            
            file.Close();
        }
    }

    public enum LogType { None, Console, File }
    public class LoggerFactory
    {
        private static LoggerFactory _inst = null;

        public static ILogger GetLogger(LogType LogType, string Parameters = null)
        {
            switch (LogType)
            {
                case LogType.Console: return new ConsoleLogger();
                case LogType.File: return new FileLogger(Parameters);
                case LogType.None: return new NullLogger();
                default: throw new ArgumentException("Wrong Logger type");
            }
        }
        public static LoggerFactory Instance 
        {
            get
            {
                if (_inst == null)
                {
                    _inst = new LoggerFactory();
                }
                return _inst;
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // klient:
            ILogger logger1 = LoggerFactory.GetLogger(LogType.File, "foo.txt");
            logger1.Log("foo bar"); // logowanie do pliku
            ILogger logger3 = LoggerFactory.GetLogger(LogType.Console);
            logger3.Log("lorem");
            ILogger logger2 = LoggerFactory.GetLogger(LogType.None);
            logger2.Log("qux"); // brak logowania

            Console.Read();
        }
    }
}
