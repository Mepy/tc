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
	auto ptrc = this->TypePtr(c); // T_PTRC


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
	auto type = this->TypeFunEnd(f); // T_I2F
	this->expr.insert(Expr(E_I2F, Eh::func(), type, ir::Symbol::CFun));
	this->expr.bind(E_I2F, "i2f");
	}

	{
	this->TypeFunBeg();
	this->TypeFunArg(f);
	auto type = this->TypeFunEnd(i); // T_F2I
	this->expr.insert(Expr(E_F2I, Eh::func(), type, ir::Symbol::CFun));
	this->expr.bind(E_F2I, "f2i");
	}

	// getc
	{
	this->TypeFunBeg();
	auto type = this->TypeFunEnd(c); // T_2C
	this->expr.insert(Expr(E_GETC, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_GETC, "getc");
	}

	// putc
	{
	this->TypeFunBeg();
	this->TypeFunArg(c);
	auto type = this->TypeFunEnd(u); // T_C2U
	this->expr.insert(Expr(E_PUTC, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_PUTC, "putc");
	}


	{ // geti
	this->TypeFunBeg();
	auto type = this->TypeFunEnd(i); // T_2I
	this->expr.insert(Expr(E_GETI, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_GETI, "geti");
	}

	{ // puti 
	this->TypeFunBeg();
	this->TypeFunArg(i);
	auto type = this->TypeFunEnd(u); // T_I2U
	this->expr.insert(Expr(E_PUTI, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_PUTI, "puti");
	}

	{ // gets
	this->TypeFunBeg();
	this->TypeFunArg(ptrc);
	auto type = this->TypeFunEnd(ptrc); // T_PC2PC
	this->expr.insert(Expr(E_GETS, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_GETS, "gets");
	}

	{ // puts
	this->TypeFunBeg();
	this->TypeFunArg(ptrc);
	auto type = this->TypeFunEnd(u); // T_PC2U
	this->expr.insert(Expr(E_PUTS, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_PUTS, "puts");
	}

	{ // sgeti
	this->TypeFunBeg();
	this->TypeFunArg(ptrc);
	auto type = this->TypeFunEnd(i); // T_PC2I
	this->expr.insert(Expr(E_SGETI, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_SGETI, "sgeti");
	}

	{ // getf
	this->TypeFunBeg();
	auto type = this->TypeFunEnd(f); // T_2F
	this->expr.insert(Expr(E_GETF, Eh::func(), type, ir::Symbol::CPrg));
	this->expr.bind(E_GETF, "getf");
	}

	this->TypeFunBeg();
	this->TypeFunArg(f);
	auto f2u = this->TypeFunEnd(u); // T_F2U

	{ // put1f
	this->expr.insert(Expr(E_PUT1F, Eh::func(), f2u, ir::Symbol::CPrg));
	this->expr.bind(E_PUT1F, "put1f");
	}

	{ // adt
	auto id = this->type.nid();
	this->type.insert(Type(id, Th::adt(), ir::type::ADT(id)));
	this->adt = &(this->type[id]);
	}

	{ // entry
	auto entry = this->new_block(ir::Kind::INST, 0, 0x0A24205952544E45L); // "ENTRY $\n"
	}
	
}
API::~API()
{

}


}}