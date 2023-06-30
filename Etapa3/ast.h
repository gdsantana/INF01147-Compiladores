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


#define AST_PROGRAM 
#define AST_LIST 
#define AST_ELEMENT 
#define AST_GLOBAL_VAR
#define AST_ARRAY
#define AST_VALUE
#define AST_FUNC
#define AST_HEADER
#define AST_TYPE
#define AST_LIST_PARAMS
#define AST_PARAMS
#define AST_PARAM
#define AST_FUNC_CALL
#define AST_LIST_ARGS
#define AST_COMMAND
#define AST_COMMAND_LIST
#define AST_BLOCK
#define AST_OUTPUT
#define AST_LIST_ELEMENTS
#define AST_EL
#define AST_RETURN
#define AST_INPUT
#define AST_ATTR
#define AST_ATTR_ARRAY
#define AST_ATTR_INPUT
#define AST_ATTR_ARRAY_INPUT
#define AST_FLUX_CONTROL
#define AST_EXPRESSION
#define AST_ARRAY_ELEMENT

#define AST_KW_INT
#define AST_KW_REAL
#define AST_KW_CHAR
#define AST_KW_BOOL

#define AST_ADD
#define AST_SUB
#define AST_MULT
#define AST_DIV
#define AST_BG
#define AST_SM
#define AST_LE
#define AST_GE
#define AST_EQ
#define AST_DIF
#define AST_AND
#define AST_OR
#define AST_NOT
#define AST_EXPRESSION_BLOCK
#define AST_SYMBOL


typedef struct astnode
{
    int type;    
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
} AST;


AST *astCreate(int type, HASH_NODE *symbol, AST* ST* s1, AST* s2, AST* s3);
void astPrint(AST *node, int level);
char* testtt();
char* astToCode(AST *node, int level);

#endif

// EOF
