CC=gcc
CFLAGS=-Wall

all: codea

codea: lex.yy.o y.tab.o node.o tree.o
	gcc -o codea node.o tree.o lex.yy.o y.tab.o codea.o -lfl

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
	gcc -ggdb -c -pedantic -Wall codea.c -DUSE_IBURG -DBURM -D_GNU_SOURCE

codea.c: codea.bfe
	bfe < codea.bfe | iburg > codea.c

#$(NAME)b: $(NAME)b.o lexer.o $(NAME)_iburg.o
#	gcc -o $(NAME)b $(NAME)b.o $(NAME)_iburg.o lexer.o -lfl
#
#$(NAME)b.o: $(NAME).c $(NAME).h
#	gcc -c -DUSE_IBURG $(NAME).c -o $(NAME)b.o
#
#$(NAME)_iburg.o: $(NAME)_iburg.c tree.h
#	gcc -c -DUSE_IBURG -DBURM $(NAME)_iburg.c
#
#$(NAME)_iburg.c: $(NAME).bfe
#	bfe < $(NAME).bfe | iburg > $(NAME)_iburg.c

clean:
	rm -f ag codea.c codea *.o oxout.* lex.yy.c y.tab.* *~
