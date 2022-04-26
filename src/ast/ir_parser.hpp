#ifndef tc_ast_ir_parser_hpp
#define tc_ast_ir_parser_hpp

#include "ir.hpp"
#include "../utils/obfstream.hpp"
#include "../utils/double_ended_forward_list.hpp"

namespace tc{
namespace ast{
namespace ir{
namespace parser{

using Obfs = tc::utils::obfstream;

struct Module
{
    Cat cat;
    Size size;
    Obfs obfs;

    Module(std::string path, Cat cat=Cat::EXEC)
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

struct Block
{
    template<typename T>
    using list = utils::double_ended_forward_list<T, Byte4>;

    Kind kind;
    list<Instruction> inst;
    list<ID>          idls; /* id list */
    Block():kind(KUNO){ }
    ~Block(){ }

    inline Block& operator<<(Kind kind)
    { this->kind=kind; return *this; }
    inline Block& operator<<(Instruction&& ins)
    { inst.push_tail(ins); return *this;}
    /* block with kind is no longer available */
    inline Block& operator>>(Module& module)
    {  save(module); return *this; }

    inline void push(Instruction&& ins)
    { inst.push_tail(ins); }
    /* block with kind is no longer available */

    inline void push(ID&& id)
    { idls.push_tail(id); }

    inline void save(Module& module)
    {
        auto& obfs = module.obfs;
        ++module.size;

        obfs<<kind;
        switch(kind)
        {
            case INST:
                obfs<<inst.size<<RESERVED;
                for(auto& iter : inst)
                    obfs<<iter;
                inst.clear(); 
                break;
            default:
                throw "Unknown kind of block";
        }
    }
};

}}}}

#endif