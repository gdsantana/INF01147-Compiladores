etapa4: lex.yy.o main.o hash.o ast.o y.tab semantic.o
	gcc -o etapa4 -g y.tab.c lex.yy.o main.o hash.o ast.o semantic.o

main.o: main.c
	gcc -c -g main.c

semantic.o: semantic.c ast.o
	gcc -c -g  semantic.c

ast.o: ast.c
	gcc -c -g ast.c

hash.o: hash.c
	gcc -c -g hash.c

lex.yy.o: lex.yy.c
	gcc -c -g lex.yy.c

lex.yy.c: scanner.l y.tab
	flex --header-file=lex.yy.h scanner.l

y.tab: parser.y
	yacc -d parser.y

clean:
	rm lex.yy.* y.tab.* *.o etapa4 output.txt
