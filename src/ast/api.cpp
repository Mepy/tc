#include "api.hpp"
#include "ir_parser.hpp"

using Table = tc::ast::Table;

void test(Table& table);

int main()
{
    Table table("test.ir"); // output filename
    test(table);
}

void test(Table& table)
{
    /* let g = \ f x => f(x); */
    table.ExprFunBeg();
    table.ExprFunArg("f");
    table.ExprFunArg("x");

    auto f = table.ExprVar("f");
    table.AppBeg(f);
    auto x  = table.ExprVar("x");
    table.AppArg(x);
    auto fx = table.ExprAppEnd();

    auto fun = table.ExprFunExpr(fx);

    auto letg = table.Let("g", fun);

    /* let main = \ => ... */
    table.ExprFunBeg();
    table.BlockBegin();

    // let x = 3;
    auto letx0 = table.Let("x", table.I(3));
    table.BlockStmt(letx0);
    // let x = g(\x=>x+1, x);
    table.AppBeg(table.ExprVar("g"));

    table.ExprFunBeg();
    table.ExprFunArg("x");
    auto temp = table.ExprFunExpr(
        table.BinOp(
            table.ExprVar("x"),
            tc::ast::Oper::Add,
            table.I(1)
        )
    );
    table.AppArg(temp);
    table.AppArg(table.ExprVar("x"));

    auto letx1 = table.Let("x", table.ExprAppEnd());
    table.BlockStmt(letx1);

    // puti(x)
    table.AppBeg(table.ExprVar("puti"));
    table.AppArg(table.ExprVar("x"));
    auto putx = table.Exp(table.ExprAppEnd());
    table.BlockStmt(putx);
    
    table.ExprFunStmt(table.BlockEnd());
}