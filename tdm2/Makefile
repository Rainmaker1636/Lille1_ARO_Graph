CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS += -g
CFLAGS += -std=c99

LDFLAGS  = -g

#PATH
inc = ../include

all: graphe.o breadth

%.o: %.c %.h
	${CC} ${CFLAGS} -c $<
	
graphe.o: ${inc}/graphe.c ${inc}/graphe.h
	${CC} ${CFLAGS} -c $<
	
breadth: breadth_traversal.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^
	
clean :
	rm *.o || true

realclean : clean
	rm breadth || true
	
.PHONY: all clean realclean
