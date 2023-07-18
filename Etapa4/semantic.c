#include "semantic.h"

#include "y.tab.h"

int SemanticErrors = 0;


void check_declarations(AST* node) {
    if(node == 0) return;

    switch (node->type) {
        case AST_GLOBAL_VAR:
        case AST_ATTR_ARRAY:
        case AST_PARAM:
            if (node->symbol->text != TK_IDENTIFIER) {
                fprintf(stderr, "Semantic ERROR: variable %s already declared \n", node->symbol->text);
                ++SemanticErrors;
            }
            else {
                node->symbol->type = SYMBOL_LABEL;
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



