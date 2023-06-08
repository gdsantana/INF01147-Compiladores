
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
// DESCRIÇÃO GERAL DE UM PROGRAMA

programa: list | ;
list: list element | element ;
element: func | global_var ;

global_var: type TK_IDENTIFIER '=' expression ';' 
          | type TK_IDENTIFIER '[' LIT_INT ']' ';'
          | type TK_IDENTIFIER '[' LIT_INT ']' array ';' ;

// vericar a questão de separação por espaço os valores do array
array: value array | value ;
value: LIT_INT | LIT_REAL | LIT_CHAR ;

// DECLARAÇÃO DE FUNÇÕES DE UMA FUNÇÃO
func: header body;
header: type TK_IDENTIFIER '(' list_params ')' ;
type: KW_INT | KW_REAL | KW_CHAR | KW_BOOL ;
list_params: params | ;
params: param ',' params | param ; 
param: type TK_IDENTIFIER ;

body: block | ;

block: '{' command '}' ;
command: attr | flux_control | block | ;


attr: TK_IDENTIFIER '=' expression 
    | 


flux_control: KW_IF '(' expression ')' command 
            | KW_IF '(' expression ')' command KW_ELSE command 
            | KW_IF '(' expression ')' KW_LOOP command ;

expression: value | KW_INPUT 
          | expression '+' expression
          | expression '-' expression
          | expression '*' expression
          | expression '/' expression
          | expression '/' expression
          | expression '>' expression
          | expression '<' expression
          | expression OPERATOR_LE expression
          | expression OPERATOR_GE expression
          | expression OPERATOR_EQ expression
          | expression OPERATOR_DIF expression
          | '(' expression ')' ;
          
%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.\n Error %s \n ", getLineNumber(), s);
    exit(3);
}