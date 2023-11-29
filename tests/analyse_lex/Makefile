prefixe=lexer
CFLAGS=-Wall -Wextra -g

test: lex.yy.o main.o
	gcc lex.yy.o main.o -lfl -o $(prefixe) $(CFLAGS)


main.o : main.c
	gcc -c main.c $(CFLAGS)

lex.yy.o: $(prefixe).lex
	flex $(prefixe).lex
	gcc -c lex.yy.c $(CFLAGS)

clean:
	rm -f *.o lex.yy.c a.out monresultat.txt $(prefixe)
