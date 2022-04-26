#ifndef tc_ast_api_hpp
#define tc_ast_api_hpp

#include "tbl.hpp"

namespace tc{
namespace ast{

struct Table : protected TableBase
{
    /* Stmt */
    void  BlockBegin();
    void  BlockStmt(Stmt* stmt);
    Stmt* BlockEnd();
    Stmt* Let(Name name, Expr* expr, Type* type=NULL);
    Stmt* Var(Name name, Expr* expr, Type* type=NULL);
    Stmt* If(Expr* cond, Stmt* fst, Stmt* snd=NULL);
    Stmt* While(Expr* cond, Stmt* stmt);
    Stmt* Empty();
    Stmt* Break();
    Stmt* Cont();
    Stmt* Ret(Expr* expr=NULL);
    Stmt* Exp(Expr* expr);
    Stmt* Del(Expr* expr);
    
    void  TypeDef(Name name);
    Stmt* Alias(Type* type);
    void  ADTBranchBegin(Name cons);
    void  ADTBranchType(Type* type);
    void  ADTBranchEnd();
    Stmt* ADT();

    // compile-time type check
    Stmt* Check(Expr* expr, Type* type=NULL);

    /* Type */
    Type* U();
    Type* B();
    Type* C();
    Type* I();
    Type* F();
    Type* TypeVar(Name name);
    Type* TypeRef(Type* type);
    Type* TypePtr(Type* type);
    Type* TypeArr(Type* type, Size size);

    void  TypeFunBeg();
    void  TypeFunArg(Type* type); /*  para  type */
    Type* TypeFunEnd(Type* rety); /* return type */

    /* Cell & Expr */
    Cell* CellVar(Name name);
    Expr* ExprVar(Name name);
    Expr* ExprVarRef(Name name);

    void  AppBeg(Expr* func=NULL);
    void  AppArg(Expr* para);
    Cell* CellAppEnd();
    Expr* ExprAppEnd();

    Expr* ExprArr(Expr* expr, Size size);
    Cell* CellEle(Cell* cell, Expr* index);
    Expr* ExprEle(Expr* expr, Expr* index);
    Expr* ExprEleRef(Expr* expr, Expr* index);
    Expr* ExprEleAddr(Expr* expr, Expr* index);

    Cell* CellRef(Expr* expr);  /* Ptr T -> Ref T */
    Expr* ExprVal(Expr* expr);  /* Ptr T ->     T */
    Expr* ExprRef(Expr* expr);  /* Ptr T -> Ref T */

    Expr* B(Bool b);
    Expr* C(Char c);
    Expr* S(Str s);
    Expr* I(Int i);
    Expr* F(Float f);

    void  ExprFunBeg();
    void  ExprFunRefArg(Name name, Type* type=NULL);
    void  ExprFunArg(Name name, Type* type=NULL);
    Expr* ExprFunExpr(Expr* expr);
    Expr* ExprFunStmt(Stmt* stmt);

    Expr* ExprPtr(Cell* cell);

    void  MatchBeg(Expr* expr);
    void  MatchBranchBeg(Name name);
    void  MatchBranchArg(Name name);
    void  MatchBranchExpr(Expr* expr);
    void  MatchBranchStmt(Stmt* stmt);
    Expr* MatchEnd();

    Expr* Asgn(Cell* cell, Oper oper, Expr* expr);
    
    Expr* UnOp(Oper oper, Expr* Expr);
    Expr* BinOp(Expr* lhs, Oper oper, Expr* rhs);

    Expr* New(Expr* expr, Expr* size=NULL);



    Table(std::string path);
    ~Table();
private:
    Type* Typing(Expr* expr, Type* type=NULL);
};

}}

#endif 