#ifndef tc_ast_ir_codegen_hpp
#define tc_ast_ir_codegen_hpp

#include "../ast/ir.hpp"
#include "../utils/ibfstream.hpp"
#include <iostream>
#include <string>
#pragma pack(push)
#pragma pack(4)

namespace tc{
namespace ast{
namespace ir{
namespace codegen{

using Ibfs = tc::utils::ibfstream;
struct Block
{
    /* align 16 Bytes, 8 Bytes reserve */
    Kind kind;
    union {
        struct {
        Size size;
        Byte8 Len;
        } ord; // ordinary for most situation
        struct {
        ID type;
        ID param;
        ID body;
        } func;
        struct {
        ID type;
        Byte8 Len;
        } arr;
        struct{
        Size size;
        ID ret;
        ID param;
        } typefunc; 
    } head;
#pragma pack(pop)
    union Extra {
        Instruction* insts;
        Type*        types;
        Symbol*      symbs;
        Char*        chars;
        ID*            ids;
        Byte*        bytes;
        Extra():bytes(nullptr){}
    } extra;


    Block():kind(Kind::KUNO){}
    Block(Ibfs& ibfs){ load(ibfs); }
    ~Block(){ delete[] extra.bytes; }

    void load(Ibfs& ibfs)
    {
        ibfs>>kind;

        switch(kind)
        {
        case INST:
        {
            auto& ord = head.ord;
            auto& size = ord.size;
            ibfs>>ord;
            extra.bytes = new Byte[ord.size*sizeof(Instruction)];
            for(auto ptr = extra.insts
            ;   ptr-extra.insts<size
            ;   ++ptr)
                ibfs>>*ptr;

            break;
        }
        case TYPE:
        {
            auto& ord = head.ord;
            auto& size = ord.size;
            ibfs>>size;
            extra.bytes = new Byte[ord.size*sizeof(Type)];
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
            auto& ord = head.ord;
            auto& size = ord.size;
            ibfs>>size;
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
            auto& ord = head.ord;
            auto& size = ord.size;
            extra.bytes = new Byte[size*sizeof(Char)];
            for(auto ptr = extra.chars
            ;   ptr-extra.chars<size
            ;   ++ptr)
                ibfs>>*ptr;

            ibfs.move((8-size)%16); // align
            break;
        }
        case FUNC:
        case BRCH:
        {
            ibfs>>head.func;
            break;
        }
        case TARR:
        {
            ibfs>>head.ord;
            break;
        }
        case MTCH:
        case PARA:
        case ARGS:
        case TFUN:
        {
            auto& ord = head.ord;
            auto& size = ord.size;
            ibfs>>size;
            extra.bytes = new Byte[size*sizeof(ID)];
            for(auto ptr = extra.ids
            ;   ptr-extra.ids<size
            ;   ++ptr)
                ibfs>>*ptr;
            // alignment
            ibfs.move(((2-size)%4) * sizeof(ID));

            break;
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
    
    Module():blocks(nullptr){}
    Module(std::string path){ load(path); }
    ~Module(){ if(nullptr!=blocks) delete[] blocks; }

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