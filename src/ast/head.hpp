#ifndef tc_ast_head_hpp
#define tc_ast_head_hpp

#include <string>
#include <stack>
#include <vector>
#include <map>
#include <fstream>

namespace tc{
namespace ast{

template<typename T> using stack = std::stack<T>; 
template<typename T> using vector = std::vector<T>;
template<typename K, typename V> using map = std::map<K, V>;
using ifstream = std::ifstream;
using ofstream = std::ofstream;


using Name = std::string;
using ID   = unsigned; /* unique identifier */
using Offset = unsigned; /* record offset in source code*/
using Size = unsigned; /* Size = size_t */

using Bool = bool;
using Char = char;
using Str = std::string;
using Int = long;
using Float = double;
using Oper = enum { Undefined,
    Add, Sub, Mul, Div, Mod, 
    Pos, Neg,
    LShift, RShift,
    BNot, BAnd, BOr, BXor, 
    LNot, LAnd, LOr, LXOr, 
    Lt, Gt, Leq, Geq,
    Eq, Neq,
    FAdd, FSub, FMul, FDiv,
    PtrAdd, PtrSub
};
/* extension data */
struct Extd
{
    Offset /* position span in source file */
        row_beg, row_end,
        col_beg, col_end;
};
struct ExtdBase
{
    Extd extd;
};

}}

#endif