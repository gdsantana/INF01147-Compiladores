etapa5: main.o lex.yy.o y.tab.o hash.o ast.o tacs.o
	gcc main.o lex.yy.o y.tab.o hash.o ast.o tacs.o -g -o etapa5

main.o: main.c 
	gcc -c -g main.c

ast.o: ast.c y.tab.o
	gcc -c -g  ast.c
	
hash.o: hash.c
	gcc -c -g  hash.c

tacs.o: tacs.c
	gcc -c -g tacs.c

y.tab.o: y.tab.c
	gcc -c -g  y.tab.c

lex.yy.o: lex.yy.c
	gcc -c -g  lex.yy.c

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l y.tab.c ast.c
	lex scanner.l

clean:
	rm lex.yy.c y.tab.c y.tab.h *.o etapa5