#include "../ast/api.hpp"
#include "head.hpp"
#include <iostream>
#include <string>

API::API(){
    std::cout << "\nCreate API" << std::endl;
}

API::~API(){

}

void  API::save(string path){}
void  API::save(Stmt* root){}



char * Oper_table[] = {
    (char*)"Undefined",
    (char*)"Pos", (char*)"Neg",
    (char*)"Add", (char*)"Sub", (char*)"Mul", (char*)"Div", 
    (char*)"Mod", (char*)"LShift", (char*)"RShift",
    (char*)"BNot", (char*)"BAnd", (char*)"BOr", (char*)"BXOr",
    (char*)"LNot", (char*)"LAnd", (char*)"LOr", (char*)"LXOr", 
    (char*)"Lt", (char*)"Gt", (char*)"Leq", (char*)"Geq",
    (char*)"Eq", (char*)"Neq",
    (char*)"FAdd", (char*)"FSub", (char*)"FMul", (char*)"FDiv",
    (char*)"PtrAdd", (char*)"AddPtr", (char*)"PtrSub"
};

// Name::Name(string name):string(name){
//     std::cout << name << std::endl;
// }

/* Stmt */

void API::BlockBegin(){
    std::cout << "BlockBegin" << std::endl;
}

void API::BlockStmt(Stmt *stmt){
    std::cout << "BlockStmt" << std::endl << std::endl;
}

Stmt* API::BlockEnd(){
    std::cout << "BlockEnd" << std::endl;
    return nullptr;
}

Stmt* API::Let(Name name, Expr* expr, Type* type){
    std::cout << "Let " << name << std::endl;
    return nullptr;
}

Stmt* API::Var(Name name, Expr* expr, Type* type){
    std::cout << "Var " << name << std::endl;
    return nullptr;
}

Stmt* API::If(Expr* cond, Stmt* fst, Stmt* snd){
    std::cout << "If" << std::endl;
    return nullptr;
}

void  API::WhileBeg(){
    std::cout << "WhileBeg" << std::endl;
}

Stmt* API::While(Expr* cond, Stmt* stmt){
    std::cout << "While" << std::endl;
    return nullptr;
}

Stmt* API::Empty(){
    std::cout << "Empty" << std::endl;
    return nullptr;
}

Stmt* API::Break(Size size){
    std::cout << "Break " << size << std::endl;
    return nullptr;
}

Stmt* API::Cont(Size size){
    std::cout << "Cont " << size << std::endl;

    return nullptr;
}

Stmt* API::Ret(Expr* expr){
    std::cout << "Ret" << std::endl;
    return nullptr;
}

Stmt* API::Exp(Expr* expr){
    std::cout << "Expr" << std::endl;
    return nullptr;
}

Stmt* API::Del(Expr* expr){
        std::cout << "Del" << std::endl;
    return nullptr;
}

Stmt* API::Asgn(Cell* cell, Oper oper, Expr* expr){
    std::cout << "Asgn " << Oper_table[oper] << std::endl;
    return nullptr;
}

void  API::TypeDef(Name name){
    std::cout << "TypeDef " << name << std::endl;

}

Stmt* API::Alias(Type* type){
    std::cout << "Alias"<< std::endl;
    return nullptr;
}

void  API::ADTBranchBegin(Name cons){
    std::cout << "ADTBranchBegin " << cons << std::endl;
}

void  API::ADTBranchType(Type* type){
    std::cout << "ADTBranchType" << std::endl;
}

void  API::ADTBranchEnd(){
    std::cout << "ADTBranchEnd" << std::endl;
}

Stmt* API::ADT(){
    std::cout << "ADT" << std::endl;
    return nullptr;
}

Stmt* API::Check(Expr* expr, Type* type){
    std::cout << "ADT" << std::endl;
    return nullptr;
}

/* Type */
Type* API::TypeVar(Name name){
    std::cout << "TypeVar " << name << std::endl;
    return nullptr;
}

Type* API::TypeRef(Type* type){
    std::cout << "TypeRef" << std::endl;
    return nullptr;
}

Type* API::TypePtr(Type* type){
    std::cout << "TypePtr" << std::endl;
    return nullptr;
}

Type* API::TypeArr(Type* type, Byte8 size){
    std::cout << "TypeArr " << size << std::endl;
    return nullptr;
}

void  API::TypeFunBeg(){
    std::cout << "TypeFunBeg " << std::endl;
}

void  API::TypeFunArg(Type* type){
    std::cout << "TypeFunArg " << std::endl;
}

Type* API::TypeFunEnd(Type* rety){
    std::cout << "TypeFunEnd " << std::endl;

    return nullptr;
}

/* Cell & Expr */
Cell* API::CellVar(Name name){
    std::cout << "CellVar " << name << std::endl;
    return nullptr;
}

Expr* API::ExprVar(Name name){
    std::cout << "ExprVar " << name << std::endl;
    return nullptr;
}

Expr* API::ExprVarRef(Name name){
    std::cout << "ExprVarRef " << name << std::endl;
    return nullptr;
}

void  API::AppBeg(Expr* func){
    std::cout << "AppBeg" << std::endl;
}

void  API::AppForceRetRef(){
    std::cout << "AppForceBeg" << std::endl;
}

void  API::AppArg(Expr* arg){
    std::cout << "AppArg" << std::endl;
}

Cell* API::CellAppEnd(){
    return nullptr;
}

Expr* API::ExprAppEnd(){
    std::cout << "ExprAppEnd" << std::endl;
    return nullptr;
}

Expr* API::ExprArr(Expr* expr, Expr* size){
    std::cout << "ExprArr " << size << std::endl;
    return nullptr;
}

Cell* API::CellEle(Cell* cell, Expr* index){
    std::cout << "CellEle" << std::endl; 
    return nullptr;
}

Expr* API::ExprEle(Expr* expr, Expr* index){
    std::cout << "ExprEle" << std::endl;
    return nullptr;
}

Expr* API::ExprEleRef(Expr* expr, Expr* index){
    std::cout << "ExprEleRef" << std::endl;
    return nullptr;
}

Expr* API::ExprEleAddr(Expr* expr, Expr* index){
    std::cout << "ExprEleAddr" << std::endl;
    return nullptr;
}

Cell* API::CellRef(Expr* expr){
    std::cout << "CellRef" << std::endl;
    return nullptr;
}

Expr* API::ExprPtr(Cell* cell){
    std::cout << "ExprPtr" << std::endl;
    return nullptr;
}

Expr* API::ExprVal(Expr* expr){
    std::cout << "ExprVal" << std::endl;
    return nullptr;
}

Expr* API::ExprRef(Expr* expr){
    std::cout << "ExprRef" << std::endl;
    return nullptr;
}

Expr* API::C(Char c){
    return nullptr;
}

Expr* API::S(Str s){
    // std::cout << s << std::endl;
    return nullptr;
}

Expr* API::I(Int i){
    return nullptr;
}

Expr* API::F(Float f){
    return nullptr;
}

void  API::ExprFunBeg(){
    std::cout << "ExprFunBeg " << std::endl;

}

void  API::ExprFunRefArg(Name name, Type* type){
    std::cout  << "ExprFunRefArg " << name << std::endl;

}

void  API::ExprFunArg(Name name, Type* type){
    std::cout << "ExprFunArg " << name << std::endl;

}

Expr* API::ExprFunExpr(Expr* expr){
    std::cout << "ExprFunExpr " << std::endl;
    return nullptr;
}

Expr* API::ExprFunStmt(Stmt* stmt){
    std::cout << "ExprFunStmt " << std::endl;
    return nullptr;
}

void  API::MatchBeg(Expr* expr){
    std::cout << "MatchBeg" << std::endl;
}

void  API::MatchBranchBeg(Name name){
    std::cout << "MatchBranchBeg " << name << std::endl;
}

void  API::MatchBranchArg(Name name){
    std::cout << "MatchBranchArg " << name << std::endl;
}

void  API::MatchBranchExpr(Expr* expr){
    std::cout << "MatchBranchExpr " << std::endl;
}

void  API::MatchBranchStmt(Stmt* stmt){
    std::cout << "MatchBranchStmt " << std::endl;

}

Expr* API::MatchEnd(){
    std::cout << "MatchEnd" << std::endl;
    return nullptr;
}


Expr* API::UnOp(Oper oper, Expr* Expr){
    printf("Unop: %s\n", Oper_table[oper]);
    return nullptr;
}
Expr* API::BinOp(Expr* lhs, Oper oper, Expr* rhs){
    printf("Binop: %s\n", Oper_table[oper]);
    return nullptr;
}

Expr* API::New(Expr* expr){
    std::cout << "New" << std::endl;
    return nullptr;
}
