#ifndef tc_ast_stmt_hpp
#define tc_ast_stmt_hpp

#include "head.hpp"
#include "token.hpp"

namespace tc{
namespace ast{
namespace stmt{

struct Shape
{
    using Flag = enum { Undefined,
        Block, If, While, 
        Break, Cont, 
        Ret, Exp, Del,
        Asgn,
        Let, Var, Check,
        Alias, ADT
    };
    Flag flag;
    Shape(Flag flag=Undefined):flag(flag){}
};

struct _block : public Shape
{
    Stmts stmts;
    _block():Shape(Block){}
};

struct _let : public Shape
{
    Name name;
    Typep type;
    Exprp expr;
    _let(Name name, Typep type, Exprp expr)
    :Shape(Let), name(name), type(type), expr(expr){}
};

struct _var : public Shape
{
    Name name;
    Typep type;
    Exprp expr;
    _var(Name name, Typep type, Exprp expr)
    :Shape(Var), name(name), type(type), expr(expr){}
};

struct _if : public Shape
{
    Exprp cond;
    Stmtp fst;
    Stmtp snd;
    _if(Exprp cond, Stmtp fst, Stmtp snd)
    :Shape(If), cond(cond), fst(fst), snd(snd){}
};

struct _while : public Shape
{
    Exprp cond;
    Stmtp body;
    _while(Exprp cond, Stmtp body)
    :Shape(While), cond(cond), body(body){}
};

struct _break : public Shape
{
    Size size;
    _break(Size size)
    :Shape(Break), size(size){}
};

struct _cont : public Shape
{
    Size size;
    _cont(Size size)
    :Shape(Cont), size(size){}
};

struct _ret : public Shape
{
    Exprp expr;
    _ret(Exprp expr)
    :Shape(Ret), expr(expr){}
};

struct _exp : public Shape
{
    Exprp expr;
    _exp(Exprp expr)
    :Shape(Exp), expr(expr){}
};

struct _del : public Shape
{
    Exprp expr;
    _del(Exprp expr)
    :Shape(Exp), expr(expr){}
};

struct _asgn : public Shape
{
    Exprp cell;
    Exprp expr;
    _asgn(Exprp cell, Exprp expr)
    :Shape(Asgn), cell(cell), expr(expr){}
};

struct _alias :  public Shape
{
    Name  name;
    Typep type;
    _alias(Name name, Typep type)
    :Shape(Alias), name(name), type(type){}
};

struct _check : public Shape
{
    Exprp expr;
    Typep type;
    _check(Exprp expr, Typep type)
    :Shape(Check), expr(expr), type(type){}
};

}}}


#endif