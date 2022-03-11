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
Expr   |  Expr ";" /* just Expr */
Block  | "{" [Stmt] "}" /* scope */
Let    |  "let" expr_name [":" Type]? "=" Expr ";"
/* Var :  "let" "@" expr_name [":" Type]? "=" Expr ";" */
Var    |  "var" expr_name [":" Type]? "=" Expr ";" 
ADT    |  "type" type_name "=" Type ";"
If     |  "if" "(" Expr ")" Stmt ["else" Stmt]?
While  |  "while" "(" Expr )" Stmt
Break  |  "break" ";"
Cont   |  "continue" ";"
Ret    |  "return" [Expr]? ";" /* if no Expr, just fill with u0 "unit" */
       ;
Type  ::=
Infer  |  "_" /* type need to infer, 
               * in fact this grammar is less frequently used. 
               */
U0     |  u0  /* "unit"  */
B1     |  b1  /* "bool"  */
C8     |  c8  /* "char"  */
I64    |  i64 /* "int"   */
F64    |  f64 /* "double */
Var    |  type_name /*       */
Ref    |  "@" Type /* @T, Ref T */
Ptr    |  "&" Type /* &T, Ptr T */
Arr    |  Type "[" integer "]" /* array */
Fun    |  "{" [Type]  "->" Type "}"
ADT    |  [ "|" expr_name [Type] ]
       ;

Cell  ::= 
Var    |  ["@"]? expr_name   /* TyCk : Ref T    -> Ref T */
App    |  Expr::App          /* TyCk : Ref T    -> Ref T */
Ele    |  Cell "[" Expr "] " /* TyCk : T[N] i64 -> Ref T */
Ref    |  "*"  Expr          /* TyCk : Ptr T    -> Ref T */
       ;

Expr  ::=
U0     |  u0      /*        "unit"            */
B1     |  boolean /*  "true"  |  "false"      */
C8     |  char    /*  similar to C            */
Str    |  string  /* TyCk : Arr[C8, length+1] */
I64    |  integer /* non-negative dec i64     */
F64    |  float   /* must differ from int, like 0. or 0f */
Fun    |  "fun" [ ["@"]? expr_name [":" Type]?] "=>" 
					( Stmt::Block | Expr )
          /* TyCk : { [@? Type] -> Typeof(Stmt::Block|Expr)  } */
App    |  ("$" | Expr) "(" [Expr] ")" /* "$" means Self, recursively call */
/*  ADT <: Expr is just the expr of a adt */
/* pattern match */
Match  |  "match" Expr "with" [ "|" expr_name [Expr] "=>" Stmt ] 
          /* ADT -> Typeof(Stmt) 
           * branches' expr_name aka constructor should have the same ADT
           * branches' stmt should have the same Type
           */
Asgn   |  Cell asgn Expr      /* TyCk : Ref T , (Ref)? T -> T */
Addr   |  "&"  Cell /* address of  TyCk : Ref T -> Ptr T */
Ref    |  "*"  Expr /* value of    TyCk : Ptr T ->     T */
VarE   |  expr_name     /* TyCk : Ref? T -> T */
          /* Check Ref T? if so, fetch T, else just T */
          /* Ref Infer or Infer !! */
VarR   | "@" expr_name  /* TyCk : Ref T -> Ref T */

/* Element of Array */
EleE   |  Expr  "[" Expr "]"  /* TyCk : T[N], i64 ->     T */
EleR   |  Expr "@[" Expr "]"  /* TyCk : T[N], i64 -> Ref T */
EleA   |  Expr "&[" Expr "]"  /* TyCk : T[N], i64 -> Ptr T */
// CellE  |  Cell
		  /*        Cell     CellE
           * TyCk : Ref T ->   T
           * Cell::Var should not appear here,
           * because Expr::Var and Expr::VarR hides it.
           * Cell::App, Cell::Ele, Cell::Ref, too.
           * So it might be useless? 
           * But we might just implement Cell, 
           * use it in Expr::CellE
           * and drop Expr::{ VarE, App, EleE, Ref }
           */
New    |  "new" Type [Expr]? /* if Expr = NULL, let it = 1 */
           /* TyCk : (Expr:I64) -> Ptr Type */
           /* if error, just terminate now  */
Del    |  "del" Expr
           /* TyCk : (Expr:Ptr T) -> unit   */
/* The following is just for data : I64 */
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
             * "+&" "-&"
             * ptr +& 1 -> ptr+1 in C
             */
       ;       
```