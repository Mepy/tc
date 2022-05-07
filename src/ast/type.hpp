#ifndef tc_ast_type_hpp
#define tc_ast_type_hpp

#include "head.hpp"

namespace tc{
namespace ast{
namespace type{

struct Shape
{
    using Flag = enum { Undefined,
        Infer, U, B, C, I, F, ADT, Ref, Ptr, Array, Fun
    };
    Flag flag;
    Shape(Flag flag=Undefined):flag(flag){}
};
using Shapep = Shape*;

// U, B, C, I, F
struct Atom : public Shape
{
    Atom(Flag flag):Shape(flag){}
};

namespace helper{

inline Shapep u(){ return new Atom(Shape::U); }
inline Shapep b(){ return new Atom(Shape::B); }
inline Shapep c(){ return new Atom(Shape::C); }
inline Shapep i(){ return new Atom(Shape::I); }
inline Shapep f(){ return new Atom(Shape::F); }

}

// Infer, Ref, Ptr
struct Typ : public Shape
{
    ID id;
    Typ(Flag flag, ID id):Shape(flag), id(id){}
};

namespace helper{

inline Shapep infer(ID id=0){ return new Typ(Shape::Infer, id); }
inline Shapep ref  (ID id  ){ return new Typ(Shape::Ref  , id); }
inline Shapep ptr  (ID id  ){ return new Typ(Shape::Ptr  , id); }

}

struct Array : public Shape
{
    ID id;
    Size  size;
    Array(ID id, Size size)
    :Shape(Shape::Array), id(id), size(size){}
};

namespace helper{

inline Shapep array(ID id, Size size){ return new Array(id, size); }

}

struct Fun : public Shape
{
    IDs params;
    ID  retype;
    Fun(ID retype=0):Shape(Flag::Fun), retype(retype){}
};

namespace helper{

inline Shapep fun (ID retype=0){ return new Fun(retype); }
inline Shapep ctor(ID adt){ return new Fun(adt); } // constructor
inline Shapep branch(ID retype){ return new Fun(retype); }

}

struct ADT : public Shape
{
    IDs cons;
    ADT():Shape(Shape::ADT){}
};


namespace helper{

inline Shapep adt(){ return new ADT(); }

}

}}}

#endif