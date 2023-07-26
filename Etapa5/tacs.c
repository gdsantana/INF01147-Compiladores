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

TAC* tacToCode(AST* node) {

    int i;
    TAC* result = 0;
    TAC* code[MAX_SONS];

    for(i=0; i<MAX_SONS; ++i)
        code[i] = tacGenerateCode(node->son[i]);
    
    switch (node->type) {
        case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;

        case AST_GLOBAL_VAR:
            switch (node->son[0]->type)
            {
                case AST_KW_INT:
                    result = makeGlobalCreate(code[0], code[1], node->symbol, TAC_DEC_GLOBAL_INT);
                    break;
                case AST_KW_CHAR:
                    result = makeGlobalCreate(code[0], code[1], node->symbol, TAC_DEC_GLOBAL_CHAR);
                    break;
                case AST_KW_REAL:
                    result = makeGlobalCreate(code[0], code[1], node->symbol, TAC_DEC_GLOBAL_REAL);
                    break;
                case AST_KW_BOOL:
                    result = makeGlobalCreate(code[0], code[1], node->symbol, TAC_DEC_GLOBAL_BOOL);
                    break;
                default:
                    break;
            }
        
        case AST_GLOBAL_VAR_ARRAY:
            result = makeArrCreate(code[0], code[1], node->symbol);
            break;
        case AST_ARRAY: result = makeArrCreateVal(code[0], code[1], node->symbol);  break;

        case AST_ATTR: result = tacJoin(code[0]?code[0]:0, tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0)); break;

        case AST_ARRAY_ELEMENT: result = makeArrGetElement(code[0], code[1],node->symbol); break;
        case AST_ATTR_ARRAY: result = makeArrSetElement(code[0], code[1],node->symbol); break;

        case AST_ADD:   result = makeBinaryOP(code[0], code[1], TAC_ADD); break;
        case AST_SUB:   result = makeBinaryOP(code[0], code[1], TAC_SUB); break;
        case AST_MULT:  result = makeBinaryOP(code[0], code[1], TAC_MULT); break;
        case AST_DIV:   result = makeBinaryOP(code[0], code[1], TAC_DIV); break;
                
        case AST_LT:    result = makeBinaryOP(code[0], code[1], TAC_LT); break;
        case AST_LE:   result = makeBinaryOP(code[0], code[1], TAC_LTE); break;
        case AST_GT:    result = makeBinaryOP(code[0], code[1], TAC_GT); break;
        case AST_GE:   result = makeBinaryOP(code[0], code[1], TAC_GTE); break;
        case AST_EQ:    result = makeBinaryOP(code[0], code[1], TAC_EQ); break;
        case AST_DIF:   result = makeBinaryOP(code[0], code[1], TAC_DIF); break;

        case AST_OUTPUT:
        case AST_LIST_ELEMENTS:   result = makePrint(code[0], code[1], node->type); break;

        case AST_INPUT:   result = makeRead(code[0]); break;

        case AST_DECLARATION_FUNCTION_INT:
        case AST_DECLARATION_FUNCTION_CHAR:
        case AST_DECLARATION_FUNCTION_FLOAT:   result = makeFunctionBody(code[0], code[1], node->symbol); break;

        case AST_DECLARATION_FUNCTION_ARGS_INT:
        case AST_DECLARATION_FUNCTION_ARGS_CHAR:
        case AST_PARAMS: result = makeFunctionArgs(code[0], node->symbol);  break;

        case AST_FUNC_CALL: result = makeCallFunction(code[0], node->symbol, TAC_FUN_CALL);  break;

        case AST_LIST_ARGS: result = makeCallFunctionArgs(code[0],code[1], node->son[0], TAC_FUNC_CALL_ARGS);  break;


        case AST_IF: result = makeIf(code[0]?code[0]:0, code[1]?code[1]:0); break;
        case AST_IF: result = makeIfElse(code[0]?code[0]:0, code[1]?code[1]:0, code[2]?code[2]:0); break;
        case AST_LOOP: result = makeWhile(code[0]?code[0]:0, code[1]?code[1]:0); break;


//        case AST_RETURN: result = tacCreate(TAC_RETURN, code[0]?code[0]->res:0, 0, 0); break;
        case AST_RETURN: result = tacJoin(code[0]?code[0]:0, tacCreate(TAC_RETURN, code[0]?code[0]->res:0, 0, 0)); break;

        default: { // return the union of code from all subrees
            result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
        }
    }

    return result;
}
TAC* makeGlobalCreate(TAC* code0, TAC* code1, HASH_NODE* symbol, int type) {
    TAC* tac = 0;

    tac = tacJoin(code0?code0:0, tacCreate(type, symbol, code0?code0->res:0, code1?code1->res:0));

    return tac;
}

TAC* makeArrGetElement(TAC* code0, TAC* code1, HASH_NODE* symbol) {
    TAC* tac = 0;
    tac = tacJoin(code0?code0:0, tacCreate(TAC_ARR_GET_ELEMENT, makeTemp(), symbol, code0?code0->res:0));
    return tac;
}

TAC* makeArrSetElement(TAC* code0, TAC* code1, HASH_NODE* symbol) {
    TAC* tac = 0;
    tac = tacJoin(code0?code0:0, tacCreate(TAC_ARR_SET_ELEMENT, code0?code0->res:0, code1?code1->res:0, 0));
    return tac;
}

TAC* makeArrCreate(TAC* code0, TAC* code1, HASH_NODE* symbol){

    TAC* args_tac = 0;

    args_tac = tacCreate(TAC_DEC_GLOBAL_ARR, symbol, code0?code0->res:0, code1?code1->res:0);
    return tacJoin(code1, tacJoin(code0, args_tac));
}

TAC* makeArrCreateVal(TAC* code0, TAC* code1, HASH_NODE* symbol){

    TAC* args_tac = 0;

    args_tac = tacCreate(TAC_DEC_GLOBAL_ARR_VAL, makeTemp(), symbol, code0?code0->res:0);

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

TAC* makePrint(TAC* code0, TAC* code1, int nodeType){
    if(nodeType == AST_PRINT_REST)
        return tacJoin(
                tacJoin(code0?code0:0, code1?code1:0),
                tacCreate(TAC_PRINT_CONCAT,
                          makeTemp(),
                          code0?code0->res:0,
                          code1?code1->res:0)
        );
    else
        return tacJoin(code0?code0:0, tacCreate(TAC_PRINT, code0?code0->res:0, 0, 0));

}

TAC* makeRead(TAC* code0){

    return tacCreate(TAC_READ,
              makeTemp(),
              code0?code0->res:0,
              0);
}

TAC* makeFunctionBody(TAC* code0, TAC* code1, HASH_NODE* symbol) {

    TAC* before_tac = 0;
    TAC* after_tac = 0;

    before_tac = tacCreate(TAC_BEGINFUN, symbol, code0?code0->res:0, 0);
    before_tac->prev = code0;
//    tacJoin(before_tac, code0);

    after_tac = tacCreate(TAC_ENDFUN, symbol, 0, 0);
    after_tac->prev = code1;
//    tacJoin(after_tac, code1 );


    return tacJoin(before_tac, after_tac);
}

TAC* makeFunctionArgs(TAC* code0, HASH_NODE* symbol){
    TAC* args_tac = 0;
    args_tac = tacCreate(TAC_DEC_FUNC_ARGS, makeTemp(), symbol, code0?code0->res:0);
    args_tac->prev = code0;

    return args_tac;
}
//TAC* makeFunctionArgs(TAC* code0, HASH_NODE* symbol, int type){
//    TAC* args_tac = 0;
//    args_tac = tacCreate(type, symbol, 0, 0);
//
//    return tacJoin(args_tac, code0);
//}

TAC* makeCallFunction(TAC* code0, HASH_NODE* symbol, int type){
    TAC* args_tac = 0;
    args_tac = tacCreate(type, makeTemp(), symbol, code0?code0->res:0);
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

TAC* makeGoto(AST* node){

    TAC* goto_tac = 0;

    goto_tac = tacCreate(TAC_GOTO, node->symbol, 0, 0);

    return goto_tac;
}

TAC* makeLabelTac(AST* node){
    TAC* label_tac = 0;

    label_tac = tacCreate(TAC_LABEL, node->symbol, 0, 0);

    return label_tac;
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


TAC* makeWhile( TAC* code0, TAC* code1){
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

TAC* makeReturn(TAC* code0){

}