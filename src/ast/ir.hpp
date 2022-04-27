#ifndef tc_ast_ir_hpp
#define tc_ast_ir_hpp

#include "head.hpp"

namespace tc{
namespace ast{
namespace ir{

enum Cat : Byte4 { /* Module's */
    CUNO = 0x4F4E5543, /* CUNO */
    EXEC = 0x43455845, /* EXEC */
};

enum Kind : Byte4 { /* Block 's */
    KUNO = 0x4F4E554B, /* KUNO */ // Kind::UNKNOWN
    
    INST = 0x54534E49, /* INST */ // ANF instruction
    ARGS = 0x53475241, /* ARGS */ // call  's arguments, just ids of expr
    FILD = 0x444C4946, /* FILD */ // constr's arguments, just ids of expr
    BRCH = 0x48435242, /* BRCH */ // destr 's branches, just ids of block
    
    SYMB = 0x424D5953, /* SYMB */ // Symbol
    PARA = 0x41524150, /* PARA */ // func  's parameters, just ids of expr
    
    TYPE = 0x54505954, /* TYPE */ // Type info, 
    TIDS = 0x53444954, /* TIDS */ // for Func type, just ids
    TCON = 0x4E4F4354, /* TCON */ // for adt's constructors, just ids of constructors
};

/* for ty : { Instruction, Symbol, Type }
 *     sizeof(ty) = 16
 */

struct Instruction
{
    enum Sort : Byte4 {
        UNNO  = 0x4F4E4E55, /* UNNO */
        IImm_ = 0x6D6D4949, /* IImm */
        FImm_ = 0x6D6D4946, /* FImm */
        IAdd  = 0x642B4149, /* IA+d */ 
        ISub  = 0x622D5349, /* IS-b */
        IMul  = 0x6C2A4D49, /* IM*l */
        IDiv  = 0x762F4449, /* ID/v */
        IMod  = 0x64254D49, /* IM%d */
        FAdd  = 0x642B4146, /* FA+d */ 
        FSub  = 0x622D5346, /* FS-b */
        FMul  = 0x6C2A4D46, /* FM*l */
        FDiv  = 0x762F4446, /* FD/v */
        FMod  = 0x64254D46, /* FM%d */

        /* used by Pointer */
        ULt   = 0x3F203C55, /* U< ? */
        ULe   = 0x3F3D3C55, /* U<=? */
        UGt   = 0x3F203E55, /* U> ? */
        UGe   = 0x3F3D3E55, /* U>=? */ 

        ILt   = 0x3F203C49, /* I< ? */
        ILe   = 0x3F3D3C49, /* I<=? */
        IGt   = 0x3F203E49, /* I> ? */
        IGe   = 0x3F3D3E49, /* I>=? */ 

        FLt   = 0x3F203C46, /* F< ? */
        FLe   = 0x3F3D3C46, /* F<=? */
        FGt   = 0x3F203E46, /* F> ? */
        FGe   = 0x3F3D3E46, /* F>=? */  

        Eq    = 0x3F3D3D54, /* T==? */
        Neq   = 0x3F3D2154, /* T!=? */

        Br    = 0x3A3F7242, /* Br?: */
        Ret   = 0x3E743D52, /* R=t> */


        Func  = 0x636E7546, /* Func */
        Call  = 0x6C6C6143, /* Call */
        Constr= 0x736E6F43, /* Cons */
        Destr = 0x74736E44, /* Dest */

        Alloc = 0x636F6C41, /* Aloc */ 
        New   = 0x2A77654E, /* New* */
        Del   = 0x2A6C6544, /* Del* */

        Set   = 0x21746553, /* Set! */
        Get   = 0x21746547, /* Get! */

        F2I   = 0x493E7E46, /* F~>I */
        I2F   = 0x463E7E49, /* I~>F */
    };
    Sort sort;
    ID dst;    // ID Destinate
    union {
        ID    id[2]; // ID Source 
        Int   Iimm;
        Float Fimm;
        Byte8 RESERVED;
    } src;
    /* switch sort
     * case IImm ~ FImm : I(F)imm = imm
     * case IAdd ~ Neq : calculate src.id[0] sort src.id[1] 
     * case Br   : dst = id of condition
     *             src.id[0] = id of block when true
     *             src.id[1] = id of block when false
     * case Ret  : dst = if of value to return, 
     *             src.RESERVED = RESERVED
     * case Func : src.id[0] = id of block of parameters
     *             src.id[1] = id of block of body
     * case Call : src.id[0] = id of function
     *             src.id[1] = id of block of arguments 
     * case Constr : src.id[0] = id of constructor
     *               src.id[1] = id of block of arguments 
     * case Destr  : src.id[0] = id of term destructed
     *               src.id[1] = id of block of branches
     * case Alloc  : src.id[0] = id of initial
     *               src.id[1] = id of length
     * case New    : src.id[0] = id of initial
     *             : src.id[1] = id of length
     * case Del    : dst = id of pointer to delete
     *               src.RESERVED = RESERVED
     * case Set    : dst = id of pointer to set
     *               src.id[0] = id of value
     *               src.id[1] = id of offset relative to ptr
     *               
     * case Get    : dst = id of value
     *               src.id[0] = id of pointer to get
     *               src.id[1] = id of offset relative to ptr
     * case F2I    : src.id[0] = id of src
     *               src.id[1] = I<~F
     * case I2F    : src.id[0] = id of src
     *               src.id[1] = F<~I
     */

    Instruction(Sort sort=UNNO, ID dst=0):sort(sort), dst(dst){}
    Instruction(Sort sort, ID dst, ID src0, ID src1)
    :sort(sort), dst(dst)
    {
        src.id[0] = src0;
        src.id[1] = src1;
    }
    static inline Instruction IImm(ID dst, Int i)
    {
        auto ins = Instruction(IImm_, dst);
        ins.src.Iimm = i; 
        return ins;
    }
    static inline Instruction FImm(ID dst, Float f)
    { 
        auto ins = Instruction(FImm_, dst);
        ins.src.Fimm = f; 
        return ins;
    }
    static inline Instruction Return(ID dst)
    {
        auto ins = Instruction(Ret, dst);
        ins.src.RESERVED = RESERVED;
        return ins;
    }
    static inline Instruction Delete(ID dst)
    {
        auto ins = Instruction(Del, dst);
        ins.src.RESERVED = RESERVED;
        return ins;
    }
    static inline Instruction ItoF(ID dst, ID src)
    { return Instruction(I2F, dst, src, 0x497E3C46); /* F<~I */ }
    static inline Instruction FtoI(ID dst, ID src)
    { return Instruction(F2I, dst, src, 0x467E3C49); /* F<~I */ }
};

struct Symbol
{
    enum Sort : Byte4 {
        Nfun_ = 0x6E75664E, /* Nfun */ // Not a function : Not Arrow Type
        Cons_ = 0x736E6F43, /* Cons */ // Constructor
        Func_ = 0x65727550, /* Func */ // (closed) Function
        Clos_ = 0x736F6C43, /* Clos */ // Closure
    };
    Sort sort;
    ID   symb;   /* id         of symbol */
    union {
        struct { ID type          ; } nfun;
        struct { ID type,     adty; } cons;
        struct { ID params, retype; } func;
        struct { ID type,     fvs;  } clos; 
        /* case cons : cons.type is id of block whose sort = TIDS
         * case func : func.params is id of block whose sort = PARA
         *             As for its type, use typeof(params) and retype to combine
         * case clos : closure is an object(fvs) but typed with
         *             clos.type,   id of block whose sort = TIDS
         *             When implemented, should pass fvs as context
         */
    } info;
    Symbol(Sort sort=Nfun_, ID symb=0)
    :sort(sort), symb(symb){}
    inline static Symbol Nfun(ID symb, ID type)
    {
        Symbol symbol(Nfun_, symb);
        symbol.info.nfun.type = type;
        return symbol;
    }
    inline static Symbol Cons(ID symb, ID type, ID adty)
    {
        Symbol symbol(Cons_, symb);
        auto& info = symbol.info.cons;
        info.type = type;
        info.adty = adty;
        return symbol;
    }
    inline static Symbol Func(ID symb, ID params, ID retype)
    {
        Symbol symbol(Cons_, symb);
        auto& info = symbol.info.func;
        info.params = params;
        info.retype = retype;
        return symbol;
    }
    inline static Symbol Clos(ID symb, ID type, ID fvs)
    {
        Symbol symbol(Clos_, symb);
        auto& info = symbol.info.clos;
        info.type = type;
        info.fvs  =  fvs;
        return symbol;
    }
};

struct Type
{
    enum Sort : Byte4 {
        Unit  = 0x30557954, /* TyU0 */ 
        Bool  = 0x31427954, /* TyB1 */
        Char  = 0x31437954, /* TyC1 */
        Int   = 0x38497954, /* TyI8 */
        Float = 0x38467954, /* TyF8 */
        Ptr   = 0x262A7954, /* Ty*& */
        Array = 0x5D5B7954, /* Ty[] */
        Func  = 0x3E2D7954, /* Ty-> */
        ADT   = 0x787C7954, /* Ty|x */
    };
    Sort sort;
    ID     id;
    Byte8 len; /* Array's */
    /* switch(sort)
     * case Unit~Float : Atom type
     * case Ptr   : id = id of T ~> &T
     * case Array : id = id of T ~> T[len]
     * case Func  : id = id of block whose Sort = TIDS
     *              block[0:size-2] = params type
     *              block[size-1]   = return type
     * case ADT   : id = id of block whose Sort = TCON
     */

    Type(Sort sort=Unit, ID id=0, Byte8 len=0)
    :sort(sort), id(id), len(len){}
};

}}}

#endif 