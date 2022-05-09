#include <iostream>
#include "../utils/obfstream.hpp"
#include "api.hpp"

#include "ir_helper.hpp"

namespace tc{
namespace ast{


namespace Th = type::helper;
namespace Ih = ir::instruction;

// [TODO] : AST ~> IR
using Obfs = utils::obfstream;

void    save(Obfs& obfs, Insts& insts)
{
	obfs<<ir::Kind::INST<<Byte4(insts.size())<<RESERVED;
	for(auto& inst : insts)
		obfs<<inst;
}

inline void save_type(Context* context, Obfs& obfs)
{
    obfs<<ir::Kind::TYPE;
    auto pos = obfs.tell();

    obfs<<0<<RESERVED;

    Size size = 0;
    for(auto& type : context->type.def)
        if(type::Shape::Infer==type.shape->flag)
        {
            auto& id = ((type::Typ*)(type.shape))->id;
            id = ID(context->type[id].shape->flag);
        }
        else
        {
            auto ty = ((tc::ast::Type*)(&type));
            switch(ty->shape->flag)
            {
            case type::Shape::Fun:
            {
                auto shape = ((type::Fun*)(ty->shape));
                auto& params = shape->params;
                auto retype = shape->retype;
                auto p_size = params.size(); 
                switch(p_size)
                {
                case 0:
                {
                    auto block = context->new_block(ir::Kind::TFUN
                        , 1, Byte8(retype));
                    ty->type.id = block->id;
                    break;
                }
                case 1:
                {
                    auto block = context->new_block(ir::Kind::TFUN
                        , 2, (Byte8(params[0])<<32)+Byte8(retype));
                    ty->type.id = block->id;
                    break;
                }
                default:
                {
                    auto block = context->new_block(ir::Kind::TFUN
                        , p_size+1, (Byte8(params[0])<<32)+Byte8(retype));
                    
                    Size index=1;
                    for( ; index+3<p_size; index+=4)
                        block->insts.push_back(*(Inst*)(&params[index]));
                    
                    switch(p_size-index)
                    {
                    case 3:block->insts.push_back(
                        Ih::IDs(params[index], params[index+1], params[index+2])
                        ); break;
                    case 2:block->insts.push_back(
                        Ih::IDs(params[index], params[index+1])
                        ); break;
                    case 1:block->insts.push_back(
                        Ih::IDs(params[index])
                        ); break;
                    default: break;
                    }
                    ty->type.id = block->id;
                }
                }
            }
            
            case type::Shape::ADT:
            {
                auto shape = ((type::ADT*)(ty->shape));
                auto& cons = shape->cons;
                auto c_size= cons.size();
                switch (c_size)
                {
                case 0:
                {
                    auto block = context->new_block(ir::Kind::TADT, 0);
                    ty->type.id = block->id;
                    break;
                }
                case 1:
                {
                    auto block = context->new_block(ir::Kind::TADT, 0
                    , Byte8(cons[0]));
                    ty->type.id = block->id;
                    break;
                }
                default:
                {
                    auto block = context->new_block(ir::Kind::TADT, 0
                    , *(Byte8*)&cons[0]);
                    Size index=2;
                    for( ; index+3<c_size; index+=4)
                        block->insts.push_back(*(Inst*)(&cons[index]));
        
                    switch(c_size-index)
                    {
                    case 3:block->insts.push_back(
                        Ih::IDs(cons[index], cons[index+1], cons[index+2])
                        ); break;
                    case 2:block->insts.push_back(
                        Ih::IDs(cons[index], cons[index+1])
                        ); break;
                    case 1:block->insts.push_back(
                        Ih::IDs(cons[index])
                        ); break;
                    default: break;
                    }
                    ty->type.id = block->id;
                    break;
                }
                }
                break;
            }

            case type::Shape::Array:
            {
                auto shape = ((type::Array*)(ty->shape));
                auto block = context->new_block(ir::Kind::TARR, shape->id, shape->size);
                ty->type.id = block->id;
            }

            case type::Shape::Ref:
                ty->type.sort = ir::Type::Sort::Ptr;
            case type::Shape::Ptr:
                break;
            default: break;
            }
            
            obfs<<type.type;
            type.shape->flag = type::Shape::Flag(size);
            ++size;
        }
    if(1==size%2)
        obfs<<Byte8(0);
    auto cur = obfs.tell();
    obfs.seek(pos)<<size;
    obfs.seek(cur);
}

// [TODO]
void    API::save(string path)
{
    auto& shape = this->adt->shape;
    delete shape;
    shape = Th::infer(0);
    // delete undefined adt

    std::cout<<"module > "<<path<<std::endl;

    Obfs obfs(path);

    obfs<<Magic<<Version
        <<ir::Cat::EXEC;
    auto pos = obfs.tell();
    obfs<<Byte4(0)<<RESERVED;

    save_type(this, obfs);

    for(auto& block : this->block)
    {
        obfs<<block.kind;
        switch(block.kind)
        {
        case ir::Kind::INST:
            obfs<<((Byte4)(block.insts.size()))<<RESERVED;
            break;
        case ir::Kind::TFUN:
        case ir::Kind::TADT:
        case ir::Kind::TARR:
            obfs<<block.size<<block.extra;
            break;
        default: break;
        }
        for(auto& inst : block.insts)
            obfs<<inst;
    }
    obfs.seek(pos)<<Byte4(this->block.size()+2);
    
}

void	API::save(string path, Exprp expr)
{
	std::cout<<"expr > "<<path<<std::endl;
	Obfs obfs(path);
    tc::ast::save(obfs, expr->insts);
}

}}