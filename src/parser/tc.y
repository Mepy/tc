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
%token  ASSIGN ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN FADDASSIGN FSUBASSIGN FMULASSIGN FDIVASSIGN
%token  SELF REFS REFLB REFLP PTRLB REF PTR BS RDARROW RSARROW ARR
%token  BNOT LNOT 
        FADD FSUB FMUL FDIV ADD SUB MUL DIV
        LAND LOR LXOR LEQ GEQ LT GT
        MOD BAND BOR BXOR LSHIFT RSHIFT
        EQ NEQ ADDPTR PTRADD PTRSUB
%token  LET IF ELSE WHILE BREAK CONT RET DEL _TYPE CHECK FUN MATCH WITH NEW
%token <ival> INT
%token <fval> FLOAT
%token <cval> CHAR
%token <sval> STRING TN EN

%type <expr> Expr I F C S Calc UnCalc BinCalc1 BinCalc2 BinCalc3 BinCalc4
%type <expr> ExprPtr ExprVal ExprRef ExprVar ExprVarRef Arr Ele EleRef EleAddr New
%type <expr> Fun ExprFunDef 
%type <expr> App
%type <expr> Match
%type <oper> UnOp BinOp1 BinOp2 BinOp3 BinOp4 AssignOp

%type <type> Type TypeVar TypeRef TypePtr TypeArr TypeFun TypeFunArg TypeDef 
%type <cell> Cell CellVar CellEle CellRef CellVarEle
%type <stmt> Stmt Empty Block Let Var If While Break Cont Ret Del Asgn NewType ADT Alias Check

%left ADD SUB MUL DIV FADD FSUB FMUL FDIV MOD
%left LAND LOR LXOR BOR BXOR  
%left LSHIFT RSHIFT
%left LEQ GEQ LT GT EQ NEQ
%left ADDPTR PTRADD PTRSUB
%right BNOT LNOT 

%start Start
%%

Start: BlockStmtList; 

Stmt: 
Empty   | 
Block   | 
Let     | 
Var     | 
If      | 
While   | 
Break   | 
Cont    | 
Del     | 
Asgn    | 
Ret     |
NewType |
Check;



Empty: SEMI { $$ = context.Empty(); };

Block: 
LC { context.BlockBegin();} BlockStmtList RC { $$ = context.BlockEnd(); };

BlockStmtList: 
Stmt { context.BlockStmt($1); } BlockStmtList | 
{ ; } ;

Let: 
LET EN TypeDef ASSIGN Expr SEMI { $$ = context.Let($2, $5, $3); };

Var: 
LET REF EN TypeDef ASSIGN Expr SEMI { $$ = context.Var($3, $6, $4); };

If: 
IF LP Expr RP Stmt { $$ = context.If($3, $5, nullptr); } |
IF LP Expr RP Stmt ELSE Stmt { $$ = context.If($3, $5, $7); };

While:
WHILE {context.WhileBeg(); } 
LP Expr RP Stmt { $$ = context.While($4, $6); };

Break: 
BREAK INT SEMI { $$ = context.Break($2); } |
BREAK SEMI { $$ = context.Break(); };

Cont:
CONT INT SEMI { $$ = context.Cont($2); } |
CONT SEMI { $$ = context.Cont(); };

Ret:
RET Expr SEMI { $$ = context.Ret($2); } |
RET SEMI { $$ = context.Ret(); };
/* 
Exp:
Expr SEMI { $$ = context.Exp($1); }; */

Del:
DEL Expr SEMI { $$ = context.Del($2); };

Asgn: Cell AssignOp Expr SEMI { $$ = context.Asgn($1, $2, $3); }
AssignOp:
ASSIGN { $$ = Oper::Undefined; } |
ADDASSIGN { $$ = Oper::Add; } |
SUBASSIGN { $$ = Oper::Sub; } |
MULASSIGN { $$ = Oper::Mul; } |
DIVASSIGN { $$ = Oper::Div; } |
FADDASSIGN { $$ = Oper::FAdd; } |
FSUBASSIGN { $$ = Oper::FSub; } |
FMULASSIGN { $$ = Oper::FMul; } |
FDIVASSIGN { $$ = Oper::FDiv; } |
MODASSIGN { $$ = Oper::Mod; };

NewType: 
NewTypeDef Alias { $$ = $2; } |
NewTypeDef ADT { $$ = $2; };

NewTypeDef: _TYPE TN { context.TypeDef($2); } ASSIGN;

Alias: 
Type SEMI { $$ = context.Alias($1); };

ADT: 
ADTLists SEMI { $$ = context.ADT(); };

ADTLists: 
ADTList ADTLists | 
{ ; };

ADTList : 
BOR EN { context.ADTBranchBegin($2); } TypeLists { context.ADTBranchEnd(); };

TypeLists: 
Type TypeLists { context.ADTBranchType($1); } |
SELF TypeLists { context.ADTBranchType();   } |
{ ; }

Check: 
CHECK Expr Type SEMI { $$ = context.Check($2, $3); }

Type: 
TypeVar | 
TypeRef | 
TypePtr | 
TypeArr | 
TypeFun;

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

Cell: 
CellVar | 
CellVarEle |
CellEle | 
CellRef;

CellVar: 
REF EN { $$ = context.CellVar($2); } |
EN { $$ = context.CellVar($1); };

CellVarEle : EN LB Expr RB { $$ = context.CellVarEle($1, $3); };

CellEle: 
Cell LB Expr RB { $$ = context.CellEle($1, $3); };

CellRef:
MUL Expr { $$ = context.CellRef($2); }

Expr: 
Fun         | 
Match       | 
ExprPtr     | 
ExprVal     | 
ExprRef     |  
ExprVar     | 
ExprVarRef  | 
Arr         | 
Ele         |  
EleRef      |   
EleAddr     |  
New         | 
Calc        | 
App         | 
F           | 
I           | 
C           |
S; 

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

Arr: Expr ARR Expr {
    $$ = context.ExprArr($1, $3);
}

Ele: Expr LB Expr RB {
    $$ = context.ExprEle($1, $3);
}

EleRef: Expr REFLB Expr RB {
    $$ = context.ExprEleRef($1, $3);
}

EleAddr: Expr PTRLB Expr RB {
    $$ = context.ExprEleAddr($1, $3);
}

New: 
NEW Expr ARR Expr { $$ = context.New($2); }


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
Stmt { $$ = context.ExprFunStmt($1); };

FunFront : FunStart {context.ExprFunBeg();} ExprFunArgLists RDARROW { context.ExprFunPre(); } 
    ;
Fun: FunFront ExprFunDef {
    $$ = $2;
};


// ************************** App **************************
AppStart:
Expr { context.AppBeg($1); } |
SELF { context.AppBeg(nullptr); };

AppArg: 
Expr { context.AppArg($1);} COMMA AppArg |
Expr { context.AppArg($1);} | 
{ ; };

App: 
AppStart LP AppArg RP { $$ = context.ExprAppEnd(); } |
AppStart REFLP {context.AppForceRetRef();} AppArg RP { $$ = context.ExprAppEnd(); };

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
Stmt { context.MatchBranchStmt($1); };


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
Expr BinOp1 Expr {
    $$ = context.BinOp($1, $2, $3);
} | 
BinCalc2 {
    $$ = $1;
};
BinOp1:
BAND { $$ = Oper::BAnd; } |
BOR { $$ = Oper::BOr; } | 
BXOR { $$ = Oper::BXOr;} |
LAND { $$ = Oper::LAnd; } |
LOR { $$ = Oper::LOr;} |
LXOR { $$ = Oper::LXOr; };

BinCalc2: 
Expr BinOp2 Expr {
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
Expr BinOp3 Expr {
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
Expr BinOp4 Expr {
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
    try{
        context.BlockBegin();
        yyparse();
        context.save(context.BlockEnd()); 
        context.save("tc.hex"); 
    }
    catch(const char *s)
    {
        printf("%s\n", s);
    }
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}