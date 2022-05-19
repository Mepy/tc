%{
    #include <stdlib.h>
    #include <string>
    #include <iostream>
    #include "head.hpp"
    #include "parser.hpp"
    int col_count = 0;
    int row_count = 0;
%}

%option yylineno

%%

[0-9]+ {
    int i = atoi(yytext);
    yylval.ival = i;
    return INT;
}

[0-9]+\.[0-9]+ {
    double f = atof(yytext);
    yylval.fval = f;
    return FLOAT; 
}

[ ] {
    col_count += 1;
}

[\t] {
    col_count += 4;
}

[\n] {
    col_count = 0;
    row_count += 1; 
}

"(" { return LP;  }
")" {return RP; }
"[" {return LB; }
"]" {return RB; }
"{" {return LC; }
"}" {return RC; }
";" {return SEMI; }
"," {return COMMA; }
":" {return COLON; }
"=" {return ASSIGN; }
"$" {return SELF; }
"@*" {return REFS; }
"@" { return REF; }
"&" {return PTR; }
[\\] {return BS; }
"=>" {return RDARROW; }
"->" {return RSARROW; }
"<-" {return LSARROW; }
"**" {return ARR; }

"~" {return BNOT; }
"!" {return LNOT; }

"+." {return FADD; }
"-." {return FSUB; }
"*." {return FMUL; }
"/." {return FDIV; }

"+" {return ADD; }
"-" {return SUB; }
"*" {return MUL; }
"/" {return DIV; }

"&&" {return LAND; }
"||" {return LOR; }
"^^" {return LXOR; }
"<=" {return LEQ; }
">=" {return GEQ; }
"<" {return LT; }
">" {return GT; }

"%" {return MOD; }
"|" {return BOR; }
"^" {return BXOR; }
"<<" {return LSHIFT; }
">>" {return RSHIFT; }

"==" {return EQ; }
"!=" {return NEQ; }
"+&" {return ADDPTR; }
"&+" {return PTRADD; }
"&-" {return PTRSUB; }

"let" {return LET; }
"var" {return VAR; }
"if" {return IF; }
"else" {return ELSE; }
"while" {return WHILE; }
"break" {return BREAK; }
"continue" {return CONT; }
"return" {return RET; }
"del" {return DEL; }
"type" {return TYPE; }
"check" {return CHECK; }
"fun" {return FUN; }
"match" {return MATCH; }
"with" {return WITH; }
"new" {return NEW;}

\'.\' {
    char c = yytext[1];
    yylval.cval = c;
    return CHAR;
}

\".*\" {
    for(int i=0; i<yyleng-1; i++){
        yytext[i] = yytext[i+1];
    }
    yytext[yyleng-2] = '\0';
    yylval.sval = yytext;
    return STRING;
}

[A-Z][a-zA-Z0-9]* {
    yylval.sval = yytext;
    return TN;
}

"_"|[a-z][a-zA-Z0-9]* {
    yylval.sval = yytext;
    return EN;
}

%%

int yywrap(){
   return 1;
}





 
