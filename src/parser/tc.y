%{
    #include <iostream>
    #include <math.h>
    #include <string>
    #include "head.hpp"
    int yylex(void);
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
%token  BS RDARROW RSARROW LSARROW ARR
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
%type <expr> ExprPtr ExprVal ExprRef ExprVar ExprVarRef Arr Ele EleRef EleAddr New
%type <expr> Fun ExprFunDef 
%type <expr> App
%type <expr> Match
%type <oper> UnOp BinOp1 BinOp2 BinOp3 BinOp4


%type <type> Type TypeVar TypeRef TypePtr TypeArr TypeFun TypeFunArg TypeDef
%type <cell> Cell CellVar CellEle CellRef
%type <stmt> Let

%start Start
%%

Start: Match; 

Let: LET EN TypeDef ASSIGN Expr SEMI {
    $$ = context.Let($2, $5, $3);
};

Type: TypeVar | TypeRef | TypePtr | TypeArr | TypeFun;
TypeVar: TN {
    printf("%s ", $1);
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

Cell: CellVar | CellEle | CellRef;

CellVar: 
REF EN { $$ = context.CellVar($2); } |
EN { $$ = context.CellVar($1); };

CellEle: 
Cell LB Expr RB { $$ = context.CellEle($1, $3); };

CellRef:
MUL Expr { $$ = context.CellRef($2); }

Expr: Fun | App | ExprVal | ExprRef | ExprVar | ExprVarRef |
Arr | Ele | EleRef | EleAddr | New | Calc | F | I | C | S ; 




I: INT {
    printf("I: %ld\n", $1);
    $$ = context.I($1); 
};

F: FLOAT { 
    printf("F: %02f\n", $1);
    $$ = context.F($1); 
};

C: CHAR {
    printf("C: %c\n", $1);
    $$ = context.C($1); 
};

S: STRING {
    printf("S: %s\n", $1);
    $$ = context.S($1); 
};

ExprPtr: PTR Cell {
    $$ = context.ExprPtr($2);
}

ExprVal: MUL Expr {
    $$ = context.ExprVal($2);
};

ExprRef: REFS Expr {
    $$ = context.ExprRef($2);
}

ExprVar: EN {
    $$ = context.ExprVar($1);
}


ExprVarRef: REF EN {
    $$ = context.ExprVarRef($2);
}

Arr: Expr ARR INT {
    $$ = context.ExprArr($1, $3);
}

Ele: Expr LB Expr RB {
    $$ = context.ExprEle($1, $3);
}

EleRef: Expr REF LB Expr RB {
    $$ = context.ExprEleRef($1, $4);
}

EleAddr: Expr PTR LB Expr RB {
    $$ = context.ExprEleAddr($1, $4);
}

New: NEW Expr {
    $$ = context.New($2);
}

// **************************Fun **************************
FunStart: FUN | BS;

ExprFunArgLists : 
EN TypeDef { 
    context.ExprFunArg($1, $2); 
} ExprFunArgLists |
REF EN TypeDef { 
    context.ExprFunRefArg($2, $3); 
} ExprFunArgLists |
{ ; };

//add stmt later 
ExprFunDef: 
LP Expr RP { $$ = context.ExprFunExpr($2); };

Fun: FunStart {context.ExprFunBeg();} ExprFunArgLists RDARROW ExprFunDef {
    $$ = $5;
};


// ************************** App **************************
AppStart:
Expr { context.AppBeg($1); } |
SELF { context.AppBeg(nullptr); };

AppRetRef:
REF { context.AppForceRetRef();} | 
{ ; };

AppArg: 
Expr { context.AppArg($1);} COMMA AppArg |
Expr { context.AppArg($1);} | 
{ ; };

App: AppStart AppRetRef LP AppArg RP { $$ = context.ExprAppEnd(); }; 

/* App: 
ExprVal { context.AppBeg($1); } AppRetRef LP AppArg RP { $$ = context.ExprAppEnd(); } |
ExprRef { context.AppBeg($1); } AppRetRef LP AppArg RP { $$ = context.ExprAppEnd(); } |
ExprVar { context.AppBeg($1); } AppRetRef LP AppArg RP { $$ = context.ExprAppEnd(); } |
ExprVarRef { context.AppBeg($1); } AppRetRef LP AppArg RP { $$ = context.ExprAppEnd(); } |
SELF { context.AppBeg(nullptr); } AppRetRef LP AppArg RP { $$ = context.ExprAppEnd(); }; */

// ************************** Match *************************
Match: MATCH Expr { context.MatchBeg($2); } WITH MatchLists{ $$ = context.MatchEnd(); }

MatchLists: MatchList MatchLists | ;
ENLists: EN { context.MatchBranchArg($1); } ENLists | ;
MatchList: BOR EN { context.MatchBranchBeg($2); } ENLists RDARROW MatchDef;

// add stmt later
MatchDef:  
LP Expr RP { context.MatchBranchExpr($2); };



// ************************** Calc **************************
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