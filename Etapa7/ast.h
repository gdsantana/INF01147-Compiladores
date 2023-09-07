

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#ifndef AST_HEADER_FILE
#define AST_HEADER_FILE
#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_PROGRAM 2
#define AST_LIST 3
#define AST_ELEMENT 4
#define AST_GLOBAL_VAR 5
#define AST_GLOBAL_VAR_ARRAY 6
#define AST_ARRAY 7
#define AST_VALUE 8
#define AST_FUNC 9
#define AST_HEADER 10
#define AST_TYPE 11
#define AST_LIST_PARAMS 12
#define AST_PARAMS 13
#define AST_PARAM 14
#define AST_FUNC_CALL 15
#define AST_LIST_ARGS 16
#define AST_COMMAND 17
#define AST_COMMAND_LIST 18
#define AST_BLOCK 19
#define AST_OUTPUT 20
#define AST_LIST_ELEMENTS 21
#define AST_RETURN 23
#define AST_INPUT 24
#define AST_ATTR 25
#define AST_ATTR_ARRAY 26
#define AST_ATTR_INPUT 27
#define AST_ATTR_ARRAY_INPUT 28
#define AST_FLUX_CONTROL 29
#define AST_EXPRESSION 30
#define AST_ARRAY_ELEMENT 31

#define AST_KW_INT 33
#define AST_KW_REAL 34
#define AST_KW_CHAR 35
#define AST_KW_BOOL 36

#define AST_ADD 37
#define AST_SUB 38
#define AST_MULT 39
#define AST_DIV 40
#define AST_GT 41
#define AST_LT 42
#define AST_LE 43
#define AST_GE 44
#define AST_EQ 45
#define AST_DIF 46
#define AST_AND 47
#define AST_OR 48
#define AST_NOT 49
#define AST_EXPRESSION_BLOCK 50
#define AST_IF 51
#define AST_IF_ELSE 61
#define AST_LOOP 52

#define ASSIGN 53

#define DATATYPE_UNDEFINED       200
#define DATATYPE_INT             201
#define DATATYPE_CHAR            202
#define DATATYPE_REAL            203
#define DATATYPE_BOOL            204
#define DATATYPE_STRING          205

#define DATATYPE_ARRAY_INT       210
#define DATATYPE_ARRAY_CHAR      211
#define DATATYPE_ARRAY_REAL      212
#define DATATYPE_ARRAY_BOOL      213

// #define AST_PRINT                  203
//#define AST_PRINT_REST             2031
#define AST_OUTPUT_STRING           2032
#define AST_OUTPUT_EXP              2033
#define AST_OUTPUT_CHAR             2034

typedef struct astnode
{
    int type;    
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
} AST;


AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST* node, int level);
char* astTypeName(int type);
char* astToCode(AST *node, int level);
char *typeToString(int type);
#endif

// EOF
