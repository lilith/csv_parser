using System;
using System.Runtime.InteropServices;

// A plcaeholder for the .NET wrapper
 
public class cs_helloworld
{
	[DllImport("libcsv_parser.so")]
	public static extern int parse_csv();

	static public void Main (string[] args)
	{
		Console.WriteLine ("Placeholder");
	}
}
