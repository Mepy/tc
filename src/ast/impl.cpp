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
	this->type.insert(Type(0, Th::u(), ir::type::Unit ()));
	this->type.insert(Type(1, Th::b(), ir::type::Bool ()));
	this->type.insert(Type(2, Th::c(), ir::type::Char ()));
	this->type.insert(Type(3, Th::i(), ir::type::Int  ()));
	this->type.insert(Type(4, Th::f(), ir::type::Float()));

	this->type.bind(0, Name("Unit" ));
	this->type.bind(1, Name("Bool" ));
	this->type.bind(2, Name("Char" ));
	this->type.bind(3, Name("Int"  ));
	this->type.bind(4, Name("Float"));

	{
	auto iter = this->type.def.begin();
	this->u = ((tc::ast::Type*)(&*iter)); ++iter;
	this->b = ((tc::ast::Type*)(&*iter)); ++iter;
	this->c = ((tc::ast::Type*)(&*iter)); ++iter;
	this->i = ((tc::ast::Type*)(&*iter)); ++iter;
	this->f = ((tc::ast::Type*)(&*iter)); ++iter;
	}

	auto u = &this->type[0];
	this->expr.insert(Expr(0, Eh::u(), u, 0));
	this->expr.bind(0, Name("unit"));
	auto b = &this->type[1];
	this->expr.insert(Expr(1, Eh::b(true), b, 0));
	this->expr.bind(1, Name("true"));
	this->expr.insert(Expr(2, Eh::b(false), b, 0));
	this->expr.bind(1, Name("false"));

	this->type.insert(Type(5, Th::adt(), ir::type::ADT(6)));

	this->adt = &(this->type[5]);
}
API::~API()
{

}


}}