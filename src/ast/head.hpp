#ifndef tc_ast_head_hpp
#define tc_ast_head_hpp

#include <string>
#include <stack>
#include <vector>
#include <list>
#include <set>
#include <map>

namespace tc{
namespace ast{

using Byte = uint8_t;
using Byte4 = uint32_t;
using Byte8 = uint64_t;

const Byte8 Magic    = 0x0063206465707974L; /* typed c\0 */
const Byte8 Version  = 0x3232343032323032L; /* 20220422  */
const Byte8 RESERVED = 0x4445565245534552L; /* RESERVED  */

using string = std::string;
template<typename T> using set = std::set<T>;
template<typename T> using list = std::list<T>;
template<typename T> using stack = std::stack<T>;
template<typename T> using vector = std::vector<T>;
template<typename K, typename V> using map = std::map<K, V>;
template<typename K, typename V> using pair = std::pair<K, V>;

using ID     = Byte4; /* unique identifier */
using IDs    = vector<ID>;

using Offset = Byte4; /* record offset in source code*/
using Size   = Byte4; /* length of array */

using Bool = bool;
using Char = char;
using Str = std::string;
using Int = int64_t;
using Float = double;

struct Context;
struct Stmt;
struct Expr;
struct Cell;
struct Type;
using Contextp = Context*;
using Stmtp = Stmt*;
using Stmts = vector<Stmtp>;
using Exprp = Expr*;
using Exprs = vector<Exprp>;
using Cellp = Cell*;
using Typep = Type*;
using Types = vector<Typep>;

}}

#endif