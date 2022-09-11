using System;
using System.Data;
using System.Data.SqlClient;
using System.Xml;
using System.IO;

namespace zad2
{
    class Program
    {
        // Template Method
        public abstract class DataAccessHandler
        {
            // connect to data connection
            public abstract void ConnectConn();
            // download data
            public abstract void DownloadData();
            // process data
            public abstract void ProcessData();
            // close connection
            public abstract void CloseConn();

            public void Execute()
            {
                ConnectConn();
                DownloadData();
                ProcessData();
                CloseConn();
            }
        }

        public class DbAccessHandler : DataAccessHandler
        {
            public int Sum = 0;
            private SqlConnection dbConn;
            private SqlDataReader dbReader;

            // connect to the DB
            public override void ConnectConn()
            {
                this.dbConn = new SqlConnection("file:testDB.db");
                this.dbConn.Open();
            }
            // get a specif column from DB
            public override void DownloadData()
            {
                var cmd = this.dbConn.CreateCommand();
                cmd.CommandText = "SELECT Price FROM Products";
                this.dbReader = cmd.ExecuteReader();
                cmd.Dispose();
            }
            // sum numbers in a column
            public override void ProcessData()
            {
                while (dbReader.Read())
                {
                    Int32 num = dbReader.GetInt32(0);
                    Sum += num;
                }
            }
            // release resources
            public override void CloseConn()
            {
                dbReader.Close();
                dbConn.Close();
            }
        }

        public class XMLAccessHandler : DataAccessHandler
        {
            public string longest_name = "";
            public int longest_len = 0;
            private FileStream file;
            private XmlReader xmlReader;

            public override void ConnectConn()
            {
                this.file = File.Open("testXML.xml", FileMode.Open);

            }
            public override void DownloadData()
            {
                xmlReader = XmlReader.Create(file);
            }
            public override void ProcessData()
            {
                while (xmlReader.Read())
                {
                    if (longest_len < xmlReader.Name.Length)
                    {
                        longest_len = xmlReader.Name.Length;
                        longest_name = xmlReader.Name;
                    }
                }
            }

            public override void CloseConn()
            {
                xmlReader.Close();
                file.Close();
            }
        }

        static void Test_db()
        {
            DbAccessHandler db_test = new DbAccessHandler();
            db_test.Execute();
            Console.WriteLine("Sum is {0}", db_test.Sum);
        }

        static void Test_xml()
        {
            XMLAccessHandler xml_test = new XMLAccessHandler();
            xml_test.Execute();
            Console.WriteLine("Longest node name is {0} of len {1}", xml_test.longest_name, xml_test.longest_len);
        }

        static void Main()
        {
            Test_db();
            Test_xml();
            Console.ReadLine();
        }
    }
}
