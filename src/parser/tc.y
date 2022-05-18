%{
    #include <iostream>
    #include <math.h>
    #include <string>
    #include "head.hpp"
    extern int yylex();
    void yyerror(char* s);
    API context;
%}

/// types
%union {
    Int ival;
    Float fval;
    Char cval;
    char* sval;

    Stmt* stmt;
    Type* type;
    Cell* cell;
    Expr* expr;
    Oper oper;
}


%token  LP RP LB RB LC RC 
%token  SEMI COMMA COLON 
%token  ASSIGN 
%token  SELF REFS REF PTR 
%token  BS RDARROW RSARROW LSARROW
%token  BNOT LNOT 
        FADD FSUB FMUL FDIV
        ADD SUB MUL DIV
        LAND LOR LXOR LEQ GEQ LT GT
        MOD BAND BOR BXOR LSHIFT RSHIFT
        EQ NEQ ADDPTR PTRADD PTRSUB
%token  LET VAR IF ELSE WHILE BREAK CONT 
        RET DEL TYPE CHECK FUN MATCH WITH NEW
%token <ival> INT
%token <fval> FLOAT
%token <cval> CHAR
%token <sval> STRING TN EN

%type <expr> Expr I F C S Calc UnCalc BinCalc1 BinCalc2 BinCalc3 BinCalc4
%type <expr> Fun ExprFunDef
%type <oper> UnOp BinOp1 BinOp2 BinOp3 BinOp4
%type <type> Type TypeVar TypeRef TypePtr TypeArr TypeFun TypeFunArg TypeDef
%type <cell> CellVar App CellEle CellRef
%start Start
%%

Start: Type |Expr;

Type: TypeVar | TypeRef | TypePtr | TypeArr | TypeFun;
TypeVar: TN {
    $$ = context.TypeVar($1);
};

TypeRef: REF Type {
    $$ = context.TypeRef($2);
};

TypePtr: PTR Type {
    $$ = context.TypePtr($2);
};

TypeArr: Type LB INT RB {
    $$ = context.TypeArr($1, $3);
};

TypeFun: LC { context.TypeFunBeg(); } TypeFunArg RSARROW Type RC {
    $$ = context.TypeFunEnd($5);
};

TypeFunArg: 
Type { context.TypeFunArg($1);} TypeFunArg | { ; } ;

TypeDef: COLON Type{
    $$ = $2;
} | { $$ = nullptr; }



Expr: F | I | C | S | Calc | Fun;

I: INT {
    $$ = context.I($1); 
};
F: FLOAT { 
    $$ = context.F($1); 
};
C: CHAR {
    $$ = context.C($1); 
};
S: STRING {
    $$ = context.S($1); 
};

Fun: FunStart {context.ExprFunBeg();} ExprFunArgLists RDARROW ExprFunDef {
    $$ = $5;
};

FunStart: FUN | BS;

ExprFunArgLists : 
ExprFunArg ExprFunArgLists |
ExprFunRefArg ExprFunArgLists | 
{ ; };

ExprFunArg : EN TypeDef {
    context.ExprFunArg($1, $2);
};

ExprFunRefArg: REF EN TypeDef {
    context.ExprFunRefArg($2, $3);
};

//add stmt later 
ExprFunDef: Expr {
    $$ = $1;
};

Calc: UnCalc | BinCalc1; 

UnCalc:  
UnOp Expr{
    $$ = context.UnOp($1, $2);
}
UnOp :
BNOT { $$ = Oper::BNot; } |
LNOT { $$ = Oper::LNot; } |
SUB  { $$ = Oper::Neg; } |
FSUB { $$ = Oper::Neg; };

BinCalc1: 
Expr BinOp1 Expr{
    $$ = context.BinOp($1, $2, $3);
} | 
BinCalc2 {
    $$ = $1;
};
BinOp1:
BAND { $$ = Oper::BAnd; } |
BOR { $$ = Oper::BOr; } | 
LAND { $$ = Oper::LAnd; } |
LOR { $$ = Oper::LOr;} |
LXOR { $$ = Oper::LXOr; };

BinCalc2: 
Expr BinOp2 Expr{
    $$ = context.BinOp($1, $2, $3);
} | 
BinCalc3 {
    $$ = $1;
};
BinOp2: 
LT { $$ = Oper::Lt; } |
GT { $$ = Oper::Gt; } |
LEQ { $$ = Oper::Leq; } |
GEQ { $$ = Oper::Geq; } |
EQ { $$ = Oper::Eq; } |
NEQ { $$ = Oper::Neq; } | 
LSHIFT { $$ = Oper::LShift; } |
RSHIFT { $$ = Oper::RShift; };

BinCalc3: 
Expr BinOp3 Expr{
    $$ = context.BinOp($1, $2, $3);
} | 
BinCalc4 {
    $$ = $1;
};
BinOp3:
ADD { $$ = Oper::Add; } |
SUB { $$ = Oper::Sub; } |
FADD { $$ = Oper::FAdd; } |
FSUB { $$ = Oper::FSub; } |
ADDPTR { $$ = Oper::AddPtr; } |
PTRADD { $$ = Oper::PtrAdd; } |
PTRSUB { $$ = Oper::PtrSub; };

BinCalc4: 
Expr BinOp4 Expr{
    $$ = context.BinOp($1, $2, $3);
} | 
LP BinCalc1 RP {
    $$ = $2;
};
BinOp4:
MUL { $$ = Oper::Mul; } |
DIV { $$ = Oper::Div; } |
FMUL { $$ = Oper::FMul; } |
FDIV { $$ = Oper::FDiv; } |
MOD { $$ = Oper::Mod; };

%%


int main() {
    /* context.BlockBegin(); */
    yyparse();
    /* context.save(context.BlockEnd());
    context.save("tc.hex"); */
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}