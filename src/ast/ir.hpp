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
    MTCH = 0x4843544D, /* MTCH */ // match's branches, just ids of expr
    
    
    SYMB = 0x424D5953, /* SYMB */ // Symbol
    PARA = 0x41524150, /* PARA */ // func  's parameters, just ids of expr
    FUNC = 0x434E5546, /* FUNC */ // for function's info
    BRCH = 0x48435242, /* BRCH */ // for branch's info
    CLOS = 0x534F4C43, /* CLOS */ // for closure's function info 

    TYPE = 0x45505954, /* TYPE */ // Type info, 
    TFUN = 0x4E554654, /* TFUN */ // for function's type, just ids of types
    TADT = 0x54444154, /* TADT */ // for adt's constructors, just ids of constructors
    TARR = 0x5D4E5B54, /* T[N] */ // for array type
    TTPL = 0x292C2854, /* T(,) */ // for tuple's type, just ids of types

    CSTR = 0x52545343, /* CSTR */ // c string immediate
};

struct Instruction
{
    enum Sort : Byte4 {
        SUNO  = 0x4F4E5553, /* SUNO */ // Sort Unknown
        Null  = 0x6C6C754E, /* Null */
        CImm  = 0x6D6D4943, /* CImm */
        IImm  = 0x6D6D4949, /* IImm */
        FImm  = 0x6D6D4946, /* FImm */
        SImm  = 0x6D6D4953, /* SImm */
        CStr  = 0x72745343, /* CStr */
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

        PAdd  = 0x642B4150, /* PA+d */ 
        PSub  = 0x622D5350, /* PS-b */
        PMov  = 0x763D4D50, /* PM=v */

        INeg  = 0x672D4E49, /* IN-g */
        FNeg  = 0x672D4e46, /* FN-g */

        LShift= 0x3C3C3C3C, /* <<<< */
        RShift= 0x3E3E3E3E, /* >>>> */
        BNot  = 0x21212121, /* !!!! */
        BAnd  = 0x26262626, /* &&&& */
        BOr   = 0x7C7C7C7C, /* |||| */
        BXor  = 0x5E5E5E5E, /* ^^^^ */
        
        LNot  = 0x746F6E20, /*  not */
        LAnd  = 0x646E6120, /*  and */
        LOr   = 0x20726F20, /*  or  */
        LXor  = 0x726F7820, /*  xor */


        /* used by Pointer */
        PLt   = 0x3F203C50, /* P< ? */
        PLe   = 0x3F3D3C50, /* P<=? */
        PGt   = 0x3F203E50, /* P> ? */
        PGe   = 0x3F3D3E50, /* P>=? */
        PEq   = 0x3F3D3D50, /* P==? */
        PNe   = 0x3F3D2150, /* P!=? */

        ILt   = 0x3F203C49, /* I< ? */
        ILe   = 0x3F3D3C49, /* I<=? */
        IGt   = 0x3F203E49, /* I> ? */
        IGe   = 0x3F3D3E49, /* I>=? */ 
        IEq   = 0x3F3D3D49, /* I==? */
        INe   = 0x3F3D2149, /* I!=? */

        FLt   = 0x3F203C46, /* F< ? */
        FLe   = 0x3F3D3C46, /* F<=? */
        FGt   = 0x3F203E46, /* F> ? */
        FGe   = 0x3F3D3E46, /* F>=? */  
        FEq   = 0x3F3D3D46, /* F==? */
        FNe   = 0x3F3D2146, /* F!=? */

        UEq   = 0x3F3D3D55, /* U==? */
        UNe   = 0x3F3D2155, /* U!=? */
        BEq   = 0x3F3D3D42, /* B==? */
        BNe   = 0x3F3D2142, /* B!=? */
        CEq   = 0x3F3D3D43, /* C==? */
        CNe   = 0x3F3D2143, /* C!=? */
        AEq   = 0x3D3D5D5B, /* []== */
        ANe   = 0x3D215D5B, /* []!= */
        TEq   = 0x3F3D3D54, /* T==? */
        TNe   = 0x3F3D2154, /* T!=? */

        Br    = 0x3A3F7242, /* Br?: */
        Jump  = 0x706D754A, /* Jump */
        Ret   = 0x3E743D52, /* R=t> */


        Call  = 0x6C6C6143, /* Call */
        Match = 0x6863744D, /* Mtch */

        Array = 0x79617241, /* Aray */
        Alloc = 0x636F6C41, /* Aloc */ 
        New   = 0x2A77654E, /* New* */
        NewAr = 0x5D775B4E, /* N[w] */
        Del   = 0x2A6C6544, /* Del* */

        Set   = 0x21746553, /* Set! */
        Get   = 0x21746547, /* Get! */

        F2I   = 0x493E7E46, /* F~>I */
        I2F   = 0x463E7E49, /* I~>F */
    };
    Sort sort;
    ID dst;    // ID Destinate
    union Src {
        ID    id[2]; // ID Source 
        Char  Cimm;
        Int   Iimm;
        Float Fimm;
        Char  SImm[8];
        Byte8 RESERVED;
        Src():RESERVED(tc::ast::RESERVED){}
    } src;
    /* switch sort
     * case BImm ~ FImm : I(F)imm = imm
     * case CStr        : src.id[0] = id of block Sort = CSTR
     * case IAdd ~ Neq : calculate src.id[0] sort src.id[1] 
     * case Br   : dst = id of condition
     *             src.id[0] = id of block when true
     *             src.id[1] = id of block when false
     * case Jump : dst = id of block to jump
     *             src.RESERVED = RESERVED
     * case Ret  : dst = if of value to return, 
     *             src.RESERVED = RESERVED
     * case Call : src.id[0] = id of function
     *             src.id[1] = id of block of arguments 
     * case Match  : src.id[0] = id of term destructed
     *               src.id[1] = id of block of branches
     * case Array  : src.id[0] = id of initial
     *               src.id[1] = id of length
     * case Alloc  : src.id[0] = id of expr
     *               src.id[1] = 0x6B617453 // Stak
     * case New    : src.id[0] = id of expr
     *               src.id[1] = 0x70616548 // Heap
     * case Del    : dst = id of pointer to delete
     *               src.RESERVED = RESERVED
     * case Set    : dst = id of pointer to set
     *               src.id[0] = id of value
     *               src.id[1] = id of offset relative to ptr
     * case Get    : dst = id of value
     *               src.id[0] = id of pointer to get
     *               src.id[1] = id of offset relative to ptr
     * case F2I    : src.id[0] = id of src
     *               src.id[1] = 0x467E3C49 // I<~F
     * case I2F    : src.id[0] = id of src
     *               src.id[1] = 0x497E3C46 // F<~I
     */

    Instruction(Sort sort=SUNO, ID dst=0):sort(sort), dst(dst){}
    Instruction(Sort sort, ID dst, ID src0, ID src1)
    :sort(sort), dst(dst)
    {
        src.id[0] = src0;
        src.id[1] = src1;
    }
};

struct Symbol
{
    enum Sort : Byte4 {
        SUNO  = 0x4F4E5553, /* SUNO */ // Sort Unknown
        Const = 0x74736E43, /* Cnst */ // Compiler-time constant
        Param = 0x61726150, /* Para */ // Parameter of function
        NonD  = 0x446E6F4E, /* NonD */ // Non-Determinate introduced by Param, NOT Pure Function

        Ctor  = 0x726F7443, /* Ctor */ // Constructor
        Brch  = 0x68637242, /* Brch */ // Branch of Match

        CFun  = 0x6E754643, /* CFun */ // Function that is Closed and     Pure
        CPrg  = 0x67725043, /* CPrg */ // Function that is Closed and NOT Pure
        
        QFun  = 0x6E754651, /* QFun */ 
            // Function that is Open and     Pure
            // but all reference of open variables are Const
            // -> Quasi-closed Func

        QPrg  = 0x67725051, /* QPrg */ 
            // Function that is Open and NOT Pure
            // ... 
            // -> Quasi-closed Prog

        Open  = 0x6E65704F, /* Open */ // Function that is Open

        Clos  = 0x736F6C43, /* Clos */ // Closure, Open Function that has been instantialized
    };
    Sort sort;
    union Info
    {
        ID  type; 
        /* case Const: case Param: case NonD:
         * type of symbol
         */
        ID block; 
        /* case Ctor: sort = ... [type, adty]
         * case CFun: sort = ... [params, retype]
         * case CPrg:            [params, retype]
         * case QFun:            [params, retype, outer]
         * case QPrg:            [params, retype, outer]
         * case Open:            [params, retype, outer]
         * case Closure:         [params, retype, outer]
         */
        Info(ID id):type(id){ }
    }    info;
    Symbol(Sort sort=SUNO, ID id=0):sort(sort), info(id){ }
};

struct Type
{
    enum Sort : Byte4 {
        SUNO  = 0x4F4E5553, /* SUNO */ // Sort Unknown
        Unit  = 0x30557954, /* TyU0 */ 
        Bool  = 0x31427954, /* TyB1 */
        Char  = 0x31437954, /* TyC1 */
        Int   = 0x38497954, /* TyI8 */
        Float = 0x38467954, /* TyF8 */
        Ptr   = 0x26407954, /* Ty@& */
        Array = 0x5D5B7954, /* Ty[] */
        Func  = 0x3E2D7954, /* Ty-> */
        Tuple = 0x29287954, /* Ty() */
        ADT   = 0x787C7954, /* Ty|x */
        ADTR  = 0x247C7954, /* Ty|$ */
    };
    Sort sort;
    ID     id;
    /* switch(sort)
     * case Unit~Float : Atom type
     * case Ptr   : id = id of T ~> &T
     * case Array : id = id of block whose Sort = T[N]
     *              id of T, len ~> T[len]
     * case Tuple : id = id of block whose Sort = T(,)
     * 
     * case Func  : id = id of block whose Sort = TFUN
     *              block[0]        = return type
     *              block[1:size-1] = params type
     * case ADT   : id = id of block whose Sort = TSUM
     */
    Type(Sort sort=SUNO, ID id=0)
    :sort(sort), id(id){}
};

}}}

#endif 