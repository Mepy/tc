#ifndef tc_ast_ir_codegen_hpp
#define tc_ast_ir_codegen_hpp

#include "../ast/ir.hpp"
#include "../utils/ibfstream.hpp"
#include <iostream>
#include <string>

namespace tc{
namespace ast{
namespace ir{
namespace codegen{

using Ibfs = tc::utils::ibfstream;
struct Block
{
    /* align 16 Bytes, 8 Bytes reserve */
    Kind kind;
    Size size;
    union Extra {
        Instruction* insts;
        Type*        types;
        Symbol*      symbs;
        Char*        chars;

        Byte*        bytes;
        Extra():bytes(nullptr){}
    } extra;

    Block():kind(Kind::KUNO), size(0){}
    Block(Ibfs& ibfs){ load(ibfs); }
    ~Block(){ delete[] extra.bytes; }

    void load(Ibfs& ibfs)
    {
        Byte8 _RESERVED;
        ibfs>>kind>>size;

        switch(kind)
        {
        case INST:
        {
            ibfs>>_RESERVED;
            extra.bytes = new Byte[size*sizeof(Instruction)];
            for(auto ptr = extra.insts
            ;   ptr-extra.insts<size
            ;   ++ptr)
                ibfs>>*ptr;

            break;
        }
        case TYPE:
        {
            extra.bytes = new Byte[size*sizeof(Type)];
            for(auto ptr = extra.types
            ;   ptr-extra.types<size
            ;   ++ptr)
                ibfs>>*ptr;
            // std::cout << size << std::endl;
            // consume leftover bytes for alignment
            if (size % 2 != 1)
                ibfs.move(8);
            break;
        }
        case SYMB:
        {
            extra.bytes = new Byte[size*sizeof(Symbol)];
            for(auto ptr = extra.symbs
            ;   ptr-extra.symbs<size
            ;   ++ptr)
                ibfs>>*ptr;

            // consume leftover bytes for alignment
            if (size % 2 != 1) 
                ibfs.move(8); 
            break;
        }
        case CSTR:
        {
            extra.bytes = new Byte[size*sizeof(Char)];
            for(auto ptr = extra.chars
            ;   ptr-extra.chars<size
            ;   ++ptr)
                ibfs>>*ptr;
            if (size % 16 != 8) 
            {
                int align_size;
                if (size < 8) 
                {
                    align_size = 8 - size;
                }
                else
                {
                    align_size = 16-((size-8)%16);
                }
                // std::cout << align_size << std::endl;
                ibfs.move(align_size);
            }
        }
        default:
            break;
            // throw "UNKNOWN Kind." + std::to_string(kind);
        }
    }
};

struct Module
{
    Cat     cat;
    Size   size;
    Block* blocks; /* new Block[this->size] */
    
    Module(std::string path){ load(path); }
    ~Module(){ delete[] blocks; }

    void load(std::string path)
    {
        Ibfs ibfs(path);
        Byte8 _Magic, _Version, _RESERVED;
        ibfs
        >>_Magic>>_Version
        >>cat>>size>>_RESERVED;
        if(_Magic!=Magic)
            throw "Not A ASTIR File.\n";
        if(_Version!=Version)
            throw "Version Mismatched.\n";
        if(_RESERVED!=RESERVED)
            throw "Not Reserved Format\n";
        // size = 1;

        this->blocks = new Block[size];
        for(auto ptr=blocks; ptr-blocks<size; ++ptr)
        {
            ptr->load(ibfs);
        }
    }
};

}}}}

#endif