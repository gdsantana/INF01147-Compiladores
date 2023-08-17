#include "asm.h"

void asm_TAC_BEGINFUN(FILE* fout, TAC* tac);
void asm_TAC_ENDFUN(FILE* fout, TAC* tac);
void asm_TAC_RETURN(FILE* fout, TAC* tac);

void asm_TAC_PRINT_STRING(FILE* fout, TAC* tac);
void asm_TAC_PRINT_INT(FILE* fout, TAC* tac);
void asm_TAC_PRINT_FLOAT(FILE* fout, TAC* tac);
void asm_TAC_PRINT_CHAR(FILE* fout, TAC* tac);
void asm_TAC_PRINT(FILE* fout, TAC* tac);

void asm_TAC_MOVE(FILE* fout, TAC* tac);

void asm_TAC_ADD(FILE* fout, TAC* tac);
void asm_TAC_SUB(FILE* fout, TAC* tac);
void asm_TAC_MULT(FILE* fout, TAC* tac);
void asm_TAC_DIV(FILE* fout, TAC* tac);

void asm_TAC_LABEL(FILE* fout, TAC* tac);

void asm_TAC_GT(FILE* fout, TAC* tac);
void asm_TAC_GTE(FILE* fout, TAC* tac);
void asm_TAC_LT(FILE* fout, TAC* tac);
void asm_TAC_LTE(FILE* fout, TAC* tac);
void asm_TAC_EQ(FILE* fout, TAC* tac);
void asm_TAC_DIF(FILE* fout, TAC* tac);

void asm_TAC_JMP(FILE* fout, TAC* tac);
void asm_TAC_JMPZ(FILE* fout, TAC* tac);
void asm_TAC_GOTO(FILE* fout, TAC* tac);

void asm_TAC_READ(FILE* fout, TAC* tac);

void asm_TAC_TAC_DEC_GLOBAL_ARR(FILE* fout, TAC* tac);
void asm_TAC_ARR_GET_ELEMENT(FILE* fout, TAC* tac);
void asm_TAC_ARR_SET_ELEMENT(FILE* fout, TAC* tac);

TAC* asm_TAC_FUN_CALL_ARGS(FILE* fout, TAC* tac);
void asm_TAC_FUN_CALL(FILE* fout, TAC* tac);


int BL = 0;
int CMP_LBL_TEMP = 0;


void generateAsm(TAC* first, char* outpath) {

    FILE *fout;

    char* out_path = str_replace(outpath, ".txt", ".s");

    fout = fopen(out_path, "w");

    // globals
    hashPrintAsm(fout);

    // init

    fprintf(fout, "\n # PRINT"
                  "\nprint_string_int:\n"
                  "\t.string\t\"%%d\"\n"

                  "\nprint_string_float:\n"
                  "\t.string\t\"%%d/%%d\"\n"

                  "\nprint_string_char:\n"
                  "\t.string\t\"%%c\"\n"

                  "print_string:\n"
                  "\t.string\t\"%%s\"\n\n");

    fprintf(fout, "\n #READ"
                  "\nread:\n"
                  "\t.string\t\"%%d\""
                  "\n\n");



    // GENERATE ARRAY DEC
    asm_TAC_TAC_DEC_GLOBAL_ARR(fout, first);


    // GENERATE
    TAC* tac;

    for (tac=first; tac; tac=tac->next) {
        switch (tac->type) {
            case TAC_BEGINFUN: asm_TAC_BEGINFUN(fout, tac); break;
            case TAC_ENDFUN: asm_TAC_ENDFUN(fout, tac); break;
            case TAC_RETURN: asm_TAC_RETURN(fout, tac); break;

            case TAC_PRINT_STRING: asm_TAC_PRINT_STRING(fout, tac); break;
            case TAC_PRINT_INT: asm_TAC_PRINT_INT(fout, tac); break;
            case TAC_PRINT_FLOAT: asm_TAC_PRINT_FLOAT(fout, tac); break;
            case TAC_PRINT_CHAR: asm_TAC_PRINT_CHAR(fout, tac); break;
            case TAC_PRINT: asm_TAC_PRINT(fout, tac); break;

            case TAC_MOVE: asm_TAC_MOVE(fout, tac); break;

            case TAC_ADD: asm_TAC_ADD(fout, tac); break;
            case TAC_SUB: asm_TAC_SUB(fout, tac); break;
            case TAC_MULT: asm_TAC_MULT(fout, tac); break;
            case TAC_DIV: asm_TAC_DIV(fout, tac); break;

            case TAC_LABEL: asm_TAC_LABEL(fout, tac); break;

            case TAC_GT: asm_TAC_GT(fout, tac); break;
            case TAC_GTE: asm_TAC_GTE(fout, tac); break;
            case TAC_LT: asm_TAC_LT(fout, tac); break;
            case TAC_LTE: asm_TAC_LTE(fout, tac); break;
            case TAC_EQ: asm_TAC_EQ(fout, tac); break;
            case TAC_DIF: asm_TAC_DIF(fout, tac); break;

            case TAC_JMP: asm_TAC_JMP(fout, tac); break;
            case TAC_JMPZ: asm_TAC_JMPZ(fout, tac); break;

            case TAC_GOTO: asm_TAC_GOTO(fout, tac); break;

            case TAC_READ: asm_TAC_READ(fout, tac); break;

            case TAC_ARR_GET_ELEMENT: asm_TAC_ARR_GET_ELEMENT(fout, tac); break;
            case TAC_ARR_SET_ELEMENT: asm_TAC_ARR_SET_ELEMENT(fout, tac); break;

            case TAC_FUNC_CALL_ARGS: tac = asm_TAC_FUN_CALL_ARGS(fout, tac); break;
            case TAC_FUN_CALL: asm_TAC_FUN_CALL(fout, tac); break;


            default:
                break;

        }
    }

    // hash table
}


void asm_TAC_BEGINFUN(FILE* fout, TAC* tac) {

//    TAC_DEC_FUNC_ARGS

    fprintf(fout, "\n\n# TAC_BEGINFUN\n"
                  "\t.text\n"
                  "\t.globl\t%s\n"
                  "%s:\n"
                  "\tpushq\t%%rbp\n"
                  "\tmovq\t%%rsp, %%rbp\n", tac->res->text, tac->res->text);

    TAC* tac_rest = 0;
    tac_rest = tac->prev;

    if(tac_rest->type == TAC_DEC_FUNC_ARGS) {

        int args_count = 0;
        fprintf(fout, "\n\t# TAC_DEC_FUNC_ARGS\n"
                      "    movl\t$0, %%edx\n");


        while (tac_rest->type == TAC_DEC_FUNC_ARGS || tac_rest->type == TAC_DEC_FUNC_ARGS_FLOAT) {
            int pos = 16 + (8 * args_count);
            if(tac_rest->type == TAC_DEC_FUNC_ARGS_FLOAT) {
                fprintf(fout, "\n\tmovl\t%d(%%rbp), %%eax"
                              "\n\tmovl\t%d(%%rbp), %%edx"
                              "\n\tmovl\t%%eax, _%s(%%rip)"
                              "\n\tmovl\t%%edx, 4+_%s(%%rip)", pos, pos+8, tac_rest->res->text, tac_rest->res->text);
//                fprintf(fout, "\n\tmovl\t%d(%%rbp), %%eax"
//                              "\n\tmovl\t%d(%%rbp), %%edx"
//                              "\n\tmovl\t%%eax, %d+_%s(%%rip)"
//                              "\n\tmovl\t%%edx, _%s(%%rip)", pos+4, pos, 4, tac_rest->res->text, tac_rest->res->text);

                args_count += 1;
            } else {
                fprintf(fout, "\n\tmovl\t%d(%%rbp), %%eax\n"
                              "\tmovl\t%%eax, _%s(%%rip)", pos, tac_rest->res->text);
            }
            args_count += 1;
            tac_rest = tac_rest->prev;
        }
    }

}
void asm_TAC_RETURN(FILE* fout, TAC* tac){

    if(tac->next->type == TAC_ENDFUN) {
        return;
    }

    fprintf(fout, "\n## TAC_ENDFUN\n"
                  "\tmovl\t_%s(%%rip), %%eax #return\n"
                  "\tpopq\t%%rbp\n"
                  "\tret\n\n", tac->prev->res->text);
}

void asm_TAC_ENDFUN(FILE* fout, TAC* tac){
    if(tac->prev->type == TAC_RETURN)
        fprintf(fout, "\n## TAC_ENDFUN\n"
                  "\tmovl\t_%s(%%rip), %%eax #return\n"
                  "\tpopq\t%%rbp\n"
                  "\tret\n\n", tac->prev->res->text);
    else
        fprintf(fout, "\n\n## TAC_ENDFUN\n"
                      "\tpopq\t%%rbp\n"
                      "\tret\n\n");
}


TAC* asm_TAC_FUN_CALL_ARGS(FILE* fout, TAC* tac) {
//    movl	f10(%rip), %r10d
//    pushq	%r10
    TAC* tac_temp = 0;
    tac_temp = tac;
    int args_count = 0;

    fprintf(fout, "\n\n# TAC_TAC_FUN_CALL_ARGS\n");
    while(tac_temp->type == TAC_FUNC_CALL_ARGS) {
//        if(0) {
        if(tac_temp->op1->datatype == DATATYPE_FLOAT) {
            fprintf(fout, "\n"
                          "\tmovl\t4+_%s(%%rip), %%r10d\n"
                          "\tpushq\t%%r10\n"
                          "\tmovl\t_%s(%%rip), %%r10d\n"
                          "\tpushq\t%%r10\n", tac_temp->op1->text, tac_temp->op1->text);
            args_count+=1;
        } else {
            fprintf(fout, "\n"
                          "\tmovl\t_%s(%%rip), %%r10d\n"
                          "\tpushq\t%%r10\n", tac_temp->op1->text);
        }

        args_count+=1;
        tac_temp =  tac_temp->next;
    }

    if(tac_temp->type == TAC_FUN_CALL) {
        fprintf(fout, "\n\t# TAC_TAC_FUN_CALL\n"
                      "\tcall\t%s\n"
                      "\taddq\t$%d, %%rsp\n"
                      "\tmovl\t%%eax, _%s(%%rip) #move return to tempvar\n",
                      tac_temp->op1->text, args_count * 8, tac_temp->res->text);
    }

    return tac_temp; // return tac_temp to not duplicate the call for each args

}
void asm_TAC_FUN_CALL(FILE* fout, TAC* tac) {

    /*
    subq	$16, %rsp
    movl	%edx, -4(%rbp)
    movl	%eax, -8(%rbp)
    */

//    fprintf(fout, "\n\n# TAC_TAC_FUN_CALL\n"
//                  "\tcall\t%s", tac->op1->text);
}



void asm_TAC_PRINT_STRING(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_PRINT_STRING \n"
                  "    leaq\t_%s(%%rip), %%rdi\n"
                  "    movl\t$0, %%eax\n"
                  "    call\tprintf@PLT\n"
                  "    movl\t$0, %%eax\n\n", tac->res->text);
}
void asm_TAC_PRINT_INT(FILE* fout, TAC* tac){
    fprintf(fout, "\n# TAC_PRINT_INT \n"
                  "    movl\t_%s(%%rip), %%esi   # mov a to reg\n"
                  "    #movl\t%%eax, %%esi\n"
                  "    leaq\tprint_string_int(%%rip), %%rdi\n"
                  "\tcall\tprintf@PLT\n\n", tac->res->text);
}
void asm_TAC_PRINT_FLOAT(FILE* fout, TAC* tac){
    fprintf(fout, "\n# TAC_PRINT_FLOAT \n"
                  "    movl\t4+_%s(%%rip), %%edx   # mov a to reg\n"
                  "    movl\t_%s(%%rip), %%eax   # mov a to reg\n"
                  "    movl\t%%eax, %%esi\n"
                  "    leaq\tprint_string_float(%%rip), %%rdi\n"
                  "\tcall\tprintf@PLT\n\n", tac->res->text, tac->res->text);
}
void asm_TAC_PRINT_CHAR(FILE* fout, TAC* tac){
    fprintf(fout, "\n# TAC_PRINT_CHAR \n"
                  "    movzbl\t_%s(%%rip), %%eax   # mov a to reg\n"
                  "    movsbl\t%%al, %%eax\n"
                  "    movl\t%%eax, %%esi\n"
                  "    leaq\tprint_string_char(%%rip), %%rdi\n"
                  "\tcall\tprintf@PLT\n\n", tac->res->text);
}
void asm_TAC_PRINT(FILE* fout, TAC* tac){
    // ignore, all in tac_print_string and tac_print_int
}

void asm_TAC_MOVE(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_MOVE //ASSIGN \n"
                  "    movl\t_%s(%%rip), %%eax\n"
                  "    movl\t%%eax, _%s(%%rip)\n"
                  "    movl\t$0, %%eax\n"  // limpa reg
                  "\n\n", tac->op1->text, tac->res->text);
}


void asm_TAC_ADD(FILE* fout, TAC* tac){

    /*
        movl	a(%rip), %edx
        movl	b(%rip), %eax
        addl	%edx, %eax
        movl	%eax, a(%rip)
        movl	$0, %eax // limpa reg
     */

    fprintf(fout, "\n\n# TAC_ADD \n"
                  "    movl\t_%s(%%rip), %%edx\n"
                  "    movl\t_%s(%%rip), %%eax\n"
                  "    addl\t%%edx, %%eax\n"
                  "    movl\t%%eax, _%s(%%rip)\n"
                  "    movl\t$0, %%eax\n"  // limpa reg
                  "\n\n", tac->op1->text, tac->op2->text, tac->res->text);
}

void asm_TAC_SUB(FILE* fout, TAC* tac){

    /*
        movl	a(%rip), %edx
        movl	b(%rip), %eax
        subl	%eax, %edx
        movl	%edx, %eax
        movl	%eax, a(%rip)
        movl	$0, %eax // limpa reg

     */

    fprintf(fout, "\n\n# TAC_SUB \n"
                  "    movl\t_%s(%%rip), %%edx\n"
                  "    movl\t_%s(%%rip), %%eax\n"
                  "    subl\t%%eax, %%edx\n"
                  "    movl\t%%edx, %%eax\n"
                  "    movl\t%%eax, _%s(%%rip)\n"
                  "    movl\t$0, %%eax\n"  // limpa reg
                  "\n\n", tac->op1->text, tac->op2->text, tac->res->text);
}

void asm_TAC_MULT(FILE* fout, TAC* tac){

    /*
        movl	a(%rip), %edx
        movl	b(%rip), %eax
        imull	%edx, %eax
        movl	%eax, a(%rip)
        movl	$0, %eax
     */
    fprintf(fout, "\n\n# TAC_MULT \n"
                  "    movl\t_%s(%%rip), %%edx\n"
                  "    movl\t_%s(%%rip), %%eax\n"
                  "    imull\t%%edx, %%eax\n"
                  "    movl\t%%eax, _%s(%%rip)\n"
                  "    movl\t$0, %%eax\n"  // limpa reg
                  "\n\n", tac->op1->text, tac->op2->text, tac->res->text);
}

void asm_TAC_DIV(FILE* fout, TAC* tac){
/*
    movl	a(%rip), %eax
    movl	b(%rip), %ecx
            cltd
    idivl	%ecx
    movl	%eax, a(%rip)
    movl	$0, %eax
*/
    fprintf(fout, "\n\n# TAC_DIV\n"
                  "    movl\t_%s(%%rip), %%eax\n"
                  "    movl\t_%s(%%rip), %%ecx\n"
                  "            cltd\n"
                  "    idivl\t%%ecx\n"
                  "    movl\t%%eax, _%s(%%rip)\n"
                  "    movl\t$0, %%eax\n\n"  // limpa reg
                  "\n\n", tac->op1->text, tac->op2->text, tac->res->text);
}


void asm_TAC_LABEL(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_LABEL\n"
                  "    _%s:\t# %s"
                  "\n\n", tac->res->text, tac->res->datastring?tac->res->datastring:"AUTO");
}

void asm_TAC_GT(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_GT \n"
                  "\tmovl\t_%s(%%rip), %%edx\n"
                  "\tmovl\t_%s(%%rip), %%eax\n"
                  "\tcmpl\t%%eax, %%edx \n", tac->op1->text, tac->op2->text);

    fprintf(fout,
            "\tjg\tCMP_LBL_TEMP_%d \t\t# se condição verdadeira pula para setar 1\n "
            "\tmovl\t$0, _%s(%%rip) \t\t# Se falsa seta 0 \n"
            "\tjmp\tCMP_LBL_TEMP_%d \t\t# e pula para o final do bloco\n"
            , CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    fprintf(fout, "\nCMP_LBL_TEMP_%d: \t\t #se condição verdadeira seta 1\n"
                  "\tmovl\t$1, _%s(%%rip)\n"
                  "\nCMP_LBL_TEMP_%d:\t#final do bloco"
                  "\n\n", CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    CMP_LBL_TEMP += 2;
}
void asm_TAC_GTE(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_GTE \n"
                  "\tmovl\t_%s(%%rip), %%edx\n"
                  "\tmovl\t_%s(%%rip), %%eax\n"
                  "\tcmpl\t%%eax, %%edx \n", tac->op1->text, tac->op2->text);

    fprintf(fout,
            "\tjge\tCMP_LBL_TEMP_%d \t\t# se condição verdadeira pula para setar 1\n "
            "\tmovl\t$0, _%s(%%rip) \t\t# Se falsa seta 0 \n"
            "\tjmp\tCMP_LBL_TEMP_%d \t\t# e pula para o final do bloco\n"
            , CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    fprintf(fout, "\nCMP_LBL_TEMP_%d: \t\t #se condição verdadeira seta 1\n"
                  "\tmovl\t$1, _%s(%%rip)\n"
                  "\nCMP_LBL_TEMP_%d:\t#final do bloco"
                  "\n\n", CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    CMP_LBL_TEMP += 2;
}
void asm_TAC_LT(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_LT \n"
                  "\tmovl\t_%s(%%rip), %%edx\n"
                  "\tmovl\t_%s(%%rip), %%eax\n"
                  "\tcmpl\t%%eax, %%edx \n", tac->op1->text, tac->op2->text);

    fprintf(fout,
            "\tjl\tCMP_LBL_TEMP_%d \t\t# se condição verdadeira pula para setar 1\n "
            "\tmovl\t$0, _%s(%%rip) \t\t# Se falsa seta 0 \n"
            "\tjmp\tCMP_LBL_TEMP_%d \t\t# e pula para o final do bloco\n"
            , CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    fprintf(fout, "\nCMP_LBL_TEMP_%d: \t\t #se condição verdadeira seta 1\n"
                  "\tmovl\t$1, _%s(%%rip)\n"
                  "\nCMP_LBL_TEMP_%d:\t#final do bloco"
                  "\n\n", CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    CMP_LBL_TEMP += 2;
}
void asm_TAC_LTE(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_LTE \n"
                  "\tmovl\t_%s(%%rip), %%edx\n"
                  "\tmovl\t_%s(%%rip), %%eax\n"
                  "\tcmpl\t%%eax, %%edx \n", tac->op1->text, tac->op2->text);

    fprintf(fout,
            "\tjle\tCMP_LBL_TEMP_%d \t\t# se condição verdadeira pula para setar 1\n "
            "\tmovl\t$0, _%s(%%rip) \t\t# Se falsa seta 0 \n"
            "\tjmp\tCMP_LBL_TEMP_%d \t\t# e pula para o final do bloco\n"
            , CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    fprintf(fout, "\nCMP_LBL_TEMP_%d: \t\t #se condição verdadeira seta 1\n"
                  "\tmovl\t$1, _%s(%%rip)\n"
                  "\nCMP_LBL_TEMP_%d:\t#final do bloco"
                  "\n\n", CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    CMP_LBL_TEMP += 2;
}
void asm_TAC_EQ(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_EQ \n"
                  "\tmovl\t_%s(%%rip), %%edx\n"
                  "\tmovl\t_%s(%%rip), %%eax\n"
                  "\tcmpl\t%%eax, %%edx \n", tac->op1->text, tac->op2->text);

    fprintf(fout,
            "\tje\tCMP_LBL_TEMP_%d \t\t# se condição verdadeira pula para setar 1\n "
            "\tmovl\t$0, _%s(%%rip) \t\t# Se falsa seta 0 \n"
            "\tjmp\tCMP_LBL_TEMP_%d \t\t# e pula para o final do bloco\n"
            , CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    fprintf(fout, "\nCMP_LBL_TEMP_%d: \t\t #se condição verdadeira seta 1\n"
                  "\tmovl\t$1, _%s(%%rip)\n"
                  "\nCMP_LBL_TEMP_%d:\t#final do bloco"
                  "\n\n", CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    CMP_LBL_TEMP += 2;
}
void asm_TAC_DIF(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_DIF \n"
                  "\tmovl\t_%s(%%rip), %%edx\n"
                  "\tmovl\t_%s(%%rip), %%eax\n"
                  "\tcmpl\t%%eax, %%edx \n", tac->op1->text, tac->op2->text);

    fprintf(fout,
            "\tjne\tCMP_LBL_TEMP_%d \t\t# se condição verdadeira pula para setar 1\n "
            "\tmovl\t$0, _%s(%%rip) \t\t# Se falsa seta 0 \n"
            "\tjmp\tCMP_LBL_TEMP_%d \t\t# e pula para o final do bloco\n"
            , CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    fprintf(fout, "\nCMP_LBL_TEMP_%d: \t\t #se condição verdadeira seta 1\n"
                  "\tmovl\t$1, _%s(%%rip)\n"
                  "\nCMP_LBL_TEMP_%d:\t#final do bloco"
                  "\n\n", CMP_LBL_TEMP, tac->res->text, CMP_LBL_TEMP+1);

    CMP_LBL_TEMP += 2;
}


void asm_TAC_JMP(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_JMP\n"
                  "\tjmp\t_%s"
                  "\n\n", tac->res->text);

}

void asm_TAC_JMPZ(FILE* fout, TAC* tac){
    // compara o temp
    fprintf(fout, "\n\n# TAC_JMPZ\n"
                  "\tmovl\t_%s(%%rip), %%edx\n"
                  "\tmovl\t$0, %%eax\n"
                  "\tcmpl\t%%eax, %%edx \t# Se condicional anterior for 0 pula o trecho a baixo\n"
                  "    jz _%s\n", tac->op1->text, tac->res->text);

}

void asm_TAC_GOTO(FILE* fout, TAC* tac){
    fprintf(fout, "\n\n# TAC_GOTO\n"
                  "\tjmp\t_%s \t# alias for label [%s]"
                  "\n\n", tac->res->text, tac->res->datastring);

}

void asm_TAC_READ(FILE* fout, TAC* tac){
    // compara o temp
    fprintf(fout, "\n\n# TAC_READ\n"
                  "\tleaq\t_%s(%%rip), %%rsi\n"
                  "\tleaq\tread(%%rip), %%rdi\n"
                  "\tmovl\t$0, %%eax\n"
                  "\tcall\t__isoc99_scanf@PLT", tac->res->text);
}


void asm_TAC_ARR_GET_ELEMENT(FILE* fout, TAC* tac) {


//    movl	%s(%%rip), %eax
//    cltq
//    leaq	0(,%%rax,4), %rdx
//    leaq	d(%rip), %rax
//    movl	(%rdx,%rax), %eax
//    movl	%eax, b(%rip)


    if(tac->op2->type == SYMBOL_TEMP || tac->op2->type == SYMBOL_VARIABLE) {
        fprintf(fout, "\n\n# TAC_ARRAY GET_ELEMENT EXP\n"
                      "    movl\t_%s(%%rip), %%eax\n"
                      "    cltq\n"
                      "    leaq\t0(,%%rax,4), %%rdx\n"
                      "    leaq\t_%s(%%rip), %%rax\n"
                      "    movl\t(%%rdx,%%rax), %%eax\n"
                      "    movl\t%%eax, _%s(%%rip)",
                tac->op2->text, tac->op1->text, tac->res->text);
    } else {
        int index = tac->op2->datavalue * 4;

        fprintf(fout, "\n\n# TAC_ARRAY GET_ELEMENT\n"
                      "    movl\t%d+_%s(%%rip), %%eax\n"
                      "    movl\t%%eax, _%s(%%rip)\n"
                      "    movl\t$0, %%eax\n"  // limpa reg
                      "\n", index, tac->op1->text, tac->res->text);
    }


}

void asm_TAC_ARR_SET_ELEMENT(FILE* fout, TAC* tac){

//    movl	b(%rip), %edx   #endereço
//    movl	c(%rip), %eax   #valor
//    movslq	%edx, %rdx
//    leaq	0(,%rdx,4), %rcx
//    leaq	d(%rip), %rdx   #array
//    movl	%eax, (%rcx,%rdx)

    if(tac->op1->type == SYMBOL_TEMP || tac->op1->type == SYMBOL_VARIABLE) {
        fprintf(fout, "\n\n# TAC_ARRAY SET_ELEMENT EXP\n"
                      "\tmovl\t_%s(%%rip), %%edx   #endereço\n"
                      "\tmovl\t_%s(%%rip), %%eax   #valor\n"
                      "\tmovslq\t%%edx, %%rdx\n"
                      "\tleaq\t0(,%%rdx,4), %%rcx\n"
                      "\tleaq\t_%s(%%rip), %%rdx   #array\n"
                      "\tmovl\t%%eax, (%%rcx,%%rdx)",
                tac->op1->text, tac->op2->text, tac->res->text);

    } else {

        int index = tac->op1->datavalue * 4;

        fprintf(fout, "\n\n# TAC_ARRAY SET_ELEMENT\n"
                      "    movl\t_%s(%%rip), %%eax\n"
                      "    movl\t%%eax, %d+_%s(%%rip)\n"
                      "    movl\t$0, %%eax\n"  // limpa reg
                      "\n", tac->op2->text, index, tac->res->text);
    }

}


void asm_TAC_TAC_DEC_GLOBAL_ARR(FILE* fout, TAC* first){

    TAC* temp = 0;
    TAC* tac = 0;

    int count = 0;

    for (tac=first; tac; tac=tac->next) {
        switch (tac->type) {
            case TAC_DEC_GLOBAL_ARR: {
                temp = tac;

                fprintf(fout, "\n\n# TAC_ARRAY\n"
                              "_%s:", tac->res->text);
                if(tac->op1) {
                    while (tac->res->text == temp->res->text) {
                        fprintf(fout, "\n\t .long %s \t# %s[%d]", tac->op1->text, temp->res->text, count);
                        tac = tac->next;
                        count++;
                    }
                } else {
                    while (count < tac->op2->datavalue) {
                        fprintf(fout, "\n\t .long 0 \t# %s[%d]", temp->res->text, count);
                        count++;
                    }
                }
                break;
            }
        }
    }
}
