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
struct Insts : public list<Inst>
{
    void concat_front(Insts& front)
    { this->splice(this->begin(), front); }
    void concat_back(Insts& back)
    { this->splice(this->end(), back); }
    void eat(Insts& insts)
    { this->concat_front(insts); }
};

namespace ir{ struct Block; }

struct Stmt
{
    stmt::Shape* shape;

    ir::Block*    beg;
    ir::Block*    end;
    Insts       insts;

    // true -> Any stmt following this stmt won't be executed.
    bool       is_end; 
    Typep      retype;

    Stmt(stmt::Shape* shape, bool is_end=false, Typep retype=nullptr)
    :shape(shape), beg(nullptr), end(nullptr), is_end(is_end), retype(retype){}
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
    using Sort = ir::Symbol::Sort;
    ID              id;
    expr::Shape* shape;
    Typep         type;

    Names        names;
    
    
    Insts        insts;

    Sort          sort;

    ID          params; /* for function only      */
    ID            body; /* for function and Const */


    Expr(ID id):id(id){}
    Expr(ID id, expr::Shape* shape, Typep type, ID body) // Const
    :id(id), shape(shape), type(type), sort(Sort::Const), body(body){}
    Expr(ID id, expr::Shape* shape, Typep type, Sort sort=Sort::SUNO)
    :id(id), shape(shape), type(type), sort(sort){}
    Expr(ID id, expr::Shape* shape, Typep type, Inst&& inst, Sort sort=Sort::SUNO)
    :id(id), shape(shape), type(type), sort(sort)
    { insts.push_back(inst); }

    void inst_front(Exprp front)
    { this->insts.concat_front(front->insts); }

};
inline bool operator<(const Expr& l, const Expr& r){ return l.id<r.id; }

}}

#endif