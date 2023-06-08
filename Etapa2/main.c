int main(int argc, char** argv) {
  
  // se existe um arquivo lê ele
  // se não lê do console;
  hashInit();
  
  if (argc < 2) { 
    fprintf(stderr, "missing file argument.");
    exit(1);
  }
  
  yyin = fopen(argv[1], "r");

  if (yyin == 0 ) {
    fprintf(stderr, "Cannot open file %s.\n", argv[1]);
    exit(2);
  }
  
  int i = yyparse();    
  hashPrint();
  printf("Numero de linhas: %d.\n", getLineNumber());    
  printf("Compilation Success.\n");    
  exit(0);
}