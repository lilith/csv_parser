// Pass the CSV parser a string to parse this will return 2d array of strings containing the parsed information
// Then call free_parsed_mem after to clear the memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
// Parse a line, return when we're done.
// Update loc whenever we move forward a character.
void parse_line(char input[], int* loc)
{
	printf("Reached parse_line\n");
	printf("loc is %d\n", *loc);
	puts(input);


	
	return;
}
*/

extern void parse_csv()
{
	printf("Reached parser\n");
	
	// Fake some input:
	char input[] = "field1,field2,fi\\\\eld3\r\n\"aaa\r\n\",\"bb,b\",\"ccc\"\r\n\"in \"\"quotes\"\"\",2,3\r\n1,2,\r\nzzz,yyy,xxx\r\n1,,3\r\n,,";
	
	// Keep track of where we are in the parse
	int location = 0;
	// Track if we are currently inside quotes
	char in_quotes = 0;
	
	/*
	parse_line(input, &location);
	location = 1;
	parse_line(&input, &location);
	*/
	
	while (input[location] != NULL)
	{
		// Iterate over the input
		
		switch(input[location])
		{
			case '"':
				// Handle quotes.
				if (in_quotes)
				{
					// We were already in quotes, so end the quote.
					in_quotes = 0;
					printf("-EQ-",input[location]);// TEST output
				} else {
					// We were not inside quotes, so start a new quoted section.
					in_quotes = 1;
					printf("-SQ-",input[location]); // TEST output
				}
				break;
			case '\\':
				// The next character is escaped.  Handle that here.
				// Escaped characters cannot be special.
				location++;
				printf("%c",input[location]);// TEST output
				break;
			case ',':
				if (in_quotes)
				{
					printf("%c",input[location]);// TEST output
				} else {
					// Start a new cell
					// TODO
				}
			// TODO: line endings
			default:
				printf("%c",input[location]);// TEST output
		}
		location++;
	}
		
}
