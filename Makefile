CC=gcc
CC_FLAGS=-c -Wall 

CS=mcs

all: libcsv_parser cs_csv_wrapper cs_csv_tester

libcsv_parser: libcsv_parser.c
	$(CC) $(CC_FLAGS) -o libcsv_parser.o libcsv_parser.c
	$(CC) -shared -o libcsv_parser.so libcsv_parser.o

cs_csv_tester: cs_csv_tester.cs
	$(CS) cs_csv_tester.cs

cs_csv_wrapper: cs_csv_wrapper.cs
	$(CS) cs_csv_wrapper.cs

clean:
	-rm csv_tester *.o *.so *.exe
