#ifndef tc_ast_ir_codegen_hpp
#define tc_ast_ir_codegen_hpp

#include "ir.hpp"
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
    
    Byte* bytes;

    Block():kind(Kind::KUNO), size(0), bytes(nullptr){}
    Block(Ibfs& ibfs):bytes(nullptr){ load(ibfs); }
    ~Block(){ delete[] bytes; }

    void load(Ibfs& ibfs)
    {
        Byte8 _RESERVED;
        ibfs>>kind>>size;

        switch(kind)
        {
            case INST:
                ibfs>>_RESERVED;
                bytes = new Byte[size*sizeof(Instruction)];
                for(auto ptr = (Instruction *)bytes
                ;   ptr-(Instruction*)bytes<size
                ;   ++ptr)
                    ibfs>>*ptr;

                break;

            case TYPE:
                bytes = new Byte[size*sizeof(Type)];
                for(auto ptr = (Type *)bytes
                ;   ptr-(Type*)bytes<size
                ;   ++ptr)
                    ibfs>>*ptr;
                // std::cout << size << std::endl;
                if (size % 2 != 1)
                {
                    // std::cout << "ty:align\n";
                    auto dumb_ptr = new Byte8;
                    ibfs>>*dumb_ptr;
                    delete dumb_ptr;
                }
                break;

            case SYMB:
                bytes = new Byte[size*sizeof(Symbol)];
                for(auto ptr = (Symbol *)bytes
                ;   ptr-(Symbol*)bytes<size
                ;   ++ptr)
                    ibfs>>*ptr;
                // std::cout << size << std::endl;
                if (size % 2 != 1)
                {
                    // std::cout << "sy:align\n";
                    auto dumb_ptr = new Byte8;
                    ibfs>>*dumb_ptr;
                    delete dumb_ptr;
                }
                break;

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