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
					// Out of spec option we could add: allow single quotes
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
				// Out of spec option that I'm adding: allow CL or RF individually to end lines as well as CLRF
				case '\r':
					if (in_quotes)
					{
						printf("%c",input[location]);// TEST output
					} else {
						// This looks like a line ending.
						if (input[location+1] == '\n')
						{
							// Next character is part of the line ending.  Include it.
							location++;
							printf("CLRF\r\n");// TEST output
						} else {
							printf("RF\r");// TEST output
						}
					}
					break;
				case '\n':
					if (in_quotes)
					{
						printf("%c",input[location]);// TEST output
					} else {
						// This looks like a line ending.
						printf("RF\r");// TEST output
					}
					break;
				default:
					printf("%c",input[location]);// TEST output
			}
		}
		location++;
	}
		
}
