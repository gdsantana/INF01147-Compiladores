#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1

#define TAC_MOVE        10

#define TAC_DEC_GLOBAL        20
#define TAC_DEC_GLOBAL_INT    21
#define TAC_DEC_GLOBAL_CHAR   22
#define TAC_DEC_GLOBAL_REAL   23

#define TAC_DEC_GLOBAL_ARR        30
#define TAC_DEC_GLOBAL_ARR_VAL    31

#define TAC_ARR_GET_ELEMENT        40
#define TAC_ARR_SET_ELEMENT        41

#define TAC_ADD         201
#define TAC_SUB         202
#define TAC_MULT        203
#define TAC_DIV         204

#define TAC_LT     301
#define TAC_LTE    302
#define TAC_GT     303
#define TAC_GTE    304
#define TAC_EQ     305
#define TAC_DIF    306

#define TAC_PRINT           601
#define TAC_PRINT_CONCAT    602
#define TAC_READ            702

#define TAC_BEGINFUN         810
#define TAC_ENDFUN           820

#define TAC_DEC_FUNC_ARGS               1100
#define TAC_DEC_FUNC_ARGS_INT           1101
#define TAC_DEC_FUNC_ARGS_CHAR          1102
#define TAC_DEC_FUNC_ARGS_REAL          1103

#define TAC_FUN_CALL            1150
#define TAC_FUNC_CALL_ARGS      1151

#define TAC_JMP         1200
#define TAC_JMPZ        1201
#define TAC_LABEL       1210
#define TAC_GOTO        1220

#define TAC_RETURN        5000





typedef struct tac_node{
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;

    struct tac_node* prev;
    struct tac_node* next;
} TAC;

TAC* tacJoin(TAC* l1, TAC* l2);
TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac); // recebe o prev
TAC* tacGenerateCode(AST* node);




#endif
