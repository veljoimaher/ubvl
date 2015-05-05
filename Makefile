all: ag

ag: lex.yy.o y.tab.o node.o
	gcc -o ag node.o lex.yy.o y.tab.o -lfl

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

clean:
	rm -f ag *.o oxout.* lex.yy.c y.tab.*
