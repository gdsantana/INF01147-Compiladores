// AST
#include <stdio.h>

#include "ast.h"

#include "y.tab.h"


AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3) {

    AST *newnode;

    newnode = (AST*) calloc(1, sizeof(AST));

    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;

    return newnode;
}
void astPrint(AST *node, int level) {

    if (node==0) return;

    for(int i=0; i<level; i++) 
        fprintf(stderr, "  ");

    fprintf(stderr, "ast(");

    switch (node->type) {
        case AST_SYMBOL:            fprintf(stderr, "AST_SYMBOL"); break;        
        case AST_PROGRAM:           fprintf(stderr, "AST_PROGRAM"); break;
        case AST_LIST:              fprintf(stderr, "AST_LIST"); break;
        case AST_ELEMENT:           fprintf(stderr, "AST_ELEMENT"); break;
        case AST_GLOBAL_VAR:        fprintf(stderr, "AST_GLOBAL_VAR"); break;
        case AST_GLOBAL_VAR_ARRAY:  fprintf(stderr, "AST_GLOBAL_VAR_ARRAY"); break;
        case AST_ARRAY:             fprintf(stderr, "AST_ARRAY"); break;
        case AST_VALUE:             fprintf(stderr, "AST_VALUE"); break;
        case AST_FUNC:              fprintf(stderr, "AST_FUNC"); break;
        case AST_HEADER:            fprintf(stderr, "AST_HEADER"); break;
        case AST_TYPE:              fprintf(stderr, "AST_TYPE"); break;
        // case AST_LIST_PARAMS:       fprintf(stderr, "AST_LIST_PARAMS"); break;
        case AST_PARAMS:            fprintf(stderr, "AST_PARAMS"); break;
        case AST_PARAM:             fprintf(stderr, "AST_PARAM"); break;
        case AST_FUNC_CALL:         fprintf(stderr, "AST_FUNC_CALL"); break;
        case AST_LIST_ARGS:         fprintf(stderr, "AST_LIST_ARGS"); break;
        case AST_COMMAND:           fprintf(stderr, "AST_COMMAND"); break;
        case AST_COMMAND_LIST:      fprintf(stderr, "AST_COMMAND_LIST"); break;
        case AST_BLOCK:             fprintf(stderr, "AST_BLOCK"); break;
        case AST_OUTPUT:            fprintf(stderr, "AST_OUTPUT"); break;
        case AST_LIST_ELEMENTS:     fprintf(stderr, "AST_LIST_ELEMENTS"); break;
        case AST_EL:                fprintf(stderr, "AST_EL"); break;
        case AST_RETURN:            fprintf(stderr, "AST_RETURN"); break;
        case AST_INPUT:             fprintf(stderr, "AST_INPUT"); break;
        case AST_ATTR:              fprintf(stderr, "AST_ATTR"); break;
        case AST_ATTR_ARRAY:        fprintf(stderr, "AST_ATTR_ARRAY"); break;
        case AST_ATTR_INPUT:        fprintf(stderr, "AST_ATTR_INPUT"); break;
        case AST_ATTR_ARRAY_INPUT:  fprintf(stderr, "AST_ATTR_ARRAY_INPUT"); break;
        case AST_FLUX_CONTROL:      fprintf(stderr, "AST_FLUX_CONTROL"); break;

        case AST_EXPRESSION:        fprintf(stderr, "AST_EXPRESSION"); break;
        case AST_EXPRESSION_BLOCK:        fprintf(stderr, "AST_EXPRESSION_BLOCK"); break;
        
        case AST_ADD:               fprintf(stderr, "AST_ADD"); break;
        case AST_SUB:               fprintf(stderr, "AST_SUB"); break;
        case AST_MULT:              fprintf(stderr, "AST_MULT"); break;
        case AST_DIV:               fprintf(stderr, "AST_DIV"); break;

        case AST_LT:                fprintf(stderr, "AST_LT"); break;
        case AST_LE:                fprintf(stderr, "AST_LE"); break;
        case AST_GT:                fprintf(stderr, "AST_GT"); break;
        case AST_GE:                fprintf(stderr, "AST_GE"); break;
        case AST_EQ:                fprintf(stderr, "AST_EQ"); break;
        case AST_DIF:               fprintf(stderr, "AST_DIF"); break;
        
        
        case AST_AND:               fprintf(stderr, "AST_AND"); break;
        case AST_OR:               fprintf(stderr, "AST_OR"); break;
        case AST_NOT:               fprintf(stderr, "AST_NOT"); break;


        case AST_BLOCK:             fprintf(stderr, "AST_BLOCK"); break;
        case AST_FLUX_CONTROL:      fprintf(stderr, "AST_FLUX_CONTROL"); break;
        
        case AST_EXPRESSION_BLOCK:  fprintf(stderr, "AST_EXPRESSION_BLOCK"); break;

        
        case AST_IF:                fprintf(stderr, "AST_IF"); break;
        case AST_LOOP:              fprintf(stderr, "AST_LOOP"); break;
        case AST_KW_INT:            fprintf(stderr, "AST_KW_INT"); break;
        case AST_KW_REAL:           fprintf(stderr, "AST_KW_REAL"); break;
        case AST_KW_CHAR:           fprintf(stderr, "AST_KW_CHAR"); break;
        case AST_KW_BOOL:           fprintf(stderr, "AST_KW_BOOL"); break;
              

    
        default: fprintf(stderr, " \n\n\n ------------>>>> AST_UNKNOWN [%d] <<<<------------ \n\n\n", node->type); break;
    }

    if (node->symbol != 0) 
        fprintf(stderr, ", %s) {\n", node->symbol->text);
    else 
        fprintf(stderr, ") {\n");

    for (int i=0; i<MAX_SONS; ++i)
        astPrint(node->son[i], level+1);    
}

char* getSpaces(int level){

    fprintf(stderr, "level: %d.\n", level);
    int clevel = 2*level;

    char *spaces;
    spaces=malloc(level*sizeof(char)+1);
    memset(spaces,'-',level);    

    return spaces;
}

char* astToCode(AST* node, int level) {
	if(node == 0)
		return "";

	switch (node->type) {
        case AST_SYMBOL: {
            fprintf(stderr, "AST_SYMBOL\n"); 
            fprintf(stderr, "AST_SYMBOL: %s\n", node->symbol->text); 

            char* buffer = (char*)calloc( strlen(node->symbol->text) +1 + 1, sizeof(char));

            switch (node->symbol->type){
                case LIT_INT:
                case LIT_REAL:
                case LIT_CHAR:
                case TK_IDENTIFIER: sprintf(buffer, "%s", node->symbol->text); break;
                case LIT_STRING: sprintf(buffer, "\"%s\"", node->symbol->text); break;
            }
            return buffer;
            break;
        }   
        case AST_PROGRAM: {
            fprintf(stderr, "AST_PROGRAM \n"); 
            char* prog = astToCode(node->son[0],level+1);
            
            return prog;
            break;
        }
        case AST_LIST: {
            fprintf(stderr, "AST_LIST \n"); 
            char* prog = astToCode(node->son[0],level);
            
            return prog;
            break;
        }
        case AST_ELEMENT: {
            fprintf(stderr, "AST_ELEMENT\n"); 
            char* prog = astToCode(node->son[0],level);
            
            return prog;
            break;
        }
        case AST_GLOBAL_VAR: {
            fprintf(stderr, "AST_GLOBAL_VAR \n"); 
            char* name = node->symbol->text;
            char* type = astToCode(node->son[0],level);
            char* value = astToCode(node->son[1],level);
            
            char* global_var = (char*)calloc(strlen(type) + strlen(name) + strlen(value) +1, sizeof(char));
            sprintf(global_var, '%s %s %s', type, name, value);

            return global_var;
            break;
        }
        case AST_GLOBAL_VAR_ARRAY: {
            fprintf(stderr, "AST_GLOBAL_VAR_ARRAY \n"); 
            char* name = node->symbol->text;
            char* type = astToCode(node->son[0],level);
            char* value = astToCode(node->son[1],level);
            char* size = astToCode(node->son[2],level);

            
            char* global_var = (char*)calloc(strlen(type) + strlen(name) + strlen(value) + strlen(size) +5 +1, sizeof(char));

            if (values[0] != '\0')
                sprintf(global_var, '%s %s [%s] %s', type, name, size, value); 
            else 
                sprintf(global_var, '%s %s [%s]', type, name, size); 

            return global_var;
            break;
        }
        case AST_ARRAY: {
            fprintf(stderr, "AST_GLOBAL_VAR_ARRAY \n"); 
            char* value = astToCode(node->son[0],level);
            char* array = astToCode(node->son[1],level);

            char* buffer = (char*)calloc(strlen(value) + strlen(array) +1 +1, sizeof(char));
            
            if (array[0] != '\0')              
                sprintf(buffer, "%s %s", value, array); 
            else               
                sprintf(buffer, "%s", value); 

            return buffer;
            break;
        }
        case AST_FUNC: {
            fprintf(stderr, "AST_FUNC\n");
            char * header = astToCode(node->son[0],level);
            char * body = astToCode(node->son[1],level);

            char* func = (char*)calloc(7+ strlen(header) + strlen(body) +1, sizeof(char));

            return func;
            break;
        }
        case AST_HEADER: {
            fprintf(stderr, "AST_HEADER\n");
            char* type = astToCode(node->son[0],level);
            char* name = node->symbol->text;
            char* list_params = astToCode(node->son[1],level);

            char* header = (char*)calloc(8 + strlen(name) + strlen(type) + strlen(list_params) +1, sizeof(char));

            return header;
            break;
        }
        case AST_PARAMS: {
            fprintf(stderr, "AST_PARAMS\n");

            char* param = astToCode(node->son[0],level);
            char* params = astToCode(node->son[1],level);

            char* buffer = (char*)calloc(strlen(param) + strlen(params) +2 +1, sizeof(char));
            
            if (params[0] != '\0')              
                sprintf(buffer, "%s, %s", param, params); 
            else               
                sprintf(buffer, "%s", param); 
            
            return buffer;
            break;
        }
        case AST_PARAM: {
            fprintf(stderr, "AST_PARAM\n");

            char* name = node->symbol->text;
            char* type = astToCode(node->son[0],level);

            char* buffer = (char*)calloc(strlen(type) + strlen(name) +1 +1, sizeof(char));
            sprintf(buffer, "%s %s", type, name); 
            
            return buffer;
            break;
        }
        case AST_FUNC_CALL: {
            fprintf(stderr, "AST_FUNC_CALL\n");
            char* name = node->symbol->text;      
            char* list_args = astToCode(node->son[0],level);      
            
            char* buffer = (char*)calloc(strlen(name) + strlen(list_args) +2 + 1, sizeof(char));
            sprintf(buffer, "%s(%s)", name, list_args);

            return buffer;
            break;
        }   
        case AST_LIST_ARGS: {
            fprintf(stderr, "AST_LIST_ARGS\n");

            char* args = astToCode(node->son[0],level);      
            char* list_args = astToCode(node->son[1],level);      
            
            char* buffer = (char*)calloc(strlen(args) + strlen(list_args) +2 + 1, sizeof(char));
            if(list_args[0] != '\0')
                sprintf(buffer, "%s, %s", args, list_args);
            else 
                sprintf(buffer, "%s", args);

            return buffer;
            break;
        }   
        case AST_BLOCK: {
            fprintf(stderr, "AST_COMMAND_BLOCK\n");
            char* block_content = astToCode(node->son[0],level);

            char* block = (char*)calloc(strlen(block_content) +4 + 1, sizeof(char));
            sprintf(block, "{\n%s\n}", block_content);

            return block;
            break;
        }
        case AST_COMMAND_LIST: {     
            fprintf(stderr, "AST_COMMAND_LIST\n");

            char* command = astToCode(node->son[0],level);
            char* command_list = astToCode(node->son[1],level);

            char* buffer = (char*)calloc(strlen(command) +strlen(command_list) +1 + 1, sizeof(char));

            if(command_list[0] != '\0')
                sprintf(buffer, "%s %s", command, command_list);
            else
                sprintf(buffer, "%s", command);
            return buffer;
            break;
        }   
        case AST_OUTPUT: {
            fprintf(stderr, "AST_OUTPUT\n");

            char* list_elements = astToCode(node->son[0],level);
            fprintf(stderr, "AST_OUTPUT: %s\n",list_elements );

            char* buffer = (char*)calloc(6 + strlen(list_elements) + 1, sizeof(char));
            sprintf(buffer, "output %s", list_elements);

            return buffer;
            break;
        }   
        case AST_LIST_ELEMENTS: {
            fprintf(stderr, "AST_LIST_ELEMENTS\n");

            char* el = astToCode(node->son[0],level);
            char* list_elements = astToCode(node->son[1],level);

            char* buffer = (char*)calloc(strlen(el) +strlen(list_elements) +2 + 1, sizeof(char));

            if(list_elements[0] != '\0')
                sprintf(buffer, "%s, %s", el, list_elements);
            else
                sprintf(buffer, "%s", el);

            return buffer;
            break;
        }   
        case AST_RETURN: {
            fprintf(stderr, "AST_RETURN\n");
            
            char* value = astToCode(node->son[0],level);

            char* buffer = (char*)calloc(strlen(value) + 7 + 1, sizeof(char));
            sprintf(buffer, "return %s", value);
            
            return buffer;            
            break;
        }
        case AST_INPUT: {
            fprintf(stderr, "AST_INPUT\n");            
            char* type =  astToCode(node->son[0],level);

            char* buffer = (char*)calloc(strlen(type) +8 + 1, sizeof(char));
            sprintf(buffer, "input (%s)");
            
            return buffer;
            break;
        }
        case AST_ATTR: {
            fprintf(stderr, "AST_ATTRIBUITION\n");
            
            char* name = node->symbol->text;
            char* value = astToCode(node->son[0],level);

            char* attr = (char*)calloc(strlen(name) + strlen(value) + 1 + 1, sizeof(char));
            sprintf(attr, "%s=%s", name, value);
            
            return attr;            
            break;
        } 
        case AST_ATTR_ARRAY: {
            fprintf(stderr, "AST_ATTR_ARRAY\n");
            
            char* arrayElement = astToCode(node->son[0],level);
            char* value = astToCode(node->son[1],level);

            char* attr = (char*)calloc(1 + strlen(arrayElement) + strlen(value) + 1, sizeof(char));
            sprintf(attr, "%s=%s", arrayElement, value);
            
            return attr;            
            break;
        }
        case AST_ARRAY_ELEMENT: {
            fprintf(stderr, "AST_ARRAY_ELEMENT\n");
            
            char* name = node->symbol->text;
            char* size = astToCode(node->son[0],level);

            char* buffer = (char*)calloc(strlen(name) + strlen(size) +2 + 1, sizeof(char));
            sprintf(buffer, "%s[%s]", name, value);
            
            return buffer;            
            break;
        } 
        // case AST_EXPRESSION_BLOCK: {
        //     fprintf(stderr, "AST_EXPRESSION_BLOCK\n");
            
        //     char* expression = astToCode(node->son[0],level);

        //     char* buffer = (char*)calloc(strlen(expression) + 2 + 1, sizeof(char));
        //     sprintf(buffer, "(%s)", expression);
            
        //     return buffer;            
        //     break;
        // }     
        
        case AST_IF: {
            fprintf(stderr, "AST_IF \n");    

            char* condition = astToCode(node->son[0], level);         
            char* body_if = astToCode(node->son[1], level);         
            char* body_else = astToCode(node->son[2], level);    
        
            char* buffer = (char*)calloc(strlen(condition) + strlen(body_if) + strlen(body_else) +11  +1, sizeof(char));            
            
            if (body_else[0] != '\0')
                sprintf(buffer, "if(%s) %s else %s", condition, body_if, body_else); 
            else
                sprintf(buffer, "if(%s) %s", condition, body_if); 
            return buffer;
            break;            
            
        }
        case AST_LOOP: {
            fprintf(stderr, "AST_LOOP \n");    

            char* condition = astToCode(node->son[0], level);         
            char* body = astToCode(node->son[1], level);              

            char* buffer = (char*)calloc(strlen(condition) + strlen(body) + 10 +1, sizeof(char));            
                        
            sprintf(buffer, "if(%s) LOOP %s", condition, body); 
            
            return buffer;
            break;            
            
        }
        case AST_EXPRESSION: {
            fprintf(stderr, "AST_EXPRESSION_BINARY\n");            
            
            char* operator = node->symbol->text;      
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
            

            char* buffer = (char*)calloc(2 + strlen(valueLeft) + strlen(operator) + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s %s %s", valueLeft, operator, valueRight);
            
            return buffer;
            break;
        }  
        
        

        /*
            EXPRESSÕES LÓGICAS        
        */
        case AST_ADD: {
            fprintf(stderr, "AST_ADD\n");            
            
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
            

            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s+%s", valueLeft, valueRight);
            
            return buffer;
            break;
        }   
        case AST_SUB: {
            fprintf(stderr, "AST_SUB\n");            
            
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
            

            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s - %s", valueLeft, valueRight);
            
            return buffer;
            break;
        }   
        case AST_DIV: {
            fprintf(stderr, "AST_DIV\n");            
            
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
            

            char* add = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(add, "%s/%s", valueLeft, valueRight);
            
            return add;
            break;
        }   
        case AST_MULT: {
            fprintf(stderr, "AST_MULT\n");            
            
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
            

            char* add = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(add, "%s*%s", valueLeft, valueRight);
            
            return add;
            break;
        }            
        case AST_LT: {
            fprintf(stderr, "AST_LT\n");            
            
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
            

            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s<%s", valueLeft, valueRight);
            
            return buffer;
            break;
        }
        case AST_LE: {
            fprintf(stderr, "AST_LTE\n");            
        
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
        

            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s<=%s", valueLeft, valueRight);
        
            return buffer;
            break;
        
        }   
        case AST_GT: {
            fprintf(stderr, "AST_GT\n");            
        
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
        
            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s>%s", valueLeft, valueRight);
        
            return buffer;
            break;
        
        }   
        case AST_GE: {
            fprintf(stderr, "AST_GTE\n");            
        
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
        
            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s>=%s", valueLeft, valueRight);
        
            return buffer;
            break;
        
        } 
        case AST_EQ: {
            fprintf(stderr, "AST_EQ\n");            
        
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
        
            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s==%s", valueLeft, valueRight);
        
            return buffer;
            break;
        
        } 
        case AST_DIF: {
            fprintf(stderr, "AST_DIF\n");            
        
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
        
            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s!=%s", valueLeft, valueRight);
        
            return buffer;
            break;
        
        } 
        case AST_AND: {
            fprintf(stderr, "AST_AND\n");            
        
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
        
            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s&&%s", valueLeft, valueRight);
        
            return buffer;
            break;
        
        } 
        case AST_OR: {
            fprintf(stderr, "AST_OR\n");            
        
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
        
            char* buffer = (char*)calloc(1 + strlen(valueLeft) + 1 + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s||%s", valueLeft, valueRight);
        
            return buffer;
            break;
        } 
        case AST_NOT: {
            fprintf(stderr, "AST_NOT\n");            

            char* expression = astToCode(node->son[1],level);
            char* buffer = (char*)calloc(1 + strlen(expression), sizeof(char));
            sprintf(buffer, "~%s", expression);

            return buffer;
            break;
        }
        
        
        
        default: fprintf(stderr, "AST_UNKNOWN\n"); return ""; break;
        
        
    }
}

// EOF
