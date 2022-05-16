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

inline void shortcut(Context* context, ID& id)
{
    auto& type = context->type.def[id];
    auto shape = ((type::Typ*)(type.shape));
    if(type::Shape::Infer==shape->flag)
    {
        auto& tid = shape->id;
        std::cout<<"id="<<type.id<<" ~> id="<<tid<<std::endl;
        id = tid = context->type.def[tid].id;
    }
}

inline void save_type(Context* context, Obfs& obfs)
{
    obfs<<ir::Kind::TYPE;
    auto pos = obfs.tell();

    obfs<<0;

    Size size = 0;
    for(auto& type : context->type.def)
        if(type::Shape::Infer==type.shape->flag)
        {
            type.shape->flag=type::Shape::Saved;
            auto& id = ((type::Typ*)(type.shape))->id;
            id = context->type.shortcut(id);
        }
        else
        {
            auto ty = ((tc::ast::Type*)(&type));
            switch(ty->shape->flag)
            {
            case type::Shape::Fun:
            {
                ty->type.sort = ir::Type::Sort::Func;
                auto shape = ((type::Fun*)(ty->shape));
                auto& params = shape->params;
                
                for(auto& param:params)
                    param = context->type.shortcut(param);
                    
                auto retype = context->type.shortcut(shape->retype);
                
                auto p_size = params.size(); 
                switch(p_size)
                {
                case 0:
                {
                    auto block = context->new_block(ir::Kind::TFUN
                        , 1, Byte8(retype));
                    ty->type.id = block->id+2;
                    break;
                }
                case 1:
                {
                    auto block = context->new_block(ir::Kind::TFUN
                        , 2, (Byte8(params[0])<<32)|Byte8(retype));
                    ty->type.id = block->id+2;

                    break;
                }
                default:
                {
                    auto block = context->new_block(ir::Kind::TFUN
                        , p_size+1, (Byte8(params[0])<<32)|Byte8(retype));
                    
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
                    ty->type.id = block->id+2;
                }
                }
                break;
            }

            case type::Shape::ADT:
            {
                auto shape = ((type::ADT*)(ty->shape));
                auto block = context->new_IDs(ir::Kind::TADT, shape->cons);
                ty->type.id = block->id+2;
                break;
            }

            case type::Shape::Array:
            {
                ty->type.sort = ir::Type::Sort::Array;
                
                auto shape = ((type::Array*)(ty->shape));
                auto id = context->type.shortcut(shape->id);
                auto block = context->new_block(ir::Kind::TARR, id, shape->size);
                ty->type.id = block->id+2;
                break;
            }

            case type::Shape::Ref: // [TODO]
                ty->type.sort = ir::Type::Sort::Ptr;
            case type::Shape::Ptr:
            {
                
                auto id = ((type::Typ*)(ty->shape))->id;
                id = ((type::Typ*)(context->type.def[id].shape))->id;
                ty->type.id   = id;
                break;
            }
            default: break;
            }
            obfs<<type.type;
            delete ty->shape;
            ty->shape = Th::saved(size);
            ++size;
        }
    
    if(0==size%2)
        obfs<<Byte8(0);
    auto cur = obfs.tell();
    obfs.seek(pos)<<size;
    obfs.seek(cur);
}

inline void save_symb(Context* context, Obfs& obfs)
{
    Size size = context->expr.def.size();
    obfs<<ir::Kind::SYMB<<size;

    auto iter = context->expr.def.begin();

    obfs<<iter->sort<<0; ++iter; // E_UNIT
    obfs<<iter->sort<<0; ++iter; // E_TRUE
    obfs<<iter->sort<<0; ++iter; // E_FALSE
    obfs<<iter->sort<<0; ++iter; // E_I2F
    obfs<<iter->sort<<0; ++iter; // E_F2I

    for( ; iter!=context->expr.def.end(); ++iter)
    {
        auto sort = iter->sort;
        auto tid = context->type.shortcut(iter->type->id);
        obfs<<sort;
        switch(sort)
        {
        case ir::Symbol::Sort::CFun:
        case ir::Symbol::Sort::CPrg:
        {
            auto block = context->new_func(tid, iter->params, iter->body);
            obfs<<block->id+2;
            break;
        }
        default:
            obfs<<tid;
            break;
        }
        
    }
    if(0==size%2)
        obfs<<Byte8(0);
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
    save_symb(this, obfs);
    
    for(auto& block : this->block)
    {
        obfs<<block.kind;
        switch(block.kind)
        {
        case ir::Kind::INST:
            obfs<<((Byte4)(block.insts.size()))<<block.extra;
            break;
        case ir::Kind::TFUN:
        case ir::Kind::TADT:
        case ir::Kind::TARR:
        case ir::Kind::CSTR:
        case ir::Kind::PARA:
        case ir::Kind::ARGS:
        case ir::Kind::BRCH:
        case ir::Kind::FUNC:
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

void	API::save(Stmtp root)
{
    auto entry = &this->block[0];

    if(nullptr==root->beg)
        entry->insts.eat(root->insts);
    else
        entry->insts.push_back(Ih::Jump(root->beg->id+2));
}

}}