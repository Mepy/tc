%{
    #include <iostream>
    #include <api.hpp>
    #include <token.hpp>    
    
%}

/// types
%union {
    int64_t ival;
    float fval;
    char cval;
    // boolean considered as string
    std::string sval;
    Stmt* stmt;
    Type* type;
    Cell* cell;
    Expr* expr;
}

%token LP RP LB RB LC RC 
%token SEMI COMMA COLON 
%token ASSIGN 
%token SELF 
%%
