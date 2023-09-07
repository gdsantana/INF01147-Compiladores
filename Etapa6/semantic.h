#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "ast.h"
#include "hash.h"


int SemanticErrors;
AST* rootNode;

int check_all_semantics(AST* startNode);
void check_undeclared();
void check_declarations(AST* rootNode);
void check_expressions(AST* rootNode);
void check_attribuition(AST* rootNode);
void check_flux_control(AST* rootNode);
void check_func_call(AST* rootNode);
void check_output(AST* rootNode);
void check_return(AST* rootNode);
void check_array_access(AST* node);
void check_list_args(AST* func_call_node);
int get_func_call_args_size(AST* node);
int check_return_type(AST* node, int type, int errors);

int get_args_size(char* func_name, AST* node);
void set_datatype(AST* node);
int isValidArrayIndex(AST* node);
int isNumber(AST* node);
int isInteger(AST* node);
int isLiteral(AST* node, int type);
int isVariableType(AST* node, int type);
int isFuncCallType(AST* node, int type);
int isArrayType(AST* node, int type);
int isArithmeticOp(AST* node);
int isBoolean(AST* node);
int isBooleanOp(AST* node);
int is_expression_of_type(AST* node, int type);
int is_expression_of_type_aux(AST* node, int type);
#endif
