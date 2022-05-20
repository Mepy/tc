#ifndef tc_ast_ir_helper_hpp
#define tc_ast_ir_helper_hpp

#include "ir.hpp"

namespace tc{
namespace ast{
namespace ir{

namespace instruction{

inline Instruction IDs(ID id0=0, ID id1=0, ID id2=0, ID id3=0)
{ return Instruction(Instruction::Sort(id0), id1, id2, id3); }

inline Instruction Call(ID dst, ID func, ID args)
{ return Instruction(Instruction::Call, dst, func, args); }

inline Instruction Match(ID dst, ID expr, ID branches)
{ return Instruction(Instruction::Match, dst, expr, branches); }

inline Instruction Null(ID dst)
{   return Instruction(Instruction::Null, dst); }

inline Instruction CImm(ID dst, Char  c)
{
    auto ins = Instruction(Instruction::CImm, dst);
    ins.src.id[0] = 0;
    ins.src.id[1] = 0x52414843; // "CHAR"
    ins.src.Cimm = c;
    return ins;
}
inline Instruction IImm(ID dst, Int   i)
{
    auto ins = Instruction(Instruction::IImm, dst);
    ins.src.Iimm = i;
    return ins;
}
inline Instruction FImm(ID dst, Float f)
{
    auto ins = Instruction(Instruction::FImm, dst);
    ins.src.Fimm = f;
    return ins;
}
inline Instruction SImm(ID dst, Str   s)
{
    auto ins = Instruction(Instruction::SImm, dst);
    ins.src.Iimm = *(Int*)s.c_str();;
    return ins;
}
inline Instruction CStr(ID dst, ID block)
{
    return Instruction(Instruction::CStr, dst, block, 0);
}
inline Instruction Alloc(ID dst, ID src)
{ return Instruction(Instruction::Alloc, dst, src, 0x6B617453 /* Stak */); }
inline Instruction Array(ID dst, ID init, ID size)
{ return Instruction(Instruction::Array, dst, init, size); }
inline Instruction New(ID dst, ID src)
{ return Instruction(Instruction::New  , dst, src, 0x70616548 /* Heap */ ); }
inline Instruction NewAr(ID dst, ID init, ID size)
{ return Instruction(Instruction::NewAr, dst, init, size); }
inline Instruction Return(ID dst)
{
    auto ins = Instruction(Instruction::Ret, dst);
    ins.src.RESERVED = RESERVED;
    return ins;
}
inline Instruction Delete(ID dst)
{
    auto ins = Instruction(Instruction::Del, dst);
    ins.src.RESERVED = RESERVED;
    return ins;
}
inline  Instruction I2F(ID dst, ID src)
{ return Instruction(Instruction::I2F, dst, src, 0x497E3C46 /* F<~I */ ); }
inline Instruction F2I(ID dst, ID src)
{ return Instruction(Instruction::F2I, dst, src, 0x467E3C49 /* I<~F */ ); }

inline Instruction Br(ID cond, ID fst, ID snd)
{ return Instruction(Instruction::Br, cond, fst+2, snd+2); }
inline Instruction Jump(ID block)
{ 
    auto ins = Instruction(Instruction::Jump, block+2);
    ins.src.RESERVED = RESERVED;
    return ins; 
}

inline Instruction Get(ID dst, ID pointer, ID offset=0)
{ return Instruction(Instruction::Get, dst, pointer, offset); }

inline Instruction Set(ID pointer, ID src, ID offset=0)
{ return Instruction(Instruction::Set, pointer, src, offset); }

inline Instruction PtrAdd(ID dst, ID pointer, ID offset)
{ return Instruction(Instruction::PAdd, dst, pointer, offset); }
inline Instruction PtrSub(ID dst, ID pointer, ID offset)
{ return Instruction(Instruction::PAdd, dst, pointer, offset); }
inline Instruction PtrMov(ID dst, ID src)
{ return Instruction(Instruction::PMov, dst, src, 0); }

inline Instruction IMod(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IMod, dst, src1, src2); }
inline Instruction IAdd(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IAdd, dst, src1, src2); }
inline Instruction ISub(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::ISub, dst, src1, src2); }
inline Instruction IMul(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IMul, dst, src1, src2); }
inline Instruction IDiv(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IDiv, dst, src1, src2); }
inline Instruction FAdd(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FAdd, dst, src1, src2); }
inline Instruction FSub(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FSub, dst, src1, src2); }
inline Instruction FMul(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FMul, dst, src1, src2); }
inline Instruction FDiv(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FDiv, dst, src1, src2); }

inline Instruction ILt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::ILt, dst, src1, src2); }
inline Instruction FLt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FLt, dst, src1, src2); }
inline Instruction PLt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::PLt, dst, src1, src2); }

inline Instruction IGt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IGt, dst, src1, src2); }
inline Instruction FGt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FGt, dst, src1, src2); }
inline Instruction PGt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::PGt, dst, src1, src2); }

inline Instruction ILe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::ILe, dst, src1, src2); }
inline Instruction FLe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FLe, dst, src1, src2); }
inline Instruction PLe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::PLe, dst, src1, src2); }

inline Instruction IGe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IGe, dst, src1, src2); }
inline Instruction FGe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FGe, dst, src1, src2); }
inline Instruction PGe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::PGe, dst, src1, src2); }

inline Instruction UEq(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::UEq, dst, src1, src2); }
inline Instruction BEq(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::BEq, dst, src1, src2); }
inline Instruction CEq(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::CEq, dst, src1, src2); }
inline Instruction IEq(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IEq, dst, src1, src2); }
inline Instruction FEq(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FEq, dst, src1, src2); }
inline Instruction PEq(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::PEq, dst, src1, src2); }
inline Instruction AEq(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::AEq, dst, src1, src2); }
inline Instruction TEq(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::TEq, dst, src1, src2); }

inline Instruction UNe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::UNe, dst, src1, src2); }
inline Instruction BNe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::BNe, dst, src1, src2); }
inline Instruction CNe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::CNe, dst, src1, src2); }
inline Instruction INe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::INe, dst, src1, src2); }
inline Instruction FNe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FNe, dst, src1, src2); }
inline Instruction PNe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::PNe, dst, src1, src2); }
inline Instruction ANe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::ANe, dst, src1, src2); }
inline Instruction TNe(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::TNe, dst, src1, src2); }

inline Instruction LShift(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::LShift, dst, src1, src2); }
inline Instruction RShift(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::RShift, dst, src1, src2); }

inline Instruction BNot(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::BNot, dst, src1, src2); }
inline Instruction BAnd(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::BAnd, dst, src1, src2); }
inline Instruction BOr (ID dst, ID src1, ID src2)
{ return Instruction(Instruction::BOr , dst, src1, src2); }
inline Instruction BXor(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::BXor, dst, src1, src2); }

inline Instruction LNot(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::LNot, dst, src1, src2); }
inline Instruction LAnd(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::LAnd, dst, src1, src2); }
inline Instruction LOr (ID dst, ID src1, ID src2)
{ return Instruction(Instruction::LOr , dst, src1, src2); }
inline Instruction LXor(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::LXor, dst, src1, src2); }



}
namespace symbol{

inline Symbol Const(ID type ){ return Symbol(Symbol::Const, type ); }
inline Symbol Param(ID type ){ return Symbol(Symbol::Param, type ); }
inline Symbol NonD (ID type ){ return Symbol(Symbol::NonD , type ); }
inline Symbol Ctor (ID block){ return Symbol(Symbol::Ctor , block); }
inline Symbol CFun (ID block){ return Symbol(Symbol::CFun , block); }
inline Symbol CPrg (ID block){ return Symbol(Symbol::CPrg , block); }
inline Symbol QFun (ID block){ return Symbol(Symbol::QFun , block); }
inline Symbol QPrg (ID block){ return Symbol(Symbol::QPrg , block); }
inline Symbol Open (ID block){ return Symbol(Symbol::Open , block); }
inline Symbol Clos (ID block){ return Symbol(Symbol::Clos , block); }

}
namespace type{

inline Type Unit (){ return Type(Type::Unit , 0); }
inline Type Bool (){ return Type(Type::Bool , 1); }
inline Type Char (){ return Type(Type::Char , 2); }
inline Type Int  (){ return Type(Type::Int  , 3); }
inline Type Float(){ return Type(Type::Float, 4); }

inline Type ADT(ID id){ return Type(Type::ADT, id); }
inline Type Fun(ID id){ return Type(Type::ADT, id); }

}

}}}

#endif