NAME = beispiel1

all: $(NAME) $(NAME)b

lexer.o: lexer.c oxout.tab.h
	gcc -c lexer.c

$(NAME).c oxout.tab.h: oxout.y
	bison -vd oxout.y && mv oxout.tab.c $(NAME).c

lexer.c: oxout.l
	flex -t oxout.l > lexer.c

oxout.y oxout.l: $(NAME).y $(NAME).l
	ox $(NAME).y $(NAME).l

# iburg
$(NAME)b: $(NAME)b.o lexer.o $(NAME)_iburg.o
	gcc -o $(NAME)b $(NAME)b.o $(NAME)_iburg.o lexer.o -lfl

$(NAME)b.o: $(NAME).c $(NAME).h
	gcc -c -DUSE_IBURG $(NAME).c -o $(NAME)b.o

$(NAME)_iburg.o: $(NAME)_iburg.c $(NAME).h
	gcc -c -DUSE_IBURG -DBURM $(NAME)_iburg.c

$(NAME)_iburg.c: $(NAME).bfe
	bfe < $(NAME).bfe | iburg > $(NAME)_iburg.c

clean:
	rm -f *.c *.o oxout.* *.output $(NAME) $(NAME)b *~ core

check: $(NAME) $(NAME)b
	cat TEST1 && $(NAME) < TEST1
	cat TEST2 && $(NAME) < TEST2
	cat TEST3 && $(NAME) < TEST3
	cat TEST1 && $(NAME)b < TEST1
	cat TEST2 && $(NAME)b < TEST2
	cat TEST3 && $(NAME)b < TEST3
