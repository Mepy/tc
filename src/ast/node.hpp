#ifndef tc_ast_node_hpp
#define tc_ast_node_hpp

#include "head.hpp"
#include "ir_parser.hpp"
#include "rc.hpp"

namespace tc{
namespace ast{

using Sort       = ir::Symbol::Sort; 
using Block      = ir::parser::Block;
using Blockp     = ir::parser::Blockp;
using Block_Ins  = ir::parser::Block_Ins;
using Block_Insp = ir::parser::Block_Insp;

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
    Block_Ins* block_beg;
    Block_Ins* block_end;

    // Stmt
    using Flag = enum { Undefined,
        Block, If, While, 
        Empty, Break, Cont, 
        Ret, Exp, Del,
        Let, Var, Check,
        TypeDef
    };

    Flag  flag;


    Stmt():flag(Undefined), block_beg(nullptr), block_end(nullptr){}
    Stmt(Flag flag, Block_Ins* beg=nullptr, Block_Ins* end=nullptr)
    :flag(flag), block_beg(beg), block_end(end){}
    virtual ~Stmt(){}
};

using Stmtp = Stmt*;
using Stmts = vector<Stmtp>;
struct Type : public Node , public RC
{
    // Data
    ID     id;

    using Flag = enum { Undefined,
        Infer, U, B, C, I, F, ADT, Ref, Ptr, Arr, Fun
    };
    Flag flag;
    Type(){}
    Type(Flag flag, ID id=0):flag(flag), id(id){}
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
    Sort    sort; /* Sort of Symbol \in { Const, Param, NonD, Ctor, CFun, CPrg, QFun, QPrg, Open, Clos } */ 
    Block_Ins* block;

    // Data
    ID        id;
    Typep   type;

    // Expr
    using Flag = enum { Undefined, Param, 
            U, B, C, S, I, F, Array, Fun, Cons, App, LabelTuple, Match,
            Asgn, Addr, Val, ValRef, Var, VarRef,
            Ele, EleRef, EleAddr,
            New, UnOp, BinOp,
        };

    Flag    flag;
    Expr(Flag flag, Typep type=nullptr
    , Block_Ins* block=new Block_Ins())
    :flag(flag), type(type), block(block){}
    // [MM] : block free by ir::parser::concat or others
    virtual ~Expr(){ decr(type); }
};
using Exprp = Expr*;
using Exprs = vector<Exprp>;

}}

#endif