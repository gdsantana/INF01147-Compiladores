#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
HASH_NODE *Table[HASH_SIZE];
int first_node = -1;
void hashInit(void){
    int i;
    for(i=0; i<HASH_SIZE; i++) {
        Table[i] = 0;
    }
}

int hashAddress(char *text) {
    int address = 1;
    int i;

    for (i=0; i<strlen(text); i++) {
        address = (address * text[i]) % HASH_SIZE + 1;        
    }

    return address-1;    
}

HASH_NODE *hashFind(char *text) {
    HASH_NODE *node;
    int address = hashAddress(text);

    for (node=Table[address]; node; node = node->next) {
        if (strcmp(node->text, text) == 0) {
            return node;
        }
    }

    return 0;
}

HASH_NODE *hashInsert(char *text, int type) {
    HASH_NODE *newnode;

    text = dash_replace(text);

    int address = hashAddress(text);
    
    if(first_node < 0)
        first_node = address;

    if ((newnode=hashFind(text)) != 0) {
        return newnode;
    }

    newnode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    newnode->type = type;
    newnode->text = (char*) calloc(strlen(text)+1, sizeof(char));
    strcpy(newnode->text, text);

    newnode->next = Table[address];
    Table[address] = newnode;

    return newnode;
}
HASH_NODE *hashFindLabel(char *text) {
    HASH_NODE *node;
    int address = hashAddress(text);

    for (node=Table[address]; node; node = node->next) {
        if (node->dataString && strcmp(node->dataString, text) == 0) {
            return node;
        }
    }

    return 0;
}
void hashPrint(void) {
    int i;
    HASH_NODE *node;

    for (i=0; i<HASH_SIZE; i++){
        for (node=Table[i]; node; node=node->next) {
            printf("Table[%d] has %s\n", i, node->text);
        }
    }
}

HASH_NODE* getNode(int i) {
    HASH_NODE* node; 
    // first = Table[first_node];
    node = Table[i];

    return node;
}

HASH_NODE* makeTemp(){
    static int serial = 0;

    char buffer[256] = "";

    sprintf(buffer, "_TMP-VAR_[%d]", serial++);

    return hashInsert(buffer, SYMBOL_TEMP);
}

HASH_NODE* makeLabel(){
    static int serial = 0;

    char buffer[256] = "";

    sprintf(buffer, "__LABEL[%d]", serial++);

    return hashInsert(buffer, SYMBOL_LABEL);
}
void hashPrintAsm(FILE* fout) {
    int i;
    HASH_NODE *node;

    fprintf(fout, "\t.data\n");

    for (i=0; i<HASH_SIZE; i++){
        for (node=Table[i]; node; node=node->next) {
            if(node->type == SYMBOL_LIT_INT)
                fprintf(fout, "_%s: .long\t%d\n", node->text, node->dataValue);
            if(node->type == SYMBOL_FUNCTION_ARGS || node->type == SYMBOL_VARIABLE){
                if(node->dataType == DATATYPE_CHAR)
                    fprintf(fout, "_%s: .byte\t%d\n", node->text, node->dataValue);

                if(node->dataType == DATATYPE_REAL)
                    fprintf(fout, "_%s: "
                                  "\t.long\t%d\n"
                                  "\t.long\t%s\n", node->text, node->dataValue,  node->dataString[0]?node->dataString:"0");

                if(node->dataType == DATATYPE_INT)
                    fprintf(fout, "_%s: .long\t%d\n", node->text, node->dataValue);
            }
            if(node->type == SYMBOL_TEMP) {
                if(node->dataType == DATATYPE_STRING)
                    fprintf(fout, "_%s: .string\t\"%s\"\n", node->text, dash_replace_back(node->dataString));

                if(node->dataType != DATATYPE_STRING)
                    fprintf(fout, "_%s: .long\t%d\n", node->text, node->dataValue);
            }
        }
    }
}


/*
    FUNÇÕES AUXILIARES
*/
char *dash_replace(char* text) {
    return str_replace(text, "-", "__dash__");
}

char *dash_replace_back(char* text) {
    char* temp = str_replace(text, "__dash__", "-");
    return temp;
}


// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
