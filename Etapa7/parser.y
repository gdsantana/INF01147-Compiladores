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
/* %token<symbol> SYMBOL_VARIABLE
%token<symbol> SYMBOL_ARRAY
%token<symbol> SYMBOL_FUNC
%token<symbol> SYMBOL_FUNC_ARGS
%token<symbol> SYMBOL_STRING */


%token<symbol> KW_CHAR      
%token<symbol> KW_INT       
%token<symbol> KW_REAL      
%token<symbol> KW_BOOL      

%token KW_IF        
%token KW_ELSE      
%token KW_LOOP      
%token KW_INPUT     
%token KW_OUTPUT    
%token KW_RETURN    


%token<symbol> OPERATOR_LE  
%token<symbol> OPERATOR_GE  
%token<symbol> OPERATOR_EQ  
%token<symbol> OPERATOR_DIF 
%token<symbol> OPERATOR_ADD
%token<symbol> OPERATOR_SUB
%token<symbol> OPERATOR_MULT
%token<symbol> OPERATOR_DIV
%token<symbol> OPERATOR_GT
%token<symbol> OPERATOR_LT


%token<symbol> TK_IDENTIFIER
%token<symbol> LIT_INT      
%token<symbol> LIT_REAL     
%token<symbol> LIT_CHAR     
%token<symbol> LIT_STRING   

%token TOKEN_ERROR   
    
%left '&' '|' OPERATOR_DIF OPERATOR_EQ OPERATOR_GE OPERATOR_LE OPERATOR_ADD OPERATOR_SUB OPERATOR_MULT OPERATOR_DIV OPERATOR_GT OPERATOR_LT
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
%type<ast> return
%type<ast> input
%type<ast> attr
%type<ast> flux_control
%type<ast> expression
%type<ast> array_element

%type<ast> semi_column
%type<ast> fun_args_comma
%type<ast> flux_expression
%%
//#####################################
//    DECLARÇÃO GERAL DE UM PROGRAMA
//#####################################

program: list { $$ = astCreate(AST_PROGRAM, 0, $1,0,0,0); rootNode = $$; }
        ;

list: element list {$$ = astCreate(AST_LIST,0,$1,$2,0,0);}
    | element  { $$ = astCreate(AST_LIST,0,$1,0,0,0); }
    ;
element: func       {$$ = astCreate(AST_ELEMENT,0,$1,0,0,0);}
       | global_var {$$ = astCreate(AST_ELEMENT,0,$1,0,0,0);}
       ;

global_var: type TK_IDENTIFIER '=' expression semi_column        {$$ = astCreate(AST_GLOBAL_VAR,$2,$1,$4,0,0);}
          | type TK_IDENTIFIER '[' LIT_INT ']' semi_column       {AST* lit_arr_size = astCreate(AST_SYMBOL, $4, 0,0,0,0); $$ = astCreate(AST_GLOBAL_VAR_ARRAY,$2,$1,lit_arr_size,0,0);}
          | type TK_IDENTIFIER '[' LIT_INT ']' array semi_column {AST* lit_arr_size = astCreate(AST_SYMBOL, $4, 0,0,0,0); $$ = astCreate(AST_GLOBAL_VAR_ARRAY,$2,$1,lit_arr_size,$6,0);}
          ;

// vericar a questão de separação por espaço os valores do array
array: value array {$$ = astCreate(AST_ARRAY, 0, $1,$2,0,0);}
     | value       {$$ = $1;}//{$$ = astCreate(AST_ARRAY, 0, $1,0,0,0);}
     ;

value: LIT_INT      {$$ = astCreate(AST_SYMBOL, $1, 0,0,0,0);}
     | LIT_REAL     {$$ = astCreate(AST_SYMBOL, $1, 0,0,0,0);}
     | LIT_CHAR     {$$ = astCreate(AST_SYMBOL, $1, 0,0,0,0);}
     ;

//############## 
//    FUNÇÕES
//##############
func: header command  {$$ = astCreate(AST_FUNC,0,$1,$2,0,0);}
    ;
//body: block;
header: type TK_IDENTIFIER '(' params ')'    {$$ = astCreate(AST_HEADER,$2,$1,$4,0,0);}
      | type TK_IDENTIFIER '(' ')'           {$$ = astCreate(AST_HEADER,$2,$1,0,0,0);}
      | type error '(' params ')'            { $$ = 0; syntaxError("Identifier not found for the type of function declaration.\n");}
      | type error '(' ')'                   { $$ = 0; syntaxError("Identifier not found for the type of function declaration.\n");}
      | error TK_IDENTIFIER '(' params ')'   { $$ = 0; syntaxError("Function type not found.\n");}
      | error TK_IDENTIFIER '(' ')'          { $$ = 0; syntaxError("Function type not found.\n");}
      ; 
type: KW_INT  {$$ = astCreate(AST_KW_INT,0,0,0,0,0);}
    | KW_REAL {$$ = astCreate(AST_KW_REAL,0,0,0,0,0);}
    | KW_CHAR {$$ = astCreate(AST_KW_CHAR,0,0,0,0,0);}
    | KW_BOOL {$$ = astCreate(AST_KW_BOOL,0,0,0,0,0);}
    ; 

params: param fun_args_comma params {$$ = astCreate(AST_PARAMS,0,$1,$3,0,0);}
      | param            {$$ = $1;}//{$$ = astCreate(AST_PARAM,0,$1,0,0,0);}
      ; 
param: type TK_IDENTIFIER  {$$ = astCreate(AST_PARAM,$2,$1,0,0,0);}
     ;

// CHAMANDO AS FUNÇÕES
func_call: TK_IDENTIFIER '(' list_args ')' {$$ = astCreate(AST_FUNC_CALL,$1,$3,0,0,0);}
         ;

list_args: expression                {$$ = $1;}
         | expression ',' list_args  {$$ = astCreate(AST_LIST_ARGS, 0,$1,$3,0,0);}
         ;


//############## 
//    BLOCO
//##############

command: attr           {$$ = $1;}
       | flux_control   {$$ = $1;}
       | output         {$$ = $1;}
       | func_call      {$$ = $1;}
       | block          {$$ = $1;}
       | return         {$$ = $1;}
       | semi_column            {$$ = 0;}
       | global_var     {$$ = $1;}
       ; 

block: '{' command_list '}' {$$ = astCreate(AST_BLOCK,0,$2,0,0,0);}
     | '{' '}'              {$$ = astCreate(AST_BLOCK,0,0,0,0,0);}
     ;
command_list: command  command_list  {$$ = astCreate(AST_COMMAND_LIST, 0, $1, $2, 0, 0);}
            | command                {$$ = $1;} //{$$ = astCreate(AST_COMMAND_LIST, 0, $1, 0, 0, 0);}
            ;

//########################
//    COMANDO OUTPUT
//########################
output: KW_OUTPUT list_elements semi_column  {$$ = astCreate(AST_OUTPUT, 0, $2, 0, 0, 0);}
      ;
list_elements: el ',' list_elements  {$$ = astCreate(AST_LIST_ELEMENTS, 0, $1, $3, 0, 0);}
             | el error list_elements  {$$ = astCreate(AST_LIST_ELEMENTS, 0, $1, $3, 0, 0);}
             | el                    { $$ = $1; }
             ;
el: expression                       { $$ = $1; }
  | LIT_STRING                       {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
  ;

return: KW_RETURN expression semi_column {$$ = astCreate(AST_RETURN,0,$2,0,0,0);} 
      | KW_RETURN error semi_column { $$ = 0; syntaxError("Return malformatted, expression or value expected \n");}
      ; 
input: KW_INPUT '(' type ')' semi_column {$$ = astCreate(AST_INPUT,0,$3,0,0,0);}
     | KW_INPUT '(' error ')' semi_column { $$ = 0; syntaxError("Input error, type expected.\n");}
     ;


attr: TK_IDENTIFIER '=' expression semi_column       {$$ = astCreate(AST_ATTR,$1,$3,0,0,0);}
    | TK_IDENTIFIER error expression semi_column     { $$ = 0; syntaxError("Attribuition error '=' expected.\n");}
    | array_element '=' expression semi_column       {$$ = astCreate(AST_ATTR_ARRAY,0,$1,$3,0,0);}
    | array_element error expression semi_column     { $$ = 0; syntaxError("Attribuition error '=' expected.\n");}
    | TK_IDENTIFIER '=' input                        {$$ = astCreate(AST_ATTR_INPUT,$1,$3,0,0,0);}
    | TK_IDENTIFIER error input                      { $$ = 0; syntaxError("Attribuition error '=' expected.\n");}
    | array_element '=' input                        {$$ = astCreate(AST_ATTR_ARRAY_INPUT,0,$1,$3,0,0);}
    | array_element error input                      { $$ = 0; syntaxError("Attribuition error '=' expected.\n");}
    ;  
array_element: TK_IDENTIFIER '[' expression ']'      {$$ = astCreate(AST_ARRAY_ELEMENT,$1,$3,0,0,0);}
             ;


flux_control: KW_IF '(' flux_expression ')' command                  {$$ = astCreate(AST_IF,0,$3,$5,0,0);}
            | KW_IF '(' flux_expression ')' command KW_ELSE command  {$$ = astCreate(AST_IF_ELSE,0,$3,$5,$7,0);}
            | KW_IF '(' flux_expression ')' KW_LOOP command          {$$ = astCreate(AST_LOOP,0,$3,$6,0,0);}
            ;

expression: expression OPERATOR_ADD expression               {$$ = astCreate(AST_ADD,0,$1,$3,0,0);}
          | expression OPERATOR_SUB expression               {$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
          | expression OPERATOR_MULT expression               {$$ = astCreate(AST_MULT,0,$1,$3,0,0);}
          | expression OPERATOR_DIV expression               {$$ = astCreate(AST_DIV,0,$1,$3,0,0);}
          | expression OPERATOR_GT expression               {$$ = astCreate(AST_GT,0,$1,$3,0,0);}
          | expression OPERATOR_LT expression               {$$ = astCreate(AST_LT,0,$1,$3,0,0);}
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
          | value                                   { $$ = $1;}
          ;

semi_column: ';'		{ $$ = 0; }
	| error		{ $$ = 0; syntaxError("Expecting ;\n");}
	;
fun_args_comma: ','		{ $$ = 0; }
	| error		{ $$ = 0; syntaxError("Function args malformatted, comma expected between arguments \n");}
	;
flux_expression: expression 	{ $$ = $1; }
	| error		{ $$ = 0; syntaxError("Flow control expects an expression \n");}
	| '(' error ')'		{ $$ = 0; syntaxError("Flow control expects an expression \n");}
	;

%%
AST* getRootNode() {
    /* astPrint(rootNode, 0); */
    return rootNode;
}

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.", getLineNumber());
    exit(3);
}
void syntaxError(const char *s) {
    fprintf(stderr, "syntax error at line %d: %s.\n", getLineNumber(), s);
    error_count += 1;

}