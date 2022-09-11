using System;

namespace Before
{
	public class ReportPrinter
	{
		public string GetData()
		{
			Console.WriteLine("Get");
			return "hello World";
		}

		public void FormatDocument()
		{
			Console.WriteLine("Format");
		}

		public void PrintReport()
		{
			string s = GetData();
			FormatDocument();
			Console.WriteLine("Hello World");
		}
	}
}

namespace After
{
	class ReportDownloader
	{
		public string GetData()
		{
			Console.WriteLine("Get");
			return "hello World";
		}
	}

	class ReportFormatter
	{
		public void FormatDocument()
		{
			Console.WriteLine("Format");
		}
	}

	class ReportPrinter
	{
		public void PrintReport()
		{
			ReportDownloader downloader = new ReportDownloader();
			string s = downloader.GetData();
			ReportFormatter formatter = new ReportFormatter();
			formatter.FormatDocument();
			Console.WriteLine("Hello World");
		}
	}
}

public class Zad2
{
	public static void Main(string[] args)
	{
		var oldR = new Before.ReportPrinter();
		var newR = new After.ReportPrinter();
		Console.WriteLine("Before:");
		oldR.PrintReport();
		Console.WriteLine();
		Console.WriteLine("After:");
		newR.PrintReport();
	}
}