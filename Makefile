CC=gcc
CC_FLAGS=-c -Wall 

CS=mcs

all: libcsv_parser cs_csv_wrapper cs_csv_tester

libcsv_parser: libcsv_parser.c
	$(CC) $(CC_FLAGS) -fPIC -o libcsv_parser.o libcsv_parser.c
	$(CC) -shared -o libcsv_parser.so libcsv_parser.o

cs_csv_wrapper: cs_csv_wrapper.cs
	$(CS) /target:library cs_csv_wrapper.cs

cs_csv_tester: cs_csv_tester.cs
	$(CS) /r:cs_csv_wrapper.dll cs_csv_tester.cs


clean:
	-rm *.o *.so *.exe *.dll
