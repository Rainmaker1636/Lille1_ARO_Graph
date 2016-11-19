CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS += -g
CFLAGS += -std=c99

LDFLAGS  = -g

#PATH
inc = ../include

all: graphe.o shortest

%.o: %.c %.h
	${CC} ${CFLAGS} -c $<
	
graphe.o: ${inc}/graphe.c ${inc}/graphe.h
	${CC} ${CFLAGS} -c $<
	
shortest: shortest.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^
	
clean :
	rm *.o || true

realclean : clean
	rm shortest || true
	
.PHONY: all clean realclean
