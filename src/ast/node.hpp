#ifndef tc_ast_node_hpp
#define tc_ast_node_hpp

#include "head.hpp"
#include "ir_parser.hpp"

namespace tc{
namespace ast{

// Token
struct Name : public ExtdBase
{
    string name;
    Name(string name):name(name){}
    ~Name();
};

struct Node : public ExtdBase
{
    using ID = ID;
    using IDs = vector<ID>;
};

struct Stmt : public Node 
{ 
    Stmt(){}
    virtual ~Stmt() = 0;
};
using Stmtp = Stmt*;
using Stmts = vector<Stmtp>;
struct Type : public Node 
{
    Type(){}
    virtual ~Type() = 0;
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
    Expr(){}
    virtual ~Expr() = 0;
};
using Exprp = Expr*;
using Exprs = vector<Exprp>;

}}

#endif