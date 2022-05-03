#ifndef tc_ast_stmt_hpp
#define tc_ast_stmt_hpp

#include "node.hpp"
#include "rc.hpp"

namespace tc{
namespace ast{
namespace stmt{
struct Block : public Stmt
{
    Stmts stmts;
    Block(){}
    ~Block(){
        del(stmts);
    }
};

// Empty, Break, Cont
struct Empty : public Stmt
{
    Empty(Flag flag):Stmt(flag){}
    ~Empty(){}
};

// Ret, Exp, Del
struct Exp : public Stmt
{
    Exprp expr;
    Exp(Flag flag, Exprp expr)
    :Stmt(flag), expr(expr){}
    ~Exp(){
        del(expr);
    }
};

struct Check : public Stmt
{
    Exprp expr; 
    Typep type;
    Check(Typep type):type(type){}
    ~Check(){
        del(expr);
        decr(type);
    }
};

// Let, Var
struct Var : public Stmt
{
    ID id; /* expr_name -> ID */
    Typep type;
    Exprp expr;
    Var(Flag flag, ID id, Exprp expr, Typep type, Block_Insp block)
    :Stmt(flag, block, block), id(id), expr(expr), type(type){}
    ~Var(){
        del(expr);
        decr(type);
    }
};

struct If : public Stmt
{
    Exprp cond;
    Stmtp fst;
    Stmtp snd;
    If(Exprp cond, Stmtp fst, Stmtp snd, Block_Insp beg, Block_Insp end)
    :Stmt(Stmt::If, beg, end), cond(cond), fst(fst), snd(snd){}
    ~If(){
        del(cond);
        del(fst);
        del(snd);
    }
};

struct While : public Stmt
{
    Exprp cond;
    Stmtp body;
    While(Exprp cond, Stmtp body, Block_Insp beg, Block_Insp end)
    :Stmt(Stmt::While, beg, end), cond(cond), body(body){}
    ~While(){
        del(cond);
        del(body);
    }
};

// As for Alias and ADT, they are erased in compile-time,
// therefore not a AST node structure

struct TypeDef : public Stmt
{
    ID id;
    TypeDef(ID id)
    :Stmt(Flag::TypeDef), id(id){}
    ~TypeDef(){}
};

}}}

#endif