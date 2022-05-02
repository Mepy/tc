#include "api.hpp"
#include "stmt.hpp"
#include "type.hpp"
#include "expr.hpp"

#include <iostream>
#include "ir_helper.hpp"
namespace tc{
namespace ast{

using Ins = ir::Instruction;

namespace ins = ir::instruction;
namespace sym = ir::symbol;

// [MM] : WARNING
void unify(Typep& t1, Typep& t2) 
{
	if(t1==t2)
		return;

	if(Type::Infer==t1->flag)
	{
		if(Type::Infer!=t2->flag)
			t1 = t2;
		else // Both Infer
		{
			auto ty1 = (type::Typ*)t1;
			auto ty2 = (type::Typ*)t2;

			if(nullptr==ty1->type)
			{
				if(nullptr==ty2->type)
					t2 = t1;
				else
					t1 = t2 = ty2->type;
			}
			else // nullptr!=ty1->type
			{
				if(nullptr==ty2->type)
					t2 = t1 = ty1->type;
				else // nullptr!=ty2->type
				{
					unify(ty1->type, ty2->type);
					t1 = t2; 
				}
			}
		}
	}
	else
	{
		if(Type::Infer==t2->flag)
			t2 = t1;
		else if(t1->flag!=t2->flag)
			throw "Not Typed.\n"; // [TODO] throw better msg
		else switch(t1->flag)
		{
			case Type::Infer: /* tc Compiler bugs here */
				throw "TC COMPILER DEBUG please.\n";
			case Type::U:case Type::B:case Type::C:
        	case Type::I:case Type::F: break;

			case Type::ADT: 
				if(t1->id==t2->id)
					break;
				else
					throw "Not Typed.\n";
			case Type::Ref:
			case Type::Ptr:
			{
				auto ty1 = (type::Typ*)t1;
				auto ty2 = (type::Typ*)t2;
				unify(ty1->type, ty2->type);
				break;
			}
			case Type::Arr:
			{
				auto ty1 = (type::Arr*)t1;
				auto ty2 = (type::Arr*)t2;
				if(ty1->size!=ty2->size)
					throw "Not Typed Array Size.\n";
				
				unify(ty1->type, ty2->type);
				break;
			}
			case Type::Fun:
			{
				auto ty1 = (type::Fun*)t1;
				auto ty2 = (type::Fun*)t2;
				auto& params1 = ty1->params;
				auto& params2 = ty2->params;

				if(params1.size()!=params2.size())
					throw "Not Typed Fun Params Size.\n";
				
				unify(ty1->retype, ty2->retype);

				for(auto it1=params1.begin(), it2=params2.begin()
				;   it1!=params1.end()
				;   ++it1, ++it2)
					unify(*it1, *it2);

				break;
			}
			

        	default: break;
		}
	}

}

API::API(std::string path)
:Context(path)
{
	this->u = new type::Atom(Type::U);
    this->u->id = 1;
    this->b = new type::Atom(Type::B);
    this->b->id = 2;
    this->c = new type::Atom(Type::C);
    this->c->id = 3;
	this->i = new type::Atom(Type::I);
    this->i->id = 4;
	this->f = new type::Atom(Type::F);
    this->f->id = 5;

	this->adt = new type::ADT();
}
API::~API()
{
	decr(u);
    decr(b);
    decr(c);
    decr(i);
    decr(f);

	decr(adt);
}

void	API::BlockBegin()
{
	auto block = new stmt::Block();
	block->flag = Stmt::Block;
	this->nodes.push(block);

	this->type.scope_beg();
	this->expr.scope_beg();
}

void	API::BlockStmt(Stmt* stmt)
{
	auto block = (stmt::Block*)(this->nodes.top());
	if( ! (stmt->flag==Stmt::Empty) )
		block->stmts.push_back(stmt);
}

Stmt*	API::BlockEnd()
{
	auto stmt = (Stmt*)(this->nodes.top());
	this->nodes.pop();
	this->type.scope_end();
	this->expr.scope_end();
	return stmt;
}

Stmt*	API::Let(Name name, Expr* expr, Typep type) // =nullptr
{
	std::cout<<"let "<<name<<" = "<<((expr::I*)expr)->i<<std::endl;
	if(nullptr==type)
		type = 
			new type::Typ(Type::Infer, type);

    Typing(expr, type);

    auto id = expr->id;
	this->expr[id].names.push_back(name);

    

    auto stmt = new stmt::Var(Stmt::Let, id, expr, type);

    stmt->block = move(expr->block);
    
	return stmt;
}

Stmt*	API::Var(Name name, Expr* expr, Typep type) // =nullptr
{
	if(nullptr==type)
		type = 
			new type::Typ(Type::Ref, 
				new type::Typ(Type::Infer, type));
    Typing(expr, type);

    auto id = this->expr.nid();

	auto& data = this->expr[id];
    data.names.push_back(name);
    data.expr = expr;
	data.expr->type = new type::Typ(Type::Ref, type);

	auto stmt = new stmt::Var(Stmt::Var, id, expr, type);

    stmt->block = move(expr->block);
    stmt->block->push(ins::Alloc(id, expr->id));

	return stmt;
}

Stmt*	API::If(Expr* cond, Stmt* fst, Stmt* snd) // =nullptr
{
	if(nullptr==snd)
		snd = new stmt::Empty(Stmt::Empty);
	
	Typing(cond, this->b);


	auto& blocks = this->ir.blocks;

	auto old_id = this->ir.current;
	auto old_block = blocks[old_id];

	auto cid = this->ir.block_cid();

	auto cond_id = cid+1;

	old_block->push(ins::Jump(cond_id));
	auto cond_block = blocks[cond_id] = move(cond->block);
	

	auto fst_id = cid+2;
	auto fst_block = blocks[fst_id] = move(fst->block);
	
	if(nullptr!=snd)
	{
		auto snd_id = cid+3;
		auto snd_block = blocks[snd_id] = move(snd->block);
		auto new_id = cid+4;
		auto new_block = blocks[new_id] = new Block(ir::Kind::INST);
		
		cond_block->push(ins::Br(cond->id, fst_id, snd_id));
		fst_block->push(ins::Jump(new_id));
		snd_block->push(ins::Jump(new_id));
		this->ir.set_current(new_id);
	}
	else
	{
		auto new_id = cid+3;
		cond_block->push(ins::Br(cond->id, fst_id, new_id));
		fst_block->push(ins::Jump(new_id));
		this->ir.set_current(new_id);
	}

	return new stmt::If(cond, fst, snd);
}

Stmt*	API::While(Expr* cond, Stmt* body) // nullptr
{	
	Typing(cond, this->b);

	auto& blocks = this->ir.blocks;

	auto old_id = this->ir.current;
	auto old_block = blocks[old_id];

	auto cid = this->ir.block_cid();
	auto cond_id = cid+1;
	auto cond_block = blocks[cond_id] = move(cond->block);

	old_block->push(ins::Jump(cond_id));

	auto body_id = cid+2;
	Block* body_block;
	if(nullptr==body)
		body_block = blocks[body_id] = new Block(ir::Kind::INST);
	else
		body_block = blocks[body_id] = move(body->block);

	body_block->push(ins::Jump(cond_id));

	auto new_id = cid+3;
	blocks[new_id] = new Block(ir::Kind::INST);

	cond_block->push(ins::Br(cond->id, body_id, new_id));

	this->ir.set_current(new_id);

	return new stmt::While(cond, body);
}

Stmt*	API::Empty()
{
	return new stmt::Empty(Stmt::Empty);
}

Stmt*	API::Break()
{
	return new stmt::Empty(Stmt::Break);
}

Stmt*	API::Cont()
{
	return new stmt::Empty(Stmt::Cont);
}

Stmt*	API::Ret(Expr* expr) // =nullptr
{
	if(nullptr==expr)
		expr = new expr::U(this->u);
	return new stmt::Exp(Stmt::Ret, expr);
}

Stmt*	API::Exp(Expr* expr)
{
	return new stmt::Exp(Stmt::Exp, expr);
}

Stmt*	API::Del(Expr* expr)
{
	auto type = Typing(expr);
	if(type->flag==Type::Ptr)
		return new stmt::Exp(Stmt::Del, expr);
	else
		throw "Del Not-A-Pointer";
}

void	API::TypeDef(Name name)
{
	// auto id = this->type.add(name);
	// this->nodes.push(new stmt::TypeDef(id));

	// TODO push
}

Stmt*	API::Alias(Typep type)
{
	auto stmt = this->nodes.top();
	this->nodes.pop();
	auto id = ((stmt::TypeDef*)stmt)->id;
	delete stmt;

	this->type[id].type = type; 
	/* no need to incr, because match type with
	 * | Primitives -> has been incred in PTypes
	 * | TypeVar    -> has been incred in TypeVar
	 * | _          -> new types
	 */
	return Empty();
}

void	API::ADTBranchBegin(Name cons)
{
	// auto id = this->expr.add(cons);
	// ((type::ADT*)(this->adt))
	// ->cons[id]=Types();
}

void	API::ADTBranchType(Typep type)
{
	((type::ADT*)(this->adt))
	->cons.rbegin()
	->second.push_back(type);
}

void	API::ADTBranchEnd()
{
    /*
	auto con = ((type::ADT*)(this->adt))
		->cons.rbegin();
	auto id = con->first;
	auto types = con->second;

	// create function for constructors

	auto label_tuple = new expr::LabelTuple(incr(this->adt), id);
	auto confun = new expr::Fun(Expr::Cons);
	for(auto iter=types.begin();iter!=types.end();++iter)
	{
		auto eid = this->expr.add("");
		confun->params.push_back(eid);
		label_tuple->tuple.push_back(new expr::Var(eid));
	}
	
	confun->stmt = new stmt::Exp(Stmt::Ret, label_tuple);
	
	this->expr[id].expr = confun;
    */
	// WARNING : let-stmt for constructor-function NOT created YET.
	// TODO    : for locality, it should be created here.
	//         : Or, we just mark it as constructor, inline when needed.
}

Stmt*	API::ADT()
{
	auto stmt = this->nodes.top();
	this->nodes.pop();
	auto id = ((stmt::TypeDef*)stmt)->id;
	delete stmt;

	this->type[id].type = this->adt;
	this->adt =  new type::ADT();

	return Empty();
}

Stmt*   API::Check(Expr* expr, Typep type)
{
	Typing(expr, type);
	return Empty();
}

/* type */

// [MM] [TODO]
/* return NOT nullptr */
Typep	API::Typing(Expr* expr, Typep type) 
{
	auto& ty = expr->type;
	if(nullptr!=type)
		unify(ty, type);
	
	return ty;
}

Typep	API::U()
{
	return incr(this->u);
}

Typep	API::B()
{
	return incr(this->b);
}

Typep	API::C()
{
	return incr(this->c);
}

Typep	API::I()
{
	return incr(this->i);
}

Typep	API::F()
{
	return incr(this->f);
}

Typep	API::TypeVar(Name name)
{
	return incr(
		this->type[ // find data
			this->type[name] // find id
			].type);
}

Typep	API::TypeRef(Typep type)
{
	return new type::Typ(Type::Ref, type);
}

Typep	API::TypePtr(Typep type)
{
	return new type::Typ(Type::Ptr, type);
}

Typep	API::TypeArr(Typep type, Size size)
{
	return new type::Arr(type, size);
}

void	API::TypeFunBeg()
{
	auto type = new type::Fun();
	this->nodes.push(type);
}
void	API::TypeFunArg(Typep type)
{
	auto fun = (type::Fun*)(this->nodes.top());
	fun->params.push_back(type);
}
Typep	API::TypeFunEnd(Typep rety)
{
	auto fun = (type::Fun*)(this->nodes.top());
	this->nodes.pop();
	fun->retype = rety;
	return fun;
}

/* cell & expr */

Cell*	API::CellVar(Name name)
{
    // TODO memory management for type
	auto id = this->expr[name];
	auto& data = this->expr[id];
    auto type = data.expr->type;
	if(Type::Ref==type->flag)
	{
		auto cell = new expr::Var(id);
		cell->type = incr(type);
		return (Cell*)cell;
	}
	else
		throw "CellVar Not-A-Ref";
}

Expr*	API::ExprVar(Name name)
{
    // [MM] : type
	auto id = this->expr[name];
	auto& data = this->expr[id];
	auto type = data.expr->type;
	auto expr = new expr::Var(id);

	if(Type::Ref==type->flag)
		expr->type = ((type::Typ*)type)->type;
	else
		expr->type = type;
	
	return expr;
}

Expr*	API::ExprVarRef(Name name)
{
    // TODO memory management for type
	auto id = this->expr[name];
	auto& data = this->expr[id];
	auto type = data.expr->type;
	auto expr = new expr::Var(id);

	if(Type::Ref==type->flag)
		expr->type = type;
	else
		throw "VarRef Not-A-Ref";
	
	return expr;
}

void	API::AppBeg(Expr* func) // = nullptr
{
	if(nullptr==func)
		func = this->fun;
	
	
}

void	API::AppArg(Expr* para)
{
	
}

Cell*	API::CellAppEnd()
{

}

Expr*	API::ExprAppEnd()
{
	
}

// TODO
Cell*	API::CellEle(Cell* cell, Expr* index)
{
	auto cell_ty = (((Expr*)cell)->type);
	if(Type::Infer==cell_ty->flag)
		;
	
}

Expr*	API::ExprEle(Expr* expr, Expr* index)
{
	
}

Expr*	API::ExprEleRef(Expr* expr, Expr* index)
{
	
}

Expr*	API::ExprEleAddr(Expr* expr, Expr* index)
{
	
}

Expr*	API::B(Bool b)
{
	auto type = B();
    auto expr = new expr::B(b, type);
    auto id = this->expr.nid();
    ir.push(sym::Const(type->id));
    expr->block->push(ins::IImm(id, b));

	return expr;
}

Expr*	API::C(Char c)
{
	return new expr::C(c, C());
}

Expr*	API::S(Str s)
{
	return new expr::S(s, 
		new type::Arr(C(), s.length()+1));
}

Expr*	API::I(Int i)
{
    auto type = I();
    auto expr = new expr::I(i, type);
    auto id = this->expr.nid();
    ir.push(sym::Const(type->id));
    expr->block->push(ins::IImm(id, i));
    
	return expr;
}

Expr*	API::F(Float f)
{
	return new expr::F(f, F());
}


void	API::ExprFunBeg()
{
	this->fun = new expr::Fun(); 
	
	return;
}

void	API::ExprFunRefArg(Name name, Typep type) // =nullptr
{
	if(nullptr==type)
		type = 
			new type::Typ(Type::Infer, type);
	
	type = new type::Typ(Type::Ref, type);

    auto id = this->expr.nid();

	auto& data = this->expr[id];
    data.names.push_back(name);
    data.expr = new expr::Param(type); /* nulllptr means it is an argument */

	this->ir.func_params.push(id);
	

}

void	API::ExprFunArg(Name name, Typep type) // =nullptr
{
	
}

Expr*	API::ExprFunExpr(Expr* expr)
{
	
}

Expr*	API::ExprFunStmt(Stmt* stmt)
{
	
}

Expr*	API::ExprPtr(Cell* cell)
{
	
}

void	API::MatchBeg(Expr* expr)
{
	
}

void	API::MatchBranchBeg(Name name)
{
	
}

void	API::MatchBranchArg(Name name)
{
	
}

void	API::MatchBranchExpr(Expr* expr)
{
	
}

void	API::MatchBranchStmt(Stmt* stmt)
{
	
}

Expr*	API::MatchEnd()
{
	
}

Expr*	API::Asgn(Cell* cell, Oper oper, Expr* expr)
{
	
}

Expr*	API::UnOp(Oper oper, Expr* Expr)
{
	
}

Expr*	API::BinOp(Expr* lhs, Oper oper, Expr* rhs)
{
	
}

Expr*	API::New(Expr* expr, Expr* size) // =nullptr
{
	
}

}}