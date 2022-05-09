#include "api.hpp"
#include "stmt.hpp"
#include "type.hpp"
#include "expr.hpp"

#include <iostream>
#include "context.hpp"
#include "ir_helper.hpp"

namespace tc{
namespace ast{

namespace Th = type::helper;
namespace Eh = expr::helper;
namespace Ih = ir::instruction;

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

	this->expr.insert(Expr(0, Eh::u(), this->U()));
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
		std::cout<<"Unification Error : \n"
		<<msg<<std::endl;
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
		std::cout<<"Unification Error : "<<msg<<std::endl;
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

Typep	API::U()
{
	return &(this->type[1]);
}

Typep	API::B()
{
	return &(this->type[2]);
}

Typep	API::C()
{
	return &(this->type[3]);
}

Typep	API::I()
{
	return &(this->type[4]);
}

Typep	API::F()
{
	return &(this->type[5]);
}

// [Improve] : name == this->type_name
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

Typep	API::TypeArr(Typep type, Size size)
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

/* cell & expr */

Cell*	API::CellVar(Name name)
{
	auto id = this->expr[name];
	if(0==id)
		throw "API::CellVar Name Not Found;";
	auto cell = &(this->expr[id]);
	auto type = cell->type;

	if(type::Shape::Ref!=type->shape->flag)
		throw "API::CellVar Not A Ref;";
	
	return (Cell*)cell;
}

Exprp   API::Dereference(Exprp ref)
{
	auto r_id = ref->id;
	auto r_type = ref->type;
	auto shape = ((type::Typ*)(r_type->shape));
	auto v_type = &(this->type[shape->id]);
	auto v_id = this->expr.nid();
	this->expr.insert(Expr(v_id, Eh::get(r_id), v_type, Ih::Get(v_id, r_id)));
	auto expr = &(this->expr[v_id]);

	expr->inst_front(ref);

	return expr;
}
Exprp   API::AutoDereference(Exprp expr)
{
	if(type::Shape::Ref==expr->type->shape->flag)
		return Dereference(expr);
	else
		return expr;
}
Exprp	API::ExprVar(Name name)
{
	auto id = this->expr[name];

	if(0==id)
		throw "API::ExprVar Name Not Found;";

	auto expr = &(this->expr[id]);

	return this->AutoDereference(expr);
}

Exprp	API::ExprVarRef(Name name)
{
	auto id = this->expr[name];
	if(0==id)
		throw "API::ExprVarRef Name Not Found;";

	auto expr = &(this->expr[id]);
	auto type = expr->type;

	if(type::Shape::Ref!=type->shape->flag)
		throw "API::ExprVarRef Not A Ref;";
	
	return expr;	
}

void	API::AppBeg(Exprp func) // = nullptr
{
	if(nullptr==func)
		func = this->funcs.top();
	

	if(type::Shape::Fun!=func->type->shape->flag)
		throw "API::AppBeg Not A Fun Type;";

	auto shape = ((type::Fun*)(func->type->shape));
	auto retype_id = shape->retype;

	auto retype = &(this->type[retype_id]);

	auto id = this->expr.nid();
	this->expr.insert(Expr(id, Eh::call(func->id), retype));
	auto call = &(this->expr[id]);

	this->calls.push(call);
}
void    API::AppForceRetRef()
{
	auto call = this->calls.top();
	auto call_shape = ((expr::Call*)(call->shape));
	auto func_id = call_shape->func;

	auto func = &(this->expr[func_id]);
	auto shape = (type::Fun*)(func->type->shape);
	auto retype = &(this->type[shape->retype]);

	if(type::Shape::Ref!=retype->shape->flag)
		throw "API::AppForceRetRef Return Not A Ref;";

	call_shape->flag = expr::Shape::CallRef;
}
void	API::AppArg(Exprp arg)
{
	auto call = this->calls.top();
	auto shape = ((expr::Call*)(call->shape));
	shape->args.push_back(arg->id);
}

Cell*	API::CellAppEnd()
{
	auto call = this->calls.top();
	auto call_shape = ((expr::Call*)(call->shape));
	auto func_id = call_shape->func;

	auto func = &(this->expr[func_id]);
	auto shape = (type::Fun*)(func->type->shape);
	auto retype = &(this->type[shape->retype]);
	
	if(type::Shape::Ref!=retype->shape->flag)
		throw "API::CellAppEnd Not A Ref;";
	
	call_shape->flag = expr::Shape::CallRef;

	return (Cell*)call;
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

Exprp  API::Element(Exprp array, Exprp index)
{
	array = this->AutoDereference(array);
	index = this->AutoDereference(index);

	Typing(index, this->I());

	auto array_type = array->type;

	switch(array_type->shape->flag)
	{
	case type::Shape::Array:
	{
		// [TODO] : static array bound check if possible
		auto tid = ((type::Array*)(array_type->shape))->id;
		auto type = &(this->type[tid]);

		auto eid = this->expr.nid();
		this->expr.insert(Expr(eid, Eh::element(array->id, index->id), type));
		auto expr = &(this->expr[eid]);
		return expr;
	}
	case type::Shape::Ptr:
	{
		auto tid = ((type::Typ*)(array_type->shape))->id;
		auto type = &(this->type[tid]);
		auto eid = this->expr.nid();
		this->expr.insert(Expr(eid, Eh::element(array->id, index->id), type));
		auto expr = &(this->expr[eid]);
		return expr;
	}
	case type::Shape::Infer: // Infer Select : Ptr T
	{
		auto tid = this->type.nid();
		this->type.insert(Type(tid, Th::infer()));
		auto type = &(this->type[tid]);
		auto shape = ((type::Typ*)(array_type->shape));
		shape->flag = type::Shape::Ptr;
		shape->id   = tid;

		auto eid = this->expr.nid();
		this->expr.insert(Expr(eid, Eh::element(array->id, index->id), type));
		auto expr = &(this->expr[eid]);
		return expr;
	}
	default:
		throw "API::Element Not A Array-like Type;";
	}
}

Exprp	API::ExprAppEnd()
{
	auto call = this->calls.top();

	auto call_shape = ((expr::Call*)(call->shape));
	auto func_id = call_shape->func;

	auto func = &(this->expr[func_id]);
	auto shape = (type::Fun*)(func->type->shape);
	auto retype = &(this->type[shape->retype]);


	if(type::Shape::Ref    ==retype->shape->flag
	&& expr::Shape::CallRef==   call_shape->flag)		
		return this->Dereference(call); // auto dereference
	else
		return call;
}

Cell*	API::CellEle(Cell* cell, Exprp index)
{
	auto expr = this->Element((Exprp)cell, index);

	expr->shape->flag = expr::Shape::EleRef;

	expr->type = this->TypeRef(expr->type);

	return (Cell*)expr;
}

Exprp	API::ExprEle(Exprp array, Exprp index)
{
	return this->Element(array, index);
}

Exprp	API::ExprEleRef(Exprp array, Exprp index)
{
	auto expr = this->Element(array, index);

	expr->shape->flag = expr::Shape::EleRef;

	expr->type = this->TypeRef(expr->type);

	return expr;
}

Exprp	API::ExprEleAddr(Exprp array, Exprp index)
{
	auto expr = this->Element(array, index);
	expr->shape->flag = expr::Shape::EleAddr;
	return expr;
}

Exprp	API::B(Bool b)
{
	auto type = this->B();
    auto id = this->expr.nid();
	this->expr.insert(Expr(id, Eh::b(b), type));
	auto expr = &(this->expr[id]);

	expr->insts.push_back(Ih::BImm(id, b));

	return expr;
}

Exprp	API::C(Char c)
{
	auto type = this->C();
    auto id = this->expr.nid();
	this->expr.insert(Expr(id, Eh::c(c), type));
	auto expr = &(this->expr[id]);
	
	return expr;
}

Exprp	API::S(Str s)
{
	auto tid = this->type.nid();
	this->type.insert(Type(tid, Th::array(3, s.length()+1)));
	// 3 == this->C().id
	auto type = &(this->type[tid]);

    auto eid = this->expr.nid();
	this->expr.insert(Expr(eid, Eh::s(s), type));
	auto expr = &(this->expr[eid]);
	
	return expr;
}

Exprp	API::I(Int i)
{
	auto type = this->I();
    auto id = this->expr.nid();
	this->expr.insert(Expr(id, Eh::i(i), type, Ih::IImm(id, i)));
	auto expr = &(this->expr[id]);
	return expr;
}

Exprp	API::F(Float f)
{
	auto type = this->F();
    auto id = this->expr.nid();
	this->expr.insert(Expr(id, Eh::f(f), type));
	auto expr = &(this->expr[id]);
	
	return expr;
}


void	API::ExprFunBeg()
{
	this->expr.scope_beg();

	auto retype = this->TypeInfer();

	auto tid = this->type.nid();
	this->type.insert(Type(tid, Th::fun(retype->id)));
	auto type = &(this->type[tid]);

	auto eid = this->expr.nid();
	this->expr.insert(Expr(eid, Eh::func(), type));
	auto func = &(this->expr[eid]);

	this->funcs.push(func);
	this->funcs_retyck.push(func);
}

void	API::ExprFunRefArg(Name name, Typep type) // = nullptr
{
	type = this->TypeInfer(type);
	type = this->TypeRef(type);

	this->ExprFunArg(name, type);
}

void	API::ExprFunArg(Name name, Typep type) // = nullptr
{
	type = this->TypeInfer(type);

	auto id = this->expr.nid();

	this->expr.insert(Expr(id, Eh::param(), type));

	if(name!="_")
		this->expr.bind(id, name);

	auto func = this->funcs_retyck.top();

	((expr::Func*)(func->shape))
		->params.push_back(id);
	((type::Fun*)(func->type->shape))
		->params.push_back(type->id);
}

Exprp	API::ExprFunExpr(Exprp expr)
{
	return this->ExprFunStmt(this->Ret(expr));
}

Exprp	API::ExprFunStmt(Stmtp stmt)
{
	this->expr.scope_end();
	auto func = this->funcs.top();

	this->funcs.pop();
	this->funcs_retyck.pop();

	auto shape = ((expr::Func*)(func->shape));

	shape->body = stmt;

	return func;
}

Exprp	API::ExprPtr(Cell* cell)
{
	auto _cell = ((Exprp)(cell));
	auto cell_type =_cell->type;
	auto shape = ((type::Typ*)(cell_type->shape));

	if(type::Shape::Ref!=shape->flag)
		throw "API::ExprPtr of Not A Ref.";
	
	auto type = &(this->type[shape->id]);

	auto eid = this->expr.nid();

	this->expr.insert(Expr(eid, Eh::addr(_cell->id), type));

	auto expr = &(this->expr[eid]);

	return expr;
}

void	API::MatchBeg(Exprp expr)
{
	this->expr.scope_beg();

	auto id = this->expr.nid();

	this->expr.insert(Expr(id, Eh::match(expr->id), this->TypeInfer()));

	auto match = &(this->expr[id]);

	this->matches.push(match);
}

void	API::MatchBranchBeg(Name name)
{
	auto match = this->matches.top();

	auto shape = ((expr::Match*)(match->shape));

	auto id = this->expr[name];
	auto constructor = &(this->expr[id]);

	if(expr::Shape::Constructor!=constructor->shape->flag)
		throw "API::MatchBranchBeg Not A Constructor.";

	auto tid = this->type.nid();

	this->type.insert(Type(tid, Th::branch(match->type->id)));
	
	auto branch_type = &(this->type[tid]);

	((type::Fun*)(branch_type->shape))->params = ((type::Fun*)(constructor->type->shape))->params;

	auto branch_id = this->expr.nid();

	this->expr.insert(Expr(branch_id, Eh::branch(), branch_type));
	shape->branches.push_back(id);

	auto branch = &(this->expr[branch_id]);

	this->funcs_retyck.push(branch);
}

void	API::MatchBranchArg(Name name)
{
	//	if(name=='_') // [TODO] : _
	//		return ;
	auto branch = this->funcs_retyck.top();
	auto shape = ((expr::Func*)(branch->shape));
	auto index = shape->params.size();
	auto& params = ((type::Fun*)(branch->type->shape))->params;

	if(index>=params.size())
		throw "API::MatchBranch Too Many Arguments.";

	auto tid = params[index];
	auto type = &(this->type[tid]);
	
	this->ExprFunArg(name, type);
}

void	API::MatchBranchExpr(Exprp expr)
{
	this->MatchBranchStmt(this->Ret(expr));
}

void	API::MatchBranchStmt(Stmtp stmt)
{
	this->ExprFunStmt(stmt);
}

Exprp	API::MatchEnd()
{
	auto match = this->matches.top();
	this->matches.pop();
	return match;
}

Exprp	API::Asgn(Cell* cell, Oper oper, Exprp value)
{

	auto ref = (Exprp)cell;
	auto shape = ((type::Typ*)(ref->type->shape));

	if(type::Shape::Ref!=shape->flag)
		throw "API::Asgn Cell Not A Ref Type;";

	if(Oper::Undefined!=oper)
		value = this->BinOp(ref, oper, value);


	auto id = this->expr.nid();

	this->expr.insert(Expr(id, Eh::set(ref->id, value->id), value->type, Ih::Set(ref->id, value->id)));

	auto expr = &(this->expr[id]);

	expr->inst_front(value);

	return expr;
}

Exprp	API::UnOp(Oper oper, Exprp expr)
{
	auto i = this->I();
	auto f = this->F();
	switch(oper)
	{
	case Pos:
	case Neg:
	{
		switch(expr->type->shape->flag)
		{
		case type::Shape::F:
		{
			auto id = this->expr.nid();
			this->expr.insert(Expr(id
			, 	new expr::Unary(
					expr::Shape::Flag((oper-Pos)+int(expr::Shape::Pos))
					, expr->id)
			, f));
			return &(this->expr[id]);
		}
		case type::Shape::Infer:
			Typing(expr, i);
			std::cout<<"WARNING : Select Int for + - T;"<<std::endl;
		case type::Shape::I:
		{
			auto id = this->expr.nid();
			this->expr.insert(Expr(id
			, 	new expr::Unary(
					expr::Shape::Flag((oper-Pos)+int(expr::Shape::Pos))
					, expr->id)
			, i));
			return &(this->expr[id]);
		}
		default:
			throw "API::UnOp + - Neither Int Nor Float;";
		}
	}
	default:
		throw "API::UnOp Unknown Op;";
	}
}

Exprp   API::Binary(expr::Shape::Flag flag, Exprp lhs, Exprp rhs, Typep type)
{
	auto id = this->expr.nid();

	
	this->expr.insert(Expr(id, new expr::Binary(flag, lhs->id, rhs->id), type));

	auto expr = &(this->expr[id]);
	auto& insts = expr->insts;
	switch(flag)
	{
	case expr::Shape::Flag::IAdd: insts.push_back(Ih::IAdd(id, lhs->id, rhs->id)); break;
	case expr::Shape::Flag::ISub: insts.push_back(Ih::ISub(id, lhs->id, rhs->id)); break;
	case expr::Shape::Flag::IMul: insts.push_back(Ih::IMul(id, lhs->id, rhs->id)); break;
	case expr::Shape::Flag::IDiv: insts.push_back(Ih::IDiv(id, lhs->id, rhs->id)); break;
	case expr::Shape::Flag::Mod : insts.push_back(Ih::IMod(id, lhs->id, rhs->id)); break;
	case expr::Shape::Flag::Lt  : 
	{
		switch(type->shape->flag)
		{
		case type::Shape::I: insts.push_back(Ih::ILt(id, lhs->id, rhs->id)); break;
		case type::Shape::F: insts.push_back(Ih::FLt(id, lhs->id, rhs->id)); break;
		default: /* Ptr T */ insts.push_back(Ih::PLt(id, lhs->id, rhs->id)); break;
		}
		expr->type = this->B();
		break;
	}
	default:
		break;
	}
	expr->inst_front(rhs);
	expr->inst_front(lhs);

	return expr;
}

Exprp	API::BinOp(Exprp lhs, Oper oper, Exprp rhs)
{
	// auto dereference if needed
	lhs = AutoDereference(lhs);
	rhs = AutoDereference(rhs);



	auto b = this->B();
	auto i = this->I();
	auto f = this->F();
	switch(oper)
	{
	case PtrAdd:
		Typing(rhs, i);
		// if lhs : Infer T
		if(false==Typing(lhs, this->TypePtr(this->TypeInfer())))
			throw "API::BinOp &+ Not a Ptr T;";
		return this->Binary(expr::Shape::PtrAdd, lhs, rhs, lhs->type);
	case PtrSub:
		Typing(rhs, i);
		if(false==Typing(lhs, this->TypePtr(this->TypeInfer())))
			throw "API::BinOp &- Not a Ptr T;";
		return this->Binary(expr::Shape::PtrSub, lhs, rhs, lhs->type);
	case AddPtr:
		Typing(lhs, i); 
		if(false==Typing(lhs, this->TypePtr(this->TypeInfer())))
			throw "API::BinOp +& Not a Ptr T;";
		return this->Binary(expr::Shape::PtrAdd, rhs, lhs, rhs->type);
	case Mod:
	case LShift: 
	case RShift:
	case BNot:
	case BAnd:
	case BOr:
	case BXOr:
		Typing(lhs, i);
		Typing(rhs, i);
		return this->Binary(
			expr::Shape::Flag((oper-Mod)+int(expr::Shape::Mod))
			, lhs, rhs, i
		);
	case LNot:
	case LAnd:
	case LOr :
	case LXOr:
		Typing(lhs, b);
		Typing(rhs, b);
		return this->Binary(
			expr::Shape::Flag((oper-LNot)+int(expr::Shape::LNot))
			, lhs, rhs, i
		);
	case FAdd:
	case FSub:
	case FMul:
	case FDiv:
		Typing(lhs, f);
		Typing(rhs, f);
		return this->Binary(
			expr::Shape::Flag((oper-FAdd)+int(expr::Shape::FAdd))
			, lhs, rhs, f
		);
	case Eq:
	case Neq:
		if(false==TypeEq(lhs, rhs))
			throw "API::BinOp ==, != Type NOT Equal;";
		return this->Binary(
			expr::Shape::Flag((oper-Eq)+int(expr::Shape::Eq))
			, lhs, rhs, lhs->type
		);
	case Lt:
	case Gt:
	case Leq:
	case Geq:
	{
		if(false==TypeEq(lhs, rhs))
			throw "API::BinOp <, <=, >, >= Type NOT Equal;";
		
		switch(lhs->type->shape->flag)
		{
		case type::Shape::Ptr:
			return this->Binary(
				expr::Shape::Flag((oper-Lt)+int(expr::Shape::Lt))
				, lhs, rhs, lhs->type
			);
		case type::Shape::F:
			return this->Binary(
				expr::Shape::Flag((oper-Lt)+int(expr::Shape::Lt))
				, lhs, rhs, f
			);
		case type::Shape::Infer: // Select Infer Int Op Int
			std::cout<<"WARNING : Select Int for <, <=, >, >=;"<<std::endl;
			Typing(lhs, i);
		case type::Shape::I:
			return this->Binary(
				expr::Shape::Flag((oper-Lt)+int(expr::Shape::Lt))
				, lhs, rhs, i
			);
		default :
			throw "API::BinOp <, <=, >, >= Neither Int Nor Float;";
		}
	}
	case Mul:
	case Div:
	{
		if(false==TypeEq(lhs, rhs))
			throw "API::BinOp * / Type NOT Equal;";
		switch(lhs->type->shape->flag)
		{
		case type::Shape::F:
			return this->Binary(
				expr::Shape::Flag((oper-Mul)+int(expr::Shape::FMul))
				, lhs, rhs, f
			);
		case type::Shape::Infer:
			Typing(lhs, i);
			std::cout<<"WARNING : Select Int for * / ;"<<std::endl;
		case type::Shape::I:
			return this->Binary(
				expr::Shape::Flag((oper-Mul)+int(expr::Shape::IMul))
				, lhs, rhs, i
			);
		default:
			throw "API::BinOp * / Neither Int Nor Float;";
		}
	}
	case Sub:
	{
		switch(rhs->type->shape->flag)
		{
		case type::Shape::F:
			TypeEq(lhs, rhs);
			return this->Binary(expr::Shape::FSub, lhs, rhs, f);
		case type::Shape::I:
		{
			switch(lhs->type->shape->flag)
			{
			case type::Shape::Ptr:
				return this->Binary(expr::Shape::PtrSub, lhs, rhs, lhs->type);
			case type::Shape::Infer:
				Typing(lhs, i);
				std::cout<<"WARNING : Select Int for T - Int ;"<<std::endl;
			case type::Shape::I:
				return this->Binary(expr::Shape::ISub, lhs, rhs, i);
			default:
				throw "API::BinOP - ;";
			}
		}
		case type::Shape::Infer:
		{
			switch(lhs->type->shape->flag)
			{
			case type::Shape::Ptr:
				Typing(rhs, i);
				return this->Binary(expr::Shape::PtrSub, lhs, rhs, lhs->type);
			case type::Shape::Infer:
				Typing(lhs, i);
				Typing(rhs, i);
				std::cout<<"WARNING : Select Int for T - T   ;"<<std::endl;
			case type::Shape::I:
				return this->Binary(expr::Shape::ISub, lhs, rhs, i);
			default:
				throw "API::BinOP - ;";
			}
		}
		default:
			throw "API::BinOP - ;";
		}
	} 
	case Add:
	{
		switch(lhs->type->shape->flag)
		{
		case type::Shape::Ptr:
			Typing(rhs, i);
			return this->Binary(expr::Shape::PtrAdd, lhs, rhs, lhs->type);
		case type::Shape::F:
			TypeEq(lhs, rhs);
			return this->Binary(expr::Shape::FAdd, lhs, rhs, f);
		case type::Shape::I:
		{
			switch(rhs->type->shape->flag)
			{
			case type::Shape::Ptr:
				return this->Binary(expr::Shape::PtrAdd, rhs, lhs, rhs->type);
			case type::Shape::Infer:
				Typing(rhs, i);
			case type::Shape::I:
				return this->Binary(expr::Shape::IAdd, lhs, rhs, i);
			default:
				throw "API::BinOP + ;";
			}
		}
		case type::Shape::Infer:
		{
			switch(rhs->type->shape->flag)
			{
			case type::Shape::F:
				Typing(lhs, f);
				return this->Binary(expr::Shape::FAdd, lhs, rhs, f);
			case type::Shape::Ptr:
				return this->Binary(expr::Shape::PtrAdd, rhs, lhs, rhs->type);
			case type::Shape::Infer:
				Typing(rhs, i);
				std::cout<<"WARNING : Select Int for T + T   ;"<<std::endl;
			case type::Shape::I:
				Typing(lhs, i);
				std::cout<<"WARNING : Select Int for T + Int ;"<<std::endl;
				return this->Binary(expr::Shape::IAdd, lhs, rhs, i);
			default:
				throw "API::BinOP + ;";
			}
		}
		default:
			throw "API::BinOP + ;";
		}

	}
	default:
		throw "API::BinOp Unknown Op;";

	}
}

Exprp	API::New(Exprp init)
{
	auto eid = this->expr.nid();

	auto i_type = init->type;
	switch(i_type->shape->flag)
	{
	case type::Shape::Array:
	{
		auto shape = ((type::Array*)(i_type->shape));
		auto tid = shape->id;
		auto _type = &(this->type[tid]);

		auto type = this->TypePtr(_type);

		this->expr.insert(Expr(eid, Eh::new_array(init->id), type));
		break;
	}
	default:
		auto type = this->TypePtr(i_type);
		this->expr.insert(Expr(eid, Eh::new_expr(init->id), type));
		break;
	}
	auto expr = &(this->expr[eid]);

	return expr;
}

}}