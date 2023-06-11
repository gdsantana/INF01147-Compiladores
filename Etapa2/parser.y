
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
value: LIT_INT | LIT_REAL | LIT_CHAR ;

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

command: attr | flux_control | output | func_call  | block  | return | input | global_var ; 
block: '{' command_list '}' | '{' '}';
command_list: command  command_list
            | command ;

//########################
//    COMANDO OUTPUT
//########################
output: KW_OUTPUT list_elements ';' ;
list_elements: el ',' list_elements | el ;
el: expression | string ;
string: LIT_STRING ;// como definir uma string??

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
          | expression '~' expression
          | '(' expression ')' 
          | TK_IDENTIFIER 
          | func_call 
          | array_element 
          | input 
          ;

array_element: TK_IDENTIFIER '[' expression ']' ;
          
%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.\n Error %s \n ", getLineNumber(), s);
    exit(3);
}