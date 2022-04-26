#ifndef tc_ast_head_hpp
#define tc_ast_head_hpp

#include <string>
#include <stack>
#include <vector>
#include <map>
#include <fstream>

namespace tc{
namespace ast{
using Byte = uint8_t;
using Byte4 = uint32_t;
using Byte8 = uint64_t;

const Byte8 Magic    = 0x0063206465707974L; /* typed c\0 */
const Byte8 Version  = 0x3232343032323032L; /* 20220422  */
const Byte8 RESERVED = 0x4445565245534552L; /* RESERVED  */

template<typename T> using stack = std::stack<T>; 
template<typename T> using vector = std::vector<T>;
template<typename K, typename V> using map = std::map<K, V>;

using Name   = std::string;
using ID     = Byte4; /* unique identifier */
using Offset = Byte4; /* record offset in source code*/
using Size   = Byte4; /* length of array */


using Bool = bool;
using Char = char;
using Str = std::string;
using Int = int64_t;
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