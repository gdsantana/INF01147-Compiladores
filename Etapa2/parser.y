
%token KW_CHAR      
%token KW_INT       
%token KW_REAL      
%token KW_BOOL      

%token KW_IF        
%token KW_THEN      
%token KW_ELSE      
%token KW_LOOP      
%token KW_INPUT     
%token KW_OUTPUT    
%token KW_RETURN    

%token OPERATOR_LE  
%token OPERATOR_GE  
%token OPERATOR_EQ  
%token OPERATOR_DIF 

%token TK_IDENTIFIER

%token LIT_INT      
%token LIT_REAL     
%token LIT_CHAR     
%token LIT_STRING   

%token TOKEN_ERROR        

%%

programa: 
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.\n Error %s \n ", getLineNumber(), s);
    exit(3);
}