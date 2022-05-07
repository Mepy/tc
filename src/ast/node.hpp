#ifndef tc_ast_node_hpp
#define tc_ast_node_hpp

#include "head.hpp"
#include "token.hpp"
#include "ir.hpp"

#include "stmt.hpp"
#include "expr.hpp"
#include "type.hpp"

namespace tc{
namespace ast{

using Names = list<Name>;
using Inst  = ir::Instruction;
using Insts = list<Inst>;

struct Stmt
{
    stmt::Shape* shape;

    Stmt(stmt::Shape* shape):shape(shape){}
};

struct Type
{
    ID              id;
    type::Shape* shape;

    Names        names;

    ir::Type      type;

    Type(ID id):id(id){}
    Type(ID id, type::Shape* shape, ir::Type type=ir::Type())
    :id(id), shape(shape), type(type){}

    inline ID& typ_id(){ return ((type::Typ*)(this->shape))->id; }
};
inline bool operator<(const Type& l, const Type& r){ return l.id<r.id; }

struct Expr
{
    ID              id;
    expr::Shape* shape;
    Typep         type;

    Names        names;
    
    ir::Symbol  symbol;
    Insts        insts;

    Expr(ID id):id(id){}
    Expr(ID id, expr::Shape* shape, Typep type)
    :id(id), shape(shape), type(type){}
    Expr(ID id, expr::Shape* shape, Typep type, Inst&& inst, ir::Symbol symbol=ir::Symbol())
    :id(id), shape(shape), type(type), symbol(symbol)
    { insts.push_back(inst); }

    void inst_front(Exprp front)
    { insts.splice(insts.begin(), front->insts); }

};
inline bool operator<(const Expr& l, const Expr& r){ return l.id<r.id; }

}}

#endif