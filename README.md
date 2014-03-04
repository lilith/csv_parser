csv_parser
==========

The task is to create a RFC 4180-compliant CSV parser in C. You can
assume that no headers are used, but it must be able to handle the
pathological case of a RFC-compliant CSV file.  You may assume any
character encoding as long as it is handled properly.


Goals are (a) correctness, and (b) code shortness and simplicity.
Ignore performance concerns, API design, or coding for the lowest
common denominator of reader. Note that real-world CSV files and
parsers are not RFC compliant, so they would likely lead you astray.
Regular expressions will be useful. You may use a parser generator,
but they're not recommended. TDD would be good; as would splitting up
the given test data into more granular components that test individual
issues.


Feel free to solve the problem in as many different ways as you like,
only the best solution will be judged. Start by committing this
information as a readme files. Commit very frequently, and make sure
your commit messages explain the approach you are taking/trying.


A ruby solution is usually 60-80 lines, a F# solution 120-160, and C#
usually 200-600. We're not precisely optimizing for shortness of the
code, just for maximum simplicity, but the two are related in this
task.


Once you have completed the implementation in C, create a simple .NET
wrapper that allows the functionality to be called from C# or F#.


http://www.ietf.org/rfc/rfc4180.txt


Test data (C#)


test_string = "field1,field2,field3\r\n" +

"\"aaa\r\n\",\"bb,b\",\"ccc\"\r\n" +

"\"in \"\"quotes\"\"\",2,3\r\n" +

"1,2,\r\n" +

"zzz,yyy,xxx\r\n" +

"1,,3\r\n" +

",,";



expected_output = new string[][]{

    new string[]{"field1", "field2", "field3"},

    new string[]{ "aaa\r\n", "bb,b", "ccc"},

    new string[]{"in \"quotes\"", "2", "3"},

    new string[]{"1", "2", ""},

    new string[]{"zzz", "yyy", "xxx"},

    new string[]{"1", "", "3"},

    new string[]{"", "", ""}};


ABNF:

The ABNF grammar [2] appears as follows:

  file = [header CRLF] record *(CRLF record) [CRLF]

  header = name *(COMMA name)

  record = field *(COMMA field)

  name = field

  field = (escaped / non-escaped)

  escaped = DQUOTE *(TEXTDATA / COMMA / CR / LF / 2DQUOTE) DQUOTE

  non-escaped = *TEXTDATA

  COMMA = %x2C

  CR = %x0D ;as per section 6.1 of RFC 2234 [2]

  DQUOTE =  %x22 ;as per section 6.1 of RFC 2234 [2]

  LF = %x0A ;as per section 6.1 of RFC 2234 [2]

  CRLF = CR LF ;as per section 6.1 of RFC 2234 [2]

  TEXTDATA =  %x20-21 / %x23-2B / %x2D-7E
