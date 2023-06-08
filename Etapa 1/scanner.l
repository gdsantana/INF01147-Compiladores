
%{
#include "tokens.h"
#include "hash.h"

int lineNumber = 1;
int isrunning = 1;
char buffer[100];
char *s;

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

[0-9]+            { hashInsert(yytext, LIT_INT); return LIT_INT; }
[0-9].[0-9]+      { hashInsert(yytext, LIT_INT); return LIT_REAL; }
\'[-+*,;:\(\)\[\]{}/<>=a-zA-Z0-9]\'   { hashInsert(yytext, LIT_CHAR); return LIT_CHAR; }      
[._a-zA-Z]*       { hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}


[ \t\r]  { } 
"\n"  { lineNumber++; }


"\\\\"   { BEGIN(LINE_COMMENT); }
"\\\\\\" { BEGIN(MULTI_COMMENT); }

\"                { BEGIN(STRING); s = buffer; } 
.                 {return TOKEN_ERROR;}

<STRING>\\n       { *s++ = '\n'; } 
<STRING>\\t       { *s++ = '\t'; } 
<STRING>\\\"      { *s++ = '\"'; } 
<STRING>\"        { 
                    *s = 0; 
                    BEGIN(INITIAL);               
                    hashInsert(buffer, LIT_STRING);   
                    return LIT_STRING;
                  } 
<STRING>\n        { 
                    *s = 0; 
                    lineNumber++;
                    BEGIN 0;
                    return TOKEN_ERROR; 
                  } 
<STRING>.         { *s++ = *yytext; } 


<LINE_COMMENT>"\n" {lineNumber++; BEGIN(INITIAL);} 
<LINE_COMMENT>.   { }

<MULTI_COMMENT>"\n" {lineNumber++;}
<MULTI_COMMENT>.    { }
<MULTI_COMMENT>"///" { BEGIN(INITIAL) ;}

%%



#include "main.c"
#include "hash.c"

int isRunning(void) {
  return isrunning;
}

int getLineNumber(void) {
  return lineNumber;
}

void initMe() {
  hashInit();
}

int yywrap() {
  isrunning = 0;
  return 1;
}
