#include "api.hpp"
#include "ir_parser.hpp"
#include <iostream>
using API = tc::ast::API;
using Name = tc::ast::Name;

void test(API& context);
void test_let_x_101(API& context);
void test_if(API& context);
void test_while(API& context);
void test_type(API& context);

int main()
{
    API context("test.hex"); // output filename
    try
    {
        test_type(context);
    }
    catch(const char* str)
    {
        std::cerr << str << '\n';
    }
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

    auto& names = context.type[5].names; // Nat, Nickname
    for(auto& name:names)
        std::cout<<name<<" ";
    std::cout<<std::endl;
}
void test_if(API& context)
{
    auto _if = context.If(
        context.B(false)
    ,   context.Let(Name("Y"), context.I(1))
    ,   context.Let(Name("N"), context.I(0))
    );
    context.set_main(_if);
}

void test_while(API& context)
{

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