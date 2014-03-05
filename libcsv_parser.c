// Pass the CSV parser a string to parse this will return 2d array of strings containing the parsed information
// Then call free_parsed_mem after to clear the memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Take filename of file to be parsed
extern void parse_csv(char* filename)
{
	printf("Reached parser\n");
	
	// char filename[] = "testfile.csv";

	FILE *file;
	file = fopen(filename, "r");
	if (!file)
	{
		// An error occured opening the file.
		printf("An error occurred opening the file: %s\n", filename);
		return;
	}
	printf("file opened\n");
	
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

	// Iterate over the input
	while (current != EOF)
	{
		
		if (current == separator)
		{
			// Out of spec option that could be added here: Handle other separators
			if (in_quotes)
			{
				printf("%c",current);// TEST output
			} else {
				// Start a new cell
				in_quotes = 0;
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
						} else {
							// Hmm.  Let's just do nothing.  If it's a separator or line feed it'll get handled next round.
							// If not, it might be best to just ignore this quote.
						}
						
					} else {
						// We were not already inside quotes, so mark this cell as quoted
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
					break;
				// Out of spec option that I'm adding: allow CL or RF individually to end lines as well as CLRF
				case '\r':
					if (in_quotes)
					{
						printf("%c",current);// TEST output
					} else {
						// This looks like a line ending.
						if (next == '\n')
						{
							// Next character is part of the line ending.  Include it.
							current = next;
							next = getc(file);
							printf("CLRF\r\n");// TEST output
						} else {
							printf("RF\r\n");// TEST output
						}
					}
					// Start a new cell
					in_quotes = 0;
					break;
				case '\n':
					if (in_quotes)
					{
						printf("%c",current);// TEST output
					} else {
						// This looks like a line ending.
						printf("RF\r\n");// TEST output
						// Start a new cell
						in_quotes = 0;
					}

					break;
				default:
					printf("%c",current);// TEST output
			}
		}
		current = next;
		next = getc(file);
	}
	
	// Clean up.
	fclose(file);
}
