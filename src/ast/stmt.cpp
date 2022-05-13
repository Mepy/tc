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
namespace Sh = ir::symbol;

void	API::BlockBegin()
{
	this->type.scope_beg();
	this->expr.scope_beg();
	auto block = new Stmt(new stmt::_block());
	this->blocks.push(block);
}

void	API::BlockStmt(Stmtp stmt)
{
	if(nullptr==stmt)
		return;

	auto block = this->blocks.top();
	auto shape = ((stmt::_block*)(block->shape));
	shape->stmts.push_back(stmt);

	// IR
	if(nullptr==block->beg)
	{
		if(nullptr==stmt->beg)
			block->insts.concat_back(stmt->insts);
		else
		{
			block->beg = stmt->beg;
			block->end = stmt->end;
			if(0!=block->insts.size())
				block->beg->insts.concat_front(block->insts);
		}
	}
	
	else
	{
		if(nullptr==stmt->beg)
			block->end->insts.concat_back(stmt->insts);
		else
		{
			block->end->insts.push_back(Ih::Jump(stmt->beg->id));
			block->end = stmt->beg;
		}
	}
}

Stmtp	API::BlockEnd()
{
	auto block = this->blocks.top(); this->blocks.pop();
	this->type.scope_end();
	this->expr.scope_end();
	return block;
}

Stmtp	API::Let(Name name, Exprp expr, Typep type) // = nullptr
{
	if(nullptr==type)
	{
		auto id = this->type.nid();
		this->type.insert(Type(id, new type::Typ(type::Shape::Infer, 0)));
		type = &(this->type[id]);
	}

    Typing(expr, type);

	this->expr.bind(expr->id, name);

	auto stmt = new Stmt(new stmt::_let(name, type, expr));

	// IR
	stmt->insts.eat(expr->insts);

	return stmt;
}

Stmtp	API::Var(Name name, Exprp expr, Typep type) // = nullptr
{
	type = this->TypeInfer(type);
    Typing(expr, type);

	auto ref_type = this->TypeRef(type);
	
	auto id = this->expr.nid();
	this->expr.insert(Expr(id, Eh::ref(expr->id), ref_type, Ih::Alloc(id, expr->id), ir::Symbol::Const));
	auto ref = &(this->expr[id]);
	this->expr.bind(ref->id, name);

	ref->inst_front(expr);

	auto stmt = new Stmt(new stmt::_var(name, type, expr));

	// IR
	stmt->insts.eat(ref->insts);

	return stmt;
}
ID If_Br(Context* context, Stmtp stmt, ID next)
{
	if(nullptr!=stmt->beg)
	{
		stmt->end->insts.push_back(Ih::Jump(next));
		return stmt->beg->id;
	}

	auto& insts = stmt->insts;
	if(1==insts.size())
	{
		auto& inst = insts.back();
		auto  sort = inst.sort;
		auto  dst  = inst.dst;
		if(sort==ir::Instruction::Sort::Br
		|| sort==ir::Instruction::Sort::Jump)
			return dst;
	}

	auto block = context->new_block();
	block->insts.eat(stmt->insts);
	block->insts.push_back(Ih::Jump(next));
	return block->id;
}
Stmtp	API::If(Exprp cond, Stmtp fst, Stmtp snd) // = nullptr
{
	Typing(cond, this->B());

	auto stmt = new Stmt(new stmt::_if(cond, fst, snd));

	// IR
	auto beg = stmt->beg = this->new_block();
	auto end = stmt->end = this->new_block();

	beg->insts.eat(cond->insts);

	auto fst_id = If_Br(this, fst, end->id);
	auto snd_id = If_Br(this, snd, end->id);

	beg->insts.push_back(Ih::Br(cond->id, fst_id, snd_id));

	return stmt;
}

void	API::WhileBeg()
{
	auto stmt = new Stmt(nullptr);
	stmt->beg = this->new_block();
	stmt->end = this->new_block();

	this->whiles.push_back(stmt);
}

Stmtp	API::While(Exprp cond, Stmtp body) // nullptr
{	
	Typing(cond, this->B());
	auto stmt = this->whiles.back(); this->whiles.pop_back();
	stmt->shape = new stmt::_while(cond, body);

	// IR
	auto beg = stmt->beg;
	auto end = stmt->end;
	auto cond_block = this->new_block();
	beg->insts.push_back(Ih::Jump(cond_block->id));
	cond_block->insts.eat(cond->insts);
	
	if(nullptr!=body->beg)
	{
		cond_block->insts.push_back(Ih::Br(cond->id, body->beg->id, end->id));
		body->end->insts.push_back(Ih::Jump(cond_block->id));
	}
	else
	{
		auto body_block = this->new_block();
		body_block->insts.eat(body->insts);
		cond_block->insts.push_back(Ih::Br(cond->id, body_block->id, end->id));
		body_block->insts.push_back(Ih::Jump(cond_block->id));
	}

	return stmt;
}

Stmtp	API::Empty()
{
	return nullptr;
}

Stmtp	API::Break(Size size)
{
	if(size<=0)
		throw "API::Break <=0 Undefined Behaviour.";

	if(size>this->whiles.size())
		throw "API::Break Out Too Much.";

	auto stmt = new Stmt(new stmt::_break(size));

	// IR
	auto end = this->whiles[this->whiles.size()-size]->end->id;
	stmt->insts.push_back(Ih::Jump(end));

	return stmt;
}

Stmtp	API::Cont(Size size)
{
	if(size<=0)
		throw "API::Cont  <=0 Undefined Behaviour.";

	if(size>this->whiles.size())
		throw "API::Cont  Out Too Much.";
	
	auto stmt = new Stmt(new stmt::_cont(size));

	// IR
	auto beg = this->whiles[this->whiles.size()-size]->beg->id;
	stmt->insts.push_back(Ih::Jump(beg));

	return stmt;
}

Stmtp	API::Ret(Exprp expr) // = nullptr
{
	if(this->funcs_retyck.empty())
		throw "API:Ret not in function's body;";

	auto fun = this->funcs_retyck.top();
	auto shape = (type::Fun*)(fun->type->shape);
	
	auto tid = shape->retype;
	auto type = &(this->type[tid]);

	Typing(expr, type);

	auto stmt = new Stmt(new stmt::_ret(expr));

	// IR
	stmt->insts.eat(expr->insts);
	stmt->insts.push_back(Ih::Return(expr->id));

	return stmt;
}
Stmtp	API::Exp(Exprp expr)
{
	auto stmt = new Stmt(new stmt::_exp(expr));

	// IR
	stmt->insts.eat(expr->insts);

	return stmt;
}

Stmtp	API::Del(Exprp expr)
{
	expr = AutoDereference(expr);

	auto type = expr->type;
	if(type::Shape::Ptr!=type->shape->flag)
		throw "API::Del Not-A-Pointer";
	
	auto stmt = new Stmt(new stmt::_del(expr));

	// IR
	stmt->insts.eat(expr->insts);
	stmt->insts.push_back(Ih::Delete(expr->id));

	return stmt;
}
Stmtp	API::Asgn(Cellp cell, Oper oper, Exprp value)
{
	auto ref = (Exprp)cell;
	auto shape = ((type::Typ*)(ref->type->shape));

	if(type::Shape::Ref!=shape->flag)
		throw "API::Asgn Cell Not A Ref Type;";

	if(Oper::Undefined!=oper)
		value = this->BinOp(ref, oper, value);

	auto stmt = new Stmt(new stmt::_asgn(ref, value));

	stmt->insts.push_back(Ih::Set(ref->id, value->id));

	stmt->insts.concat_front(ref->insts);
	stmt->insts.concat_front(value->insts);

	return stmt;
}

void	API::TypeDef(Name name)
{
	this->type_name = name;
}

Stmtp	API::Alias(Typep type)
{
	this->type.bind(type->id, this->type_name);

	return new Stmt(new stmt::_alias(this->type_name, type));;
}

void	API::ADTBranchBegin(Name cons)
{
	auto shape = (type::ADT*)(this->adt->shape);

	auto eid = this->expr.nid();
	auto tid = this->type.nid();
	this->type.insert(Type(tid, new type::Fun(this->adt->id)));
	auto type = &(this->type[tid]);

	this->expr.insert(Expr(eid, Eh::ctor(), type));
	this->expr.bind(eid, cons);
	
	shape->cons.push_back(eid);
}

void	API::ADTBranchType(Typep type) // = nullptr
{
	if(nullptr==type)
		type = this->adt;

	auto con_id = ((type::ADT*)(this->adt->shape))->cons.back();
	auto con_type = this->expr[con_id].type;
	auto shape = (type::Fun*)(con_type->shape);

	shape->params.push_back(type->id);

	if(this->adt==type&&ir::Type::ADTR!=this->adt->type.sort)
		this->adt->type.sort = ir::Type::ADTR;
}

void	API::ADTBranchEnd()
{
	auto con_id = ((type::ADT*)(this->adt->shape))->cons.back();
	auto& con    = this->expr[con_id];
	auto con_type = con.type;
	auto shape = (type::Fun*)(con_type->shape);
	
	if(0==shape->params.size()) // Not a function-like constructor
	{
		delete shape;
		con_type->shape = Th::infer(this->adt->id);
		con.sort = ir::Symbol::Const;
	}
	else con.sort = ir::Symbol::Ctor;
}

Stmtp	API::ADT()
{
	this->type.bind(this->adt->id, this->type_name);

	auto stmt = new Stmt(new stmt::_alias(this->type_name, this->adt));;

	// replace the old adt
	auto id = this->type.nid();
	this->type.insert(Type(id, Th::adt(), ir::type::ADT(id)));
	this->adt = &(this->type[id]);

	return stmt;
}

Stmtp   API::Check(Exprp expr, Typep type)
{
	Typing(expr, type);

	return new Stmt(new stmt::_check(expr, type));
}

}}