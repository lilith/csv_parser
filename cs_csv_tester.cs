using System;
using System.Runtime.InteropServices;
using my_csv_wrapper;

// A csv test

 
public class cs_csv_tester
{
	[DllImport("libcsv_parser.so")]
	public static extern int parse_csv();

	static public void Main (string[] args)
	{
		string test_string = "field1,field2,field3\r\n" +

			"\"aaa\r\n\",\"bb,b\",\"ccc\"\r\n" +

			"\"in \"\"quotes\"\"\",2,3\r\n" +

			"1,2,\r\n" +

			"zzz,yyy,xxx\r\n" +

			"1,,3\r\n" +

			",,";



		string[][] expected_output = new string[][]{

			new string[]{"field1", "field2", "field3"},

			new string[]{ "aaa\r\n", "bb,b", "ccc"},

			new string[]{"in \"quotes\"", "2", "3"},

			new string[]{"1", "2", ""},

			new string[]{"zzz", "yyy", "xxx"},

			new string[]{"1", "", "3"},

			new string[]{"", "", ""}};
	
		Console.WriteLine ("Starting CSV Tester");
		
		cs_csv_wrapper.do_parse_csv();
	}
}

