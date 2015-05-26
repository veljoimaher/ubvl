CC=gcc
CFLAGS=-Wall

all: codea

codea: lex.yy.o y.tab.o node.o tree.o reg.o assembler.o
	gcc -o codea node.o tree.o lex.yy.o y.tab.o reg.o assembler.o codea.o -lfl

tree.o: tree.c tree.h codea.o
	gcc -c -ansi -pedantic -Wall tree.c -D_GNU_SOURCE

node.o: node.c node.h
	gcc -c -ansi -pedantic -Wall node.c -D_GNU_SOURCE

y.tab.c y.tab.h: oxout.y
	yacc -d oxout.y -o y.tab.c

oxout.y oxout.l: ag.y ag.flex
	ox ag.y ag.flex

lex.yy.c: oxout.l y.tab.h
	flex oxout.l

y.tab.o: y.tab.c node.h
	gcc -c -ansi -pedantic y.tab.c

lex.yy.o: lex.yy.c y.tab.h node.h
	gcc -c -ansi -pedantic lex.yy.c -D_GNU_SOURCE

# iburg
codea.o: codea.c
	gcc -ggdb -c -pedantic -Wall codea.c -D_GNU_SOURCE

codea.c: codea.bfe
	bfe < codea.bfe | iburg > codea.c

reg.o: reg.c reg.h
	gcc -c -ansi -pedantic -Wall reg.c -D_GNU_SOURCE

assembler.o: assembler.c assembler.h
	gcc -c -ansi -pedantic -Wall assembler.c 

clean:
	rm -f ag codea.c codea *.o oxout.* lex.yy.c y.tab.* *~
