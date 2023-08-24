
#ifndef ASM_HEADER
#define ASM_HEADER


#include "hash.h"
#include "ast.h"
#include "tacs.h"

void asm_TAC_BEGINFUN(FILE* fout, TAC* tac);
void asm_TAC_ENDFUN(FILE* fout, TAC* tac);
void asm_TAC_RETURN(FILE* fout, TAC* tac);

void asm_TAC_OUTPUT_STRING(FILE* fout, TAC* tac);
void asm_TAC_OUTPUT_INT(FILE* fout, TAC* tac);
void asm_TAC_OUTPUT_REAL(FILE* fout, TAC* tac);
void asm_TAC_OUTPUT_CHAR(FILE* fout, TAC* tac);
void asm_TAC_OUTPUT(FILE* fout, TAC* tac);

void asm_TAC_MOVE(FILE* fout, TAC* tac);

void asm_TAC_ADD(FILE* fout, TAC* tac);
void asm_TAC_SUB(FILE* fout, TAC* tac);
void asm_TAC_MULT(FILE* fout, TAC* tac);
void asm_TAC_DIV(FILE* fout, TAC* tac);

void asm_TAC_LABEL(FILE* fout, TAC* tac);

void asm_TAC_GT(FILE* fout, TAC* tac);
void asm_TAC_GE(FILE* fout, TAC* tac);
void asm_TAC_LT(FILE* fout, TAC* tac);
void asm_TAC_LE(FILE* fout, TAC* tac);
void asm_TAC_EQ(FILE* fout, TAC* tac);
void asm_TAC_DIF(FILE* fout, TAC* tac);

void asm_TAC_JMP(FILE* fout, TAC* tac);
void asm_TAC_JMPZ(FILE* fout, TAC* tac);
void asm_TAC_GOTO(FILE* fout, TAC* tac);

void asm_TAC_INPUT(FILE* fout, TAC* tac);

void asm_TAC_TAC_DEC_GLOBAL_ARR(FILE* fout, TAC* tac);
void asm_TAC_ARR_GET_ELEMENT(FILE* fout, TAC* tac);
void asm_TAC_ARR_SET_ELEMENT(FILE* fout, TAC* tac);

TAC* asm_TAC_FUN_CALL_ARGS(FILE* fout, TAC* tac);
void asm_TAC_FUN_CALL(FILE* fout, TAC* tac);

void generateAsm(TAC* first, char* outpath);



#endif