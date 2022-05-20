#ifndef tc_ast_api_hpp
#define tc_ast_api_hpp

#include "head.hpp"
#include "token.hpp"
#include "context.hpp"

namespace tc{
namespace ast{

struct API : public Context
{
    /* Stmt */
    void  BlockBegin();
    void  BlockStmt(Stmt* stmt);
    Stmt* BlockEnd();
    Stmt* Let(Name name, Expr* expr, Type* type=nullptr);
    Stmt* Var(Name name, Expr* expr, Type* type=nullptr);
    Stmt* If(Expr* cond, Stmt* fst, Stmt* snd=nullptr);
    void  WhileBeg();
    Stmt* While(Expr* cond, Stmt* stmt);
    Stmt* Empty();
    Stmt* Break(Size size=1);
    Stmt* Cont(Size size=1);
    Stmt* Ret(Expr* expr=nullptr);
    Stmt* Exp(Expr* expr);
    Stmt* Del(Expr* expr);
    Stmt* Asgn(Cell* cell, Oper oper, Expr* expr);
    
    void  TypeDef(Name name);
    Stmt* Alias(Type* type);
    void  ADTBranchBegin(Name cons);
    void  ADTBranchType(Type* type=nullptr);
    void  ADTBranchEnd();
    Stmt* ADT();

    // compile-time type check
    Stmt* Check(Expr* expr, Type* type=nullptr);

    /* Type */
    Type* TypeVar(Name name);
    Type* TypeRef(Type* type);
    Type* TypePtr(Type* type);
    Type* TypeArr(Type* type, Byte8 size);

    void  TypeFunBeg();
    void  TypeFunArg(Type* type); /*  para  type */
    Type* TypeFunEnd(Type* rety); /* return type */

    /* Cell & Expr */
    Cell* CellVar(Name name);
    Expr* ExprVar(Name name);
    Expr* ExprVarRef(Name name);

    
    void  AppBeg(Expr* func=nullptr);
    void  AppForceRetRef();
    void  AppArg(Expr* arg);
    Cell* CellAppEnd();
    Expr* ExprAppEnd();

    Expr* ExprArr(Expr* expr, Expr* size);
    Cell* CellEle(Cell* cell, Expr* index);
    Expr* ExprEle(Expr* expr, Expr* index);
    Expr* ExprEleRef(Expr* expr, Expr* index);
    Expr* ExprEleAddr(Expr* expr, Expr* index);

    Cell* CellRef(Expr* expr);  /* Ptr T -> Ref T */
    Expr* ExprPtr(Cell* cell);  /* Ref T -> Ptr T */
    Expr* ExprVal(Expr* expr);  /* Ptr T ->     T */
    Expr* ExprRef(Expr* expr);  /* Ptr T -> Ref T */

    Expr* Null();
    Expr* C(Char c);
    Expr* S(Str s);
    Expr* I(Int i);
    Expr* F(Float f);

    void  ExprFunBeg();
    void  ExprFunRefArg(Name name, Type* type=nullptr);
    void  ExprFunArg(Name name, Type* type=nullptr);
    Expr* ExprFunExpr(Expr* expr);
    Expr* ExprFunStmt(Stmt* stmt);

    

    void  MatchBeg(Expr* expr);
    void  MatchBranchBeg(Name name);
    void  MatchBranchArg(Name name);
    void  MatchBranchExpr(Expr* expr);
    void  MatchBranchStmt(Stmt* stmt);
    Expr* MatchEnd();
    
    Expr* UnOp(Oper oper, Expr* Expr);
    Expr* BinOp(Expr* lhs, Oper oper, Expr* rhs);

    Expr* New(Expr* expr);


    API();
    ~API();

    void  save(string path);
    void  save(Stmt* root);
    void  save(string path, Expr* expr);
private:
    bool  Typing(Expr* expr, Type* type=nullptr);
    bool  TypeEq(Expr* lhs, Expr* rhs);
    Expr* Dereference(Expr* expr);
    Expr* AutoDereference(Expr* expr);
    Type* TypeInfer(Type* type=nullptr); // return Infer type;
    Expr* Element(Expr* array, Expr* index);
    Expr* Binary(expr::Shape::Flag flag, Expr* lhs, Expr* rhs, Type* type);
};

}}

#endif 