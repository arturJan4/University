using System;
using System.Data;
using System.Data.SqlClient;
using System.Xml;
using System.IO;

namespace zad3
{
    class Program
    {
        // Template Method -> Strategy
        public interface IDataAccessStrategy
        {
            void ConnectConn();
            void DownloadData();
            void ProcessData();
            void CloseConn();

            object GetResult();
        }

        public class DataAccessHandler
        {
            private readonly IDataAccessStrategy strategy;
            public object Result;

            public DataAccessHandler(IDataAccessStrategy strategy)
            {
                this.strategy = strategy;
            }

            public void Execute()
            {
                this.strategy.ConnectConn();
                this.strategy.DownloadData();
                this.strategy.ProcessData();
                this.strategy.CloseConn();
                Result = this.strategy.GetResult();
            }
        }

        public class DbAccessStrategy : IDataAccessStrategy
        {
            public int Sum = 0;
            private SqlConnection dbConn;
            private SqlDataReader dbReader;

            // connect to the DB
            public void ConnectConn()
            {
                this.dbConn = new SqlConnection("file:testDB.db");
                this.dbConn.Open();
            }
            // get a specific column from DB
            public void DownloadData()
            {
                var cmd = this.dbConn.CreateCommand();
                cmd.CommandText = "SELECT Price FROM Products";
                this.dbReader = cmd.ExecuteReader();
                cmd.Dispose();
            }
            // sum numbers in a column
            public void ProcessData()
            {
                while (dbReader.Read())
                {
                    Int32 num = dbReader.GetInt32(0);
                    Sum += num;
                }
            }
            // release resources
            public void CloseConn()
            {
                dbReader.Close();
                dbConn.Close();
            }

            public object GetResult()
            {
                return Sum;
            }
        }

        public class XMLAccessStrategy : IDataAccessStrategy
        {
            public string longest_name = "";
            public int longest_len = 0;
            private FileStream file;
            private XmlReader xmlReader;

            public void ConnectConn()
            {
                this.file = File.Open("testXML.xml", FileMode.Open);

            }
            public void DownloadData()
            {
                xmlReader = XmlReader.Create(file);
            }
            public void ProcessData()
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

            public void CloseConn()
            {
                xmlReader.Close();
                file.Close();
            }

            public object GetResult()
            {
                return longest_name;
            }
        }

        static void Test_db()
        {
            DataAccessHandler db_test = new DataAccessHandler(new DbAccessStrategy());
            db_test.Execute();
            Int32 result = Convert.ToInt32(db_test.Result);

            Console.WriteLine("Sum is {0}", result);
        }

        static void Test_xml()
        {
            DataAccessHandler xml_test = new DataAccessHandler(new XMLAccessStrategy());
            xml_test.Execute();
            String result = Convert.ToString(xml_test.Result);
            Console.WriteLine("Longest node name is {0} of len {1}", result, result.Length);
        }

        static void Main()
        {
            Test_db();
            Test_xml();
            Console.ReadLine();
        }
    }
}
