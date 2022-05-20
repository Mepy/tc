## Grammar
[...]? 表示出现0~1次
[...]  表示出现0~次
[...]+ 表示出现1~次

- 大写开头的单词是非终结符，
  被建模为一个纯虚基类，其推导分支分别是其实子类
- 小写开头的表示终结符（某个正则表达式）
  被建模为一个简单类
- 双引号括起者也是终结符，其仅做关键字使用，不被建模，在AST结点中不存储

```
/* type_name and expr_name could be the same RegExp */
Stmt  ::= 
_      | ";" /* drop these */
Block  | "{" [Stmt] "}" /* scope */
       /* BlockBegin "{" 
        * BlockStmt  Stmt
        * BlockEnd   "}" 
        */
Let    |  "let" expr_name [":" Type]? "=" Expr ";"
Var    |  "let" "@" expr_name [":" Type]? "=" Expr ";"
Var    |  "var" expr_name [":" Type]? "=" Expr ";" 
If     |  "if" "(" Expr ")" Stmt ["else" Stmt]?
While  |  "while" "(" Expr )" Stmt
Break  |  "break" [integer]? ";"
       /* no integer, just break
        * exists integer n, break n while-body
        * [TODO] Cont is similar.
        */
Cont   |  "continue" [integer]? ";"
Ret    |  "return" [Expr]? ";" /* if no Expr, just fill with u0 "unit" */
Exp    |  Expr ";" /* just Expr */
Del    |  "del" Expr ";" /* Ptr T */
Asgn   |  Cell asgn Expr ";"     /* TyCk : Ref T , (Ref)? T -> T */

Alias  |  "type" type_name "=" Type ";"
ADT    |  "type" type_name "=" [ "|" expr_name [Type | "$"] ] ";"
       /* TypeDef(type_name)
        * - Alias(Type)
        * - ADT
        *   ADTBranchBegin ADTBranchType ADTBranchEnd 
        *   for "|" expr_name Type
        *   ";" -> ADT()
        */

Check  |  "check" Expr Type ";"
       ;

Type      ::=
/* Use TypeVar instead
U          |  u0  /* "Unit"   */
B          |  b1  /* "Bool"   */
C          |  c8  /* "Char"   */
I          |  i64 /* "Int"    */
F          |  f64 /* "Double" */
*/
TypeVar    |  type_name /*       */
TypeRef    |  "@" Type /* @T, Ref T */
TypePtr    |  "&" Type /* &T, Ptr T */
TypeArr    |  Type "[" integer "]" /* array */
TypeFun    |  "{" [Type]  "->" Type "}"
           ;

Cell  ::= 
CellVar    |  ["@"]? expr_name   /* TyCk : Ref T    -> Ref T */
App        |  Expr::App          /* TyCk : Ref T    -> Ref T */
           /* AppBeg AppArg ... AppArg
            * CellAppEnd() 
            */
CellVarEle |  expr_name "[" Expr "]"
CellEle    |  Cell "[" Expr "]" /* TyCk : T[N] i64 -> Ref T */
CellRef    |  "*"  Expr          /* TyCk : Ptr T    -> Ref T */
           ;

Expr  ::=
NULL   |  np      /* "nullptr" */
B      |  boolean /*  "true"  |  "false"      */
C      |  char    /*  similar to C            */
S      |  string  /* TyCk : Arr[C8, length+1] */
I      |  integer /* non-negative dec i64     */
F      |  float   /* must differ from int, like 0. or 0f */
Fun    |  ("fun" | "\") [ ["@"]? expr_name [":" Type]?] "=>" 
					( Stmt | Expr )
       /* ExprFunBeg "fun"
        * ExprFunRefArg(Name, Type) /* "@" */
        * ExprFunArg(Name, Type)    /* " " */
        * ExprFunExpr(Expr) -> Expr
        * ExprFunStmt(Stmt) -> Stmt
        */
          /* TyCk : { [@? Type] -> Typeof(Stmt::Block|Expr)  } */
App    |  ("$" | Expr) ["@"]? (" [Expr] ")" /* "$" means Self, recursively call */
       /* AppBeg(if "$" then NULL else Expr) 
        * AppForceRetRef() /* "@" */
        * AppArg [Expr] for many times
        * ExprAppEnd
        */

/*  ADT <: Expr is just the expr of a adt */
/* pattern match */
Match  |  "match" Expr "with" [ "|" expr_name [expr_name] "=>" (Stmt|Expr) ] 
          /* MatchBeg 
           * MatchBranch Beg(Name) Arg(Name) "=>" Stmt|Expr
           * MatchEnd
           */
          /* ADT -> Typeof(Stmt) 
           * branches' expr_name aka constructor should have the same ADT
           * branches' stmt should have the same Type
           */

ExprPtr    |  "&"  Cell /* address of  TyCk : Ref T -> Ptr T */
ExprVal    |  "*"  Expr /* value of    TyCk : Ptr T ->     T */
ExprRef    |  "@*" Expr
ExprVar    |  expr_name     /* TyCk : Ref? T -> T */
              /* Check Ref T? if so, fetch T, else just T */
              /* Ref Infer or Infer !! */
ExprVarRef | "@" expr_name  /* TyCk : Ref T -> Ref T */

/* Element of Array */
Arr       |  Expr "**" integer   /* TyCk : T         ->  T[N] */
          /* integer should be constant when in lexer pass */
Ele       |  Expr  "[" Expr "]"  /* TyCk : T[N], i64 ->     T */
EleRef    |  Expr "@[" Expr "]"  /* TyCk : T[N], i64 -> Ref T */
EleAddr   |  Expr "&[" Expr "]"  /* TyCk : T[N], i64 -> Ptr T */
New       |  "new" Expr
           /* TyCk : T[N] -> Ptr T */
           /* TyCk : T    -> Ptr T */

UnOp   |  unary Expr 
            /* unary operator
             * around inverse
             * - "~":bit not 
             * - "!":logical not 
             * - "-":negative sign : for I64
             * - "-." : for F64
             *   If we want to denote a neg' num, use this
             */
BinOp  |  Expr binary Expr
            /* binary operator : 
             * they have association and priority, refer that in C
             * Arithmetic, Bits or Calculate operation for int
             * "+"  "-"  "*"  "/" "%"  "&"  '|'  "^" "<<" ">>"
             * Arithmetic for float
             * "+." "-." "*." "/."
             * Logical operation for bool
             * "&&" "||"  "^^"
             * Order operation for int, int
             * "<"  ">" "<="  ">=" 
             * Equal operation for T
             * "=="  "!=" 
             * operation for Pointer
             * "+&" "&+" "&-"
             * ptr +& 1 -> ptr+1 in C
             */
       ;       
```