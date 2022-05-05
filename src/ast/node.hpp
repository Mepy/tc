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

    Expr(ID id):id(id){}
    Expr(ID id, expr::Shape* shape, Typep type, ir::Symbol symbol=ir::Symbol())
    :id(id), shape(shape), type(type), symbol(symbol){}

};
inline bool operator<(const Expr& l, const Expr& r){ return l.id<r.id; }

}}

#endif