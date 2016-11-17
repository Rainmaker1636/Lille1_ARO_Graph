CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS += -g
CFLAGS += -std=c99

LDFLAGS  = -g

#PATH
inc = ../include

all: testAnalyseur donnees viz graphe.o

%.o: %.c %.h
	${CC} ${CFLAGS} -c $<
	
testAnalyseur: testAnalyseur.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^
	
donnees: donnees.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^
	
viz: viz.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^
	
graphe.o: ${inc}/graphe.c ${inc}/graphe.h
	${CC} ${CFLAGS} -c $<
	
clean :
	rm  *.o || true

realclean : clean
	rm testAnalyseur donnees viz || true
	
.PHONY: all clean realclean
