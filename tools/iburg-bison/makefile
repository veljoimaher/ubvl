CC=cc
CFLAGS=-O2
LDFLAGS=-O2
YFLAGS=
OBJS=aburg.o gram.o

iburg:		aburg.o gram.o
		$(CC) -o iburg $(LDFLAGS) $(OBJS)

$(OBJS):	iburg.h

test:		iburg sample4.brg sample5.brg
		iburg -I sample4.brg sample4.c; $(CC) sample4.c; a.out
		iburg -I sample5.brg sample5.c; $(CC) sample5.c; a.out

clean:
		rm -f *.o core sample*.c a.out

clobber:	clean
		rm -f y.tab.c iburg
