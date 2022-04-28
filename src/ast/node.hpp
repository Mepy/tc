#ifndef tc_ast_node_hpp
#define tc_ast_node_hpp

#include "head.hpp"
#include "ir_parser.hpp"
#include "rc.hpp"

namespace tc{
namespace ast{

using Sort  = tc::ast::ir::Symbol::Sort; 
using Block = tc::ast::ir::parser::Block;

// Token
struct Name : public ExtdBase, string
{
    Name(){}
    Name(string name):string(name){}
    ~Name(){}
};

struct Node : public ExtdBase {};
using Nodep = Node*;

struct Stmt : public Node 
{
    // IR
    Block* block;

    // Stmt
    using Flag = enum { Undefined,
        Block, If, While, 
        Empty, Break, Cont, 
        Ret, Exp, Del,
        Let, Var, Check,
        TypeDef
    };

    Flag flag;
    Stmt():flag(Undefined){}
    Stmt(Flag flag):flag(flag){}
    virtual ~Stmt(){}
};

using Stmtp = Stmt*;
using Stmts = vector<Stmtp>;
struct Type : public Node , public RC
{
    // Data
    ID        id;

    using Flag = enum { Undefined,
        Infer, U, B, C, I, F, ADT, Ref, Ptr, Arr, Fun
    };
    Flag flag;
    Type(){}
    Type(Flag flag):flag(flag){}
    virtual ~Type(){}
};
using Typep = Type*;
using Types = vector<Typep>;

struct Cell : public Node 
{
    Cell(){}
    virtual ~Cell() = 0;
};
using Cellp = Cell*;
using Cells = vector<Cellp>;
struct Expr : public Node 
{
    // IR
    Sort    sort; /* Sort of Symbol \in { Nfun, Func, Clos }*/
    Block* block;

    // Data
    ID        id;
    Typep   type;

    // Expr
    using Flag = enum { Undefined,
            U, B, C, S, I, F, Array, Fun, Cons, App, LabelTuple, Match,
            Asgn, Addr, Val, ValRef, Var, VarRef,
            Ele, EleRef, EleAddr,
            New, UnOp, BinOp,
        };

    Flag    flag;
    Expr(Flag flag, Typep type=nullptr
    , Block* block=new Block(ir::Kind::INST))
    :flag(flag), type(type), block(block){}
    // [MM] : block free by ir::parser::concat or others
    virtual ~Expr(){ decr(type); }
};
using Exprp = Expr*;
using Exprs = vector<Exprp>;

}}

#endif