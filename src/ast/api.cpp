#include "api.hpp"
#include "ir_parser.hpp"

using API = tc::ast::API;
using Name = tc::ast::Name;

void test(API& context);
void test_let_x_101(API& context);

int main()
{
    API context("test.ir"); // output filename
    test_let_x_101(context);
}

void test_let_x_101(API& context)
{
    auto stmt = context.Let(Name("x"), context.I(101));
    stmt->block->save(context.ir);
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