// AST

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

/* 
    TROCAR ESSES DEFINE PELO VALOR
    CORRETO DE ACORDO COM A DEFINIÇÃO

*/

#ifndef ASH_HEADER
#define ASH_HEADER

#define MAX_SONS 4


#define AST_SYMBOL      1
#define AST_PROGRAM     2

#define AST_READ        90
#define AST_ADD         101
#define AST_SUB         102
#define AST_MULT        103
#define AST_DIV         104
#define AST_EXPRESSION_BINARY         109

#define AST_LT          111
#define AST_LTE         112
#define AST_GT          113
#define AST_GTE         114

#define AST_EQ          121
#define AST_DIF         122



#define AST_COMMAND                200
#define AST_COMMAND_BLOCK          201
#define AST_FLUX_CONTROL           202
#define AST_PRINT                  203
#define AST_PRINT_REST             2031
#define AST_RETURN                 204
#define AST_ATTRIBUITION           205
#define AST_LABEL                  206
#define AST_EXPRESSION_BLOCK       207

#define AST_COMMAND_LIST    300

#define AST_FLUX_CONTROLL_IF               500
#define AST_FLUX_CONTROLL_WHILE            510
#define AST_FLUX_CONTROLL_GOTO             520

#define AST_DECLARATION               700
#define AST_DECLARATION_LIST          710

#define AST_DECLARATION_FUNCTION                    1000
#define AST_DECLARATION_FUNCTION_INT                1001
#define AST_DECLARATION_FUNCTION_CHAR               1002
#define AST_DECLARATION_FUNCTION_FLOAT              1003

#define AST_DECLARATION_FUNCTION_ARGS               1100
#define AST_DECLARATION_FUNCTION_ARGS_INT           1101
#define AST_DECLARATION_FUNCTION_ARGS_CHAR          1102
#define AST_DECLARATION_FUNCTION_ARGS_FLOAT         1103
#define AST_DECLARATION_FUNCTION_ARGS_OR_EMPTY      1200
#define AST_DECLARATION_FUNCTION_BODY               1300

#define AST_FUNCTION_CALL                   1400
#define AST_FUNCTION_CALL_ARGS              1450


#define AST_DECLARATION_GLOBAL_INT               2010
#define AST_DECLARATION_GLOBAL_ARRAY_INT         2015

#define AST_DECLARATION_GLOBAL_CHAR              2020
#define AST_DECLARATION_GLOBAL_ARRAY_CHAR        2025

#define AST_DECLARATION_GLOBAL_FLOAT             2030
#define AST_DECLARATION_GLOBAL_ARRAY_FLOAT       2035

#define AST_ARRAY_VAL                  2500
#define AST_ARRAY_ELEMENT              2501
#define AST_ARRAY_ATTRIBUITION         2502



typedef struct astnode
{
    int type;    
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
} AST;


AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST *node, int level);
char* testtt();
char* astToCode(AST *node, int level);

#endif

// EOF
