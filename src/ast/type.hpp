#ifndef tc_ast_type_hpp
#define tc_ast_type_hpp

#include "node.hpp"
#include "rc.hpp"

namespace tc{
namespace ast{
namespace type{
// U, B, C, I, F
struct Atom : public Type
{
    Atom(Flag flag, ID id=0):Type(flag, id){}
    ~Atom(){}
};

struct ADT : public Type
{
    map<ID, Types> cons;
    ADT(ID id=0):Type(Flag::ADT, id){}
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