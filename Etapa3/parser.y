%{
    #include <stdio.h>
    #include "hash.h"
    #include "ast.h"
    
    void yyerror(const char *s);  
    int getLineNumber(void); 
    AST* getRootNode(void); 
    
    int yylex(void); 

    AST *rootNode;

%}

%union 
{
    HASH_NODE *symbol;
    AST *ast;
}


%token<symbol> KW_CHAR      
%token<symbol> KW_INT       
%token<symbol> KW_REAL      
%token<symbol> KW_BOOL      

%token KW_IF        
%token KW_THEN      
%token KW_ELSE      
%token KW_LOOP      
%token KW_INPUT     
%token KW_OUTPUT    
%token KW_RETURN    

// ADIOCIONAR DEMAIS OPERAÇÕES

%token<symbol> OPERATOR_LE  
%token<symbol> OPERATOR_GE  
%token<symbol> OPERATOR_EQ  
%token<symbol> OPERATOR_DIF 
%token<symbol> OPERATOR_ADD
%token<symbol> OPERATOR_SUB
%token<symbol> OPERATOR_MULT
%token<symbol> OPERATOR_DIV
%token<symbol> OPERATOR_BG
%token<symbol> OPERATOR_SM


%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INT      
%token<symbol> LIT_REAL     
%token<symbol> LIT_CHAR     
%token<symbol> LIT_STRING   

%token TOKEN_ERROR   
    
%left '&' '|'  OPERATOR_DIF OPERATOR_EQ OPERATOR_GE OPERATOR_LE OPERATOR_ADD OPERATOR_SUB OPERATOR_MULT OPERATOR_DIV OPERATOR_BG OPERATOR_SM
%right '~'

%type<ast> program
%type<ast> list
%type<ast> element
%type<ast> global_var
%type<ast> array
%type<ast> value
%type<ast> func
%type<ast> header
%type<ast> type
%type<ast> list_params
%type<ast> params
%type<ast> param
%type<ast> func_call
%type<ast> list_args
%type<ast> command
%type<ast> command_list
%type<ast> block
%type<ast> output
%type<ast> list_elements
%type<ast> el
// %type<ast> string  talvez remover
%type<ast> return
%type<ast> input
%type<ast> attr
%type<ast> flux_control
%type<ast> expression
%type<ast> array_element
%%
//#####################################
//    DECLARÇÃO GERAL DE UM PROGRAMA
//#####################################

program: list | ;
list: element list | ;
element: func | global_var ;

global_var: type TK_IDENTIFIER '=' expression ';' 
          | type TK_IDENTIFIER '[' LIT_INT ']' ';'
          | type TK_IDENTIFIER '[' LIT_INT ']' array ';' ;

// vericar a questão de separação por espaço os valores do array
array: value array | value ;
value: LIT_INT {{ }}
     | LIT_REAL 
     | LIT_CHAR 
     ;

//############## 
//    FUNÇÕES
//##############
func: header command;
//body: block;
header: type TK_IDENTIFIER '(' list_params ')' ;
type: KW_INT | KW_REAL | KW_CHAR | KW_BOOL ;
list_params: params | ;
params: param ',' params | param ; 
param: type TK_IDENTIFIER ;

// CHAMANDO AS FUNÇÕES
func_call: TK_IDENTIFIER '(' list_args ')' ;
list_args: expression | expression ',' list_args ;


//############## 
//    BLOCO
//##############

command: attr | flux_control | output | func_call  | block  | return | ';' | global_var ; 
block: '{' command_list '}' | '{' '}';
command_list: command  command_list
            | command ;

//########################
//    COMANDO OUTPUT
//########################
output: KW_OUTPUT list_elements ';' ;
list_elements: el ',' list_elements | el ;
el: expression | LIT_STRING ;
// string: LIT_STRING ;  talvez remover 

return: KW_RETURN expression ';'; 
input: KW_INPUT '(' type ')' ';';


attr: TK_IDENTIFIER '=' expression ';' 
    | array_element '=' expression ';'
    | TK_IDENTIFIER '=' input  
    | array_element '=' input
    ;  


flux_control: KW_IF '(' expression ')' command 
            | KW_IF '(' expression ')' command KW_ELSE command 
            | KW_IF '(' expression ')' KW_LOOP command ;

expression: value 
          | expression '+' expression 
          | expression '-' expression
          | expression '*' expression
          | expression '/' expression
          | expression '>' expression
          | expression '<' expression
          | expression OPERATOR_LE expression
          | expression OPERATOR_GE expression
          | expression OPERATOR_EQ expression
          | expression OPERATOR_DIF expression
          | expression '&' expression
          | expression '|' expression
          | '~' expression
          | '(' expression ')' 
          | TK_IDENTIFIER 
          | func_call 
          | array_element 
          | input 
          ;

array_element: TK_IDENTIFIER '[' expression ']' ;
          
%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.", getLineNumber());
    exit(3);
}