#ifndef tc_ast_ir_parser_hpp
#define tc_ast_ir_parser_hpp

#include "ir.hpp"
#include "../utils/obfstream.hpp"
#include "../utils/double_ended_forward_list.hpp"

namespace tc{
namespace ast{
namespace ir{
namespace parser{

namespace instruction{
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
inline static Instruction F2I(ID dst, ID src)
{ return Instruction(Instruction::F2I, dst, src, 0x467E3C49 /* I<~F */ ); }

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

}

struct IR
{
private: /* member module : struct Module */
    using Obfs = tc::utils::obfstream;
    struct Module
    {
        Cat cat;
        Size size;
        Obfs obfs;

        Module(std::string path, Cat cat)
        :cat(cat), size(0), obfs(path)
        {
            obfs
            <<Magic<<Version
            <<cat<<size<<RESERVED
            ;
        }
        ~Module()
        {
            obfs
            .seek(sizeof(Magic)+sizeof(Version)+sizeof(Cat))
            <<size
            ;
        }
    };
    
    Module  module;
public: /* struct Block  */
    template<typename T>
    using list = utils::double_ended_forward_list<T, Byte4>;
    
    struct Block_IR
    {
        Kind kind;
        list<Instruction> irs;
        Block_IR(Kind kind=KUNO):kind(kind){ }
        ~Block_IR(){ }

        inline Block_IR& operator<<(Kind kind)
        { this->kind=kind; return *this; }
        inline Block_IR& operator<<(Instruction&& inst)
        { irs.push_tail(inst); return *this;}
        
        /* block with kind is no longer available */
        inline Block_IR& operator>>(IR& ir)
        {  save(ir); return *this; }

        inline void push(Instruction&& inst)
        { irs.push_tail(inst); }

        /* block with kind is no longer available */
        inline void save(IR& ir)
        {
            auto& module = ir.module;
            auto& obfs = module.obfs;
            switch(kind)
            {
                case INST:
                case SYMB:
                case TYPE:
                    ++module.size;
                    obfs<<kind<<irs.size<<RESERVED;
                    for(auto& iter : irs)
                        obfs<<iter;
                    irs.clear(); 
                    break;
                case ARGS:
                case FILD:
                case BRCH:
                case PARA:
                case TIDS:
                case TCON:

                case CSTR:
                    throw "Not IR  kind of block\n";
                default:
                    throw "Unknown kind of block\n";
            }
        }
    };
    struct Block_ID
    {
        Kind kind;
        list<ID> ids;
        Block_ID(Kind kind=KUNO):kind(kind){ }
        ~Block_ID(){ }

        inline Block_ID& operator<<(Kind kind)
        { this->kind=kind; return *this; }

        inline Block_ID& operator<<(ID id){ ids.push_tail(id); return *this; }
        
        /* block with kind is no longer available */
        inline Block_ID& operator>>(IR& ir)
        {  save(ir); return *this; }

        inline void push(ID id){ ids.push_tail(id); }

        /* block with kind is no longer available */
        inline void save(IR& ir)
        {
            auto& module = ir.module;
            auto& obfs = module.obfs;
            switch(kind)
            {
                case ARGS:
                case FILD:
                case BRCH:
                case PARA:
                case TIDS:
                case TCON:
                    ++module.size;
                    obfs<<kind<<ids.size;
                    for(auto& iter : ids)
                        obfs<<iter;
                    // align
                    for(unsigned n = 4 - (ids.size+2)%4;n;--n)
                        obfs<<Byte4(0); 
                    ids.clear();
                    break;
                case INST:
                case SYMB:
                case TYPE:
                case CSTR:
                    throw "Not ID  kind of block\n";
                default:
                    throw "Unknown kind of block\n";
            }
        }
    };
    // [TODO] : Block_Ch
    struct Block_Ch
    {
        Kind kind;
        list<Char> chs;
        Block_Ch(Kind kind=KUNO):kind(kind){ }
        ~Block_Ch(){ }

        inline Block_Ch& operator<<(Kind kind)
        { this->kind=kind; return *this; }
        inline Block_Ch& operator<<(Char&& ch)
        { chs.push_tail(ch); return *this; }
        
        /* block with kind is no longer available */
        inline Block_Ch& operator>>(IR& ir)
        {  save(ir); return *this; }

        inline void push(Char&& ch)
        { chs.push_tail(ch); }
        

        /* block with kind is no longer available */
        inline void save(IR& ir)
        {
            auto& module = ir.module;
            auto& obfs = module.obfs;
            switch(kind)
            {
                case CSTR:
                    ++module.size;
                    obfs<<kind<<chs.size;
                    for(auto& iter : chs)
                        obfs<<iter;
                    // align
                    for(unsigned n = 16 - (chs.size+8)%16;n;--n)
                        obfs<<Byte(0); 
                    chs.clear();
                    break;
                case ARGS:
                case FILD:
                case BRCH:
                case PARA:
                case TIDS:
                case TCON:

                case INST:
                case SYMB:
                case TYPE:
                    throw "Not Ch  kind of block\n";
                default:
                    throw "Unknown kind of block\n";
            }
        }
    };
public: 
    using Blocks = map<ID, Block_IR*>;
public: /* members */ 
    Block_IR  symb,
              type;
    Block_ID   ids;
    /* cons_type use this */
// func_params, clos_func
    Block_Ch   str;
    Block_ID cons_type,
           func_params; /* when closure, reuse this */

    Blocks  blocks; /* reserve ID for block */

    IR(std::string path, Cat cat=Cat::EXEC)
    :module(path, cat)
    ,symb(ir::Kind::SYMB)
    ,type(ir::Kind::TYPE)
    { }

    ~IR(){ symb>>(*this); type>>(*this); }

    inline IR& operator<<(Symbol&& symb)
    { this->symb.irs.push_tail(*(Instruction*)&symb); return *this;}
    inline IR& operator<<(Type&& type)
    { this->type.irs.push_tail(*(Instruction*)&type); return *this;}

    inline void push(Symbol&& symb)
    { this->symb.irs.push_tail(*(Instruction*)&symb); }
    inline void push(Type&& type)
    { this->type.irs.push_tail(*(Instruction*)&type); }

};

using Block = IR::Block_IR;
using Blockp = Block*;

inline Blockp move(Blockp& block)
{
    auto ret = block;
 block = nullptr;
    return ret;
}
inline Blockp concat(Blockp& left, Blockp& right)
{
    Blockp ret;
    if(nullptr==right)
    { ret = left; left = nullptr; return ret; }
    
    if(nullptr==left)
    { ret = right; right = nullptr; return ret; }

    left->irs + right->irs;
    ret = left;
    delete right;
    left = right = nullptr;
    return ret;
}

}}}}

#endif