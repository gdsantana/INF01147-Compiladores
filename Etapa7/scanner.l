
%{
#include "hash.h"
#include "ast.h"
#include "y.tab.h"


int lineNumber = 1;
int isrunning = 1;
char buffer[100];
char *s;

void yyerror(const char *s);  
int getLineNumber(void);
%}

%x LINE_COMMENT
%x MULTI_COMMENT
%x STRING

%%
"char"  { return KW_CHAR; }
"int"   { return KW_INT;}
"real"   { return KW_REAL; }
"bool"   { return KW_BOOL; }

"if"     { return KW_IF; }
"else"   { return KW_ELSE; }
"then"   { return KW_THEN; }
"loop"   { return KW_LOOP; }
"input"   { return KW_INPUT; }
"output"   { return KW_OUTPUT; }
"return"   { return KW_RETURN; }

"<="    { yylval.symbol = hashInsert(yytext, OPERATOR_LE); return OPERATOR_LE; }
">="    { yylval.symbol = hashInsert(yytext, OPERATOR_GE); return OPERATOR_GE; }
"=="    { yylval.symbol = hashInsert(yytext, OPERATOR_EQ); return OPERATOR_EQ; }
"!="    { yylval.symbol = hashInsert(yytext, OPERATOR_DIF); return OPERATOR_DIF; }


">"    { yylval.symbol = hashInsert(yytext, OPERATOR_GT); return OPERATOR_GT; }
"<"    { yylval.symbol = hashInsert(yytext, OPERATOR_LT); return OPERATOR_LT; }

"+"    { yylval.symbol = hashInsert(yytext, OPERATOR_ADD); return OPERATOR_ADD; }
"-"    { yylval.symbol = hashInsert(yytext, OPERATOR_SUB); return OPERATOR_SUB; }
"*"    { yylval.symbol = hashInsert(yytext, OPERATOR_MULT); return OPERATOR_MULT; }
"/"    { yylval.symbol = hashInsert(yytext, OPERATOR_DIV); return OPERATOR_DIV; }

[=,;:\(\)\[\]{}|&~] {return yytext[0];  }

[0-9]+            { yylval.symbol = hashInsert(yytext, LIT_INT); return LIT_INT; }
[0-9].[0-9]+      { yylval.symbol = hashInsert(yytext, LIT_REAL); return LIT_REAL; }
\'[-+*,;:\(\)\[\]{}/<>=a-zA-Z0-9]\'   { yylval.symbol = hashInsert(yytext, LIT_CHAR); return LIT_CHAR; }      
[._a-zA-Z]*       { yylval.symbol = hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}


[ \t\r]  { } 
"\n"  { lineNumber++; }


"\\\\"   { BEGIN(LINE_COMMENT); }
"\\\\\\" { BEGIN(MULTI_COMMENT); }

\"                { BEGIN(STRING); s = buffer; } 
.                 {return TOKEN_ERROR;}

<STRING>\\n       { *s++ = '\\'; *s++ = 'n'; } 
<STRING>\\t       { *s++ = '\\'; *s++ = 't';} 
<STRING>\\\"      { *s++ = '\"'; } 
<STRING>\"        { 
                    *s = 0; 
                    BEGIN(INITIAL);               
                    yylval.symbol = hashInsert(buffer, LIT_STRING);   
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
