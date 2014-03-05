// Pass the CSV parser a string to parse this will return 2d array of strings containing the parsed information
// Then call free_parsed_mem after to clear the memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Take filename of file to be parsed
extern void parse_csv()
{
	printf("Reached parser\n");

	// Read file to be parsed
	// Fake some input:
	char input[] = "field1,field2,fi\\\\eld3\r\n\"aaa\r\n\",\"bb,b\",\"ccc\"\r\n\"in \"\"quotes\"\"\",2,3\r\n1,2,\r\nzzz,yyy,xxx\r\n1,,3\r\n,,";
	
	// Keep track of where we are in the parse
	int location = 0;
	// Track if we are currently inside quotes
	char in_quotes = 0;
	const int separator = (int)','; // Don't set this to something wierd like a backslash.
	
	// Iterate over the input
	while (input[location] != NULL)
	{
		
		if (input[location] == separator)
		{
			// Out of spec option that could be added here: Handle other separators
			if (in_quotes)
			{
				printf("%c",input[location]);// TEST output
			} else {
				// Start a new cell
				printf(">"); // TEST output
			}
		} else {
			switch(input[location])
			{
				case '"':
					// Handle quotes.
					if (in_quotes)
					{
						// We were already in quotes, so end the quote.
						in_quotes = 0;
						printf("-EQ-");// TEST output
					} else {
						// We were not inside quotes, so start a new quoted section.
						in_quotes = 1;
						printf("-SQ-"); // TEST output
					}
					break;
				case '\\':
					// The next character is escaped.  Handle that here.
					// Escaped characters cannot be special.
					location++;
					printf("%c",input[location]);// TEST output
					break;
				case '\r':
					if (in_quotes)
					{
						printf("%c",input[location]);// TEST output
					} else {
						// This looks like the start of a line ending.
						if (input[location] == '\n')
						{
							printf("CLRF\r\n",input[location]);// TEST output
						} else {
							printf("%c",input[location]);// TEST output
						}
					}
				// Out of spec option that could be added here: allow CL or RF individually to end lines
				default:
					printf("%c",input[location]);// TEST output
			}
		}
		location++;
	}
		
}
