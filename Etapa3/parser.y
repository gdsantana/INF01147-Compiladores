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

program: list { $$ = astCreate(AST_PROGRAM, 0, $1,0,0,0); rootNode = $$; }
        |     { $$ = 0; }
        ;

list: element list {$$ = astCreate(AST_LIST,0,$1,$2,0,0)}
    |              { $$ = 0; }
    ;
element: func       {$$ = astCreate(AST_ELEMENT,0,$1,0,0,0)}
       | global_var {$$ = astCreate(AST_ELEMENT,0,$1,0,0,0)}
       ;

global_var: type TK_IDENTIFIER '=' expression ';'        {$$ = astCreate(AST_GLOBAL_VAR,0,$1,0,0,0)}
          | type TK_IDENTIFIER '[' LIT_INT ']' ';'       {$$ = astCreate(AST_GLOBAL_VAR,$4,$1,0,0,0)}
          | type TK_IDENTIFIER '[' LIT_INT ']' array ';' {$$ = astCreate(AST_GLOBAL_VAR,$4,$1,0,0,0)}
          ;

// vericar a questão de separação por espaço os valores do array
array: value array {$$ = astCreate(AST_ARRAY, 0, $1,$2,0,0);}
     | value       {$$ = astCreate(AST_ARRAY, 0, $1,0,0,0);}
     ;    
value: LIT_INT      {$$ = astCreate(AST_VALUE, $1, 0,0,0,0);}
     | LIT_REAL     {$$ = astCreate(AST_VALUE, $1, 0,0,0,0);}
     | LIT_CHAR     {$$ = astCreate(AST_VALUE, $1, 0,0,0,0);}
     ;

//############## 
//    FUNÇÕES
//##############
func: header command;   {$$ = astCreate(AST_FUNC,0,$1,$2,0,0);}
//body: block;
header: type TK_IDENTIFIER '(' list_params ')' ; 
type: KW_INT  {$$ = astCreate(AST_KW_INT,0,0,0,0,0);}
    | KW_REAL {$$ = astCreate(AST_KW_REAL,0,0,0,0,0);}
    | KW_CHAR {$$ = astCreate(AST_KW_CHAR,0,0,0,0,0);}
    | KW_BOOL {$$ = astCreate(AST_KW_BOOL,0,0,0,0,0);}
    ; 
list_params: params {$$ = astCreate(AST_LIST_PARAMS,0,$1,0,0,0);}
           |        {$$ = 0;}
           ;
params: param ',' params {$$ = astCreate(AST_PARAMS,0,$1,$3,0,0);}
      | param            {$$ = astCreate(AST_PARAM,0,$1,0,0,0);}
      ; 
param: type TK_IDENTIFIER ; {$$ = astCreate(AST_PARAM,$2,$1,0,0,0);}

// CHAMANDO AS FUNÇÕES
func_call: TK_IDENTIFIER '(' list_args ')' ;
list_args: expression | expression ',' list_args ;


//############## 
//    BLOCO
//##############

command: attr           {$$ = $1;}
       | flux_control   {$$ = $1;}
       | output         {$$ = $1;}
       | func_call      {$$ = $1;}
       | block          {$$ = $1;}
       | return         {$$ = $1;}
       | ';'            {$$ = 0;}
       | global_var     {$$ = $1;}
       ; 
block: '{' command_list '}' 
     | '{' '}'
     ;
command_list: command  command_list
            | command ;

//########################
//    COMANDO OUTPUT
//########################
output: KW_OUTPUT list_elements ';' ;
list_elements: el ',' list_elements | el ;
el: expression | LIT_STRING ;
// string: LIT_STRING ;  talvez remover 

return: KW_RETURN expression ';' {$$ = astCreate(AST_RETURN,0,$2,0,0,0);}
      ; 
input: KW_INPUT '(' type ')' ';' {$$ = astCreate(AST_INPUT,0,$3,0,0,0);}
     ;


attr: TK_IDENTIFIER '=' expression ';'  {$$ = astCreate(AST_ATTR,$1,$3,0,0,0);}
    | array_element '=' expression ';'  {$$ = astCreate(AST_ATTR_ARRAY,0,$1,$3,0,0);}
    | TK_IDENTIFIER '=' input           {$$ = astCreate(AST_ATTR_INPUT,$1,$3,0,0,0);}
    | array_element '=' input           {$$ = astCreate(AST_ATTR_INPUT_ARRAY,$1,$3,0,0,0);}
    ;  


flux_control: KW_IF '(' expression ')' command                  {$$ = astCreate(AST_IF,0,$3,$4,0,0);}
            | KW_IF '(' expression ')' command KW_ELSE command  {$$ = astCreate(AST_IF,0,$3,$4,$6,0);}
            | KW_IF '(' expression ')' KW_LOOP command          {$$ = astCreate(AST_LOOP,0,$3,$5,0,0);}
            ;

expression:                                      
          | expression '+' expression               {$$ = astCreate(AST_ADD,0,$1,$3,0,0);}
          | expression '-' expression               {$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
          | expression '*' expression               {$$ = astCreate(AST_MULT,0,$1,$3,0,0);}
          | expression '/' expression               {$$ = astCreate(AST_DIV,0,$1,$3,0,0);}
          | expression '>' expression               {$$ = astCreate(AST_BG,0,$1,$3,0,0);}
          | expression '<' expression               {$$ = astCreate(AST_SM,0,$1,$3,0,0);}
          | expression OPERATOR_LE expression       {$$ = astCreate(AST_LE,0,$1,$3,0,0);}
          | expression OPERATOR_GE expression       {$$ = astCreate(AST_GE,0,$1,$3,0,0);}
          | expression OPERATOR_EQ expression       {$$ = astCreate(AST_EQ,0,$1,$3,0,0);}
          | expression OPERATOR_DIF expression      {$$ = astCreate(AST_DIF,0,$1,$3,0,0);}
          | expression '&' expression               {$$ = astCreate(AST_AND,0,$1,$3,0,0);}
          | expression '|' expression               {$$ = astCreate(AST_OR,0,$1,$3,0,0);}
          | '~' expression                          {$$ = astCreate(AST_NOT,0,$2,0,0,0);}
          | '(' expression ')'                      {$$ = astCreate(AST_EXPRESSION_BLOCK,0,$2,0,0,0);}
          | TK_IDENTIFIER                           {$$ = astCreate(AST_SYMBOL, $1, 0,0,0,0);}
          | func_call                               { $$ = $1;}
          | array_element                           { $$ = $1;}
          | input                                   { $$ = $1;}
          ;

array_element: TK_IDENTIFIER '[' expression ']' ;
          
%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.", getLineNumber());
    exit(3);
}