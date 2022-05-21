#ifndef tc_ast_expr_hpp
#define tc_ast_expr_hpp

#include "head.hpp"
#include "token.hpp"

namespace tc{
namespace ast{
namespace expr{

struct Shape
{
    using Flag = enum { Undefined,
        Func, CallVal, CallRef, Match, Branch,
        EleVal, EleRef, EleAddr,
        Null, U, B, C, S, I, F, Constructor, Param,
        Get, NewExpr, NewArray, Addr, Ref, Decay,
        
        // Unary
        Pos, Neg,

        // Binary
        // T, Int -> T[N] | Ptr T
        Array,

        // (Ptr T, Int) -> Ptr T
        PtrAdd, PtrSub, 

        // (Int, Int) -> Int
        Mod, LShift, RShift, BNot, BAnd, BOr, BXor, 

        // (Bool, Bool) -> Bool
        LNot, LAnd, LOr, LXor,

        // (Float, Float) -> Float
        FAdd, FSub, FMul, FDiv,

        // (T, T) -> Bool
        Eq, Neq,

        // (Int, Int) & (Float, Float) -> Bool
        Lt, Gt, Leq, Geq,

        //    { (Int  , Int  ) -> Int   } 
        // && { (Float, Float) -> Float }
        IMul, IDiv,

        // Sub
        //    (Ptr T, Int  ) -> Ptr T
        // && (Int  , Int  ) -> Int
        // && (Float, Float) -> Float
        ISub,

        // Add
        //    (Ptr T, Int  ) -> Ptr T
        // && (Float, Float) -> Float
        // && (Int  , Ptr T) -> Ptr T
        // && (Int  , Int  ) -> Int
        IAdd, 
    
        
        
    };
    Flag flag;
    Shape(Flag flag=Undefined):flag(flag){}
};
using Shapep = Shape*;

struct Nullary : public Shape
{
    Nullary(Flag flag):Shape(flag){}
};

struct B : public Shape
{
    Bool b;
    B(Bool b):Shape(Flag::B), b(b){}
};
struct C : public Shape
{
    Char c;
    C(Char c):Shape(Flag::C), c(c){}
};
struct S : public Shape
{
    Str s;
    S(Str s):Shape(Flag::S), s(s){}
};
struct I : public Shape
{
    Int i;
    I(Int i):Shape(Flag::I), i(i){}
};
struct F : public Shape
{
    Float f;
    F(Float f):Shape(Flag::F), f(f){}
};

namespace helper
{

inline Shapep null(){ return new Nullary(Shape::Null); }
inline Shapep u(){ return new Nullary(Shape::U); }
inline Shapep b(Bool  b){ return new B(b); }
inline Shapep c(Char  c){ return new C(c); }
inline Shapep s(Str   s){ return new S(s); }
inline Shapep i(Int   i){ return new I(i); }
inline Shapep f(Float f){ return new F(f); }

inline Shapep ctor(){ return new Nullary(Shape::Constructor); }
inline Shapep param(){ return new Nullary(Shape::Param); }

}

struct Unary : public Shape
{
    ID expr;
    Unary(Flag flag, ID expr)
    :Shape(flag), expr(expr){}
};

namespace helper
{

inline Shapep get(ID ptr){ return new Unary(Shape::Get, ptr); }
inline Shapep addr(ID cell){ return new Unary(Shape::Addr, cell); }
inline Shapep new_expr (ID init){ return new Unary(Shape::NewExpr , init); }
inline Shapep ref(ID value){ return new Unary(Shape::Ref, value); }
inline Shapep decay(ID value){ return new Unary(Shape::Decay, value); }

}

struct Binary : public Shape
{
    ID lhs;
    ID rhs;
    Binary(Flag flag, ID lhs, ID rhs)
    :Shape(flag), lhs(lhs), rhs(rhs){}
};

namespace helper
{

inline Shapep element(ID base, ID offset)
{ return new Binary(Shape::EleVal, base, offset); }
inline Shapep array(ID init, ID size)
{ return new Binary(Shape::Array, init, size); }
inline Shapep new_array(ID init, ID size)
{ return new Binary(Shape::NewArray, init, size); }

}

struct Func : public Shape
{
    IDs params;
    Stmtp body;
    Func(Flag flag=Flag::Func):Shape(flag){}
};

struct Call : public Shape
{
    ID      func;
    IDs     args;
    Call(ID func)
    :Shape(Flag::CallVal), func(func){}
};

struct Match : public Shape
{
    ID      expr;
    IDs branches;
    Match(ID expr)
    :Shape(Flag::Match), expr(expr){}
};

struct Branch : public Shape
{
    IDs params;
    Stmtp body;
    ID    cons;
    Branch(ID cons):Shape(Flag::Branch), cons(cons){}
};

namespace helper{

inline Shapep func(){ return new Func(); }
inline Shapep call(ID func){ return new Call(func); }
inline Shapep match(ID expr){ return new Match(expr); }
inline Shapep branch(ID cons){ return new Branch(cons); }

}

}}}

#endif