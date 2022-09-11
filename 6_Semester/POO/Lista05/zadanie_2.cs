using System;
using System.IO;
using System.Text;

namespace POO_Lista5
{
    class CaesarStream : Stream
    {
        readonly private Stream inStream;
        readonly private int offset = 0;
        public CaesarStream(Stream inStream, int offset)
        {
            this.inStream = inStream;
            this.offset = offset;
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            var result = inStream.Read(buffer, offset, count);
            for (int i = 0; i < buffer.Length; i++)
            {
                buffer[i] = (byte)(((int)buffer[i] + this.offset) % 255);
            }
            return result;
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            byte[] buffer_n = new byte[buffer.Length];
            for (int i = 0; i < buffer.Length; i++)
            {
                buffer_n[i] = (byte)(((int)buffer[i] + this.offset) % 255);
            }
            inStream.Write(buffer_n, offset, count);
        }


        // use inStream methods directly
        public override long Length
        {
            get { return inStream.Length; }
        }

        public override bool CanSeek
        {
            get { return inStream.CanSeek; }
        }

        public override bool CanRead
        {
            get { return inStream.CanRead; }
        }

        public override bool CanWrite
        {
            get { return inStream.CanWrite; }
        }

        public override long Position
        {
            get { return inStream.Position; }
            set { inStream.Position = value; }
        }
        public override long Seek(long offset, SeekOrigin start)
        {
            return inStream.Seek(offset, start);
        }

        public override void SetLength(long length)
        {
            inStream.SetLength(length);
        }
        public override void Flush()
        {
            inStream.Flush();
        }

    }

    class Program
    {
        static void Main()
        {
            const string test = "ABCDEFabcdef123456 tekst to zaszyfrowania";
            int test_len = System.Text.ASCIIEncoding.ASCII.GetByteCount(test);


            // write ciphered
            FileStream fileToWrite = File.Create("test_zad2_in.txt");
            CaesarStream caeToWrite = new CaesarStream(fileToWrite, 5);
            // 5 to przesunięcie
            caeToWrite.Write(Encoding.ASCII.GetBytes(test), 0, test_len);
            fileToWrite.Close();

            // read ciphered
            FileStream fileCiphered = File.OpenRead("test_zad2_in.txt");
            var bytes_ciphered = new byte[test_len];
            fileCiphered.Read(bytes_ciphered, 0, test_len);
            fileCiphered.Close();
            
            // decipher
            FileStream fileToRead = File.OpenRead("test_zad2_in.txt");
            CaesarStream caeToRead = new CaesarStream(fileToRead, -5);
            // -5 znosi 5
            var bytes_read = new byte[test_len];
            caeToRead.Read(bytes_read, 0, test_len);
            fileToRead.Close();

            Console.WriteLine("before: '{0}'", test);
            Console.WriteLine("ciphered: '{0}'", Encoding.ASCII.GetString(bytes_ciphered));
            Console.WriteLine("deciphered: '{0}'", Encoding.ASCII.GetString(bytes_read));
            Console.ReadLine();
        }
    }
}
