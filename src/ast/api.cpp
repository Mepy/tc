#include "api.hpp"
#include <iostream>
using API = tc::ast::API;
using Name = tc::ast::Name;

void test(API& context);
void test_let_x_101(API& context);
void test_if(API& context);
void test_while(API& context);
void test_type(API& context);
void test_func_ref(API& context);
void test_insts(API& context);
void test_fact(API& context);
void test_swap(API& context);
void test_imm(API& context);

int main()
{
    API context;
    try
    {
        test_imm(context);
    }
    catch(const char* str)
    {
        std::cerr << str << '\n';
    }
}
void test_imm(API& context)
{
    /* // imm.tc
    let b = true;
    let c = 'c';
    let i =  1 ;
    let f = 0.0;
    let h = "Hello!\n"; // h.len < 8
    let s = "To be, or not to be, that is the question:\n";
     */
    context.BlockBegin();
    context.BlockStmt(context.Let("b", context.B(true)));
    context.BlockStmt(context.Let("c", context.C('c')));
    context.BlockStmt(context.Let("i", context.I(1)));
    context.BlockStmt(context.Let("f", context.F(0.0)));
    context.BlockStmt(context.Let("h", context.S("Hello!\n")));
    context.BlockStmt(
        context.Let("s", context.S(
            "To be, or not to be, that is the question:\n"
        ))
    );
    auto stmt = context.BlockEnd();
    context.save(stmt);
    context.save("imm.hex");
}
void test_swap(API& context)
{
    /* // swap.tc
    let swap = fun @x @y:Int =>{
        let t = x;
            x = y;
            y = t;
    };
    */
    context.ExprFunBeg();
    context.ExprFunRefArg("x");
    context.ExprFunRefArg("y", context.TypeVar("Int"));
    context.BlockBegin();
    context.BlockStmt(
        context.Let("t", context.ExprVar("x"))
    );
    context.BlockStmt(context.Exp(
        context.Asgn(context.CellVar("x"), tc::ast::Oper::Undefined, context.ExprVar("y"))
    ));
    context.BlockStmt(context.Exp(
        context.Asgn(context.CellVar("y"), tc::ast::Oper::Undefined, context.ExprVar("t"))
    ));
    context.Let("swap", context.ExprFunStmt(context.BlockEnd()));
    context.save("swap.hex");
}

void test_fact(API& context)
{
    /* // fact.tc
     * let fact = \ n => 
     *     if ( n<2 ) return 1 
     *     else return n * fact(n-1)
     *     ;
     */

    context.ExprFunBeg();
    context.ExprFunArg(Name("n"));
    
    auto cond = context.BinOp(context.ExprVar(Name("n")), tc::ast::Oper::Lt, context.I(2));
    auto fst = context.Ret(context.I(1));
    auto n = context.ExprVar(Name("n"));
    context.AppBeg();
    context.AppArg(context.BinOp(context.ExprVar(Name("n")), tc::ast::Oper::Sub, context.I(1)));
    auto snd = context.Ret(context.BinOp(n, tc::ast::Oper::Mul, context.ExprAppEnd()));
    auto let = context.Let(Name("fact"), context.ExprFunStmt(context.If(cond, fst, snd)));

}

void test_insts(API& context)
{
    /* // insts.tc
     * let @x  = 1234;
     *      x += 5678;
     */
    context.BlockBegin();
    context.BlockStmt(
        context.Var(Name("x"), context.I(1234))
    );
    context.BlockStmt(context.Exp(
        context.Asgn(context.CellVar(Name("x")), tc::ast::Oper::Add, context.I(5678))
    ));
    context.save("test.hex");
}

void test_func_ref(API& context)
{
    /* // func_ref.tc
     * let foo = \ @x => @x + 1     ;
     * let bar = \ @x => @x@[1]     ;
     * check bar : { @&Int -> @Int };
     */
    context.ExprFunBeg();
    context.ExprFunRefArg(Name("x")); // , context.TypeVar(Name("Int")) : Int
    context.Let(Name("foo"),context.ExprFunExpr(context.BinOp(
        context.ExprVarRef(Name("x")), tc::ast::Oper::Add, context.I(1)
    )));

    context.ExprFunBeg();
    context.ExprFunRefArg(Name("x"));
    context.Let(Name("bar"),context.ExprFunExpr(context.ExprEleRef(
        context.ExprVarRef(Name("x")), context.I(1)
    )));

    context.TypeFunBeg();
    context.TypeFunArg(
        context.TypeRef(context.TypePtr(context.TypeVar(Name("Int"))))
    );
    context.Check(context.ExprVar(Name("bar")), context.TypeFunEnd(
       context.TypeRef(context.TypeVar(Name("Int")))
    ));
}

void test_type(API& context)
{
    /* // adt.tc
     * type Nat = 
     *     | zero 
     *     | succ Nat
     *     ;
     * type False =
     *     ;
     * type Nickname = Nat;
     * let @n = zero;
     */
    
    context.TypeDef(Name("Nat"));
    
    context.ADTBranchBegin(Name("zero"));
    context.ADTBranchEnd();
    
    context.ADTBranchBegin(Name("succ"));
    context.ADTBranchType(
        context.TypeVar(Name("Nat"))
    );
    context.ADTBranchEnd();
    
    context.ADT();
    
    
    context.TypeDef(Name("False"));
    context.ADT();
    
    context.TypeDef(Name("Nickname"));
    context.Alias(context.TypeVar(Name("Nat")));
    context.Var(Name("x"), context.ExprVar(Name("zero")));

    auto& names = context.type[6].names; // Nat, Nickname
    for(auto& name:names)
        std::cout<<name<<" ";
    std::cout<<std::endl;

    context.save("type.hex");
}
void test_if(API& context)
{
    auto _if = context.If(
        context.B(false)
    ,   context.Let(Name("Y"), context.I(1))
    ,   context.Let(Name("N"), context.I(0))
    );
    context.save("test.hex");
}

// while if break else continue
void test_while(API& context) 
{
    /* // while.tc
     * let b1 = true;
     * let b2 = true;
     * let b3 = true;
     * while(b1) while(b2)
     *    if(b3) break 2; 
     *    else continue 2;
     *  
     */
    context.BlockBegin();
    context.BlockStmt(context.Let(Name("b1"), context.B(true)));
    context.BlockStmt(context.Let(Name("b2"), context.B(true)));
    context.BlockStmt(context.Let(Name("b3"), context.B(true)));
    context.WhileBeg(); // outer
    context.WhileBeg(); // inner

    auto while_while = 
        context.While(context.ExprVar(Name("b1")), context.While(context.ExprVar(Name("b2")), 
        context.If(
            context.ExprVar(Name("b3"))
        ,   context.Break(2)
        ,   context.Cont (2)
        )
    ));

    context.BlockStmt(while_while);
    context.BlockEnd();

    context.save("while.hex");
}

void test_let_x_101(API& context)
{
    auto stmt = context.Let(Name("x"), context.I(101));
    // stmt->block->save(context.ir);
}

void test(API& context)
{
    /* let g = \ f x => f(x); */
    context.ExprFunBeg();
    context.ExprFunArg(Name("f"));
    context.ExprFunArg(Name("x"));

    auto f = context.ExprVar(Name("f"));
    context.AppBeg(f);
    auto x  = context.ExprVar(Name("x"));
    context.AppArg(x);
    auto fx = context.ExprAppEnd();

    auto fun = context.ExprFunExpr(fx);

    auto letg = context.Let(Name("g"), fun);

    /* let main = \ => ... */
    context.ExprFunBeg();
    context.BlockBegin();

    // let x = 3;
    auto letx0 = context.Let(Name("x"), context.I(3));
    context.BlockStmt(letx0);
    // let x = g(\x=>x+1, x);
    context.AppBeg(context.ExprVar(Name("g")));

    context.ExprFunBeg();
    context.ExprFunArg(Name("x"));
    auto temp = context.ExprFunExpr(
        context.BinOp(
            context.ExprVar(Name("x")),
            tc::ast::Oper::Add,
            context.I(1)
        )
    );
    context.AppArg(temp);
    context.AppArg(context.ExprVar(Name("x")));

    auto letx1 = context.Let(Name("x"), context.ExprAppEnd());
    context.BlockStmt(letx1);

    // puti(x)
    context.AppBeg(context.ExprVar(Name("puti")));
    context.AppArg(context.ExprVar(Name("x")));
    auto putx = context.Exp(context.ExprAppEnd());
    context.BlockStmt(putx);
    
    context.ExprFunStmt(context.BlockEnd());
}