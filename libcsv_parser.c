// Pass the CSV parser a string to parse this will return 2d array of strings containing the parsed information
// Then call free_parsed_mem after to clear the memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Usage:
// Call parse_csv with the filename, a variable to hold a pointer, 
// and two ints that will tell you the dimensions of the array that it will keep at the pointer.
// Use the arrays as you see fit, then call free_csv_mem() with the pointer and the dimensions to free up the memory.
extern void parse_csv(char* filename, char* pointer_to_memory, int* rows, int* cols, int* cell_size)
{
	printf("Reached parser\n");

	FILE *file;
	file = fopen(filename, "r");
	if (!file)
	{
		// An error occured opening the file.
		printf("An error occurred opening the file: %s\n", filename);
		return;
	}
	//printf("file opened\n");
	
	// Read file to be parsed
	// Fake some input:
	//char input[] = "field1,field2,fi\\\\eld3\r\n\"aaa\r\n\",\"bb,b\",\"ccc\"\r\n\"in \"\"quotes\"\"\",2,3\r\n1,2,\r\nzzz,yyy,xxx\r\n1,,3\r\n,,";
	
	// Track if we are currently inside quotes
	char in_quotes = 0;
	const int separator = (int)','; // Don't set this to something wierd like a backslash.
	
	// We will be keeping track of the next character as well as the current character.
	char current = getc(file);
	char next = EOF;
	if (current != EOF)
	{
		next = getc(file);
	}

	// Iterate over the input, counting rows and columns.
	// We're doing this to find out how much memory we need to assign.
	
	int cur_cols = 1;
	int cur_rows = 0;
	int cur_cell_size = 1;
	int max_cols = 1;
	int max_cell_size = 1;
	
	while (current != EOF)
	{
		if (current == separator)
		{
			// Out of spec option that could be added here: Handle other separators
			if (in_quotes)
			{
				printf("%c%d",current,in_quotes);// TEST output
				cur_cell_size++;
			} else {
				// Start a new cell
				in_quotes = 0;
				if (cur_cell_size > max_cell_size)
				{
					max_cell_size = cur_cell_size;
				}
				cur_cell_size = 1;
				cur_cols++;
				printf(">"); // TEST output
			}
		} else {
			switch(current)
			{
				case '"':
					// Handle quotes.
					// Out of spec option we could add: allow single quotes
					if (in_quotes)
					{
						// We were already in quotes, so either this is a double-quote which turns into a single quote
						// or it should be the end of the cell.
						if (next == '"')
						{
							printf("\"");// TEST output
							current = next;
							next = getc(file);
							cur_cell_size++;
						} else if (next == '\r' || next == '\n' || next == separator) {
							in_quotes = 0;
						}
						
					} else if (cur_cell_size == 1) {
						// We were not already inside quotes and this is the first char, so mark this cell as quoted
						in_quotes = 1;
						//printf("-SQ-"); // TEST output
					}
					break;
				case '\\':
					// The next character is escaped.  Handle that here.
					// Escaped characters cannot be special.
					// Note: if you want to handle line endings in a cell, it's probably best to use quotes and not escape.
					//  This is because if you try to escape a CLRF, I think you'll just end up escaping the CL and leave the
					//  RF alone.
					current = next;
					next = getc(file);
					printf("%c",current);// TEST output
					cur_cell_size++;
					break;
				// Out of spec option that I'm adding: allow CL or RF individually to end lines as well as CLRF
				case '\r': // fallthrough
				case '\n':
					if (in_quotes)
					{
						printf("=%c",current);// TEST output
						cur_cell_size++;
					} else {
						// This looks like a line ending.
						if (current == '\r' && next == '\n')
						{
							// Next character is part of the line ending.  Include it.
							current = next;
							next = getc(file);
						}
						printf("LF\r\n");// TEST output
						
						// Start a new row
						cur_rows++;
						if (cur_cols > max_cols)
						{
							max_cols = cur_cols;
						}
						if (cur_cell_size > max_cell_size)
						{
							max_cell_size = cur_cell_size;
						}
						cur_cell_size = 1;
						// Start a new cell
						cur_cols = 1;
						in_quotes = 0;
					}
					break;
				default:
					printf("%c",current);// TEST output
					cur_cell_size++;
			}
		}
		current = next;
		next = getc(file);
	}
	if (cur_cols > max_cols)
	{
		max_cols = cur_cols;
	}
	if (cur_cell_size > max_cell_size)
	{
		max_cell_size = cur_cell_size;
	}
	
	printf("max columns is: %d  rows is:%d  cell size is: %d\n", max_cols, cur_rows, max_cell_size);

	*cols = max_cols;
	*cell_size = max_cell_size;
	*rows = cur_rows;
	
	// Ok, now allocate memory for this, and go through it again.  This time we'll assign the cells to the memory.
	// Test passing strings back to C#
	pointer_to_memory = malloc((sizeof(char) * cur_rows * max_cols * max_cell_size));

	
	((char***)pointer_to_memory)[0][0][0] = 'a';
	((char***)pointer_to_memory)[0][0][1] = NULL;
	
	// Assign the cells to the allocated memory.
	
	// Clean up.
	fclose(file);
}


extern void free_csv_mem(char* pointer_to_memory)
{
	// Free the memory.
	free(pointer_to_memory);
	pointer_to_memory = NULL;
}
