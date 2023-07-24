#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "ast.h"
#include "hash.h"


int SemanticErrors;
AST* rootNode;

int check_all_semantics(AST* startNode);
void check_declarations(AST* rootNode);
void check_expressions(AST* rootNode);
void check_attribuition(AST* rootNode);
void check_func_call(AST* rootNode);
void check_flux_control(AST* rootNode);
void check_output(AST* rootNode);
void check_return(AST* rootNode);

#endif
