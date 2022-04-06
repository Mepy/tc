#include "api.hpp"
#include "stmt.hpp"
#include "type.hpp"
#include "cell.hpp"
#include "expr.hpp"

namespace tc{
namespace ast{

Table::Table()
{
	this->u = new type::Lit(type::Type::U);
    this->b = new type::Lit(type::Type::B);
    this->c = new type::Lit(type::Type::C);
	this->i = new type::Lit(type::Type::I);
	this->f = new type::Lit(type::Type::F);
}
Table::~Table()
{
	decr(u);
    decr(b);
    decr(c);
    decr(i);
    decr(f);
}

void	Table::BlockBegin()
{
	auto block = new stmt::Block();
	block->flag = stmt::Stmt::Block;
	this->nodes.push(block);

	this->type.scope_beg();
	this->expr.scope_beg();
}

void	Table::BlockStmt(Stmt* stmt)
{
	auto block = (stmt::Block*)(this->nodes.top());
	if( ! (((stmt::Stmt*)stmt)->flag==stmt::Stmt::Empty) )
		block->stmts.push_back(stmt);
}

Stmt*	Table::BlockEnd()
{
	auto stmt = (stmt::Stmt*)(this->nodes.top());
	this->nodes.pop();
	this->type.scope_end();
	this->expr.scope_end();
	return stmt;
}

Stmt*	Table::Let(Name name, Expr* expr, Typep type) // =NULL
{
	
	if(NULL==type)
		type = 
			new type::Typ(type::Type::Infer, type);

	auto id = this->expr.add(name);
	this->expr[id] = expr::Data(name, type, expr);

	Typing(expr, type);

	auto stmt = new stmt::Var(id, expr, type);
	stmt->flag = stmt::Stmt::Let;
	return stmt;
}

Stmt*	Table::Var(Name name, Expr* expr, Typep type) // =NULL
{
	
	if(NULL==type)
		type = 
			new type::Typ(type::Type::Ref, 
				new type::Typ(type::Type::Infer, type));

	auto id = this->expr.add(name);
	this->expr[id] = expr::Data(name, type, expr);

	Typing(expr, type);

	auto stmt = new stmt::Var(id, expr, type);
	stmt->flag = stmt::Stmt::Var;
	return stmt;
}

Stmt*	Table::If(Expr* cond, Stmt* fst, Stmt* snd) // =NULL
{
	if(NULL==snd)
		snd = new stmt::Empty(stmt::Stmt::Empty);
	
	Typing(cond, this->b);

	return new stmt::If(cond, fst, snd);
}

Stmt*	Table::While(Expr* cond, Stmt* body)
{	
	Typing(cond, this->b);

	return new stmt::While(cond, body);
}

Stmt*	Table::Empty()
{
	return new stmt::Empty(stmt::Stmt::Empty);
}

Stmt*	Table::Break()
{
	return new stmt::Empty(stmt::Stmt::Break);
}

Stmt*	Table::Cont()
{
	return new stmt::Empty(stmt::Stmt::Cont);
}

Stmt*	Table::Ret(Expr* expr) // =NULL
{
	if(NULL==expr)
		expr = new expr::U(this->u);
	return new stmt::Exp(stmt::Stmt::Ret, expr);
}

Stmt*	Table::Exp(Expr* expr)
{
	return new stmt::Exp(stmt::Stmt::Exp, expr);
}

Stmt*	Table::Del(Expr* expr)
{
	auto type = (type::Type*)(Typing(expr));
	if(type->flag==type::Type::Ptr)
		return new stmt::Exp(stmt::Stmt::Del, expr);
	else
		throw "Del Not-A-Pointer";
}

void	Table::TypeDef(Name name)
{
	auto id = this->type.add(name);
	this->nodes.push(new stmt::TypeDef(id));
	// TODO push
}

Stmt*	Table::Alias(Typep type)
{

	if(((type::Type*)type)->flag==type::Type::Var)
		type = this->type[((type::Var*)type)->id].type;

	auto stmt = this->nodes.top();
	this->nodes.pop();
	auto id = ((stmt::TypeDef*)stmt)->id;
	delete stmt;

	this->type[id].type = type;
	return Empty();
}

void	Table::ADTBranchBegin(Name cons)
{
	
}

void	Table::ADTBranchType(Typep type)
{
	
}

void	Table::ADTBranchEnd()
{
	
}

Stmt*	Table::ADT()
{
	auto stmt = this->nodes.top();
	this->nodes.pop();
	auto id = ((stmt::TypeDef*)stmt)->id;
	delete stmt;

	auto type = new type::Var(type::Type::Let, id);
	this->type[id].type = type;

	return Empty();
}

Stmt*   Table::Check(Expr* expr, Typep type)
{
	Typing(expr, type);
	return Empty();
}

Typep	Table::Typing(Expr* expr, Typep type)
{
	
}

Typep	Table::U()
{
	return incr(this->u);
}

Typep	Table::B()
{
	return incr(this->b);
}

Typep	Table::C()
{
	return incr(this->c);
}

Typep	Table::I()
{
	return incr(this->i);
}

Typep	Table::F()
{
	return incr(this->f);
}

Typep	Table::TypeVar(Name name)
{
	auto id = this->type[name];
	return new type::Var(type::Type::Var, id);
}

Typep	Table::TypeRef(Typep type)
{
	return new type::Typ(type::Type::Ref, type);
}

Typep	Table::TypePtr(Typep type)
{
	return new type::Typ(type::Type::Ptr, type);
}

Typep	Table::TypeArr(Typep type, Size size)
{
	return new type::Arr(type, size);
}

void	Table::TypeFunBeg()
{
	auto type = new type::Fun();
	this->nodes.push(type);
}
void	Table::TypeFunArg(Typep type)
{
	auto fun = (type::Fun*)(this->nodes.top());
	fun->params.push_back(type);
}
Typep	Table::TypeFunEnd(Typep rety)
{
	auto fun = (type::Fun*)(this->nodes.top());
	this->nodes.pop();
	fun->retype = rety;
	return fun;
}

Cell*	Table::CellVar(Name name)
{
	auto id = this->expr[name];
	auto data = this->expr[id];
	if(type::Type::Ref==((type::Type*)data.type)->flag)
		return (Cell*)(new expr::Var(id));
	else
		throw "CellVar Not-A-Ref";
}

Expr*	Table::ExprVar(Name name)
{
	auto id = this->expr[name];
	auto data = this->expr[id];
	auto type = (type::Type*)data.type;
	auto expr = new expr::Var(id);

	if(type::Type::Ref==type->flag)
		expr->type = ((type::Typ*)type)->type;
	else
		expr->type = type;
	
	return expr;
}

Expr*	Table::ExprVarRef(Name name)
{
	auto id = this->expr[name];
	auto data = this->expr[id];
	auto type = (type::Type*)data.type;
	auto expr = new expr::Var(id);

	if(type::Type::Ref==type->flag)
		expr->type = type;
	else
		throw "VarRef Not-A-Ref";
	
	return expr;
}

void	Table::AppBeg(Expr* func) // = NULL
{
	if(NULL==func)
		func = NULL; // TODO func self
}

void	Table::AppArg(Expr* para)
{
	
}

Cell*	Table::CellAppEnd()
{

}

Expr*	Table::ExprAppEnd()
{
	
}

Cell*	Table::CellEle(Cell* cell, Expr* index)
{
	auto cell_ty = (type::Type*)(((expr::Expr*)cell)->type);
	if(type::Type::Infer==cell_ty->flag)
		;
	
}

Expr*	Table::ExprEle(Expr* expr, Expr* index)
{
	
}

Expr*	Table::ExprEleRef(Expr* expr, Expr* index)
{
	
}

Expr*	Table::ExprEleAddr(Expr* expr, Expr* index)
{
	
}

Expr*	Table::B(Bool b)
{
	return new expr::B(b, B());
}

Expr*	Table::C(Char c)
{
	return new expr::C(c, C());
}

Expr*	Table::S(Str s)
{
	return new expr::S(s, 
		new type::Arr(C(), s.length()+1));
}

Expr*	Table::I(Int i)
{
	return new expr::I(i, I());
}

Expr*	Table::F(Float f)
{
	return new expr::F(f, F());
}

void	Table::ExprFunBeg()
{
	
}

void	Table::ExprFunRefArg(Name name, Typep type) // =NULL
{
	
}

void	Table::ExprFunArg(Name name, Typep type) // =NULL
{
	
}

Expr*	Table::ExprFunExpr(Expr* expr)
{
	
}

Expr*	Table::ExprFunStmt(Stmt* stmt)
{
	
}

Expr*	Table::ExprPtr(Cell* cell)
{
	
}

void	Table::MatchBeg(Expr* expr)
{
	
}

void	Table::MatchBranchBeg(Name name)
{
	
}

void	Table::MatchBranchArg(Name name)
{
	
}

void	Table::MatchBranchExpr(Expr* expr)
{
	
}

void	Table::MatchBranchStmt(Stmt* stmt)
{
	
}

Expr*	Table::MatchEnd()
{
	
}

Expr*	Table::Asgn(Cell* cell, Oper oper, Expr* expr)
{
	
}

Expr*	Table::UnOp(Oper oper, Expr* Expr)
{
	
}

Expr*	Table::BinOp(Expr* lhs, Oper oper, Expr* rhs)
{
	
}

Expr*	Table::New(Expr* expr, Expr* size) // =NULL
{
	
}

Table&	Table::operator>>(ofstream& file)
{
	return *this;
}

Table&	Table::operator<<(ifstream& file)
{
	return *this;
}

}}