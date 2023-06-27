

etapa2: yacc lex
	gcc -o etapa2 lex.yy.c
yacc:
	yacc -d parser.y 
lex: scanner.l
	lex scanner.l

clean:
	rm lex.yy.c etapa2 y.tab.c y.tab.h