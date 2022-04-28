#ifndef tc_ast_expr_hpp
#define tc_ast_expr_hpp

#include "node.hpp"
namespace tc{
namespace ast{
namespace expr{
struct U : public Expr
{
    U(Typep type):Expr(Flag::U, incr(type)){}
    ~U(){ }
};

struct B : public Expr
{
    Bool b;
    B(Bool b, Typep type):Expr(Flag::B, incr(type)), b(b){}
    ~B(){ }
};
struct C : public Expr
{
    Char c;
    C(Char c, Typep type):Expr(Flag::C, incr(type)), c(c){}
    ~C(){ }
};
struct S : public Expr
{
    Str s;
    S(Str s, Typep type):Expr(Flag::S, incr(type)), s(s){}
    ~S(){ }
};
struct I : public Expr
{
    Int i;
    I(Int i, Typep type):Expr(Flag::I, incr(type)), i(i){}
    ~I(){ }
};
struct F : public Expr
{
    Float f;
    F(Float f, Typep type):Expr(Flag::F, incr(type)), f(f){}
    ~F(){ }
};

struct App : public Expr
{
    Exprp func;
    Exprs args;
    App():Expr(Flag::App), func(nullptr){}
    ~App(){
        del(func);
        del(args);
    }
};

struct LabelTuple : public Expr
{
    ID    label; /* Data::ID of constructor */
    Exprs tuple;
    LabelTuple(Typep type, ID label)
    :Expr(Flag::LabelTuple, type), label(label){}
    ~LabelTuple(){
        del(tuple);
    }
};

struct Match : public Expr
{
    Exprp expr;
    map<ID, struct Fun*> branches;
    Match():Expr(Flag::Match){}
    ~Match(){
        del(expr);
        del(branches);
    }
};

struct Asgn : public Expr
{
    Cell* cell;
    Exprp expr;
    Asgn():Expr(Flag::Asgn){}
    ~Asgn(){
        del(cell);
        del(expr);
    }
};

struct Addr : public Expr
{
    Cell* cell;
    Addr():Expr(Flag::Addr){}
    ~Addr(){
        del(cell);
    }
};

struct Val : public Expr
{
    Exprp expr;
    Val():Expr(Flag::Val){}
    ~Val(){
        del(expr);
    }
};

struct ValRef : public Expr
{
    Exprp expr;
    ValRef():Expr(Flag::ValRef){}
    ~ValRef(){
        del(expr);
    }
};

struct Var : public Expr
{
    ID id;
    Var(ID id):Expr(Flag::Var), id(id){}
    ~Var(){}
};

struct VarRef : public Expr
{
    ID id;
    VarRef(ID id):Expr(Flag::VarRef), id(id){}
    ~VarRef(){}
};

struct Ele : public Expr
{
    Exprp array;
    Exprp index;
    Ele():Expr(Flag::Ele){}
    ~Ele(){
        del(array);
        del(index);
    }
};

struct EleRef : public Expr
{
    Exprp array;
    Exprp index;
    EleRef():Expr(Flag::EleRef){}
    ~EleRef(){
        del(array);
        del(index);
    }
};

struct EleAddr : public Expr
{
    Exprp array;
    Exprp index;
    EleAddr():Expr(Flag::EleAddr){}
    ~EleAddr(){
        del(array);
        del(index);
    }
};

// Fun, Cons : Constructor
struct Fun : public Expr
{
    IDs   params;
    Stmt* stmt ;
    Fun(Flag flag=Flag::Fun):Expr(flag), stmt(nullptr){}
    ~Fun(){ 
        del(stmt);
    }
};

struct New : public Expr
{
    Exprp init;
    Exprp size;
    New():Expr(Flag::New){}
    ~New(){
        del(init);
        del(size);
    }
};

struct UnOp : public Expr
{
    Exprp expr;
    UnOp():Expr(Flag::UnOp){}
    ~UnOp(){
        del(expr);
    }
};

struct BinOp : public Expr
{
    Exprp lhs;
    Exprp rhs;
    BinOp():Expr(Flag::BinOp){}
    ~BinOp(){
        del(lhs);
        del(rhs);
    }
};

}}}

#endif