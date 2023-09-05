
#ifndef HASH_HEADER
#define HASH_HEADER


#define HASH_SIZE 997
#define  SYMBOL_VARIABLE            258
#define  SYMBOL_FUNC            259
#define  SYMBOL_FUNCTION_ARGS       260
#define  SYMBOL_ARRAY              261

#define  SYMBOL_LIT_INT             262
#define  SYMBOL_LIT_CHAR            263
#define  SYMBOL_STRING              264
#define  SYMBOL_LABEL               265
#define  SYMBOL_RETURN              266

#define  SYMBOL_EXPRESSION_BLOCK    267

#define SYMBOL_TEMP                 1607
#define DATATYPE_UNDEFINED       200
#define DATATYPE_INT             201
#define DATATYPE_CHAR            202
#define DATATYPE_REAL            203
#define DATATYPE_BOOL            204
#define DATATYPE_STRING          205

#include <stdio.h>
typedef struct hash_node {
    int type;
    int dataType;
    int dataValue;
    char* dataString;
    char *text;
    struct hash_node * next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);

HASH_NODE *hashFind(char *text);
HASH_NODE *hashFindLabel(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
void hashPrintAsm(FILE* fout);
HASH_NODE *getNode(int i);
HASH_NODE* makeTemp();
HASH_NODE* makeLabel();

char *dash_replace(char *text);
char *dash_replace_back(char* text);
char *str_replace(char *orig, char *rep, char *with);

#endif