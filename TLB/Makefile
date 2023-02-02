CC = gcc

all: teste teste2

teste: tlb.c 
	$(CC) -o teste tlb.c

teste2: tlb2.c 
	$(CC) -o teste2 tlb2.c

run:
	./teste script.txt > dados1.csv
	./teste2 script.txt > dados2.csv

clear:
	rm -rf *.o *~ teste
	rm -rf *.o *~ teste2
	rm -rf *.csv