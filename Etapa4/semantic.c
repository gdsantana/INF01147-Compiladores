#include "semantic.h"

#include "y.tab.h"

int SemanticErrors = 0;

void check_undeclared() {

    HASH_NODE *node;

    int undeclered_errors = 0;

    for (int i=0; i<HASH_SIZE; i++){
        for (node=getNode(i); node; node=node->next) {
            if(node -> type == TK_IDENTIFIER) {
                printf("\nSEMANTIC ERROR: symbol %s undeclared.\n", node->text);
                ++SemanticErrors;
                ++undeclered_errors;
            }
        }
    }
    printf("\n\n Undeclared semantic errors: %d \n\n", undeclered_errors);
}
void check_declarations(AST* node) {
    if(node == 0) return;

    switch (node->type) {
        case AST_GLOBAL_VAR:
            if (node->symbol)
                if (node->symbol->text != TK_IDENTIFIER) {
                        fprintf(stderr, "Semantic ERROR[VARIABLE]: %s already declared \n", node->symbol->text);
                        ++SemanticErrors;
                    }
                    else {
                        node->symbol->type = SYMBOL_VARIABLE;
                        set_datatype(node);
                    }
            break;
        case AST_ATTR_ARRAY:
            if (node->symbol)
                if(node->symbol->type != TK_IDENTIFIER) {
                    fprintf(stderr, "Semantic ERROR[ARRAY]: %s already declared \n", node->symbol->text);
                    ++SemanticErrors;
                } else{
                    node->symbol->type = SYMBOL_ARRAY;
                    set_datatype(node);
                }
            break;
        case AST_PARAM:
            if (node->symbol)
                if(node->symbol->type != TK_IDENTIFIER) {
                    fprintf(stderr, "Semantic ERROR[FUNC ARGS]: function args or variable name [%s] already declared \n", node->symbol->text);
                    ++SemanticErrors;
                } else{
                    node->symbol->type = SYMBOL_FUNC_ARGS;
                    set_datatype(node);
                }
            break;
        case AST_HEADER:
            if (node->symbol)
                if(node->symbol->type != TK_IDENTIFIER) {
                    fprintf(stderr, "Semantic ERROR[FUNC]:  %s already declared \n", node->symbol->text);
                    ++SemanticErrors;
                } else{
                    node->symbol->type = SYMBOL_FUNC;
                    set_datatype(node);
                }
            break;
        case AST_SYMBOL:
            set_datatype(node);
            break;
        default:
            break;
    }
    for (int i=0; i<MAX_SONS; i++)
        check_declarations(node->son[i]);
}
void check_attribuition(AST* node) {
    if(node == 0) return;
    switch (node->type)
    {
    case AST_ATTR:
        switch (node->symbol->type) {
            case SYMBOL_VARIABLE:
            /*
                VER QUAIS SÃO AS REGRAS DE ATRIBUIÇÕES 
            */
                if(!is_number(node->son[0]) && is_boolean(node->son[0])){
                    fprintf(stderr,"Semantic ERROR: [ATTIBUITION]: Invalid assignment block [%s] \n", astToCode(node, 0));
                    ++SemanticErrors;
                }
                break;
            default:
                fprintf(stderr,"Semantic ERROR: [TYPE ATTIBUITION]: Invalid assignment block [%s] \n", astToCode(node, 0));
                ++SemanticErrors;
                break;
        }
    default:
        break;
    }
}

void check_flux_control(AST* node) {
    if (node==0) return;

    switch (node->type) {
        case AST_IF:
            if(!is_boolean(node->son[0])){
                fprintf(stderr,"Semantic ERROR: [IF]: Invalid condition [%s] \n", astToCode(node, 0));
                ++SemanticErrors;
            }
            break;
        case AST_LOOP:
            if(!is_boolean(node->son[0])){
                fprintf(stderr,"Semantic ERROR: [LOOP]: Invalid condition [%s] \n", astToCode(node, 0));
                ++SemanticErrors;
            }
            break;
        default:
            break;
    }

    for (int i=0; i<MAX_SONS; ++i)
        check_flux_control(node->son[i]);
}

void check_func_call(AST* node){
    if (node==0) return;

    switch (node->type) {
        case AST_FUNC_CALL:
            check_list_args(node);
            break;
        default:
            break;

    }
    for (int i=0; i<MAX_SONS; ++i)
        check_function_call(node->son[i]);
}

void check_list_args(AST* func_call_node) {
    if (func_call_node==0) return;

    if (func_call_node->type == AST_FUNCTION_CALL) {
        int args_size = get_args_size(func_call_node->symbol->text, rootNode);
        if (args_size < 0) args_size = 0;

        int args_size_call = get_func_call_args_size(func_call_node);
        if (args_size_call < 0) args_size = 0;

        if (args_size != args_size_call) {
            fprintf(stderr, "\nSemantic ERROR: [CHECK FUNCTION CALL ARGS SIZE]: \n invalid number of argument function [%s] expected [%d] received [%d]\n\n", func_call_node->symbol->text,args_size, args_size_call);
            SemanticErrors += 1;
        }
    }

    return;
}
int get_func_call_args_size(AST* node) {
    if (node==0) return 0;

    int size = 0;
    AST* args_node;

    if (node->type == AST_FUNC_CALL) {
        if (node->son[0] != 0) {
            args_node = node->son[0];
            do {
                size += 1;
                args_node = args_node->son[1];
            } while (args_node != 0);
        }
    }
    return size;
}

int get_func_args_size(char* func_name, AST* node) {
    if (node==0) return -1;

    int size = 0;
    AST* args_node;
    AST* body_node;

    switch (node->type){
        case AST_HEADER: {
            if (node->symbol->text == func_name) {
                args_node = node->son[0]; 
                while (args_node && args_node->son[0] != 0) {
                    size += 1;
                    args_node = args_node->son[0];
                }
                return size;
            }
            break;
        }
        default:
            break;
    }

    for (int i=0; i<MAX_SONS; ++i) {
        int returned_size = get_func_args_size(func_name, node->son[i]);
        if (returned_size >= 0)
            return returned_size;
    }
}

void check_output(AST* node){
    if (node==0) return;

    switch (node->type) {
        case AST_OUTPUT:
            check_output(node->son[0]);
            break;
        case AST_LIST_ELEMENTS:
            if((node->son[0]->symbol->type == SYMBOL_STRING) && !(node->son[1])) {
                break; // ok só string
            }
            else if ((node->son[0]->symbol->type == SYMBOL_STRING) && node->son[1]) {
                if (node->son[1]->type == AST_LIST_ELEMENTS)
                    check_output(node->son[1]);
                else
                    check_expressions(node->son[1]);
            }
            break;
        default:
            break;
    }
    for (int i=0; i<MAX_SONS; ++i)
        check_print(node->son[i]);
}
void check_expressions(AST* node) {
    if(node == 0) return;

    switch (node->type)
    {
        case AST_ADD:               
        case AST_SUB:              
        case AST_MULT:              
        case AST_DIV:             
        case AST_LT:               
        case AST_LE:                
        case AST_GT:              
        case AST_GE:               
        case AST_EQ:               
        case AST_DIF:               
        case AST_AND:              
        case AST_OR:             
        case AST_NOT: 
            if(!is_number(node->son[0])) {
                if(node->son[0]->type == AST_EXPRESSION_BLOCK)
                    fprintf(stderr,"Semantic ERROR: [CHECK EXPRESSIONS]: Invalid left block [%s] for aritmetic expression [%s]\n", astToCode(node->son[0], 0), astToCode(node, 0));
                else
                    fprintf(stderr, "\nSemantic ERROR: [CHECK EXPRESSIONS]: invalid left operand [%s] datatype [%d] for OP[%s] \n\n", node->son[0]->symbol->text, node->son[0]->symbol->datatype, node->symbol->text);
                ++SemanticErrors;
            }
            if(!is_number(node->son[1])) {
                if(node->son[1]->type == AST_EXPRESSION_BLOCK)
                    fprintf(stderr,"Semantic ERROR: [CHECK EXPRESSIONS]: Invalid right block [%s] for aritmetic expression [%s]\n", astToCode(node->son[1], 0), astToCode(node, 0));
                else
                    fprintf(stderr, "\nSemantic ERROR: [CHECK EXPRESSIONS]: invalid right operand [%s] datatype [%d] for OP[%s] \n\n", node->son[1]->symbol->text, node->son[1]->symbol->datatype, node->symbol->text);
                ++SemanticErrors;
            }
            break;
            break;

        case AST_EXPRESSION_BLOCK:
            break
        default:
            break;
    }
    for (int i=0; i<MAX_SONS; ++i)
        check_expressions(node->son[i]);
}

void check_array_acess(AST* node) {
    if (node==0) return;

    switch (node->type) {
        case AST_ARRAY_ELEMENT:
            //logBinaryExpression(node);

            if(!is_valid_array_index(node->son[0])) {
                fprintf(stderr, "\nSemantic ERROR: [CHECK INDEX]: \n invalid array access index [%s] datatype [%d] for OP[%s] \n\n", node->son[0]->symbol->text, node->son[0]->symbol->datatype, node->symbol->text);
                ++SemanticErrors;
            }
            break;
        case AST_EXPRESSION_BLOCK:
            break;
        default:
            break;

    }

    for (int i=0; i<MAX_SONS; ++i)
        check_array_acess(node->son[i]);
}

void check_return(AST* node) {
    if(node == 0) return;

    switch (node->type) {
        case AST_FUNC:
            if(check_return_type(node->son[1], node->symbol->dataType, 0))
                ++SemanticErrors;
            break;
        default:
            break;
    }

    for (int i=0; i<MAX_SONS; ++i)
        check_return(node->son[i]);
}
int check_return_type(AST* node, int type, int errors) {
    if(node->type == AST_RETURN) {

    }
}





/*
        ##########################
        ### FUNÇÕES AUXILIARES ###
        ##########################
*/

void set_datatype(AST* node) {
    switch (node->type) {
        case AST_GLOBAL_VAR:
        case AST_GLOBAL_VAR_ARRAY:
            switch (node->son[0]->type)
            {
                case AST_KW_INT:
                    node->symbol->datatype = DATATYPE_ARRAY_INT;
                    // node->symbol->datavalue = atoi(node->son[1]->symbol->text);
                    break;
                case AST_KW_CHAR:
                    node->symbol->datatype = DATATYPE_ARRAY_INT;
                    // node->symbol->datavalue = atoi(node->son[1]->symbol->text); 
                    break;
                case AST_KW_REAL:
                    node->symbol->datatype = DATATYPE_ARRAY_REAL;
                    // node->symbol->datavalue = atoi(node->son[1]->symbol->text); 
                    break;
                case AST_KW_BOOL:
                    node->symbol->datatype = DATATYPE_ARRAY_BOOL;
                    // node->symbol->datavalue = atoi(node->son[1]->symbol->text); // TODO: validação de true or false
                    break;
                default:
                    break;
            }
        case AST_FUNC:
            // func -> header -> tipo 
            switch (node->son[0]->son[0]->type)
            {
                case AST_KW_INT:
                    node->symbol->datatype = DATATYPE_ARRAY_INT;
                    // node->symbol->datavalue = atoi(node->son[1]->symbol->text);
                    break;
                case AST_KW_CHAR:
                    node->symbol->datatype = DATATYPE_ARRAY_INT;
                    // node->symbol->datavalue = atoi(node->son[1]->symbol->text); 
                    break;
                case AST_KW_REAL:
                    node->symbol->datatype = DATATYPE_ARRAY_REAL;
                    // node->symbol->datavalue = atoi(node->son[1]->symbol->text); 
                    break;
                case AST_KW_BOOL:
                    node->symbol->datatype = DATATYPE_ARRAY_BOOL;
                    // node->symbol->datavalue = atoi(node->son[1]->symbol->text); // TODO: validação de true or false
                    break;
                default:
                    break;
            }
        case AST_SYMBOL:
            if (node->symbol) {
                if (node->symbol->type == LIT_INTEGER) {
                    node->symbol->datatype = DATATYPE_INT;
                    node->symbol->datavalue = atoi(node->symbol->text);
                    // node->symbol->type = SYMBOL_LIT_INT;
                }
                if (node->symbol->type == LIT_CHAR) {
                    node->symbol->datatype = DATATYPE_CHAR;
                    // node->symbol->type = SYMBOL_LIT_CHAR;
                }
                if (node->symbol->type == LIT_REAL) {
                    node->symbol->datatype = DATATYPE_REAL;
                    // node->symbol->type = SYMBOL_LIT_CHAR;
                }
                if (node->symbol->type == LIT_STRING) {
                    node->symbol->datatype = DATATYPE_STRING;
                    // node->symbol->type = SYMBOL_STRING;
                }
            } else {
                char *code = astToCode(node, 0);
                fprintf(stderr, "WARNING UNDEFINED AST_SYMBOL: \t %s \n\n", code);
            }
            break;
        default: 
            break;
    }
}

int is_valid_array_index(AST* node){
    if(node->symbol
       && node->symbol->type == SYMBOL_ARRAY
       && is_integer(node->son[0])
       && node->symbol->datavalue > node->son[0]->symbol->datavalue)
        return 1;
    return 0;
}