
#ifndef tc_ast_token_hpp
#define tc_ast_token_hpp

#include "head.hpp"

namespace tc{
namespace ast{

/* extension data */
struct Extd
{
    Offset /* position span in source file */
        row_beg, row_end,
        col_beg, col_end;
    Extd():row_beg(0), row_end(0), col_beg(0), col_end(0){}
    ~Extd(){}
};
struct ExtdBase
{
    Extd extd;
};

struct Name : public ExtdBase, string
{
    Name(){}
    Name(string name):string(name){}
    ~Name(){}
};

using Oper = enum { Undefined,
    Pos, Neg,
    Add, Sub, Mul, Div, 
    Mod, LShift, RShift,
    BNot, BAnd, BOr, BXOr,
    LNot, LAnd, LOr, LXOr, 
    Lt, Gt, Leq, Geq,
    Eq, Neq,
    FAdd, FSub, FMul, FDiv,
    PtrAdd, AddPtr, PtrSub
};



}}

#endif