
%{
#include "tokens.h"

%}





%%

"int" {return KW_INT}



int main(){
    yylex();
}

int yywrap() {
    return 1;
}