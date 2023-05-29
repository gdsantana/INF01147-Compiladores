
%{
#include "tokens.h"

int lineCount = 1;
int running = 1;
char buffer[100];
char *string;

%}

%x LINE_COMMENT
%x MULTI_COMMENT
%x STRING

%%
"char"  { return KW_CHAR; }
"int"   { return KW_INT;}
"real"   { return KW_REAL; }
"bool"   { return KW_BOOL; }

"if"  { return KW_IF; }
"else"   { return KW_ELSE; }
"then"   { return KW_THEN; }
"loop"   { return KW_LOOP; }
"input"   { return KW_INPUT; }
"output"   { return KW_OUTPUT; }
"return"   { return KW_RETURN; }

"<="    { return OPERATOR_LE; }
">="    { return OPERATOR_GE; }
"=="    { return OPERATOR_EQ; }
"!="    { return OPERATOR_DIF; }

[-+*,;:\(\)\[\]{}/<>=] { return yytext[0]; }

[0-9]+          { hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER; }
[0-9]'.'[0-9]+  { hashInsert(yytext, LIT_INTEGER); return LIT_REAL; }
\'[a-zA-Z]\''   { hashInsert(yytext, LIT_INTEGER); return LIT_CHAR; }      
[-_a-z]+        { hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}


<STRING>\"      { 
                    *string = 0; 
                    BEGIN(INITIAL);               
                    hashInsert(buffer, LIT_STRING);      
                // printf("found '%s'\n", buf);
                    return LIT_STRING;
                } 
<STRING>"\n"    { 
                    *string = 0; 
                    lineCount++;
                    BEGIN 0;
                    return TOKEN_ERROR; 
                  } 
<STRING>.       { *string++ = *yytext; } 


"\t"
"\n"    { lineCount++; }


"\\\\"   { BEGIN(LINE_COMMENT); }
"\\\\\\" { BEGIN(MULTI_COMMENT); }
.        { return TOKEN_ERROR; }

<LINE_COMMENT>"\n" {lineCount++;} 
<LINE_COMMENT>. 

<MULTI_COMMENT>"\n" {lineCount++;}
<MULTI_COMMENT>.
<MULTI_COMMENT>"///" {  BEGIN(INITIAL) ;}

%%



#include "main.c"
#include "hash.c"

int isRunning() {
  return running;
}

int getLineCount() {
  return lineCount;
}

void initMe() {
  hashInit();
}

int yywrap() {
  running = 0;
  return 1;
}