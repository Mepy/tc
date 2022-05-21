#include "api.hpp"
#include "stmt.hpp"
#include "type.hpp"
#include "expr.hpp"

#include <iostream>
#include "ir_helper.hpp"

namespace tc{
namespace ast{

namespace Th = type::helper;
namespace Eh = expr::helper;

// [TODO] : AST ~> IR

API::API()
{
	this->type.insert(Type(T_UNIT , Th::u(), ir::type::Unit ()));
	this->type.insert(Type(T_BOOL , Th::b(), ir::type::Bool ()));
	this->type.insert(Type(T_CHAR , Th::c(), ir::type::Char ()));
	this->type.insert(Type(T_INT  , Th::i(), ir::type::Int  ()));
	this->type.insert(Type(T_FLOAT, Th::f(), ir::type::Float()));

	this->type.bind(T_UNIT , "Unit" );
	this->type.bind(T_BOOL , "Bool" );
	this->type.bind(T_CHAR , "Char" );
	this->type.bind(T_INT  , "Int"  );
	this->type.bind(T_FLOAT, "Float");

	{
	auto iter = this->type.def.begin();
	this->u = ((tc::ast::Type*)(&*iter)); ++iter;
	this->b = ((tc::ast::Type*)(&*iter)); ++iter;
	this->c = ((tc::ast::Type*)(&*iter)); ++iter;
	this->i = ((tc::ast::Type*)(&*iter)); ++iter;
	this->f = ((tc::ast::Type*)(&*iter)); ++iter;
	}


	this->expr.insert(Expr(E_UNIT, Eh::u(), this->u, 0));
	this->expr.bind(E_UNIT , "unit" );
	this->unit = &this->expr[E_UNIT];

	this->expr.insert(Expr(E_TRUE, Eh::b(true), this->b, 0));
	this->expr.bind(E_TRUE , "true" );
	this->expr.insert(Expr(E_FALSE, Eh::b(false), this->b, 0));
	this->expr.bind(E_FALSE, "false");

	{
	this->TypeFunBeg();
	this->TypeFunArg(i);
	auto type = this->TypeFunEnd(f);
	this->expr.insert(Expr(E_I2F, Eh::func(), type, ir::Symbol::CFun));
	this->expr.bind(E_I2F, "i2f");
	}

	{
	this->TypeFunBeg();
	this->TypeFunArg(f);
	auto type = this->TypeFunEnd(i);
	this->expr.insert(Expr(E_F2I, Eh::func(), type, ir::Symbol::CFun));
	this->expr.bind(E_F2I, "f2i");
	}
	
	{ // entry
	auto entry = this->new_block(ir::Kind::INST, 0, 0x0A24205952544E45L); // "ENTRY $\n"
	}

	{ // geti
	this->TypeFunBeg();
	auto type = this->TypeFunEnd(i);
	this->expr.insert(Expr(E_GETI, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_GETI, "geti");
	}

	{ // puti 
	this->TypeFunBeg();
	this->TypeFunArg(i);
	auto type = this->TypeFunEnd(u);
	this->expr.insert(Expr(E_PUTI, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_PUTI, "puti");
	}

	{ // puts
	auto cptr = this->TypePtr(c);
	this->TypeFunBeg();
	this->TypeFunArg(cptr);
	auto type = this->TypeFunEnd(u);
	this->expr.insert(Expr(E_PUTS, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_PUTS, "puts");
	}

	// putc
	{
	this->TypeFunBeg();
	this->TypeFunArg(c);
	auto type = this->TypeFunEnd(u);
	this->expr.insert(Expr(E_PUTC, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_PUTC, "putc");
	}

	{ // adt
	auto id = this->type.nid();
	this->type.insert(Type(id, Th::adt(), ir::type::ADT(id)));
	this->adt = &(this->type[id]);
	}
	
}
API::~API()
{

}


}}