#include "api.hpp"
#include "type.hpp"

namespace tc{
namespace ast{

namespace Th = type::helper;

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

void	API::Typing(Exprp expr, Typep type, const char *msg) 
{
	try{ this->unify(*(expr->type), *type); }
	catch(const char *_)
	{
		if(nullptr==msg)
			throw  _;
		else
			throw msg;
	}
	// unify will modify expr->type
	// ensure expr->type has such property : 
	// Either Infer 0
	// Or     Known T
	auto shape = ((type::Typ*)(expr->type->shape));
	if(type::Shape::Infer==shape->flag&&shape->id!=0)
		expr->type = &(this->type[shape->id]);
}

// nullptr -> Infer 0
// ...     -> Infer 0 
//          | Known
Typep   API::TypeInfer(Typep ty)
{
	if(nullptr==ty)
	{
		auto tid = this->type.nid();
		this->type.insert(Type(tid, Th::infer(0)));
		auto type = &(this->type[tid]);

		return type;
	}

	auto shape = ((type::Typ*)(ty->shape));
	if(type::Shape::Infer==shape->flag&&shape->id!=0)
		return &(this->type[shape->id]);
	else
		return ty;
}

Typep	API::TypeVar(Name name)
{
	if(name==this->type_name)
		return this->adt;
	return &(
		this->type[ // find data
			this->type[name] // find id
			]);
}

Typep	API::TypeRef(Typep type)
{
	auto id = this->type.nid();
	this->type.insert(Type(id, Th::ref(type->id)));
	return &(this->type[id]);
}

Typep	API::TypePtr(Typep type)
{
	auto id = this->type.nid();
	this->type.insert(Type(id, Th::ptr(type->id)));
	return &(this->type[id]);
}

Typep	API::TypeArr(Typep type, Byte8 size)
{
	auto id = this->type.nid();
	this->type.insert(Type(id, Th::array(type->id, size)));
	return &(this->type[id]);
}

void	API::TypeFunBeg()
{
	auto id = this->type.nid();
	this->type.insert(Type(id, Th::fun()));
	auto type = &(this->type[id]);

	this->func_types.push(type);
}
void	API::TypeFunArg(Typep type)
{
	auto fun = this->func_types.top();
	auto shape = ((type::Fun*)(fun->shape));
	shape->params.push_back(type->id);
}
Typep	API::TypeFunEnd(Typep rety)
{
	auto fun = this->func_types.top();
	auto shape = ((type::Fun*)(fun->shape));
	shape->retype = rety->id;

	this->func_types.pop();

	return fun;
}

}}