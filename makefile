CC=gcc
all:valorizacion

INCLUDEDIR=./includes
CFLAGS=-I$(INCLUDEDIR)

utils.o: src/utils.c $(INCLUDEDIR)/utils.h
	gcc $(CFLAGS) -c src/utils.c -o utils.o 

Options.o: src/Options.c $(INCLUDEDIR)/Options.h utils.o
	gcc $(CFLAGS) -c src/Options.c -o Options.o

FinancialAsset.o: src/FinancialAsset.c $(INCLUDEDIR)/FinancialAsset.h utils.o
	gcc $(CFLAGS) -c src/FinancialAsset.c -o FinancialAsset.o

ChildProcess.o: src/ChildProcess.c $(INCLUDEDIR)/ChildProcess.h utils.o
	gcc $(CFLAGS) -c src/ChildProcess.c -o ChildProcess.o

GrandChildProcess.o: src/GrandChildProcess.c $(INCLUDEDIR)/GrandChildProcess.h FinancialAsset.o
	gcc $(CFLAGS) -c src/GrandChildProcess.c -o GrandChildProcess.o

main.o: src/main.c  Options.o ChildProcess.o utils.o
	gcc $(CFLAGS) -c src/main.c -o main.o

valorizacion: main.o GrandChildProcess.o ChildProcess.o FinancialAsset.o Options.o utils.o
	gcc main.o GrandChildProcess.o ChildProcess.o FinancialAsset.o Options.o utils.o -o valorizacion

clean:
	rm -f valorizacion *.o
