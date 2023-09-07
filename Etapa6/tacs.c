#include "tacs.h"

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2) {
    TAC* newtac = 0;
    newtac = (TAC*) calloc(1, sizeof (TAC));

    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = 0;
    newtac->next = 0;

    return newtac;
}

void tacPrint(TAC* tac) {
    if(!tac || tac->type == TAC_SYMBOL) return;

    fprintf(stderr, "TAC(");

    switch (tac->type) {
        case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;

        case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break; // ASSINALAMENTO

        case TAC_GLOBAL_VAR: fprintf(stderr, "TAC_DEC_GLOBAL"); break;
        case TAC_GLOBAL_VAR_INT: fprintf(stderr, "TAC_DEC_GLOBAL_INT"); break;
        case TAC_GLOBAL_VAR_CHAR: fprintf(stderr, "TAC_DEC_GLOBAL_CHAR"); break;
        case TAC_GLOBAL_VAR_REAL: fprintf(stderr, "TAC_DEC_GLOBAL_REAL"); break;

        case TAC_GLOBAL_VAR_ARR: fprintf(stderr, "TAC_DEC_GLOBAL_ARR"); break;
        case TAC_GLOBAL_VAR_ARR_VAL: fprintf(stderr, "TAC_DEC_GLOBAL_ARR_VAL"); break;

        case TAC_ARR_GET_ELEMENT: fprintf(stderr, "TAC_ARR_GET_ELEMENT"); break;
        case TAC_ARR_SET_ELEMENT: fprintf(stderr, "TAC_ARR_SET_ELEMENT"); break;

        case TAC_ADD:   fprintf(stderr, "TAC_ADD"); break;
        case TAC_SUB:   fprintf(stderr, "TAC_SUB"); break;
        case TAC_MULT:  fprintf(stderr, "TAC_MULT"); break;
        case TAC_DIV:   fprintf(stderr, "TAC_DIV"); break;

        case TAC_LT:    fprintf(stderr, "TAC_LT"); break;
        case TAC_LE:   fprintf(stderr, "TAC_LTE"); break;
        case TAC_GT:    fprintf(stderr, "TAC_GT"); break;
        case TAC_GE:   fprintf(stderr, "TAC_GTE"); break;
        case TAC_EQ:    fprintf(stderr, "TAC_EQ"); break;
        case TAC_DIF:   fprintf(stderr, "TAC_DIF"); break;

        case TAC_OUTPUT:   fprintf(stderr, "TAC_OUTPUT"); break;
        case TAC_OUTPUT_INT:   fprintf(stderr, "TAC_OUTPUT_INT"); break;
        case TAC_OUTPUT_CHAR:   fprintf(stderr, "TAC_OUTPUT_CHAR"); break;
        case TAC_INPUT:   fprintf(stderr, "TAC_INPUT"); break;

        case TAC_BEGINFUN:   fprintf(stderr, "TAC_BEGINFUN"); break;
        case TAC_ENDFUN:   fprintf(stderr, "TAC_ENDFUN"); break;


//        case TAC_DEC_FUNC_ARGS_INT  :   fprintf(stderr, "TAC_DEC_FUNC_ARGS_INT"); break;
//        case TAC_DEC_FUNC_ARGS_CHAR :   fprintf(stderr, "TAC_DEC_FUNC_ARGS_CHAR"); break;
//        case TAC_DEC_FUNC_ARGS_FLOAT:   fprintf(stderr, "TAC_DEC_FUNC_ARGS_FLOAT"); break;
        case TAC_DEC_FUNC_ARGS:   fprintf(stderr, "TAC_DEC_FUNC_ARGS"); break;

        case TAC_FUN_CALL:   fprintf(stderr, "TAC_FUN_CALL"); break;
        case TAC_FUNC_CALL_ARGS:   fprintf(stderr, "TAC_FUNC_CALL_ARGS"); break;


        case TAC_JMP: fprintf(stderr, "TAC_JMP"); break;
        case TAC_JMPZ: fprintf(stderr, "TAC_JMPZ"); break;
        case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
        case TAC_GOTO: fprintf(stderr, "TAC_GOTO"); break;

        case TAC_RETURN: fprintf(stderr, "TAC_RETURN"); break;

        default: fprintf(stderr, "TAC_UNKNOWN"); break;
    }

    fprintf(stderr, ", %s", (tac->res)?tac->res->text:"0");
    fprintf(stderr, ", %s", (tac->op1)?tac->op1->text:"0");
    fprintf(stderr, ", %s", (tac->op2)?tac->op2->text:"0");

    fprintf(stderr, ");\n");
}
void tacPrintBackwards(TAC* tac) { // recebe o prev
    if(!tac)
        return;
    else {
        tacPrintBackwards(tac->prev);
        tacPrint(tac);
    }

}

TAC* tacJoin(TAC* l1, TAC* l2){

    TAC* point;

    if(!l1) return l2;
    if(!l2) return l1;

    for(point=l2; point->prev != 0; point=point->prev){
        ;
    }

    point->prev = l1;
    return l2;
}

TAC* tacGenerateCode(AST* node) {

    int i;
    TAC* result = 0;
    TAC* code[MAX_SONS];

    if(!node) return result;

    // process filhos

    for(i=0; i<MAX_SONS; ++i)
        code[i] = tacGenerateCode(node->son[i]);

    switch (node->type) {
        case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;

        case AST_GLOBAL_VAR:
            switch (node->son[0]->type)
            {
            case AST_KW_INT:
                result = makeGlobalCreate(code[0], code[1], node->symbol, TAC_GLOBAL_VAR_INT); break;
                break;
            case AST_KW_CHAR:
                result = makeGlobalCreate(code[0], code[1], node->symbol, TAC_GLOBAL_VAR_CHAR); break;
                break;
            case AST_KW_REAL:
                result = makeGlobalCreate(code[0], code[1], node->symbol, TAC_GLOBAL_VAR_REAL); break;
                break;
            case AST_KW_BOOL:
                result = makeGlobalCreate(code[0], code[1], node->symbol, TAC_GLOBAL_VAR_BOOL); break;
                break;
            default:
                break;
            }
        case AST_GLOBAL_VAR_ARRAY: result = makeArrCreate(code[0], code[1], node->symbol);  break;
        case AST_ARRAY: result = makeArrCreateVal(code[0], code[1], node->symbol);  break;

        case AST_ATTR: result = tacJoin(code[0]?code[0]:0, tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0)); break;

        case AST_ARRAY_ELEMENT: result = makeArrGetElement(code[0], code[1],node->symbol); break;
        case AST_ATTR_ARRAY: result = makeArrSetElement(code[0], code[1],node->symbol); break;

        case AST_ADD:   result = makeBinaryOP(code[0], code[1], TAC_ADD); break;
        case AST_SUB:   result = makeBinaryOP(code[0], code[1], TAC_SUB); break;
        case AST_MULT:  result = makeBinaryOP(code[0], code[1], TAC_MULT); break;
        case AST_DIV:   result = makeBinaryOP(code[0], code[1], TAC_DIV); break;
                
        case AST_LT:    result = makeBinaryOP(code[0], code[1], TAC_LT); break;
        case AST_LE:   result = makeBinaryOP(code[0], code[1], TAC_LE); break;
        case AST_GT:    result = makeBinaryOP(code[0], code[1], TAC_GT); break;
        case AST_GE:   result = makeBinaryOP(code[0], code[1], TAC_GE); break;
        case AST_EQ:    result = makeBinaryOP(code[0], code[1], TAC_EQ); break;
        case AST_DIF:   result = makeBinaryOP(code[0], code[1], TAC_DIF); break;

        case AST_OUTPUT:
            result = makeOutput(code[0], code[1], node); break;

        case AST_INPUT:   result = makeInput(code[0]); break;// talvez um pouco diferente pq passamos o tipo da entrada

        case AST_FUNC:
           result = makeFunctionBody(code[0], code[1], node->symbol); break;
        
        // case AST_PARAMS: result = flipArgsTAC(code[0], code[1]); break;
        case AST_PARAMS:
            switch (node->son[0]->son[0]->type)
                {
                case AST_KW_INT:
                case AST_KW_CHAR:
                    result =  makeFunctionArgs(code[0], code[1],node->symbol);  break;
                    break;
                case AST_KW_REAL:
                    result = makeFunctionArgsReal(code[0], code[1],node->symbol);  break;
                    break;

                    break;
                default:
                    break;
                }
            break;
        case AST_PARAM:
            switch (node->son[0]->type)
                {
                case AST_KW_INT:
                case AST_KW_CHAR:
                    result =  makeFunctionArgs(code[0], code[1],node->symbol);  break;
                    break;
                case AST_KW_REAL:
                    result = makeFunctionArgsReal(code[0], code[1],node->symbol);  break;
                    break;

                    break;
                default:
                    break;
                }
            break;
        
        case AST_FUNC_CALL: result = makeCallFunction(code[0], node->symbol, TAC_FUN_CALL);  break;

        case AST_LIST_ARGS: result = makeCallFunctionArgs(code[0],code[1], node->son[0], TAC_FUNC_CALL_ARGS);  break;


        case AST_IF: result = makeIf(code[0]?code[0]:0, code[1]?code[1]:0); break;
        case AST_IF_ELSE: result = makeIfElse(code[0]?code[0]:0, code[1]?code[1]:0, code[2]?code[2]:0); break;
        case AST_LOOP: result = makeLoop(code[0]?code[0]:0, code[1]?code[1]:0); break;


//        case AST_RETURN: result = tacCreate(TAC_RETURN, code[0]?code[0]->res:0, 0, 0); break;
        case AST_RETURN: result = makeReturn(code[0], code[1]); break;

        default: { // return the union of code from all subrees
            result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
        }
    }

    return result;
}

/*
            ##################################################################
            ####################### FUNÇÕES AUXILIARES #######################
            ##################################################################

*/

TAC* makeGlobalCreate(TAC* code0, TAC* code1, HASH_NODE* symbol, int type) {
    TAC* tac = 0;

    tac = tacJoin(code0?code0:0, tacCreate(type, symbol, code0?code0->res:0, code1?code1->res:0));

    return tac;
}

TAC* makeArrGetElement(TAC* code0, TAC* code1, HASH_NODE* symbol) {
    TAC* tac = 0;
//    tac = tacJoin(tacCreate(TAC_ARR_GET_ELEMENT, code0?code0->res:0, symbol, code1?code1->res:0), code1?code1:0);
    tac = tacCreate(TAC_ARR_GET_ELEMENT, makeTemp(), symbol, code0?code0->res:0);
    return tacJoin(code0?code0:0, tac);
}

TAC* makeArrSetElement(TAC* code0, TAC* code1, HASH_NODE* symbol) {
    TAC* tac = 0;
    //tac = tacJoin(code0?code0:0, tacCreate(TAC_ARR_SET_ELEMENT, code0?code0->res:0, code1?code1->res:0, 0));
//    tac = tacJoin(code0?code0:0, tacCreate(TAC_ARR_SET_ELEMENT, code0?code0->op1:0, code0?code0->op2:0, code1?code1->res:0));
    tac = tacJoin(code1?code1:0, tacCreate(TAC_ARR_SET_ELEMENT, symbol, code0?code0->res:0, code1?code1->res:0));
//    return tacCreate(TAC_ARR_SET_ELEMENT, symbol, code0?code0->res:0, code1?code1->res:0);
//    tacJoin(code[0]?code[0]:0, tacCreate(TAC_ARR_SET_ELEMENT, symbol, code0?code0->res:0, code1?code1->res:0));
    return tacJoin(code0?code0:0, tac);
}

TAC* makeArrCreate(TAC* code0, TAC* code1, HASH_NODE* symbol){

    TAC* tac = 0;

    TAC *tmp = 0;
    TAC *tac_arr = 0;
    tmp = code1?code1:0;

    if(!tmp) {
        tac = tacCreate(TAC_GLOBAL_VAR_ARR, symbol, 0, code0?code0->res:0);
    } else {
        while (tmp) {
            tac_arr = tacCreate(TAC_GLOBAL_VAR_ARR, symbol, tmp->res, code0 ? code0->res : 0);
            tac = tacJoin(tac, tac_arr);
            tmp = tmp->prev;
        }
    }


    return tac;
    return tacJoin(code1, tacJoin(code0, tac));
}

TAC* makeArrCreateVal(TAC* code0, TAC* code1, HASH_NODE* symbol){

    TAC* args_tac = 0;

    args_tac = tacCreate(TAC_GLOBAL_VAR_ARR_VAL, symbol, 0,0);

    return tacJoin(code0, args_tac);

}


TAC* makeBinaryOP(TAC* code0, TAC* code1, int type) {
    return tacJoin(
            tacJoin(code0?code0:0, code1?code1:0),
            tacCreate(type,
                      makeTemp(),
                      code0?code0->res:0,
                      code1?code1->res:0)
    );
}
TAC* makeOutput(TAC* code0, TAC* code1, AST* node){
    if(node->type == AST_OUTPUT_STRING) {
        TAC *string_val = 0;
        HASH_NODE* node_string = 0;
        node_string = makeTemp();
        node_string->dataString = code0?code0->res->text:"";
        node_string->dataType = DATATYPE_STRING;

        string_val = tacCreate(TAC_SYMBOL_STRING,
                               node_string,
                               code0 ? code0->res : 0,
                               code1 ? code1->res : 0);

        return tacJoin(
                tacJoin(code0 ? code0 : 0, tacCreate(TAC_OUTPUT_STRING, string_val->res, 0, 0)),
                code1 ? code1 : 0
        );
    }
    if(node->type == AST_OUTPUT_EXP) {
        TAC *tac = 0;

        switch (code0->res->dataType) {
            case DATATYPE_CHAR:
                tac = tacCreate(TAC_OUTPUT_CHAR, code0 ? code0->res : 0, 0, 0);
                break;
            case DATATYPE_REAL:
                tac = tacCreate(TAC_OUTPUT_REAL, code0 ? code0->res : 0, 0, 0);
                break;
            case DATATYPE_INT:
                tac = tacCreate(TAC_OUTPUT_INT, code0 ? code0->res : 0, 0, 0);
                break;
            default:
                tac = tacCreate(TAC_OUTPUT_INT, code0 ? code0->res : 0, 0, 0);
        }

        return tacJoin(
                tacJoin(code0 ? code0 : 0, tac),
                code1 ? code1 : 0
        );
    }
    if(node->type == AST_OUTPUT)
        return tacJoin(  code0?code0:0, tacCreate(TAC_OUTPUT, code0?code0->res:0, 0, 0));


}

TAC* makeInput(TAC* code0){

    return tacCreate(TAC_INPUT,
              makeTemp(),
              code0?code0->res:0,
              0);
}

TAC* makeFunctionBody(TAC* code0, TAC* code1, HASH_NODE* symbol) {

    TAC* before_tac = 0;
    TAC* after_tac = 0;

    before_tac = tacCreate(TAC_BEGINFUN, symbol, code1?code1->res:0, 0);
//    before_tac->prev = code0;
    tacJoin( code0, before_tac);

    after_tac = tacCreate(TAC_ENDFUN, symbol, code0?code0->res:0, 0);
//    after_tac->prev = code1;
    tacJoin(code1, after_tac);


    return tacJoin(before_tac, after_tac);
}

TAC* makeFunctionArgs(TAC* code0, TAC* code1, HASH_NODE* symbol){
    TAC* args_tac = 0;
    args_tac = tacCreate(TAC_DEC_FUNC_ARGS, symbol, code0?code0->res:0,code1?code1->res:0);

    return tacJoin(code0, args_tac);
    return tacJoin(tacJoin(code0, code1),args_tac);
    return tacJoin(code0, tacJoin(code1, args_tac));
}

TAC* makeFunctionArgsReal(TAC* code0, TAC* code1, HASH_NODE* symbol){
    TAC* args_tac = 0;
    args_tac = tacCreate(TAC_DEC_FUNC_ARGS_REAL, symbol, code0?code0->res:0,code1?code1->res:0);

    return tacJoin(code0, args_tac);
    return tacJoin(tacJoin(code0, code1),args_tac);
    return tacJoin(code0, tacJoin(code1, args_tac));
}

TAC* flipArgsTAC(TAC* code0, TAC* code1){
    return tacJoin(code0, code1);
}

TAC* makeCallFunction(TAC* code0, HASH_NODE* symbol, int type){
    TAC* args_tac = 0;
//    args_tac = tacCreate(type, makeTemp(), symbol, code0?code0->res:0);
    args_tac = tacCreate(type, makeTemp(), symbol, 0);
    //args_tac->prev = code0;

//    return tacJoin(args_tac, code0);
    return tacJoin(code0, args_tac);
}

TAC* makeCallFunctionArgs(TAC* code0, TAC* code1, AST* node, int type){
    TAC* args_tac = 0;
    args_tac = tacCreate(type, makeTemp(), code0?code0->res:0, code1?code1->res:0);
//    args_tac->prev = code0->prev;

    return tacJoin(tacJoin(code0, code1), args_tac);
//    return args_tac;
}


TAC* makeIf( TAC* code0, TAC* code1){
    TAC* jump_tac = 0;
    TAC* label_tac = 0;

    HASH_NODE* new_label_tac = 0;

    new_label_tac = makeLabel();

    jump_tac = tacCreate(TAC_JMPZ, new_label_tac, code0?code0->res:0, 0);
    jump_tac->prev = code0;

    label_tac = tacCreate(TAC_LABEL, new_label_tac, 0, 0);
    label_tac->prev = code1;
    return tacJoin(jump_tac, label_tac);

}

TAC* makeIfElse( TAC* code0, TAC* code1, TAC* code2){
    TAC* jump_tac_end_true = 0;
    TAC* jump_tac_else = 0;
    TAC* label_tac_else = 0;
    TAC* label_tac = 0;

    HASH_NODE* new_label_tac_else = 0;
    HASH_NODE* new_label_tac = 0;

    new_label_tac_else = makeLabel();
    new_label_tac = makeLabel();

    jump_tac_else = tacCreate(TAC_JMPZ, new_label_tac_else, code0?code0->res:0, 0);
    jump_tac_else->prev = code0;

    jump_tac_end_true = tacCreate(TAC_JMP, new_label_tac, 0, 0);
    jump_tac_end_true->prev = code1;

    label_tac_else = tacCreate(TAC_LABEL, new_label_tac_else, 0, 0);
    label_tac_else->prev = jump_tac_end_true;

    label_tac = tacCreate(TAC_LABEL, new_label_tac, 0, 0);
    label_tac->prev = code2;

    return tacJoin(jump_tac_else,tacJoin(label_tac_else, label_tac));

}


TAC* makeLoop( TAC* code0, TAC* code1){
    TAC* jump_tac_false = 0;
    TAC* jump_tac_loop = 0;

    TAC* label_tac_before = 0;
    TAC* label_tac_after = 0;

    HASH_NODE* new_label_tac_before = 0;
    HASH_NODE* new_label_tac_after = 0;

    new_label_tac_before = makeLabel();
    new_label_tac_after = makeLabel();

    label_tac_before = tacCreate(TAC_LABEL, new_label_tac_before, 0, 0);
    //label_tac_before->prev = jump_tac_false;

    jump_tac_false = tacCreate(TAC_JMPZ, new_label_tac_after, code0?code0->res:0, 0);
    jump_tac_false->prev = tacJoin(label_tac_before, code0);

    jump_tac_loop = tacCreate(TAC_JMP, new_label_tac_before, 0, 0);
    jump_tac_loop->prev = code1;

    label_tac_after = tacCreate(TAC_LABEL, new_label_tac_after, 0, 0);
    label_tac_after->prev = jump_tac_loop;
    return tacJoin(jump_tac_false, label_tac_after);
}

TAC* makeReturn(TAC* code0, TAC* code1){
    return tacJoin(code0?code0:0, tacCreate(TAC_RETURN, code0?code0->res:0,code1?code1->res:0, 0));
}


TAC* tacReverseTAC(TAC* tac) {
    TAC* t;

    for(t=tac; t->prev; t = t->prev) {
        //printf("tac type [%d] - res type [%d] - res text [%s]\n", t->type, t->res->type, t->res->text);
        t->prev->next = t;
    }

    return t;
}

