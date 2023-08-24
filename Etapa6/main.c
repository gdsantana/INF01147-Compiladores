#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "ast.h"
#include "tacs.h"
#include "asm.h"


extern FILE *yyin;

int yyparse(void);

int getLineNumber(void);

AST *getRootNode(void);

int main(int argc, char **argv)
{

  // se existe um arquivo lê ele
  // se não lê do console;
  hashInit();

  if (argc < 2)
  {
    fprintf(stderr, "missing file argument.");
    exit(1);
  }

  yyin = fopen(argv[1], "r");

  if (yyin == 0)
  {
    fprintf(stderr, "Cannot open file %s.\n", argv[1]);
    exit(2);
  }

  int i = yyparse();

  AST *rootNode = getRootNode();
  // char *code = astToCode(rootNode, 0);
  TAC *code = tacGenerateCode(rootNode);

  // astPrint(rootNode,0);

  tacPrintBackwards(tacGenerateCode(rootNode));
  TAC* reversedTac = tacReverseTAC(code);
  generateAsm(reversedTac, argv[1]);

  if (argc > 2) {  
    FILE *fp;

    char *code = astToCode(rootNode, 0);
    fp = fopen(argv[2], "w+");
    fputs(code, fp);


    fclose(fp);
    }

  printf("Numero de linhas: %d.\n", getLineNumber());
  printf("Compilation Success.\n");

  exit(0);
}