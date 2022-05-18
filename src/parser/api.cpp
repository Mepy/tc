#include "../ast/api.hpp"
#include "head.hpp"
#include <iostream>
#include <string>

API::API(){
    std::cout << "\nCreate API" << std::endl;
}

API::~API(){

}

// Name::Name(string name):string(name){
//     std::cout << name << std::endl;
// }

/* Stmt */

void API::BlockBegin(){
    std::cout << "BlockBegin" << std::endl;
}

void API::BlockStmt(Stmt *stmt){
    std::cout << "BlockStmt" << std::endl;
}

Stmt* API::BlockEnd(){
    std::cout << "BlockEnd" << std::endl;
    return nullptr;
}

Stmt* API::Let(Name name, Expr* expr, Type* type){
    return nullptr;
}

Stmt* API::Var(Name name, Expr* expr, Type* type){
    return nullptr;
}

Stmt* API::If(Expr* cond, Stmt* fst, Stmt* snd){
    return nullptr;
}

void  API::WhileBeg(){

}

Stmt* API::While(Expr* cond, Stmt* stmt){
    return nullptr;
}

Stmt* API::Empty(){
    return nullptr;
}

Stmt* API::Break(Size size){
    return nullptr;
}

Stmt* API::Cont(Size size){
    return nullptr;
}

Stmt* API::Ret(Expr* expr){
    return nullptr;
}

Stmt* API::Exp(Expr* expr){
    return nullptr;
}

Stmt* API::Del(Expr* expr){
    return nullptr;
}

Stmt* API::Asgn(Cell* cell, Oper oper, Expr* expr){
    return nullptr;
}

void  API::TypeDef(Name name){

}

Stmt* API::Alias(Type* type){
    return nullptr;
}

void  API::ADTBranchBegin(Name cons){

}

void  API::ADTBranchType(Type* type){

}

void  API::ADTBranchEnd(){

}

Stmt* API::ADT(){
    return nullptr;
}

Stmt* API::Check(Expr* expr, Type* type){
    return nullptr;
}

/* Type */
Type* API::TypeVar(Name name){
    std::cout << "TypeVar" << std::endl;
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
    return nullptr;
}

Expr* API::ExprVar(Name name){
    return nullptr;
}

Expr* API::ExprVarRef(Name name){
    return nullptr;
}

void  API::AppBeg(Expr* func){

}

void  API::AppForceRetRef(){

}

void  API::AppArg(Expr* arg){

}

Cell* API::CellAppEnd(){
    return nullptr;
}

Expr* API::ExprAppEnd(){
    return nullptr;
}

Expr* API::ExprArr(Expr* expr, Size size){
    return nullptr;
}

Cell* API::CellEle(Cell* cell, Expr* index){
    return nullptr;
}

Expr* API::ExprEle(Expr* expr, Expr* index){
    return nullptr;
}

Expr* API::ExprEleRef(Expr* expr, Expr* index){
    return nullptr;
}

Expr* API::ExprEleAddr(Expr* expr, Expr* index){
    return nullptr;
}

Cell* API::CellRef(Expr* expr){
    return nullptr;
}

Expr* API::ExprPtr(Cell* cell){
    return nullptr;
}

Expr* API::ExprVal(Expr* expr){
    return nullptr;
}

Expr* API::ExprRef(Expr* expr){
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
    std::cout << "ExprFunRefArg " << std::endl;

}

void  API::ExprFunArg(Name name, Type* type){
    std::cout << "ExprFunArg " << std::endl;

}

Expr* API::ExprFunExpr(Expr* expr){
    std::cout << "ExprFunExpr " << std::endl;

    return nullptr;
}

Expr* API::ExprFunStmt(Stmt* stmt){
    return nullptr;
}

void  API::MatchBeg(Expr* expr){

}

void  API::MatchBranchBeg(Name name){

}

void  API::MatchBranchArg(Name name){

}

void  API::MatchBranchExpr(Expr* expr){

}

void  API::MatchBranchStmt(Stmt* stmt){

}

Expr* API::MatchEnd(){
    return nullptr;
}

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

Expr* API::UnOp(Oper oper, Expr* Expr){
    printf("Unop: %s\n", Oper_table[oper]);
    return nullptr;
}
Expr* API::BinOp(Expr* lhs, Oper oper, Expr* rhs){
    printf("Binop: %s\n", Oper_table[oper]);
    return nullptr;
}

Expr* API::New(Expr* expr){
    return nullptr;
}




 


// int main(){
//     struct API x;
//     x.BlockBegin();
//     return 0;
// }