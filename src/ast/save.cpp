#include <iostream>
#include "../utils/obfstream.hpp"
#include "api.hpp"

namespace tc{
namespace ast{

// [TODO] : AST ~> IR
using Obfs = utils::obfstream;

void    save(Obfs& obfs, Insts& insts)
{
	obfs<<ir::Kind::INST<<Byte4(insts.size())<<RESERVED;
	for(auto& inst : insts)
		obfs<<inst;
}

void	API::save(string path, Exprp expr)
{
	std::cout<<"expr > "<<path<<std::endl;
	Obfs obfs(path);
    tc::ast::save(obfs, expr->insts);
}

}}