
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

typedef struct hash_node {
    int type;
    int dataType;
    int dataValue;
    char *text;
    struct hash_node * next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);

HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
HASH_NODE *getNode(int i);
HASH_NODE* makeTemp();
HASH_NODE* makeLabel();


#endif