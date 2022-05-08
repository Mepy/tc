#include <iostream>
#include "../utils/obfstream.hpp"
#include "api.hpp"

#include "ir_helper.hpp"

namespace tc{
namespace ast{


namespace Th = ir::type;
// [TODO] : AST ~> IR
using Obfs = utils::obfstream;

void    save(Obfs& obfs, Insts& insts)
{
	obfs<<ir::Kind::INST<<Byte4(insts.size())<<RESERVED;
	for(auto& inst : insts)
		obfs<<inst;
}

// [TODO]
void    API::save(string path)
{
    std::cout<<"module > "<<path<<std::endl;

    Obfs obfs(path);
    
    obfs<<ir::Kind::TYPE<<this->type.def<<RESERVED;
    for(auto& type : this->type.def)
    switch(type.shape->flag)
    {
    case type::Shape::U: obfs<<Th::Unit (); break;
    case type::Shape::B: obfs<<Th::Bool (); break;
    case type::Shape::C: obfs<<Th::Char (); break;
    case type::Shape::I: obfs<<Th::Int  (); break;
    case type::Shape::F: obfs<<Th::Float(); break;
    default: break;
    }
}

void	API::save(string path, Exprp expr)
{
	std::cout<<"expr > "<<path<<std::endl;
	Obfs obfs(path);
    tc::ast::save(obfs, expr->insts);
}

}}