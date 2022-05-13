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

	auto u = &this->type[0];
	this->expr.insert(Expr(0, Eh::u(), u), ir::Symbol::Const);
	this->expr.bind(0, Name("unit"));

	this->type.insert(Type(5, Th::adt(), ir::type::ADT(6)));

	this->adt = &(this->type[5]);
}
API::~API()
{

}

/* type */

bool	API::TypeEq(Exprp lhs, Exprp rhs)
{
	try{ this->unify(*(lhs->type), *(rhs->type)); }
	catch(const char* msg)
	{
		std::cerr<<"Unification Error : "<<msg<<std::endl;
		return false;
	}

	// unify will modify expr->type
	// ensure expr->type has such property : 
	// Either Infer 0
	// Or     Known T
	{
	auto shape = ((type::Typ*)(lhs->type->shape));
	if(type::Shape::Infer==shape->flag&&shape->id!=0)
		lhs->type = &(this->type[shape->id]);
	}
	{
	auto shape = ((type::Typ*)(rhs->type->shape));
	if(type::Shape::Infer==shape->flag&&shape->id!=0)
		rhs->type = &(this->type[shape->id]);
	}

	return true;
}
// [TODO] : Check this function
bool	API::Typing(Exprp expr, Typep type) 
{
	try{ this->unify(*(expr->type), *type); }
	catch(const char* msg)
	{
		std::cerr<<"Unification Error : "<<msg<<std::endl;
		return false;
	}
	// unify will modify expr->type
	// ensure expr->type has such property : 
	// Either Infer 0
	// Or     Known T
	auto shape = ((type::Typ*)(expr->type->shape));
	if(type::Shape::Infer==shape->flag&&shape->id!=0)
		expr->type = &(this->type[shape->id]);

	return true;
}

}}