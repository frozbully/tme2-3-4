GCCFLAGS = -Wall
all : hachage_test

parser.o : parser.c parser.h
	gcc ${GCCFLAGS} -c parser.c

biblio.o : parser.o biblio.c biblio.h
	gcc ${GCCFLAGS} -c biblio.c

test.o : biblio.o test.c
	gcc ${GCCFLAGS} -c test.c biblio.o

biblio_hachage.o : biblio.o biblio_hachage.c biblio_hachage.h
	gcc ${GCCFLAGS} -c biblio_hachage.c biblio.o

hachage_test : biblio_hachage.o test.o
	gcc ${GCCFLAGS} -o tabdyn_test biblio_hachage.o test.o

clean :
	rm -f *.o
