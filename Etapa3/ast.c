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
        case AST_SYMBOL:        fprintf(stderr, "AST_SYMBOL"); break;        
        case AST_PROGRAM:       fprintf(stderr, "AST_PROGRAM"); break;

        case AST_EXPRESSION_BINARY:          fprintf(stderr, "AST_EXPRESSION_BINARY"); break;
        
        case AST_READ:          fprintf(stderr, "AST_READ"); break;
        case AST_ADD:           fprintf(stderr, "AST_ADD"); break;
        case AST_SUB:           fprintf(stderr, "AST_SUB"); break;
        case AST_MULT:          fprintf(stderr, "AST_MULT"); break;
        case AST_DIV:           fprintf(stderr, "AST_DIV"); break;

        case AST_LT:            fprintf(stderr, "AST_LT"); break;
        case AST_LTE:           fprintf(stderr, "AST_LTE"); break;
        case AST_GT:            fprintf(stderr, "AST_GT"); break;
        case AST_GTE:           fprintf(stderr, "AST_GTE"); break;
        case AST_EQ:            fprintf(stderr, "AST_EQ"); break;
        case AST_DIF:           fprintf(stderr, "AST_DIF"); break;

        case AST_COMMAND:       fprintf(stderr, "AST_COMMAND"); break;
        case AST_COMMAND_BLOCK: fprintf(stderr, "AST_COMMAND_BLOCK"); break;
        case AST_FLUX_CONTROL:  fprintf(stderr, "AST_FLUX_CONTROL"); break;
        case AST_PRINT:             fprintf(stderr, "AST_PRINT"); break;
        case AST_PRINT_REST:        fprintf(stderr, "AST_PRINT_REST"); break;
        case AST_RETURN:        fprintf(stderr, "AST_RETURN"); break;
        case AST_ATTRIBUITION:  fprintf(stderr, "AST_ATTRIBUITION"); break;
        
        case AST_LABEL:             fprintf(stderr, "AST_LABEL"); break;
        case AST_EXPRESSION_BLOCK:      fprintf(stderr, "AST_EXPRESSION_BLOCK"); break;

        case AST_COMMAND_LIST:       fprintf(stderr, "AST_COMMAND_LIST"); break;
        
        case AST_FLUX_CONTROLL_IF:       fprintf(stderr, "AST_FLUX_CONTROLL_IF"); break;
        case AST_FLUX_CONTROLL_WHILE:    fprintf(stderr, "AST_FLUX_CONTROLL_WHILE"); break;
        case AST_FLUX_CONTROLL_GOTO:     fprintf(stderr, "AST_FLUX_CONTROLL_GOTO"); break;

        case AST_DECLARATION:                   fprintf(stderr, "AST_DECLARATION"); break;
        case AST_DECLARATION_LIST:              fprintf(stderr, "AST_DECLARATION_LIST"); break;
        
        case AST_DECLARATION_FUNCTION:                  fprintf(stderr, "AST_DECLARATION_FUNCTION"); break;
        case AST_DECLARATION_FUNCTION_INT:              fprintf(stderr, "AST_DECLARATION_FUNCTION_INT"); break;
        case AST_DECLARATION_FUNCTION_CHAR:             fprintf(stderr, "AST_DECLARATION_FUNCTION_CHAR"); break;
        case AST_DECLARATION_FUNCTION_FLOAT:            fprintf(stderr, "AST_DECLARATION_FUNCTION_FLOAT"); break;

        case AST_DECLARATION_FUNCTION_ARGS_INT:             fprintf(stderr, "AST_DECLARATION_FUNCTION_ARGS_INT"); break;
        case AST_DECLARATION_FUNCTION_ARGS_CHAR:            fprintf(stderr, "AST_DECLARATION_FUNCTION_ARGS_CHAR"); break;
        case AST_DECLARATION_FUNCTION_ARGS_FLOAT:           fprintf(stderr, "AST_DECLARATION_FUNCTION_ARGS_FLOAT"); break;
        case AST_DECLARATION_FUNCTION_ARGS_OR_EMPTY:        fprintf(stderr, "AST_DECLARATION_FUNCTION_ARGS_OR_EMPTY"); break;
        case AST_DECLARATION_FUNCTION_BODY:                 fprintf(stderr, "AST_DECLARATION_FUNCTION_BODY"); break;
        
        case AST_FUNCTION_CALL:                     fprintf(stderr, "AST_FUNCTION_CALL"); break;
        case AST_FUNCTION_CALL_ARGS:                fprintf(stderr, "AST_FUNCTION_CALL_ARGS"); break;
        

        case AST_DECLARATION_GLOBAL_INT:             fprintf(stderr, "AST_DECLARATION_GLOBAL_INT"); break;
        case AST_DECLARATION_GLOBAL_ARRAY_INT:       fprintf(stderr, "AST_DECLARATION_GLOBAL_ARRAY_INT"); break;

        case AST_DECLARATION_GLOBAL_CHAR:               fprintf(stderr, "AST_DECLARATION_GLOBAL_CHAR"); break;
        case AST_DECLARATION_GLOBAL_ARRAY_CHAR:         fprintf(stderr, "AST_DECLARATION_GLOBAL_ARRAY_CHAR"); break;

        case AST_DECLARATION_GLOBAL_FLOAT:             fprintf(stderr, "AST_DECLARATION_GLOBAL_FLOAT"); break;
        case AST_DECLARATION_GLOBAL_ARRAY_FLOAT:       fprintf(stderr, "AST_DECLARATION_GLOBAL_ARRAY_FLOAT"); break;

        case AST_ARRAY_VAL:                 fprintf(stderr, "AST_ARRAY_VAL"); break;
        case AST_ARRAY_ELEMENT:             fprintf(stderr, "AST_ARRAY_ELEMENT"); break;
        case AST_ARRAY_ATTRIBUITION:        fprintf(stderr, "AST_ARRAY_ATTRIBUITION"); break;

                

    
        default: fprintf(stderr, " \n\n\n ------------>>>> AST_UNKNOWN [%d] <<<<------------ \n\n\n", node->type); break;
    }

    if (node->symbol != 0) 
        fprintf(stderr, ", %s) {\n", node->symbol->text);
    else 
        fprintf(stderr, ") {\n");

    for (int i=0; i<MAX_SONS; ++i)
        astPrint(node->son[i], level+1);    

    // for(int i=0; i<level; i++) 
    //     fprintf(stderr, "  ");
    
    // fprintf(stderr, "}\n");
    
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

            char* buffer = (char*)calloc(1 + strlen(node->symbol->text) + 1, sizeof(char));

            switch (node->symbol->type){
                case LIT_INTEGER:
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
        
        case AST_READ: {
            fprintf(stderr, "AST_READ\n");            
            
            char* buffer = (char*)calloc(4 + 1, sizeof(char));
            sprintf(buffer, "read");
            
            return buffer;
            break;
        }   
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
        case AST_LTE: {
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
        case AST_GTE: {
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

        case AST_EXPRESSION_BINARY: {
            fprintf(stderr, "AST_EXPRESSION_BINARY\n");            
            
            char* operator = node->symbol->text;      
            char* valueLeft = astToCode(node->son[0],level);            
            char* valueRight = astToCode(node->son[1],level);
            

            char* buffer = (char*)calloc(2 + strlen(valueLeft) + strlen(operator) + strlen(valueRight) + 1, sizeof(char));
            sprintf(buffer, "%s %s %s", valueLeft, operator, valueRight);
            
            return buffer;
            break;
        }   

        case AST_COMMAND_BLOCK: {
            fprintf(stderr, "AST_COMMAND_BLOCK\n");
            char* block_content = astToCode(node->son[0],level);

            char* block = (char*)calloc(4 + strlen(block_content) + 1, sizeof(char));
            sprintf(block, "{\n%s\n}", block_content);

            return block;
            break;
        }   
        case AST_PRINT: {
            fprintf(stderr, "AST_PRINT\n");

            char* stringContent = astToCode(node->son[0],level);
            fprintf(stderr, "AST_PRINT stringContent: %s\n",stringContent );

            char* buffer = (char*)calloc(6 + strlen(stringContent) + 1, sizeof(char));
            sprintf(buffer, "print %s", stringContent);

            return buffer;
            break;
        }   
        case AST_PRINT_REST: {
            fprintf(stderr, "AST_PRINT_REST\n");

            char* stringContent1 = astToCode(node->son[0],level);
            char* stringContent2 = astToCode(node->son[1],level);
            char* stringContent3 = astToCode(node->son[2],level);
            fprintf(stderr, "AST_PRINT_REST stringContent1: %s\n",stringContent1 );
            fprintf(stderr, "AST_PRINT_REST stringContent2: %s\n",stringContent2 );
            fprintf(stderr, "AST_PRINT_REST stringContent3: %s\n",stringContent3 );

            char* buffer = (char*)calloc(5 + strlen(stringContent1) + strlen(stringContent2) + strlen(stringContent3) + 1, sizeof(char));

            if (stringContent3[0] != '\0')
                sprintf(buffer, "%s, %s, %s", stringContent1, stringContent2, stringContent3);
            else if (stringContent2[0] != '\0')
                sprintf(buffer, "%s, %s", stringContent1, stringContent2);
            else 
                sprintf(buffer, "%s", stringContent1);
            
            return buffer;
            break;
        }   
        case AST_ATTRIBUITION: {
            fprintf(stderr, "AST_ATTRIBUITION\n");
            
            char* varName = node->symbol->text;
            char* value = astToCode(node->son[0],level);

            char* attribuition = (char*)calloc(1 + strlen(varName) + strlen(value) + 1, sizeof(char));
            sprintf(attribuition, "%s=%s", varName, value);
            
            return attribuition;            
            break;
        }     
        case AST_RETURN: {
            fprintf(stderr, "AST_RETURN\n");
            
            char* value = astToCode(node->son[0],level);

            char* buffer = (char*)calloc(7 + strlen(value) + 1, sizeof(char));
            sprintf(buffer, "return %s", value);
            
            return buffer;            
            break;
        }     
         
        case AST_LABEL: {
            fprintf(stderr, "AST_LABEL\n");
            
            char* label = node->symbol->text;

            char* buffer = (char*)calloc(1 + strlen(label) + 1, sizeof(char));
            sprintf(buffer, "%s:", label);
            
            return buffer;            
            break;
        }     
        case AST_EXPRESSION_BLOCK: {
            fprintf(stderr, "AST_EXPRESSION_BLOCK\n");
            
            char* expression = astToCode(node->son[0],level);

            char* buffer = (char*)calloc(2 + strlen(expression) + 1, sizeof(char));
            sprintf(buffer, "(%s)", expression);
            
            return buffer;            
            break;
        }     
        
        case AST_COMMAND_LIST: {                        
            fprintf(stderr, "AST_COMMAND_LIST\n");
            
            char* cmd = astToCode(node->son[0],level);
            char* cmdListRest = astToCode(node->son[1],level);
                        
            char* buffer = (char*)calloc(2 + strlen(cmd) + strlen(cmdListRest) + 1, sizeof(char));     

            if (node->son[0] != 0)
                if (node->son[0]->type == AST_LABEL)
                    sprintf(buffer, "%s \n%s", cmd, cmdListRest);
                else 
                    sprintf(buffer, "%s;\n%s", cmd, cmdListRest);
            else      
                sprintf(buffer, ";\n%s", cmdListRest);
                          
            

            return buffer;            
            break;
        }   
        
        case AST_FLUX_CONTROLL_IF: {
            fprintf(stderr, "AST_FLUX_CONTROLL_IF \n");    

            char* condition = astToCode(node->son[0], level);         
            char* body_if = astToCode(node->son[1], level);         
            char* body_else = astToCode(node->son[2], level);    
            
            fprintf(stderr, "condition: %s body_if: %s body_else:%s\n\n.", condition, body_if, body_else);        

            char* buffer = (char*)calloc(15 + strlen(condition) + strlen(body_if) + strlen(body_else) +1, sizeof(char));            
            
            if (body_else[0] != '\0')
                sprintf(buffer, "if %s then %s else %s", condition, body_if, body_else); 
            else
                sprintf(buffer, "if %s then %s", condition, body_if); 
            return buffer;
            break;            
            
        }
        case AST_FLUX_CONTROLL_WHILE: {
            fprintf(stderr, "AST_FLUX_CONTROLL_WHILE \n");    

            char* condition = astToCode(node->son[0], level);         
            char* body = astToCode(node->son[1], level);              

            char* buffer = (char*)calloc(7 + strlen(condition) + strlen(body) +1, sizeof(char));            
                        
            sprintf(buffer, "while %s %s", condition, body); 
            
            return buffer;
            break;            
            
        }
        case AST_FLUX_CONTROLL_GOTO: {
            fprintf(stderr, "AST_FLUX_CONTROLL_GOTO \n");    

            char* label = node->symbol->text;       
            
            char* buffer = (char*)calloc(5 + strlen(label) +1, sizeof(char));            
                        
            sprintf(buffer, "goto %s", label); 
            
            return buffer;
            break;            
            
        }
        
        case AST_DECLARATION_LIST: {
            fprintf(stderr, "AST_DECLARATION_LIST \n");    

            char* left = astToCode(node->son[0], level);         
            char* right = astToCode(node->son[1], level);         

            char* declaration_list = (char*)calloc(1 + strlen(left) + strlen(right) +1, sizeof(char));            

            sprintf(declaration_list, "%s\n%s", left, right); 

            return declaration_list;
            break;            
        }
 
        case AST_DECLARATION_FUNCTION_INT: {
            fprintf(stderr, "AST_DECLARATION_FUNCTION_INT \n"); 
            
            char* args = astToCode(node->son[0],level);
            char* body = astToCode(node->son[1],level);
            
            char* fn_name = node->symbol->text;
            char* fn_declaration = (char*)calloc(7+ strlen(fn_name) + strlen(args) + strlen(body) +1, sizeof(char));            
                        
            sprintf(fn_declaration, "int %s(%s)%s", fn_name, args, body); 
            
            return fn_declaration;
            break;
        }   
        case AST_DECLARATION_FUNCTION_CHAR: {
            fprintf(stderr, "AST_DECLARATION_FUNCTION_CHAR \n"); 
            
            char* args = astToCode(node->son[0],level);
            char* body = astToCode(node->son[1],level);

            char* fn_name = node->symbol->text;
            char* fn_declaration = (char*)calloc(8 + strlen(fn_name) + strlen(args) + strlen(body) +1, sizeof(char));            
                        
            sprintf(fn_declaration, "char %s(%s)%s", fn_name, args, body); 
            
            return fn_declaration;
            break;
        }     
        case AST_DECLARATION_FUNCTION_FLOAT: {
            fprintf(stderr, "AST_DECLARATION_FUNCTION_FLOAT \n"); 
            
            char* args = astToCode(node->son[0],level);
            char* body = astToCode(node->son[1],level);

            char* fn_declaration = (char*)calloc(9 + strlen(node->symbol->text) + strlen(args) + strlen(body) +1, sizeof(char));            
            char* fn_name = node->symbol->text;
            
            sprintf(fn_declaration, "float %s(%s)%s", fn_name, args, body); 
            
            return fn_declaration;
            break;
        }   
        
        case AST_DECLARATION_FUNCTION_ARGS_OR_EMPTY: {
            fprintf(stderr, "AST_DECLARATION_FUNCTION_ARGS_OR_EMPTY\n");
            
            char* args = astToCode(node->son[0],level);
            return args;

            break;
        }   
        case AST_DECLARATION_FUNCTION_ARGS_INT: {
            fprintf(stderr, "AST_DECLARATION_FUNCTION_ARGS_INT\n");
            
            char* fn_args_rest = astToCode(node->son[0],level);
            
            char* fn_args = (char*)calloc(4 + strlen(node->symbol->text) + strlen(fn_args_rest) +1, sizeof(char));
            
            if (fn_args_rest[0] != '\0') {                
                sprintf(fn_args, "int %s, %s", node->symbol->text, fn_args_rest); 
            } else {                
                sprintf(fn_args, "int %s", node->symbol->text); 
            }
                        
            return fn_args;            
            break;
        }   
        case AST_DECLARATION_FUNCTION_ARGS_CHAR: {
            fprintf(stderr, "AST_DECLARATION_FUNCTION_ARGS_CHAR\n");
            
            char* fn_args_rest = astToCode(node->son[0],level);
            
            char* fn_args = (char*)calloc(5 + strlen(node->symbol->text) + strlen(fn_args_rest) +1, sizeof(char));
            
            if (fn_args_rest[0] != '\0') {                
                sprintf(fn_args, "char %s, %s", node->symbol->text, fn_args_rest); 
            } else {                
                sprintf(fn_args, "char %s", node->symbol->text); 
            }
                        
            return fn_args;            
            break;
        }   
        case AST_DECLARATION_FUNCTION_ARGS_FLOAT: {
            fprintf(stderr, "AST_DECLARATION_FUNCTION_ARGS_FLOAT\n");
            
            char* fn_args_rest = astToCode(node->son[0],level);
            
            char* fn_args = (char*)calloc(6 + strlen(node->symbol->text) + strlen(fn_args_rest) +1, sizeof(char));
            
            if (fn_args_rest[0] != '\0') {                
                sprintf(fn_args, "float %s, %s", node->symbol->text, fn_args_rest); 
            } else {                
                sprintf(fn_args, "float %s", node->symbol->text); 
            }
                        
            return fn_args;            
            break;
        }   
        
        case AST_DECLARATION_FUNCTION_BODY: {
            fprintf(stderr, "AST_DECLARATION_FUNCTION_BODY\n");
            char* body = astToCode(node->son[0],level);      
            
            char* buffer = (char*)calloc(strlen(body) + 1, sizeof(char));
            sprintf(buffer, "%s", body);

            return buffer;
            break;
        }   
        case AST_FUNCTION_CALL: {
            fprintf(stderr, "AST_FUNCTION_CALL\n");
            char* name = node->symbol->text;      
            char* args = astToCode(node->son[0],level);      
            
            char* buffer = (char*)calloc(2 + strlen(name) + strlen(args) + 1, sizeof(char));
            sprintf(buffer, "%s(%s)", name, args);

            return buffer;
            break;
        }   
        case AST_FUNCTION_CALL_ARGS: {
            fprintf(stderr, "AST_FUNCTION_CALL_ARGS\n");
            char* args = astToCode(node->son[0],level);      
            char* args_rest = astToCode(node->son[1],level);      
            
            char* buffer = (char*)calloc(2 + strlen(args) + strlen(args_rest) + 1, sizeof(char));
            if(args_rest[0] != '\0')
                sprintf(buffer, "%s, %s", args, args_rest);
            else 
                sprintf(buffer, "%s", args);

            return buffer;
            break;
        }   
        
        case AST_DECLARATION_GLOBAL_INT: {
            fprintf(stderr, "AST_DECLARATION_GLOBAL_INT \n");    

            char* name = node->symbol->text;         
            char* value = astToCode(node->son[0], level);         

            char* declaration_global = (char*)calloc(7 + strlen(name) + strlen(value) +1, sizeof(char));            

            sprintf(declaration_global, "int %s: %s;", name, value); 

            return declaration_global;
            break;            
        }
        case AST_DECLARATION_GLOBAL_CHAR: {
            fprintf(stderr, "AST_DECLARATION_GLOBAL_CHAR \n");    

            char* name = node->symbol->text;         
            char* value = astToCode(node->son[0], level);         

            char* declaration_global = (char*)calloc(8 + strlen(name) + strlen(value) +1, sizeof(char));            

            sprintf(declaration_global, "char %s: %s;", name, value); 

            return declaration_global;
            break;            
        }
        case AST_DECLARATION_GLOBAL_FLOAT: {
            fprintf(stderr, "AST_DECLARATION_GLOBAL_FLOAT \n");    

            char* name = node->symbol->text;         
            char* value1 = astToCode(node->son[0], level);         
            char* value2 = astToCode(node->son[1], level);         

            char* declaration_global = (char*)calloc(9 + strlen(name) + strlen(value1) + strlen(value2) +1, sizeof(char));            

            sprintf(declaration_global, "float %s: %s/%s;", name, value1, value2); 

            return declaration_global;
            break;            
        }
        
        case AST_DECLARATION_GLOBAL_ARRAY_INT: {
            fprintf(stderr, "AST_DECLARATION_GLOBAL_ARRAY_INT \n");    

            char* name = node->symbol->text;         
            char* size = astToCode(node->son[0], level);      

            char* values = astToCode(node->son[1], level);      
            fprintf(stderr, "values: %s\n", values);

            char* declaration_global = (char*)calloc(9 + strlen(name) + strlen(size) + strlen(values) +1, sizeof(char));            

            if (values[0] != '\0')
                sprintf(declaration_global, "int %s[%s]: %s;", name, size, values); 
            else 
                sprintf(declaration_global, "int %s[%s];", name, size); 


            return declaration_global;
            break;            
        }
        case AST_DECLARATION_GLOBAL_ARRAY_CHAR: {
            fprintf(stderr, "AST_DECLARATION_GLOBAL_ARRAY_CHAR \n");    

            char* name = node->symbol->text;         
            char* size = astToCode(node->son[0], level);      

            char* values = astToCode(node->son[1], level);      
            fprintf(stderr, "values: %s\n", values);

            char* declaration_global = (char*)calloc(9 + strlen(name) + strlen(size) + strlen(values) +1, sizeof(char));            

            if (values[0] != '\0')
                sprintf(declaration_global, "char %s[%s]: %s;", name, size, values); 
            else 
                sprintf(declaration_global, "char %s[%s];", name, size); 


            return declaration_global;
            break;            
        }
        case AST_DECLARATION_GLOBAL_ARRAY_FLOAT: {
            fprintf(stderr, "AST_DECLARATION_GLOBAL_ARRAY_FLOAT \n");    

            char* name = node->symbol->text;         
            char* size = astToCode(node->son[0], level);      

            char* declaration_global = (char*)calloc(9 + strlen(name) + strlen(size) +1, sizeof(char));           
            
            sprintf(declaration_global, "float %s[%s];", name, size); 

            return declaration_global;
            break;            
        }

        case AST_ARRAY_VAL: {
            fprintf(stderr, "AST_ARRAY_VAL\n");
            
            char* arr_val = node->symbol->text;
            char* arr_val_rest = astToCode(node->son[0],level);
            
            char* buffer = (char*)calloc(1 + strlen(arr_val) + strlen(arr_val_rest) +1, sizeof(char));
            
            if (arr_val_rest[0] != '\0') {                
                sprintf(buffer, "%s %s", arr_val, arr_val_rest); 
            } else {                
                sprintf(buffer, "%s", arr_val); 
            }
                        
            return buffer;            
            break;
        }   
        case AST_ARRAY_ATTRIBUITION: {
            fprintf(stderr, "AST_ARRAY_ATTRIBUITION\n");
            
            char* arrayElement = astToCode(node->son[0],level);
            char* value = astToCode(node->son[1],level);

            char* attribuition = (char*)calloc(1 + strlen(arrayElement) + strlen(value) + 1, sizeof(char));
            sprintf(attribuition, "%s=%s", arrayElement, value);
            
            return attribuition;            
            break;
        }
        case AST_ARRAY_ELEMENT: {
            fprintf(stderr, "AST_ARRAY_ELEMENT\n");
            
            char* varName = node->symbol->text;
            char* value = astToCode(node->son[0],level);

            char* buffer = (char*)calloc(1 + strlen(varName) + strlen(value) + 1, sizeof(char));
            sprintf(buffer, "%s[%s]", varName, value);
            
            return buffer;            
            break;
        }        
        
        
        
        
        default: fprintf(stderr, "AST_UNKNOWN\n"); return ""; break;
        
        
    }
}

// EOF
