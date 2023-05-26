
%{
#include "tokens.h"

int lineCount = 1;
 int running = 1;

%}

%x COMMENT

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

[-+*/();,\]\[{}] { return yytext[0]; }

[0-9]+        { hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER; }
[0-9].[0-9]+  { hashInsert(yytext, LIT_INTEGER); return LIT_REAL; }
\'[a-zA-Z]\''      { hashInsert(yytext, LIT_INTEGER); return LIT_CHAR; }      






"\t"
"\n"    { lineCount++; }
.       { return TOKEN_ERROR; }


"\\*"    { }
"\\" { BEGIN(COMMENT); } //ADD MAIS UMA \ PRA COMPILAR

<COMMENT>. { }
<COMMENT>"\n" { lineCount++; }
<COMMENT>"///" { BEGIN(INITIAL); }

%%





int main(){
    yylex();
}

int yywrap() {
    return 1;
}