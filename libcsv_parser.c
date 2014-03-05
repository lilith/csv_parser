// Pass the CSV parser a string to parse this will return 2d array of strings containing the parsed information
// Then call free_parsed_mem after to clear the memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Parse a line, return when we're done.
// Update loc whenever we move forward a character.
void parse_line(char input[], int* loc)
{
	printf("Reached parse_line\n");
	printf("loc is %d\n", *loc);
	puts(input);

	// Is this character only 1-character wide?
	// Escapes and line endings are multiple characters.
	
	// Is this character a comma?
	
	// Is this character at the start of a word?
	// Is it at the start of a word, and is a quote?
	
	return;
}


extern void parse_csv()
{
	printf("Reached parser\n");
	
	// Fake the input:
	char input[] = "field1,field2,field3\r\n\"aaa\r\n\",\"bb,b\",\"ccc\"\r\n\"in \"\"quotes\"\"\",2,3\r\n1,2,\r\nzzz,yyy,xxx\r\n1,,3\r\n,,";
	
	// Keep track of where we are in the parse
	int location = 0;
	
	// Iterate over the input, breaking it up into lines.
	// Every time we've just ended a line either we're done or we start another.
	parse_line(input, &location);
	location = 1;
	parse_line(&input, &location);
		
}
