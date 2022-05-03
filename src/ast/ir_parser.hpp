#ifndef tc_ast_ir_parser_hpp
#define tc_ast_ir_parser_hpp

#include <iostream>
#include "ir.hpp"
#include "../utils/obfstream.hpp"
#include "../utils/double_ended_forward_list.hpp"

namespace tc{
namespace ast{
namespace ir{
namespace parser{



struct IR
{
private: /* Types included */
    using Obfs = tc::utils::obfstream;
    template<typename T>
    using List = utils::double_ended_forward_list<T, Byte4>;
public: 
    struct Block_Sym : public List<Symbol>
    {
        void save(Obfs& obfs)
        {
            obfs<<Kind::SYMB<<this->size<<RESERVED;
            for(auto& iter : (*this))
                obfs<<iter;
            // align
            if(this->size%2==1)
                obfs<<Byte8(0);
            this->clear();
        }
    };
    struct Block_Typ : public List<Type>
    {
        void save(Obfs& obfs)
        {
            obfs<<Kind::TYPE<<this->size<<RESERVED;
            for(auto& iter : (*this))
                obfs<<iter;
            this->clear();
        }
    };
    struct Block 
    {
        Kind kind;
        Block(Kind kind=KUNO):kind(kind){ }
        virtual ~Block(){ }
        virtual void save(Obfs& obfs) = 0;
    };
    template<typename T>
    struct Block_ : public Block
    {
        Block_(Kind kind=KUNO):Block(kind){ }
        List<T> ls;
        void push(T&& t){ push(t); }
        void push(T&  t){ ls.push_tail(t); }
        void save(Obfs& obfs)
        {
            switch(kind)
            {
            case INST:
                obfs<<Kind::INST<<ls.size<<RESERVED;
                for(auto& iter : ls)
                    obfs<<iter;
                ls.clear();
                break;
            case PARA:
            case ARGS:
            case FILD:
            case BRCH:
            case TFUN:
            case TCON:
            case TSUM:
                obfs<<kind<<ls.size;
                for(auto& iter : ls)
                    obfs<<iter;
                // align
                for(unsigned n = (2-ls.size)%4;n;--n)
                    obfs<<Byte4(0); 
                ls.clear();
                break;
            case CSTR:
                obfs<<Kind::CSTR<<ls.size;
                for(auto& iter : ls)
                    obfs<<iter;
                // align
                for(unsigned n = (8-ls.size)%16;n;--n)
                    obfs<<Byte(0);
                ls.clear();
                break;
            default:
                std::cout<<"kind = "<<kind<<std::endl;
                throw "Not INST, ID or CSTR kind of block.";
            }
        }
    };
    struct Block_Ins : public Block_<Instruction>
    { Block_Ins():Block_<Instruction>(Kind::INST){} };
    using Block_ID  = Block_<ID>;
    using Block_Str = Block_<Char>;
    using Blocks = map<ID, Block*>;
public: /* members */ 
    Block_Str  str;
    Block_Sym symb;
    Block_Typ type;
    Block_ID   ids;
    /* cons_type use this */
// func_params, clos_func
    
    Block_ID cons_type,
             func_params; /* when closure, reuse this */

    Blocks  blocks; /* reserve ID for block */

    /* Module */
    Obfs obfs;
    Cat   cat;
    Size size;
    Block_Ins* main; /* main block */
    struct ADT
    {
        bool  is_recur;
        ID        type; /* id of adt            */
        Block_ID* tcon; /* ids of product types */
        Block_ID* tsum; /* ids of constructors  */

        ADT()
        :is_recur(false)
        ,tcon(new Block_ID(Kind::TCON))
        ,tsum(new Block_ID(Kind::TSUM))
        {}
        ~ADT()
        {
            delete tsum;
            delete tcon;
        }
        void clear(){ is_recur = false; }
    } adt;
    IR(std::string path, Cat cat=Cat::EXEC)
    :obfs(path), cat(cat), size(0), main(nullptr)
    { 
        obfs
        <<Magic<<Version
        <<cat<<size<<RESERVED
        ;
        auto block = new Block_Ins();
        this->blocks[0] = block;
        
        auto entry = Instruction(Instruction::Jump, 0);
        entry.src.RESERVED = RESERVED;
        block->push(entry);
    }
    ~IR()
    {
        auto cid = this->block_cid();
        for(auto& iter : blocks)
        {
            std::cout<<"~IR() saving block with id="<<iter.first<<std::endl;
            iter.second->save(obfs);
            delete iter.second;
        }
        
        if(nullptr!=this->main) // [TODO] : nullptr==main
            this->main->save(obfs);
        this->symb.save(obfs);
        this->type.save(obfs);
        this->obfs
            .seek(sizeof(Magic)+sizeof(Version)+sizeof(Cat))
            <<cid+3
            ;
        
        this->obfs
            .seek(sizeof(Magic)+sizeof(Version)
                 +sizeof(Cat  )+sizeof(Size)+sizeof(RESERVED)
                 +sizeof(Kind )+sizeof(Size)+sizeof(RESERVED)
                 +sizeof(Instruction::Sort)
            )
            <<cid+1 // Jump to the main block
            ;
    }

    inline IR& operator<<(Symbol&& symb)
    { this->symb.push_tail(symb); return *this;}
    inline IR& operator<<(Type&& type)
    { this->type.push_tail(type); return *this;}

    inline void push(Symbol&& symb)
    { this->symb.push_tail(symb); }
    inline void push(Type&& type)
    { this->type.push_tail(type); }

    inline ID block_cid()
    { return blocks.rbegin()->first; }

    // save blocks whose ids \\in [~, id)
    inline void save(ID id)
    {
        auto iter=this->blocks.begin();
        for(
        ;   iter->first<id
        ;   ++iter)
        {
            std::cout<<"saving id="<<iter->first<<std::endl;
            iter->second->save(this->obfs);
            delete iter->second;
        }
        this->blocks.erase(this->blocks.begin(), iter);
    }
};

using Block      = IR::Block    ;
using Blockp     = Block*       ;
using Block_Ins  = IR::Block_Ins;
using Block_Insp = Block_Ins*   ;
using Block_ID   = IR::Block_ID ;
using Block_IDp  = Block_ID*    ;

inline Block_Insp move(Block_Insp& old_block, Block_Insp new_block=nullptr)
{
    auto ret  = old_block;
    old_block = new_block;
    return ret;
}
inline Block_IDp move(Block_IDp& old_block, Block_IDp new_block=nullptr)
{
    auto ret  = old_block;
    old_block = new_block;
    return ret;
}
inline Block_Insp concat(Block_Insp& left, Block_Insp& right)
{
    Block_Insp ret;
    if(nullptr==right)
    { ret = left; left = nullptr; return ret; }
    
    if(nullptr==left)
    { ret = right; right = nullptr; return ret; }

    left->ls + right->ls;
    ret = left;
    delete right;
    left = right = nullptr;
    return ret;
}

}}}}

#endif