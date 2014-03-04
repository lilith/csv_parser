using System;
using System.Runtime.InteropServices;

// A wrapper for the CSV parser

namespace my_csv_wrapper
{
public class cs_csv_wrapper
{
	[DllImport("libcsv_parser.so")]
	public static extern void parse_csv();

	public static void do_parse_csv()
	{
		Console.WriteLine ("Reached wrapper");
		parse_csv();
	}
	
}
}
