#ifndef tc_ast_ir_helper_hpp
#define tc_ast_ir_helper_hpp

#include "ir.hpp"

namespace tc{
namespace ast{
namespace ir{

namespace instruction{

inline Instruction BImm(ID dst, Bool  b)
{
    auto ins = Instruction(Instruction::BImm, dst);
    ins.src.id[0] = 0;
    ins.src.id[1] = b?0x45555254:0x534C4146; // b?"TRUE":"FALS"
    ins.src.Bimm = b;
    return ins;
}
inline Instruction CImm(ID dst, Char  c)
{
    auto ins = Instruction(Instruction::CImm, dst);
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
inline Instruction Alloc(ID dst, ID src)
{ return Instruction(Instruction::Alloc, dst, src, 0x6B617453 /* Stak */); }
inline Instruction New(ID dst, ID src)
{ return Instruction(Instruction::New  , dst, src, 0x70616548 /* Heap */ ); }
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
{ return Instruction(Instruction::Br, cond, fst, snd); }
inline Instruction Jump(ID block)
{ 
    auto ins = Instruction(Instruction::Jump, block);
    ins.src.RESERVED = RESERVED;
    return ins; 
}

inline Instruction Get(ID dst, ID pointer, ID offset=0)
{ return Instruction(Instruction::Get, dst, pointer, offset); }

inline Instruction Set(ID pointer, ID src, ID offset=0)
{ return Instruction(Instruction::Set, pointer, src, offset); }

inline Instruction PtrAdd(ID dst, ID pointer, ID offset)
{ return Instruction(Instruction::PAdd, dst, pointer, offset); }

inline Instruction IAdd(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IAdd, dst, src1, src2); }
inline Instruction ISub(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::ISub, dst, src1, src2); }
inline Instruction IMul(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IMul, dst, src1, src2); }
inline Instruction IDiv(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IDiv, dst, src1, src2); }
inline Instruction IMod(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::IMod, dst, src1, src2); }

inline Instruction ILt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::ILt, dst, src1, src2); }
inline Instruction FLt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::FLt, dst, src1, src2); }
inline Instruction PLt(ID dst, ID src1, ID src2)
{ return Instruction(Instruction::ULt, dst, src1, src2); }

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

inline Type Unit (){ return Type(Type::Unit , 1); }
inline Type Bool (){ return Type(Type::Bool , 2); }
inline Type Char (){ return Type(Type::Char , 3); }
inline Type Int  (){ return Type(Type::Int  , 4); }
inline Type Float(){ return Type(Type::Float, 5); }

inline Type ADT(ID id)
{ return Type(Type::ADT, id); }

}

}}}

#endif