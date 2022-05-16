%{
    #include <stdlib.h>
    #include <string>
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
    yylval.dval = f;
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

"(" {return LP; }
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
"@" {return REF; }
"&" {return ADDR; }
[\\] {return BS; }
"=>" {return RDARROW; }
"->" {return RSARROW; }
"<-" {return LSARROW; }
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
"<<" {return LShift; }
">>" {return RShift; }

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

\'.\' {
    char c = yytext[1];
    yylval.cval = c;
    return CHAR;
}

"_"|[a-zA-Z][a-zA-Z0-9]* {
    std::string s = std::string(yytext, yyleng);
    yylval.sval = s;
    return NAME;
}

%%
int main(){
    yylex();

    return 0;
}




 
