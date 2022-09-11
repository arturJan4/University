using System;
using System.Net;
using System.IO;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Threading;

namespace zad1
{
    public interface ICommand
    {
        void Execute();
    }

    // a)
    // download a file through FTP
    public class FTPDownloadCommand : ICommand
    {
        private readonly Uri address;
        private readonly string fileName;
        private readonly WebClient client = new WebClient();
        public FTPDownloadCommand(string address, string fileName)
        {
            this.address = new Uri(address);
            this.fileName = fileName;
        }

        public void Execute()
        {
            client.DownloadFile(address, fileName);
        }
    }

    // b)
    // download a file through HTTP
    public class HTTPDownloadCommand : ICommand
    {
        private readonly Uri address;
        private readonly string fileName;
        private readonly WebClient client = new WebClient();
        public HTTPDownloadCommand(string address, string fileName)
        {
            this.address = new Uri(address);
            this.fileName = fileName;
        }

        public void Execute()
        {
            client.DownloadFile(address, fileName);
        }
    }

    // c)
    // create an empty file and fill with random data
    public class RandomFileCommand : ICommand
    {
        private readonly string fileName;
        private readonly int fileSize; // in bytes

        public RandomFileCommand(int size, string fileName)
        {
            this.fileSize = size;
            this.fileName = fileName;
        }

        public void Execute()
        {
            Random random_gen = new Random();
            Byte[] bytes = new Byte[this.fileSize];

            random_gen.NextBytes(bytes);
            File.WriteAllBytes(fileName, bytes);
        }
    }
    // d)
    // copy given file with a different name
    public class CopyFileCommand : ICommand
    {
        private readonly string fileNameSrc;
        private readonly string fileNameDest;

        public CopyFileCommand(string fileNameSrc, string fileNameDest)
        {
            this.fileNameSrc = fileNameSrc;
            this.fileNameDest = fileNameDest;
        }

        public void Execute()
        {
            File.Copy(fileNameSrc, fileNameDest);
        }
    }

    // part-2 queueing automata
    public class CommandInvoker
    {
        private readonly ConcurrentQueue<ICommand> queue;
        public CommandInvoker()
        {
            this.queue = new ConcurrentQueue<ICommand>();

            var thread1 = new Thread(this.RunQueue);
            var thread2 = new Thread(this.RunQueue);

            // main threads enqueues
            // two additional threads taking commands from queue
            thread1.Start();
            thread2.Start();
        }

        private void RunQueue()
        {
            while (true)
            {
                if (this.queue.Count < 1)
                {
                    Thread.Sleep(15); // sleep current for 15ms
                    continue;
                }

                lock (this.queue)
                {
                    if (this.queue.Count > 0)
                    {

                        if (this.queue.TryDequeue(out ICommand comm))
                        {
                            comm.Execute();
                        }
                    }
                }
            }
        }

        // instead of executing primary thread adds to queue
        public void Execute(ICommand command)
        {
            queue.Enqueue(command);
        }
    }
    class Program
    {
        static void Test_commands()
        {
            const string FTP_URI = "ftp://ftp.task.gda.pl/test/1mega";
            const string HTTP_URI = "https://ftp.task.gda.pl/test/1mega";

            var commandFTP = new FTPDownloadCommand(FTP_URI, "test_ftp");
            var commandHTTP = new HTTPDownloadCommand(HTTP_URI, "test_http");
            var commandRandom = new RandomFileCommand(10000, "test_random");
            var commandCopy = new CopyFileCommand("test_random", "test_copy");

            commandFTP.Execute();
            Console.WriteLine("FTP downloaded");
            commandHTTP.Execute();
            Console.WriteLine("HTTP downloaded");
            commandRandom.Execute();
            Console.WriteLine("Random created");
            commandCopy.Execute();
            Console.WriteLine("File copied");

            //Console.WriteLine(FTP_URI);
            //Console.ReadLine();
        }

        static void Test_invoker()
        {
            const string FTP_URI = "ftp://ftp.task.gda.pl/test/1mega";
            const string HTTP_URI = "https://ftp.task.gda.pl/test/1mega";

            var commandFTP = new FTPDownloadCommand(FTP_URI, "test_ftp_invoke");
            var commandHTTP = new HTTPDownloadCommand(HTTP_URI, "test_http_invoke");
            var commandRandom = new RandomFileCommand(10000, "test_random_invoke");
            var commandCopy = new CopyFileCommand("test_random", "test_copy_invoke");

            CommandInvoker invoker = new CommandInvoker();

            invoker.Execute(commandFTP);
            invoker.Execute(commandHTTP);
            invoker.Execute(commandRandom);
            invoker.Execute(commandCopy);
            Console.WriteLine("invoker finished");
            Console.ReadLine();
        }

        static void Main()
        {
            Test_commands();
            Test_invoker();
            Console.ReadLine();
        }
    }
}
