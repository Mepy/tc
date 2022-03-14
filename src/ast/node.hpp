#ifndef tc_ast_node_hpp
#define tc_ast_node_hpp

#include "head.hpp"

namespace tc{
namespace ast{

struct Node : public ExtdBase
{
    using ID = ID;
};

struct Stmt;
using Stmtp = Stmt*;
using Stmts = vector<Stmtp>;
struct Type;
using Typep = Type*;
using Types = vector<Typep>;
struct Cell;
using Cellp = Cell*;
using Cells = vector<Cellp>;
struct Expr;
using Exprp = Expr*;
using Exprs = vector<Exprp>;

}}

#endif