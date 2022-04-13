#ifndef tc_ast_type_hpp
#define tc_ast_type_hpp

#include "node.hpp"
#include "rc.hpp"

namespace tc{
namespace ast{
namespace type{

struct Type : public ast::Type, public RC
{
    using Flag = enum { Undefined,
        Infer, U, B, C, I, F, ADT, Ref, Ptr, Arr, Fun
    };
    Flag flag;
    Type(){}
    Type(Flag flag):flag(flag){}
    virtual ~Type() = 0;
};

// U, B, C, I, F
struct Lit : public Type
{
    Lit(Flag flag):Type(flag){}
    ~Lit(){}
};

struct ADT : public Type
{
    map<ID, Types> cons;
    ADT():Type(Flag::ADT){}
    ~ADT(){
        decr(cons);
    }
};

// Infer, Ref, Ptr
struct Typ : public Type
{
    Typep type;
    Typ(Flag flag, Typep type)
    :Type(flag), type(type){}
    ~Typ(){
        decr(type);
    }
};

struct Arr : public Type
{
    Typep type;
    Size  size;
    Arr(Typep type, Size size)
    :Type(Flag::Arr)
    ,type(type), size(size){}
    ~Arr(){
        decr(type);
    }
};

struct Fun : public Type
{
    Types params;
    Typep retype;
    Fun():Type(Flag::Fun){}
    ~Fun(){
        decr(params);
        decr(retype);
    }
};

}}}

#endif