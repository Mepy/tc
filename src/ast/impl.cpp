#include "api.hpp"
#include "stmt.hpp"
#include "type.hpp"
#include "expr.hpp"

#include "ir_parser.hpp"

namespace tc{
namespace ast{


API::API(std::string path)
:Context(path)
{
	this->u = new type::Lit(type::Type::U);
    this->b = new type::Lit(type::Type::B);
    this->c = new type::Lit(type::Type::C);
	this->i = new type::Lit(type::Type::I);
	this->f = new type::Lit(type::Type::F);

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
	block->flag = stmt::Stmt::Block;
	this->nodes.push(block);

	this->type.scope_beg();
	this->expr.scope_beg();
}

void	API::BlockStmt(Stmt* stmt)
{
	auto block = (stmt::Block*)(this->nodes.top());
	if( ! (((stmt::Stmt*)stmt)->flag==stmt::Stmt::Empty) )
		block->stmts.push_back(stmt);
}

Stmt*	API::BlockEnd()
{
	auto stmt = (stmt::Stmt*)(this->nodes.top());
	this->nodes.pop();
	this->type.scope_end();
	this->expr.scope_end();
	return stmt;
}

Stmt*	API::Let(Name name, Expr* expr, Typep type) // =NULL
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

Stmt*	API::Var(Name name, Expr* expr, Typep type) // =NULL
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

Stmt*	API::If(Expr* cond, Stmt* fst, Stmt* snd) // =NULL
{
	if(NULL==snd)
		snd = new stmt::Empty(stmt::Stmt::Empty);
	
	Typing(cond, this->b);

	return new stmt::If(cond, fst, snd);
}

Stmt*	API::While(Expr* cond, Stmt* body)
{	
	Typing(cond, this->b);

	return new stmt::While(cond, body);
}

Stmt*	API::Empty()
{
	return new stmt::Empty(stmt::Stmt::Empty);
}

Stmt*	API::Break()
{
	return new stmt::Empty(stmt::Stmt::Break);
}

Stmt*	API::Cont()
{
	return new stmt::Empty(stmt::Stmt::Cont);
}

Stmt*	API::Ret(Expr* expr) // =NULL
{
	if(NULL==expr)
		expr = new expr::U(this->u);
	return new stmt::Exp(stmt::Stmt::Ret, expr);
}

Stmt*	API::Exp(Expr* expr)
{
	return new stmt::Exp(stmt::Stmt::Exp, expr);
}

Stmt*	API::Del(Expr* expr)
{
	auto type = (type::Type*)(Typing(expr));
	if(type->flag==type::Type::Ptr)
		return new stmt::Exp(stmt::Stmt::Del, expr);
	else
		throw "Del Not-A-Pointer";
}

void	API::TypeDef(Name name)
{
	auto id = this->type.add(name);
	this->nodes.push(new stmt::TypeDef(id));

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
	auto id = this->expr.add(cons);
	((type::ADT*)(this->adt))
	->cons[id]=Types();
}

void	API::ADTBranchType(Typep type)
{
	((type::ADT*)(this->adt))
	->cons.rbegin()
	->second.push_back(type);
}

void	API::ADTBranchEnd()
{
	auto con = ((type::ADT*)(this->adt))
		->cons.rbegin();
	auto id = con->first;
	auto types = con->second;

	// create function for constructors

	auto label_tuple = new expr::LabelTuple(incr(this->adt), id);
	auto confun = new expr::Fun(expr::Expr::Cons);
	for(auto iter=types.begin();iter!=types.end();++iter)
	{
		auto eid = this->expr.add("");
		confun->params.push_back(eid);
		label_tuple->tuple.push_back(new expr::Var(eid));
	}
	
	confun->stmt = new stmt::Exp(stmt::Stmt::Ret, label_tuple);
	
	this->expr[id].expr = confun;

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

// TODO
Typep	API::Typing(Expr* expr, Typep type)
{
	auto ty = ((expr::Expr*)expr)->type;
	if(NULL==type)
		return ty;


	// ty_eq
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
	return new type::Typ(type::Type::Ref, type);
}

Typep	API::TypePtr(Typep type)
{
	return new type::Typ(type::Type::Ptr, type);
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
	auto id = this->expr[name];
	auto data = this->expr[id];
	if(type::Type::Ref==((type::Type*)data.type)->flag)
	{
		auto cell = new expr::Var(id);
		cell->type = incr((type::Typ*)data.type);
		return (Cell*)cell;
	}
	else
		throw "CellVar Not-A-Ref";
}

Expr*	API::ExprVar(Name name)
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

Expr*	API::ExprVarRef(Name name)
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

void	API::AppBeg(Expr* func) // = NULL
{
	if(NULL==func)
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
	auto cell_ty = (type::Type*)(((expr::Expr*)cell)->type);
	if(type::Type::Infer==cell_ty->flag)
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
	return new expr::B(b, B());
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
	return new expr::I(i, I());
}

Expr*	API::F(Float f)
{
	return new expr::F(f, F());
}

// TODO
void	API::ExprFunBeg()
{
	this->fun = new expr::Fun(); 
	/* emmm, there should be sth
	 * must use id to refer to it!!!
	 */
}

void	API::ExprFunRefArg(Name name, Typep type) // =NULL
{
	
}

void	API::ExprFunArg(Name name, Typep type) // =NULL
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

Expr*	API::New(Expr* expr, Expr* size) // =NULL
{
	
}

API&	API::operator>>(ofstream& file)
{
	return *this;
}

API&	API::operator<<(ifstream& file)
{
	return *this;
}

}}