#ifndef tc_ast_builtin_hpp
#define tc_ast_builtin_hpp

#include "head.hpp"

namespace tc{
namespace ast{

enum T_ID : ID
{   T_UNIT  = 0
,   T_BOOL  = 1
,   T_CHAR  = 2
,   T_INT   = 3
,   T_FLOAT = 4
,   T_PTRC  = 5
,   T_I2F   = 6
,   T_F2I   = 7
,   T_2C    = 8  // {       -> Char  }
,   T_C2U   = 9  // { Char  -> Unit  }
,   T_2I    = 10 // {       -> Int   }
,   T_I2U   = 11 // { Int   -> Unit  }
,   T_PC2PC = 12 // { &Char -> &Char }
,   T_PC2U  = 13 // { &Char -> Unit  }
,   T_PC2I  = 14 // { &Char -> Int   }
,   T_2F    = 15 // {       -> Float }
,   T_F2U   = 16 // { Float -> Unit  }
,   T_END
};
enum E_ID : ID 
{   E_UNIT  = 0
,   E_TRUE  = 1
,   E_FALSE = 2
,   E_I2F   = 3
,   E_F2I   = 4
,   E_GETC  = 5
,   E_PUTC  = 6
,   E_GETI  = 7
,   E_PUTI  = 8
,   E_GETS  = 9
,   E_PUTS  = 10
,   E_SGETI = 11
,   E_GETF  = 12
,   E_PUT1F = 13
,   E_END
};


}}


#endif