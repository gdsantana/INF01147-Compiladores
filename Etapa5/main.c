#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "ast.h"
#include "semantic.h"

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
  char *code = astToCode(rootNode, 0);

  // astPrint(rootNode,0);
  // int semanticErrors = check_all_semantics(rootNode);
  // if (semanticErrors > 0)
  // {
  //   printf("\n\nCompilation Fail! Semantic errors count %d\n", semanticErrors);
  //   exit(4);
  // }

  if (argc > 2)
  { // write output
    FILE *fp;

    fp = fopen(argv[2], "w+");
    fputs(code, fp);
    fclose(fp);
  }

  printf("Numero de linhas: %d.\n", getLineNumber());
  printf("Compilation Success.\n");

  exit(0);
}