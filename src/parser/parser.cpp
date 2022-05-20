/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "tc.y"

    #include <iostream>
    #include <math.h>
    #include <string>
    #include "head.hpp"
    int yylex(void);
    void yyerror(char* s);
    API context;

#line 80 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LP = 258,
    RP = 259,
    LB = 260,
    RB = 261,
    LC = 262,
    RC = 263,
    SEMI = 264,
    COMMA = 265,
    COLON = 266,
    ASSIGN = 267,
    ADDASSIGN = 268,
    SUBASSIGN = 269,
    MULASSIGN = 270,
    DIVASSIGN = 271,
    MODASSIGN = 272,
    FADDASSIGN = 273,
    FSUBASSIGN = 274,
    FMULASSIGN = 275,
    FDIVASSIGN = 276,
    SELF = 277,
    REFS = 278,
    REFLB = 279,
    REFLP = 280,
    PTRLB = 281,
    REF = 282,
    PTR = 283,
    BS = 284,
    RDARROW = 285,
    RSARROW = 286,
    ARR = 287,
    BNOT = 288,
    LNOT = 289,
    FADD = 290,
    FSUB = 291,
    FMUL = 292,
    FDIV = 293,
    ADD = 294,
    SUB = 295,
    MUL = 296,
    DIV = 297,
    LAND = 298,
    LOR = 299,
    LXOR = 300,
    LEQ = 301,
    GEQ = 302,
    LT = 303,
    GT = 304,
    MOD = 305,
    BAND = 306,
    BOR = 307,
    BXOR = 308,
    LSHIFT = 309,
    RSHIFT = 310,
    EQ = 311,
    NEQ = 312,
    ADDPTR = 313,
    PTRADD = 314,
    PTRSUB = 315,
    LET = 316,
    IF = 317,
    ELSE = 318,
    WHILE = 319,
    BREAK = 320,
    CONT = 321,
    RET = 322,
    DEL = 323,
    _TYPE = 324,
    CHECK = 325,
    FUN = 326,
    MATCH = 327,
    WITH = 328,
    NEW = 329,
    INT = 330,
    FLOAT = 331,
    CHAR = 332,
    STRING = 333,
    TN = 334,
    EN = 335
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "tc.y"

    Int ival;
    Float fval;
    Char cval;
    char* sval;

    Stmt* stmt;
    Type* type;
    Cell* cell;
    Expr* expr;
    Oper oper;

#line 226 "parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  101
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   432

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  92
/* YYNRULES -- Number of rules.  */
#define YYNRULES  189
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  287

#define YYUNDEFTOK  2
#define YYMAXUTOK   335


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    63,    63,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    82,    85,    85,    88,
      88,    89,    92,    95,    98,    99,   102,   102,   106,   107,
     110,   111,   114,   115,   121,   123,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   137,   138,   140,   140,
     143,   146,   149,   150,   153,   153,   156,   157,   158,   161,
     164,   165,   166,   167,   168,   170,   174,   178,   182,   186,
     186,   191,   191,   191,   193,   195,   198,   199,   200,   201,
     204,   205,   208,   211,   214,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   236,   241,   246,   251,   256,   260,   264,
     268,   273,   277,   281,   285,   289,   294,   298,   298,   301,
     301,   304,   304,   307,   311,   314,   314,   315,   322,   323,
     326,   326,   327,   328,   331,   332,   332,   342,   342,   344,
     344,   345,   345,   345,   346,   346,   350,   354,   354,   357,
     362,   363,   364,   365,   368,   371,   375,   376,   377,   378,
     379,   380,   383,   386,   390,   391,   392,   393,   394,   395,
     396,   397,   400,   403,   407,   408,   409,   410,   411,   412,
     413,   416,   419,   424,   427,   430,   431,   432,   433,   434
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LP", "RP", "LB", "RB", "LC", "RC",
  "SEMI", "COMMA", "COLON", "ASSIGN", "ADDASSIGN", "SUBASSIGN",
  "MULASSIGN", "DIVASSIGN", "MODASSIGN", "FADDASSIGN", "FSUBASSIGN",
  "FMULASSIGN", "FDIVASSIGN", "SELF", "REFS", "REFLB", "REFLP", "PTRLB",
  "REF", "PTR", "BS", "RDARROW", "RSARROW", "ARR", "BNOT", "LNOT", "FADD",
  "FSUB", "FMUL", "FDIV", "ADD", "SUB", "MUL", "DIV", "LAND", "LOR",
  "LXOR", "LEQ", "GEQ", "LT", "GT", "MOD", "BAND", "BOR", "BXOR", "LSHIFT",
  "RSHIFT", "EQ", "NEQ", "ADDPTR", "PTRADD", "PTRSUB", "LET", "IF", "ELSE",
  "WHILE", "BREAK", "CONT", "RET", "DEL", "_TYPE", "CHECK", "FUN", "MATCH",
  "WITH", "NEW", "INT", "FLOAT", "CHAR", "STRING", "TN", "EN", "$accept",
  "Start", "Stmt", "Empty", "Block", "$@1", "BlockStmtList", "$@2", "Let",
  "Var", "If", "While", "$@3", "Break", "Cont", "Ret", "Del", "Asgn",
  "AssignOp", "NewType", "NewTypeDef", "$@4", "Alias", "ADT", "ADTLists",
  "ADTList", "$@5", "TypeLists", "Check", "Type", "TypeVar", "TypeRef",
  "TypePtr", "TypeArr", "TypeFun", "$@6", "TypeFunArg", "$@7", "TypeDef",
  "Cell", "CellVar", "CellVarEle", "CellEle", "CellRef", "Expr", "I", "F",
  "C", "S", "ExprPtr", "ExprVal", "ExprRef", "ExprVar", "ExprVarRef",
  "Arr", "Ele", "EleRef", "EleAddr", "New", "FunStart", "ExprFunArgLists",
  "$@8", "$@9", "ExprFunDef", "FunFront", "$@10", "Fun", "AppStart",
  "AppArg", "$@11", "App", "$@12", "Match", "$@13", "MatchLists",
  "ENLists", "$@14", "MatchList", "$@15", "MatchDef", "Calc", "UnCalc",
  "UnOp", "BinCalc1", "BinOp1", "BinCalc2", "BinOp2", "BinCalc3", "BinOp3",
  "BinCalc4", "BinCalc5", "BinOp4", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335
};
# endif

#define YYPACT_NINF (-249)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-138)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     102,  -249,  -249,   -76,   157,   -22,    12,  -249,    -6,     4,
      27,   157,   -56,   157,    26,    66,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
       1,  -249,   411,  -249,  -249,  -249,  -249,   102,  -249,   157,
    -249,   157,    -2,    -7,  -249,  -249,  -249,  -249,  -249,   157,
    -249,   157,   157,  -249,  -249,  -249,  -249,  -249,    86,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,   102,  -249,    49,  -249,  -249,  -249,
    -249,   157,  -249,   161,   357,   362,   328,     2,    72,   157,
      91,  -249,    88,  -249,   104,  -249,   149,   198,  -249,    14,
     157,  -249,   102,  -249,    44,    44,    20,  -249,  -249,  -249,
     111,    69,     9,  -249,  -249,  -249,  -249,  -249,   157,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,   157,
     116,   271,    86,  -249,   117,    86,   114,   214,   157,   157,
     157,   157,    35,  -249,  -249,   157,  -249,   383,  -249,  -249,
    -249,  -249,  -249,  -249,   157,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,   157,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,   157,  -249,  -249,  -249,  -249,  -249,   157,    72,    44,
     118,   274,   157,  -249,  -249,  -249,  -249,   119,    17,   283,
    -249,    44,   127,   127,  -249,  -249,  -249,    67,  -249,   287,
     311,  -249,  -249,    71,   157,   320,   324,   335,    82,    65,
      72,   126,   123,   153,   157,   383,   161,   357,   362,   328,
     141,   127,   157,   102,   350,  -249,  -249,  -249,   127,   128,
      37,   155,  -249,  -249,   113,   245,  -249,  -249,  -249,    72,
    -249,  -249,   167,  -249,   179,   157,   359,   125,   102,    44,
      44,    37,  -249,     5,  -249,   109,  -249,   113,  -249,    35,
     157,  -249,   368,  -249,   102,  -249,  -249,    87,  -249,  -249,
    -249,  -249,    35,  -249,  -249,  -249,  -249,  -249,   115,  -249,
    -249,   164,   115,   102,  -249,  -249,  -249
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      21,    17,    16,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,     0,    81,     0,    19,     3,     4,     2,
       5,     6,     7,     8,     9,    10,    13,    11,    12,    14,
      53,    15,     0,    76,    77,    78,    79,    21,    80,     0,
     129,     0,     0,     0,   118,   150,   151,   153,   152,     0,
     117,     0,     0,   103,   104,   105,   106,   110,    84,   100,
      99,   101,   102,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   125,     0,    85,     0,    98,    86,    97,
     147,     0,   148,   155,   163,   173,   182,     0,    75,     0,
       0,    29,     0,    31,     0,    33,   184,   184,    48,   184,
       0,     1,    21,    69,     0,     0,     0,    65,    46,    47,
       0,    53,     0,    60,    61,    62,    63,    64,     0,    36,
      37,    38,    39,    40,    45,    41,    42,    43,    44,     0,
       0,   184,   109,   111,   107,   108,   184,   184,     0,     0,
       0,     0,   123,   124,   127,   133,   135,   149,   159,   160,
     161,   156,   157,   158,     0,   166,   167,   164,   165,   170,
     171,   168,   169,     0,   176,   177,   174,   175,   178,   179,
     180,     0,   187,   188,   185,   186,   189,     0,    75,     0,
       0,   184,     0,    28,    30,    32,    34,     0,     0,   184,
      20,    73,    66,    67,    54,    51,    52,     0,    50,   184,
     184,    18,   183,     0,     0,   184,   184,   184,   112,     0,
      75,     0,   184,     0,   133,   184,   154,   162,   172,   181,
       0,    74,     0,     0,   184,    49,    59,    82,    71,     0,
      58,     0,    83,    35,   140,   112,   113,   114,   115,    75,
     119,   126,     0,   134,     0,     0,   184,    24,     0,    73,
       0,    58,    55,    58,    68,     0,   138,   140,   121,   123,
     133,   136,   184,    22,     0,    27,    72,     0,    57,    56,
     144,   139,   123,   120,   131,    23,    25,    70,   143,   122,
     141,     0,   143,     0,   142,   146,   145
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -249,  -249,   -72,  -249,  -249,  -249,   -21,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,    85,  -249,  -249,  -163,  -249,   -29,
    -249,  -249,  -249,  -249,  -249,  -249,   -50,  -249,  -153,   159,
    -249,  -249,  -249,  -249,    -4,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -248,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -171,  -249,
    -249,  -249,  -249,  -249,   -49,   -73,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,    61,  -249,    53,  -249,    54,
      50,  -249
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    15,    16,    17,    18,    37,    19,   102,    20,    21,
      22,    23,    90,    24,    25,    26,    27,    28,   129,    29,
      30,   187,   108,   109,   110,   111,   230,   252,    31,   253,
     113,   114,   115,   116,   117,   191,   229,   249,   180,    32,
      33,    34,    35,    36,   215,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
     211,   259,   272,   144,    74,   142,    75,    76,   213,   242,
      77,   214,    78,   203,   256,   281,   282,   257,   278,   286,
      79,    80,    81,    82,   154,    83,   163,    84,   171,    85,
      86,   177
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,   112,   143,    91,    38,    87,    96,    97,   103,    99,
     197,   273,   103,    93,   197,    89,   130,  -128,   198,   138,
       3,   103,   197,    98,   279,   220,   226,   251,   104,   105,
      39,   100,   104,   105,     4,   131,    95,   132,   139,  -128,
     140,   104,   105,   244,   103,   135,   141,   136,   137,    40,
      41,   103,   145,   106,    42,    43,    44,   240,    88,   251,
      45,    46,   209,    47,   104,   105,   101,    48,    49,    92,
     188,   104,   105,    14,   146,   192,   193,   147,   133,    94,
     107,   190,   178,   179,   107,   181,   258,   138,   268,   274,
     269,   138,   197,   107,   182,   277,   189,   183,    50,    51,
     194,    52,    53,    54,    55,    56,   139,    57,   140,     1,
     139,     2,   140,   184,   199,   210,   107,  -128,   141,   138,
     195,   106,   118,   107,   201,   200,  -128,  -132,   138,     3,
     222,   225,   197,  -130,   205,   206,   207,   208,   139,  -128,
     140,   212,   231,     4,   234,   239,   141,   139,  -128,   140,
     221,   247,  -128,   245,   138,   141,   241,   243,   185,   250,
      39,   254,   228,     5,     6,   255,     7,     8,     9,    10,
      11,    12,    13,   139,  -128,   140,   265,   260,   224,    40,
      41,   141,    14,   261,    42,    43,    44,  -137,   264,   270,
      45,    46,   276,    47,   283,   280,   196,    48,    49,   266,
     235,  -128,   134,   138,   148,   149,   150,   186,   271,   284,
     212,   285,   151,   152,   153,   216,   217,  -128,   246,   138,
     228,   267,   139,  -128,   140,   218,     0,   219,    50,    51,
     141,    52,    53,    54,    55,    56,     0,    57,   139,  -128,
     140,   262,     0,     0,     0,     0,   204,     0,     0,  -116,
     138,  -116,  -116,     0,  -116,  -116,   212,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,     0,     0,   139,
       0,   140,  -116,  -116,  -128,   202,   138,  -128,   223,   138,
       0,     0,     0,     0,     0,     0,  -128,     0,   138,   227,
    -128,     0,   138,   232,     0,   139,  -128,   140,   139,  -128,
     140,     0,     0,   141,     0,     0,   141,   139,  -128,   140,
       0,   139,  -128,   140,  -128,   141,   138,     0,  -116,   141,
     233,     0,     0,  -128,  -116,   138,   236,  -128,     0,   138,
     237,     0,     0,     0,     0,   139,  -128,   140,  -128,     0,
     138,   238,     0,   141,   139,  -128,   140,     0,   139,  -128,
     140,     0,   141,  -128,   248,   138,   141,     0,     0,   139,
    -128,   140,  -128,     0,   138,   172,   173,   141,   263,   174,
     175,  -128,     0,   138,   139,  -128,   140,   275,   176,     0,
       0,     0,   141,   139,  -128,   140,  -128,     0,   138,     0,
       0,   141,   139,  -128,   140,     0,     0,   164,   165,     0,
     141,   166,   167,   155,   156,   157,   158,   139,  -128,   140,
       0,   159,   160,   161,   162,   141,   118,     0,     0,     0,
     168,   169,   170,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128
};

static const yytype_int16 yycheck[] =
{
       4,    30,    74,     9,    80,    27,    10,    11,     7,    13,
       5,   259,     7,     9,     5,     3,    37,     3,     9,     5,
      27,     7,     5,    79,   272,   178,     9,    22,    27,    28,
       3,     5,    27,    28,    41,    39,     9,    41,    24,    25,
      26,    27,    28,   214,     7,    49,    32,    51,    52,    22,
      23,     7,     3,    52,    27,    28,    29,   210,    80,    22,
      33,    34,    27,    36,    27,    28,     0,    40,    41,    75,
      99,    27,    28,    80,    25,   104,   105,    81,    80,    75,
      79,   102,    80,    11,    79,    89,   239,     5,   251,   260,
     253,     5,     5,    79,     3,     8,   100,     9,    71,    72,
      80,    74,    75,    76,    77,    78,    24,    80,    26,     7,
      24,     9,    26,     9,   118,    80,    79,     3,    32,     5,
       9,    52,     5,    79,     8,   129,     3,     4,     5,    27,
      12,    12,     5,    10,   138,   139,   140,   141,    24,    25,
      26,   145,    75,    41,    73,    80,    32,    24,    25,    26,
     179,   223,     3,    12,     5,    32,    30,     4,     9,    31,
       3,     6,   191,    61,    62,    52,    64,    65,    66,    67,
      68,    69,    70,    24,    25,    26,   248,    10,   182,    22,
      23,    32,    80,     4,    27,    28,    29,    73,    63,    80,
      33,    34,   264,    36,    30,    80,   111,    40,    41,   249,
     204,     3,    43,     5,    43,    44,    45,     9,   257,   282,
     214,   283,    51,    52,    53,   154,   163,     3,   222,     5,
     249,   250,    24,    25,    26,   171,    -1,   177,    71,    72,
      32,    74,    75,    76,    77,    78,    -1,    80,    24,    25,
      26,   245,    -1,    -1,    -1,    -1,    32,    -1,    -1,     4,
       5,     6,     7,    -1,     9,    10,   260,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    24,
      -1,    26,    27,    28,     3,     4,     5,     3,     4,     5,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,     6,
       3,    -1,     5,     6,    -1,    24,    25,    26,    24,    25,
      26,    -1,    -1,    32,    -1,    -1,    32,    24,    25,    26,
      -1,    24,    25,    26,     3,    32,     5,    -1,    73,    32,
       9,    -1,    -1,     3,    79,     5,     6,     3,    -1,     5,
       6,    -1,    -1,    -1,    -1,    24,    25,    26,     3,    -1,
       5,     6,    -1,    32,    24,    25,    26,    -1,    24,    25,
      26,    -1,    32,     3,     4,     5,    32,    -1,    -1,    24,
      25,    26,     3,    -1,     5,    37,    38,    32,     9,    41,
      42,     3,    -1,     5,    24,    25,    26,     9,    50,    -1,
      -1,    -1,    32,    24,    25,    26,     3,    -1,     5,    -1,
      -1,    32,    24,    25,    26,    -1,    -1,    35,    36,    -1,
      32,    39,    40,    46,    47,    48,    49,    24,    25,    26,
      -1,    54,    55,    56,    57,    32,     5,    -1,    -1,    -1,
      58,    59,    60,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     9,    27,    41,    61,    62,    64,    65,    66,
      67,    68,    69,    70,    80,    82,    83,    84,    85,    87,
      89,    90,    91,    92,    94,    95,    96,    97,    98,   100,
     101,   109,   120,   121,   122,   123,   124,    86,    80,     3,
      22,    23,    27,    28,    29,    33,    34,    36,    40,    41,
      71,    72,    74,    75,    76,    77,    78,    80,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   145,   147,   148,   151,   153,   161,
     162,   163,   164,   166,   168,   170,   171,    27,    80,     3,
      93,     9,    75,     9,    75,     9,   125,   125,    79,   125,
       5,     0,    88,     7,    27,    28,    52,    79,   103,   104,
     105,   106,   110,   111,   112,   113,   114,   115,     5,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    99,
      87,   125,   125,    80,   120,   125,   125,   125,     5,    24,
      26,    32,   146,    83,   144,     3,    25,   125,    43,    44,
      45,    51,    52,    53,   165,    46,    47,    48,    49,    54,
      55,    56,    57,   167,    35,    36,    39,    40,    58,    59,
      60,   169,    37,    38,    41,    42,    50,   172,    80,    11,
     119,   125,     3,     9,     9,     9,     9,   102,   110,   125,
      87,   116,   110,   110,    80,     9,   105,     5,     9,   125,
     125,     8,     4,   154,    32,   125,   125,   125,   125,    27,
      80,   141,   125,   149,   152,   125,   166,   168,   170,   171,
     119,   110,    12,     4,   125,    12,     9,     6,   110,   117,
     107,    75,     6,     9,    73,   125,     6,     6,     6,    80,
     119,    30,   150,     4,   149,    12,   125,    83,     4,   118,
      31,    22,   108,   110,     6,    52,   155,   158,   119,   142,
      10,     4,   125,     9,    63,    83,   117,   110,   108,   108,
      80,   155,   143,   141,   149,     9,    83,     8,   159,   141,
      80,   156,   157,    30,   156,    83,   160
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    84,    86,    85,    88,
      87,    87,    89,    90,    91,    91,    93,    92,    94,    94,
      95,    95,    96,    96,    97,    98,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,   100,   100,   102,   101,
     103,   104,   105,   105,   107,   106,   108,   108,   108,   109,
     110,   110,   110,   110,   110,   111,   112,   113,   114,   116,
     115,   118,   117,   117,   119,   119,   120,   120,   120,   120,
     121,   121,   122,   123,   124,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   140,   142,
     141,   143,   141,   141,   144,   146,   145,   147,   148,   148,
     150,   149,   149,   149,   151,   152,   151,   154,   153,   155,
     155,   157,   156,   156,   159,   158,   160,   161,   161,   162,
     163,   163,   163,   163,   164,   164,   165,   165,   165,   165,
     165,   165,   166,   166,   167,   167,   167,   167,   167,   167,
     167,   167,   168,   168,   169,   169,   169,   169,   169,   169,
     169,   170,   170,   171,   171,   172,   172,   172,   172,   172
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       3,     0,     6,     7,     5,     7,     0,     6,     3,     2,
       3,     2,     3,     2,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     0,     4,
       2,     2,     2,     0,     0,     4,     2,     2,     0,     4,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     0,
       6,     0,     3,     0,     2,     0,     1,     1,     1,     1,
       2,     1,     4,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       1,     2,     3,     4,     4,     4,     4,     1,     1,     0,
       4,     0,     5,     0,     1,     0,     4,     2,     1,     1,
       0,     4,     1,     0,     4,     0,     5,     0,     5,     2,
       0,     0,     3,     0,     0,     6,     1,     1,     1,     2,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 16:
#line 82 "tc.y"
            { (yyval.stmt) = context.Empty(); }
#line 1667 "parser.cpp"
    break;

  case 17:
#line 85 "tc.y"
   { context.BlockBegin();}
#line 1673 "parser.cpp"
    break;

  case 18:
#line 85 "tc.y"
                                             { (yyval.stmt) = context.BlockEnd(); }
#line 1679 "parser.cpp"
    break;

  case 19:
#line 88 "tc.y"
     { context.BlockStmt((yyvsp[0].stmt)); }
#line 1685 "parser.cpp"
    break;

  case 21:
#line 89 "tc.y"
{ ; }
#line 1691 "parser.cpp"
    break;

  case 22:
#line 92 "tc.y"
                                { (yyval.stmt) = context.Let((yyvsp[-4].sval), (yyvsp[-1].expr), (yyvsp[-3].type)); }
#line 1697 "parser.cpp"
    break;

  case 23:
#line 95 "tc.y"
                                    { (yyval.stmt) = context.Var((yyvsp[-4].sval), (yyvsp[-1].expr), (yyvsp[-3].type)); }
#line 1703 "parser.cpp"
    break;

  case 24:
#line 98 "tc.y"
                   { (yyval.stmt) = context.If((yyvsp[-2].expr), (yyvsp[0].stmt), nullptr); }
#line 1709 "parser.cpp"
    break;

  case 25:
#line 99 "tc.y"
                             { (yyval.stmt) = context.If((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 1715 "parser.cpp"
    break;

  case 26:
#line 102 "tc.y"
      {context.WhileBeg(); }
#line 1721 "parser.cpp"
    break;

  case 27:
#line 103 "tc.y"
                { (yyval.stmt) = context.While((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1727 "parser.cpp"
    break;

  case 28:
#line 106 "tc.y"
               { (yyval.stmt) = context.Break((yyvsp[-1].ival)); }
#line 1733 "parser.cpp"
    break;

  case 29:
#line 107 "tc.y"
           { (yyval.stmt) = context.Break(); }
#line 1739 "parser.cpp"
    break;

  case 30:
#line 110 "tc.y"
              { (yyval.stmt) = context.Cont((yyvsp[-1].ival)); }
#line 1745 "parser.cpp"
    break;

  case 31:
#line 111 "tc.y"
          { (yyval.stmt) = context.Cont(); }
#line 1751 "parser.cpp"
    break;

  case 32:
#line 114 "tc.y"
              { (yyval.stmt) = context.Ret((yyvsp[-1].expr)); }
#line 1757 "parser.cpp"
    break;

  case 33:
#line 115 "tc.y"
         { (yyval.stmt) = context.Ret(); }
#line 1763 "parser.cpp"
    break;

  case 34:
#line 121 "tc.y"
              { (yyval.stmt) = context.Del((yyvsp[-1].expr)); }
#line 1769 "parser.cpp"
    break;

  case 35:
#line 123 "tc.y"
                              { (yyval.stmt) = context.Asgn((yyvsp[-3].cell), (yyvsp[-2].oper), (yyvsp[-1].expr)); }
#line 1775 "parser.cpp"
    break;

  case 36:
#line 125 "tc.y"
       { (yyval.oper) = Oper::Undefined; }
#line 1781 "parser.cpp"
    break;

  case 37:
#line 126 "tc.y"
          { (yyval.oper) = Oper::Add; }
#line 1787 "parser.cpp"
    break;

  case 38:
#line 127 "tc.y"
          { (yyval.oper) = Oper::Sub; }
#line 1793 "parser.cpp"
    break;

  case 39:
#line 128 "tc.y"
          { (yyval.oper) = Oper::Mul; }
#line 1799 "parser.cpp"
    break;

  case 40:
#line 129 "tc.y"
          { (yyval.oper) = Oper::Div; }
#line 1805 "parser.cpp"
    break;

  case 41:
#line 130 "tc.y"
           { (yyval.oper) = Oper::FAdd; }
#line 1811 "parser.cpp"
    break;

  case 42:
#line 131 "tc.y"
           { (yyval.oper) = Oper::FSub; }
#line 1817 "parser.cpp"
    break;

  case 43:
#line 132 "tc.y"
           { (yyval.oper) = Oper::FMul; }
#line 1823 "parser.cpp"
    break;

  case 44:
#line 133 "tc.y"
           { (yyval.oper) = Oper::FDiv; }
#line 1829 "parser.cpp"
    break;

  case 45:
#line 134 "tc.y"
          { (yyval.oper) = Oper::Mod; }
#line 1835 "parser.cpp"
    break;

  case 46:
#line 137 "tc.y"
                 { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1841 "parser.cpp"
    break;

  case 47:
#line 138 "tc.y"
               { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1847 "parser.cpp"
    break;

  case 48:
#line 140 "tc.y"
                     { context.TypeDef((yyvsp[0].sval)); }
#line 1853 "parser.cpp"
    break;

  case 50:
#line 143 "tc.y"
          { (yyval.stmt) = context.Alias((yyvsp[-1].type)); }
#line 1859 "parser.cpp"
    break;

  case 51:
#line 146 "tc.y"
              { (yyval.stmt) = context.ADT(); }
#line 1865 "parser.cpp"
    break;

  case 53:
#line 150 "tc.y"
{ ; }
#line 1871 "parser.cpp"
    break;

  case 54:
#line 153 "tc.y"
       { context.ADTBranchBegin((yyvsp[0].sval)); }
#line 1877 "parser.cpp"
    break;

  case 55:
#line 153 "tc.y"
                                                 { context.ADTBranchEnd(); }
#line 1883 "parser.cpp"
    break;

  case 56:
#line 156 "tc.y"
               { context.ADTBranchType((yyvsp[-1].type)); }
#line 1889 "parser.cpp"
    break;

  case 57:
#line 157 "tc.y"
               { context.ADTBranchType();   }
#line 1895 "parser.cpp"
    break;

  case 58:
#line 158 "tc.y"
{ ; }
#line 1901 "parser.cpp"
    break;

  case 59:
#line 161 "tc.y"
                     { (yyval.stmt) = context.Check((yyvsp[-2].expr), (yyvsp[-1].type)); }
#line 1907 "parser.cpp"
    break;

  case 65:
#line 170 "tc.y"
            {
    (yyval.type) = context.TypeVar((yyvsp[0].sval));
}
#line 1915 "parser.cpp"
    break;

  case 66:
#line 174 "tc.y"
                  {
    (yyval.type) = context.TypeRef((yyvsp[0].type));
}
#line 1923 "parser.cpp"
    break;

  case 67:
#line 178 "tc.y"
                  {
    (yyval.type) = context.TypePtr((yyvsp[0].type));
}
#line 1931 "parser.cpp"
    break;

  case 68:
#line 182 "tc.y"
                        {
    (yyval.type) = context.TypeArr((yyvsp[-3].type), (yyvsp[-1].ival));
}
#line 1939 "parser.cpp"
    break;

  case 69:
#line 186 "tc.y"
            { context.TypeFunBeg(); }
#line 1945 "parser.cpp"
    break;

  case 70:
#line 186 "tc.y"
                                                                 {
    (yyval.type) = context.TypeFunEnd((yyvsp[-1].type));
}
#line 1953 "parser.cpp"
    break;

  case 71:
#line 191 "tc.y"
     { context.TypeFunArg((yyvsp[0].type));}
#line 1959 "parser.cpp"
    break;

  case 73:
#line 191 "tc.y"
                                             { ; }
#line 1965 "parser.cpp"
    break;

  case 74:
#line 193 "tc.y"
                   {
    (yyval.type) = (yyvsp[0].type);
}
#line 1973 "parser.cpp"
    break;

  case 75:
#line 195 "tc.y"
    { (yyval.type) = nullptr; }
#line 1979 "parser.cpp"
    break;

  case 80:
#line 204 "tc.y"
       { (yyval.cell) = context.CellVar((yyvsp[0].sval)); }
#line 1985 "parser.cpp"
    break;

  case 81:
#line 205 "tc.y"
   { (yyval.cell) = context.CellVar((yyvsp[0].sval)); }
#line 1991 "parser.cpp"
    break;

  case 82:
#line 208 "tc.y"
              { (yyval.cell) = context.CellVarEle((yyvsp[-3].sval), (yyvsp[-1].expr)); }
#line 1997 "parser.cpp"
    break;

  case 83:
#line 211 "tc.y"
                { (yyval.cell) = context.CellEle((yyvsp[-3].cell), (yyvsp[-1].expr)); }
#line 2003 "parser.cpp"
    break;

  case 84:
#line 214 "tc.y"
         { (yyval.cell) = context.CellRef((yyvsp[0].expr)); }
#line 2009 "parser.cpp"
    break;

  case 103:
#line 236 "tc.y"
       {
    printf("I: %ld\n", (yyvsp[0].ival));
    (yyval.expr) = context.I((yyvsp[0].ival)); 
}
#line 2018 "parser.cpp"
    break;

  case 104:
#line 241 "tc.y"
         { 
    printf("F: %02f\n", (yyvsp[0].fval));
    (yyval.expr) = context.F((yyvsp[0].fval)); 
}
#line 2027 "parser.cpp"
    break;

  case 105:
#line 246 "tc.y"
        {
    printf("C: %c\n", (yyvsp[0].cval));
    (yyval.expr) = context.C((yyvsp[0].cval)); 
}
#line 2036 "parser.cpp"
    break;

  case 106:
#line 251 "tc.y"
          {
    printf("S: %s\n", (yyvsp[0].sval));
    (yyval.expr) = context.S((yyvsp[0].sval)); 
}
#line 2045 "parser.cpp"
    break;

  case 107:
#line 256 "tc.y"
                  {
    (yyval.expr) = context.ExprPtr((yyvsp[0].cell));
}
#line 2053 "parser.cpp"
    break;

  case 108:
#line 260 "tc.y"
                  {
    (yyval.expr) = context.ExprVal((yyvsp[0].expr));
}
#line 2061 "parser.cpp"
    break;

  case 109:
#line 264 "tc.y"
                   {
    (yyval.expr) = context.ExprRef((yyvsp[0].expr));
}
#line 2069 "parser.cpp"
    break;

  case 110:
#line 268 "tc.y"
            {
    (yyval.expr) = context.ExprVar((yyvsp[0].sval));
}
#line 2077 "parser.cpp"
    break;

  case 111:
#line 273 "tc.y"
                   {
    (yyval.expr) = context.ExprVarRef((yyvsp[0].sval));
}
#line 2085 "parser.cpp"
    break;

  case 112:
#line 277 "tc.y"
                   {
    (yyval.expr) = context.ExprArr((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2093 "parser.cpp"
    break;

  case 113:
#line 281 "tc.y"
                     {
    (yyval.expr) = context.ExprEle((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2101 "parser.cpp"
    break;

  case 114:
#line 285 "tc.y"
                           {
    (yyval.expr) = context.ExprEleRef((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2109 "parser.cpp"
    break;

  case 115:
#line 289 "tc.y"
                            {
    (yyval.expr) = context.ExprEleAddr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2117 "parser.cpp"
    break;

  case 116:
#line 294 "tc.y"
                  { (yyval.expr) = context.New((yyvsp[-2].expr)); }
#line 2123 "parser.cpp"
    break;

  case 119:
#line 301 "tc.y"
           { 
    context.ExprFunArg((yyvsp[-1].sval), (yyvsp[0].type)); 
}
#line 2131 "parser.cpp"
    break;

  case 121:
#line 304 "tc.y"
               { 
    context.ExprFunRefArg((yyvsp[-1].sval), (yyvsp[0].type)); 
}
#line 2139 "parser.cpp"
    break;

  case 123:
#line 307 "tc.y"
{ ; }
#line 2145 "parser.cpp"
    break;

  case 124:
#line 311 "tc.y"
     { (yyval.expr) = context.ExprFunStmt((yyvsp[0].stmt)); }
#line 2151 "parser.cpp"
    break;

  case 125:
#line 314 "tc.y"
         {context.ExprFunBeg();}
#line 2157 "parser.cpp"
    break;

  case 126:
#line 314 "tc.y"
                                                         { context.ExprFunPre(); }
#line 2163 "parser.cpp"
    break;

  case 127:
#line 315 "tc.y"
                         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 2171 "parser.cpp"
    break;

  case 128:
#line 322 "tc.y"
     { context.AppBeg((yyvsp[0].expr)); }
#line 2177 "parser.cpp"
    break;

  case 129:
#line 323 "tc.y"
     { context.AppBeg(nullptr); }
#line 2183 "parser.cpp"
    break;

  case 130:
#line 326 "tc.y"
     { context.AppArg((yyvsp[0].expr));}
#line 2189 "parser.cpp"
    break;

  case 132:
#line 327 "tc.y"
     { context.AppArg((yyvsp[0].expr));}
#line 2195 "parser.cpp"
    break;

  case 133:
#line 328 "tc.y"
{ ; }
#line 2201 "parser.cpp"
    break;

  case 134:
#line 331 "tc.y"
                      { (yyval.expr) = context.ExprAppEnd(); }
#line 2207 "parser.cpp"
    break;

  case 135:
#line 332 "tc.y"
               {context.AppForceRetRef();}
#line 2213 "parser.cpp"
    break;

  case 136:
#line 332 "tc.y"
                                                     { (yyval.expr) = context.ExprAppEnd(); }
#line 2219 "parser.cpp"
    break;

  case 137:
#line 342 "tc.y"
                  { context.MatchBeg((yyvsp[0].expr)); }
#line 2225 "parser.cpp"
    break;

  case 138:
#line 342 "tc.y"
                                                           { (yyval.expr) = context.MatchEnd(); }
#line 2231 "parser.cpp"
    break;

  case 141:
#line 345 "tc.y"
            { context.MatchBranchArg((yyvsp[0].sval)); }
#line 2237 "parser.cpp"
    break;

  case 144:
#line 346 "tc.y"
                  { context.MatchBranchBeg((yyvsp[0].sval)); }
#line 2243 "parser.cpp"
    break;

  case 146:
#line 350 "tc.y"
     { context.MatchBranchStmt((yyvsp[0].stmt)); }
#line 2249 "parser.cpp"
    break;

  case 149:
#line 357 "tc.y"
         {
    (yyval.expr) = context.UnOp((yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 2257 "parser.cpp"
    break;

  case 150:
#line 362 "tc.y"
     { (yyval.oper) = Oper::BNot; }
#line 2263 "parser.cpp"
    break;

  case 151:
#line 363 "tc.y"
     { (yyval.oper) = Oper::LNot; }
#line 2269 "parser.cpp"
    break;

  case 152:
#line 364 "tc.y"
     { (yyval.oper) = Oper::Neg; }
#line 2275 "parser.cpp"
    break;

  case 153:
#line 365 "tc.y"
     { (yyval.oper) = Oper::Neg; }
#line 2281 "parser.cpp"
    break;

  case 154:
#line 368 "tc.y"
                         {
    (yyval.expr) = context.BinOp((yyvsp[-2].expr), (yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 2289 "parser.cpp"
    break;

  case 155:
#line 371 "tc.y"
         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 2297 "parser.cpp"
    break;

  case 156:
#line 375 "tc.y"
     { (yyval.oper) = Oper::BAnd; }
#line 2303 "parser.cpp"
    break;

  case 157:
#line 376 "tc.y"
    { (yyval.oper) = Oper::BOr; }
#line 2309 "parser.cpp"
    break;

  case 158:
#line 377 "tc.y"
     { (yyval.oper) = Oper::BXOr;}
#line 2315 "parser.cpp"
    break;

  case 159:
#line 378 "tc.y"
     { (yyval.oper) = Oper::LAnd; }
#line 2321 "parser.cpp"
    break;

  case 160:
#line 379 "tc.y"
    { (yyval.oper) = Oper::LOr;}
#line 2327 "parser.cpp"
    break;

  case 161:
#line 380 "tc.y"
     { (yyval.oper) = Oper::LXOr; }
#line 2333 "parser.cpp"
    break;

  case 162:
#line 383 "tc.y"
                         {
    (yyval.expr) = context.BinOp((yyvsp[-2].expr), (yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 2341 "parser.cpp"
    break;

  case 163:
#line 386 "tc.y"
         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 2349 "parser.cpp"
    break;

  case 164:
#line 390 "tc.y"
   { (yyval.oper) = Oper::Lt; }
#line 2355 "parser.cpp"
    break;

  case 165:
#line 391 "tc.y"
   { (yyval.oper) = Oper::Gt; }
#line 2361 "parser.cpp"
    break;

  case 166:
#line 392 "tc.y"
    { (yyval.oper) = Oper::Leq; }
#line 2367 "parser.cpp"
    break;

  case 167:
#line 393 "tc.y"
    { (yyval.oper) = Oper::Geq; }
#line 2373 "parser.cpp"
    break;

  case 168:
#line 394 "tc.y"
   { (yyval.oper) = Oper::Eq; }
#line 2379 "parser.cpp"
    break;

  case 169:
#line 395 "tc.y"
    { (yyval.oper) = Oper::Neq; }
#line 2385 "parser.cpp"
    break;

  case 170:
#line 396 "tc.y"
       { (yyval.oper) = Oper::LShift; }
#line 2391 "parser.cpp"
    break;

  case 171:
#line 397 "tc.y"
       { (yyval.oper) = Oper::RShift; }
#line 2397 "parser.cpp"
    break;

  case 172:
#line 400 "tc.y"
                         {
    (yyval.expr) = context.BinOp((yyvsp[-2].expr), (yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 2405 "parser.cpp"
    break;

  case 173:
#line 403 "tc.y"
         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 2413 "parser.cpp"
    break;

  case 174:
#line 407 "tc.y"
    { (yyval.oper) = Oper::Add; }
#line 2419 "parser.cpp"
    break;

  case 175:
#line 408 "tc.y"
    { (yyval.oper) = Oper::Sub; }
#line 2425 "parser.cpp"
    break;

  case 176:
#line 409 "tc.y"
     { (yyval.oper) = Oper::FAdd; }
#line 2431 "parser.cpp"
    break;

  case 177:
#line 410 "tc.y"
     { (yyval.oper) = Oper::FSub; }
#line 2437 "parser.cpp"
    break;

  case 178:
#line 411 "tc.y"
       { (yyval.oper) = Oper::AddPtr; }
#line 2443 "parser.cpp"
    break;

  case 179:
#line 412 "tc.y"
       { (yyval.oper) = Oper::PtrAdd; }
#line 2449 "parser.cpp"
    break;

  case 180:
#line 413 "tc.y"
       { (yyval.oper) = Oper::PtrSub; }
#line 2455 "parser.cpp"
    break;

  case 181:
#line 416 "tc.y"
                         {
    (yyval.expr) = context.BinOp((yyvsp[-2].expr), (yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 2463 "parser.cpp"
    break;

  case 182:
#line 419 "tc.y"
         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 2471 "parser.cpp"
    break;

  case 183:
#line 424 "tc.y"
           {
    (yyval.expr) = (yyvsp[-1].expr);
}
#line 2479 "parser.cpp"
    break;

  case 184:
#line 427 "tc.y"
     { (yyval.expr) =(yyvsp[0].expr);}
#line 2485 "parser.cpp"
    break;

  case 185:
#line 430 "tc.y"
    { (yyval.oper) = Oper::Mul; }
#line 2491 "parser.cpp"
    break;

  case 186:
#line 431 "tc.y"
    { (yyval.oper) = Oper::Div; }
#line 2497 "parser.cpp"
    break;

  case 187:
#line 432 "tc.y"
     { (yyval.oper) = Oper::FMul; }
#line 2503 "parser.cpp"
    break;

  case 188:
#line 433 "tc.y"
     { (yyval.oper) = Oper::FDiv; }
#line 2509 "parser.cpp"
    break;

  case 189:
#line 434 "tc.y"
    { (yyval.oper) = Oper::Mod; }
#line 2515 "parser.cpp"
    break;


#line 2519 "parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 437 "tc.y"



int main() {
    try{
        context.BlockBegin();
        yyparse();
        context.save(context.BlockEnd()); 
        context.save("tc.hex"); 
    }
    catch(const char *s)
    {
        printf("%s\n", s);
    }
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
