#include "api.hpp"
#include "type.hpp"

namespace tc{
namespace ast{

namespace Th = type::helper;

Typep	API::U()
{
	return &(this->type[0]);
}

Typep	API::B()
{
	return &(this->type[1]);
}

Typep	API::C()
{
	return &(this->type[2]);
}

Typep	API::I()
{
	return &(this->type[3]);
}

Typep	API::F()
{
	return &(this->type[4]);
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