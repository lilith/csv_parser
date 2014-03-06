using System;
using System.Text;
using System.Runtime.InteropServices;

// A wrapper for the CSV parser

namespace my_csv_wrapper
{
public class cs_csv_wrapper
{
	[DllImport("libcsv_parser.so", CallingConvention = CallingConvention.Cdecl)]
	public static extern void parse_csv(string filename, System.IntPtr output,ref int rows,ref int cols,ref int cell_size);
	[DllImport("libcsv_parser.so", CallingConvention = CallingConvention.Cdecl)]
	public static extern void free_csv_mem(System.IntPtr output);

	public static void do_parse_csv(string filename)
	{
		Console.WriteLine ("Reached wrapper");

		IntPtr csv_ptr = new IntPtr();
		int rows = 0;
		int cols = 0;
		int cell_size = 0;
		
		parse_csv(filename, csv_ptr, ref rows, ref cols, ref cell_size);
		// Need to figure out how to extract strings out of the csv_ptr.
		//StringBuilder test = new StringBuilder(csv_ptr[0,1]);
		//Console.WriteLine(test);
		free_csv_mem(csv_ptr);
		//Console.WriteLine(csv[0,5]);
	}
	
}
}
