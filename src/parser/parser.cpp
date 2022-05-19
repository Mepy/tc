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
    SELF = 268,
    REFS = 269,
    REF = 270,
    PTR = 271,
    BS = 272,
    RDARROW = 273,
    RSARROW = 274,
    LSARROW = 275,
    ARR = 276,
    BNOT = 277,
    LNOT = 278,
    FADD = 279,
    FSUB = 280,
    FMUL = 281,
    FDIV = 282,
    ADD = 283,
    SUB = 284,
    MUL = 285,
    DIV = 286,
    LAND = 287,
    LOR = 288,
    LXOR = 289,
    LEQ = 290,
    GEQ = 291,
    LT = 292,
    GT = 293,
    MOD = 294,
    BAND = 295,
    BOR = 296,
    BXOR = 297,
    LSHIFT = 298,
    RSHIFT = 299,
    EQ = 300,
    NEQ = 301,
    ADDPTR = 302,
    PTRADD = 303,
    PTRSUB = 304,
    LET = 305,
    VAR = 306,
    IF = 307,
    ELSE = 308,
    WHILE = 309,
    BREAK = 310,
    CONT = 311,
    RET = 312,
    DEL = 313,
    TYPE = 314,
    CHECK = 315,
    FUN = 316,
    MATCH = 317,
    WITH = 318,
    NEW = 319,
    INT = 320,
    FLOAT = 321,
    CHAR = 322,
    STRING = 323,
    TN = 324,
    EN = 325
  };
#endif
/* Tokens.  */
#define LP 258
#define RP 259
#define LB 260
#define RB 261
#define LC 262
#define RC 263
#define SEMI 264
#define COMMA 265
#define COLON 266
#define ASSIGN 267
#define SELF 268
#define REFS 269
#define REF 270
#define PTR 271
#define BS 272
#define RDARROW 273
#define RSARROW 274
#define LSARROW 275
#define ARR 276
#define BNOT 277
#define LNOT 278
#define FADD 279
#define FSUB 280
#define FMUL 281
#define FDIV 282
#define ADD 283
#define SUB 284
#define MUL 285
#define DIV 286
#define LAND 287
#define LOR 288
#define LXOR 289
#define LEQ 290
#define GEQ 291
#define LT 292
#define GT 293
#define MOD 294
#define BAND 295
#define BOR 296
#define BXOR 297
#define LSHIFT 298
#define RSHIFT 299
#define EQ 300
#define NEQ 301
#define ADDPTR 302
#define PTRADD 303
#define PTRSUB 304
#define LET 305
#define VAR 306
#define IF 307
#define ELSE 308
#define WHILE 309
#define BREAK 310
#define CONT 311
#define RET 312
#define DEL 313
#define TYPE 314
#define CHECK 315
#define FUN 316
#define MATCH 317
#define WITH 318
#define NEW 319
#define INT 320
#define FLOAT 321
#define CHAR 322
#define STRING 323
#define TN 324
#define EN 325

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

#line 285 "parser.cpp"

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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   351

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

#define YYUNDEFTOK  2
#define YYMAXUTOK   325


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
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    56,    56,    62,    62,    62,    62,    62,    63,    68,
      72,    76,    80,    80,    85,    85,    85,    87,    89,    92,
      92,    92,    92,    92,    92,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    95,   100,   105,   110,   115,
     119,   123,   129,   134,   138,   142,   146,   150,   155,   155,
     158,   158,   161,   161,   164,   167,   171,   171,   178,   179,
     182,   183,   186,   186,   187,   188,   190,   200,   200,   203,
     207,   208,   209,   210,   213,   216,   220,   221,   222,   223,
     224,   227,   230,   234,   235,   236,   237,   238,   239,   240,
     241,   244,   247,   251,   252,   253,   254,   255,   256,   257,
     260,   263,   267,   268,   269,   270,   271
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LP", "RP", "LB", "RB", "LC", "RC",
  "SEMI", "COMMA", "COLON", "ASSIGN", "SELF", "REFS", "REF", "PTR", "BS",
  "RDARROW", "RSARROW", "LSARROW", "ARR", "BNOT", "LNOT", "FADD", "FSUB",
  "FMUL", "FDIV", "ADD", "SUB", "MUL", "DIV", "LAND", "LOR", "LXOR", "LEQ",
  "GEQ", "LT", "GT", "MOD", "BAND", "BOR", "BXOR", "LSHIFT", "RSHIFT",
  "EQ", "NEQ", "ADDPTR", "PTRADD", "PTRSUB", "LET", "VAR", "IF", "ELSE",
  "WHILE", "BREAK", "CONT", "RET", "DEL", "TYPE", "CHECK", "FUN", "MATCH",
  "WITH", "NEW", "INT", "FLOAT", "CHAR", "STRING", "TN", "EN", "$accept",
  "Start", "Type", "TypeVar", "TypeRef", "TypePtr", "TypeArr", "TypeFun",
  "$@1", "TypeFunArg", "$@2", "TypeDef", "Expr", "I", "F", "C", "S",
  "ExprVal", "ExprRef", "ExprVar", "ExprVarRef", "Arr", "Ele", "EleRef",
  "EleAddr", "New", "FunStart", "ExprFunArgLists", "$@3", "$@4",
  "ExprFunDef", "Fun", "$@5", "AppStart", "AppRetRef", "AppArg", "$@6",
  "App", "Calc", "UnCalc", "UnOp", "BinCalc1", "BinOp1", "BinCalc2",
  "BinOp2", "BinCalc3", "BinOp3", "BinCalc4", "BinOp4", YY_NULLPTR
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
     325
};
# endif

#define YYPACT_NINF (-116)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-65)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,     1,  -116,     1,   -65,  -116,  -116,  -116,  -116,  -116,
       1,  -116,     1,  -116,  -116,  -116,  -116,  -116,     6,    84,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,    -8,  -116,  -116,  -116,     1,
    -116,  -116,  -116,  -116,   302,     5,   302,  -116,   302,   302,
    -116,     1,    12,    16,   -43,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
       1,     1,     1,     1,   -13,  -116,    25,    84,  -116,   175,
       1,     1,  -116,    84,    84,    84,    84,   -37,    26,     9,
       1,  -116,   220,   265,    26,     4,  -116,     1,   130,    32,
    -116,  -116,  -116,  -116,     4,     4,  -116,    33,  -116,  -116,
    -116,  -116,  -116,   -13,   302,  -116,    30,  -116,   -13,     4,
      33,    33,   -24,  -116,     1,  -116,    33,    23,    37,  -116,
       4,     4,  -116,  -116,    24,  -116
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    59,     0,     0,    49,    70,    71,    73,    72,
       0,    48,     0,    35,    36,    37,    38,    41,     0,     2,
      32,    31,    33,    34,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    56,    19,    61,    20,    30,    67,     0,
      68,    75,    82,    92,    58,    68,    40,    42,    39,    47,
       1,     0,     0,     0,     0,    95,    96,   104,   105,    93,
      94,   102,   103,    78,    79,    80,    85,    86,    83,    84,
     106,    76,    77,    89,    90,    87,    88,    97,    98,    99,
       0,     0,     0,     0,    54,    60,     0,    69,   101,    58,
       0,     0,    43,    74,    81,    91,   100,     0,    18,     0,
      65,    44,    58,    58,    18,     0,    50,     0,    58,     0,
      45,    46,    52,    12,     0,     0,     8,    17,     3,     4,
       5,     6,     7,    54,    55,    57,     0,    66,    54,    16,
       9,    10,     0,    51,    65,    53,    14,     0,     0,    63,
      16,     0,    11,    15,     0,    13
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -116,  -116,   -80,  -116,  -116,  -116,  -116,  -116,  -116,   -96,
    -116,   -59,     0,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -115,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,   -88,  -116,  -116,  -116,  -116,
    -116,    46,  -116,  -116,  -116,  -116,  -116,  -116,  -116
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    18,   136,   118,   119,   120,   121,   122,   129,   137,
     140,   106,   108,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    99,   123,   128,
     125,    34,    84,    35,    86,   109,   126,    36,    37,    38,
      39,    40,    80,    41,    81,    42,    82,    43,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      19,    44,    97,    46,     1,    47,    50,    85,   133,    88,
      48,   113,    49,   135,     2,     3,     4,    90,     5,   114,
     115,    91,    92,     6,     7,   117,     8,   107,   100,   132,
       9,    10,   145,   104,   130,   131,   127,   105,   132,    87,
     134,   138,   141,   142,   143,   112,   139,    45,     0,     0,
       0,    89,     0,     0,     0,     0,     0,    98,     0,     0,
       0,   144,    11,     0,     0,    12,    13,    14,    15,    16,
       0,    17,     0,   116,     0,     0,     0,     0,     0,     0,
      93,    94,    95,    96,     0,     0,     0,   -58,     0,    51,
     102,   103,     0,     0,     0,     0,     0,     0,     0,    52,
      53,     0,     0,     0,     0,    54,     0,   124,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,     0,    73,    74,    75,
      76,    77,    78,    79,   -64,    51,     0,     0,     0,     0,
     -62,     0,     0,     0,     0,    52,    53,     0,     0,     0,
       0,    54,     0,     0,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,     0,    73,    74,    75,    76,    77,    78,    79,
      51,   101,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    53,     0,     0,     0,     0,    54,     0,     0,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,     0,    73,    74,
      75,    76,    77,    78,    79,    51,   110,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    53,     0,     0,     0,
       0,    54,     0,     0,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,     0,    73,    74,    75,    76,    77,    78,    79,
      51,   111,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    53,     0,     0,     0,     0,    54,     0,     0,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    51,    73,    74,
      75,    76,    77,    78,    79,     0,     0,    52,    53,     0,
       0,     0,     0,    54,     0,     0,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,     0,    73,    74,    75,    76,    77,
      78,    79
};

static const yytype_int16 yycheck[] =
{
       0,     1,    15,     3,     3,    70,     0,    15,   123,     4,
      10,     7,    12,   128,    13,    14,    15,     5,    17,    15,
      16,     5,    65,    22,    23,   105,    25,    18,     3,     5,
      29,    30,     8,    70,   114,   115,     4,    11,     5,    39,
      10,    65,    19,     6,   140,   104,   134,     1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,
      -1,   141,    61,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    81,    82,    83,    -1,    -1,    -1,     3,    -1,     5,
      90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    -1,    -1,    -1,    -1,    21,    -1,   107,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    45,
      46,    47,    48,    49,     4,     5,    -1,    -1,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    16,    -1,    -1,    -1,    -1,    21,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      45,    46,    47,    48,    49,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    16,    -1,    -1,    -1,    -1,    21,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     5,    43,    44,
      45,    46,    47,    48,    49,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    45,    46,    47,
      48,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    13,    14,    15,    17,    22,    23,    25,    29,
      30,    61,    64,    65,    66,    67,    68,    70,    72,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,   102,   104,   108,   109,   110,   111,
     112,   114,   116,   118,    83,   112,    83,    70,    83,    83,
       0,     5,    15,    16,    21,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    43,    44,    45,    46,    47,    48,    49,
     113,   115,   117,   119,   103,    15,   105,    83,     4,    83,
       5,     5,    65,    83,    83,    83,    83,    15,    70,    98,
       3,     6,    83,    83,    70,    11,    82,    18,    83,   106,
       6,     6,    82,     7,    15,    16,    69,    73,    74,    75,
      76,    77,    78,    99,    83,   101,   107,     4,   100,    79,
      73,    73,     5,    98,    10,    98,    73,    80,    65,   106,
      81,    19,     6,    80,    73,     8
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    71,    72,    73,    73,    73,    73,    73,    74,    75,
      76,    77,    79,    78,    81,    80,    80,    82,    82,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    97,
      99,    98,   100,    98,    98,   101,   103,   102,   104,   104,
     105,   105,   107,   106,   106,   106,   108,   109,   109,   110,
     111,   111,   111,   111,   112,   112,   113,   113,   113,   113,
     113,   114,   114,   115,   115,   115,   115,   115,   115,   115,
     115,   116,   116,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   119,   119,   119,   119,   119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     4,     0,     6,     0,     3,     0,     2,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     2,     3,     4,     5,     5,     2,     1,     1,
       0,     4,     0,     5,     0,     1,     0,     5,     1,     1,
       1,     0,     0,     4,     1,     0,     5,     1,     1,     2,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1
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
  case 8:
#line 63 "tc.y"
            {
    printf("%s ", (yyvsp[0].sval));
    (yyval.type) = context.TypeVar((yyvsp[0].sval));
}
#line 1627 "parser.cpp"
    break;

  case 9:
#line 68 "tc.y"
                  {
    (yyval.type) = context.TypeRef((yyvsp[0].type));
}
#line 1635 "parser.cpp"
    break;

  case 10:
#line 72 "tc.y"
                  {
    (yyval.type) = context.TypePtr((yyvsp[0].type));
}
#line 1643 "parser.cpp"
    break;

  case 11:
#line 76 "tc.y"
                        {
    (yyval.type) = context.TypeArr((yyvsp[-3].type), (yyvsp[-1].ival));
}
#line 1651 "parser.cpp"
    break;

  case 12:
#line 80 "tc.y"
            { context.TypeFunBeg(); }
#line 1657 "parser.cpp"
    break;

  case 13:
#line 80 "tc.y"
                                                                 {
    (yyval.type) = context.TypeFunEnd((yyvsp[-1].type));
}
#line 1665 "parser.cpp"
    break;

  case 14:
#line 85 "tc.y"
     { context.TypeFunArg((yyvsp[0].type));}
#line 1671 "parser.cpp"
    break;

  case 16:
#line 85 "tc.y"
                                             { ; }
#line 1677 "parser.cpp"
    break;

  case 17:
#line 87 "tc.y"
                   {
    (yyval.type) = (yyvsp[0].type);
}
#line 1685 "parser.cpp"
    break;

  case 18:
#line 89 "tc.y"
    { (yyval.type) = nullptr; }
#line 1691 "parser.cpp"
    break;

  case 35:
#line 95 "tc.y"
       {
    printf("I: %ld\n", (yyvsp[0].ival));
    (yyval.expr) = context.I((yyvsp[0].ival)); 
}
#line 1700 "parser.cpp"
    break;

  case 36:
#line 100 "tc.y"
         { 
    printf("F: %02f\n", (yyvsp[0].fval));
    (yyval.expr) = context.F((yyvsp[0].fval)); 
}
#line 1709 "parser.cpp"
    break;

  case 37:
#line 105 "tc.y"
        {
    printf("C: %c\n", (yyvsp[0].cval));
    (yyval.expr) = context.C((yyvsp[0].cval)); 
}
#line 1718 "parser.cpp"
    break;

  case 38:
#line 110 "tc.y"
          {
    printf("S: %s\n", (yyvsp[0].sval));
    (yyval.expr) = context.S((yyvsp[0].sval)); 
}
#line 1727 "parser.cpp"
    break;

  case 39:
#line 115 "tc.y"
                  {
    (yyval.expr) = context.ExprVal((yyvsp[0].expr));
}
#line 1735 "parser.cpp"
    break;

  case 40:
#line 119 "tc.y"
                   {
    (yyval.expr) = context.ExprRef((yyvsp[0].expr));
}
#line 1743 "parser.cpp"
    break;

  case 41:
#line 123 "tc.y"
            {
    printf("%s ", (yyvsp[0].sval));
    (yyval.expr) = context.ExprVar((yyvsp[0].sval));
}
#line 1752 "parser.cpp"
    break;

  case 42:
#line 129 "tc.y"
                   {
    printf("%s ", (yyvsp[0].sval));
    (yyval.expr) = context.ExprVarRef((yyvsp[0].sval));
}
#line 1761 "parser.cpp"
    break;

  case 43:
#line 134 "tc.y"
                  {
    (yyval.expr) = context.ExprArr((yyvsp[-2].expr), (yyvsp[0].ival));
}
#line 1769 "parser.cpp"
    break;

  case 44:
#line 138 "tc.y"
                     {
    (yyval.expr) = context.ExprEle((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 1777 "parser.cpp"
    break;

  case 45:
#line 142 "tc.y"
                            {
    (yyval.expr) = context.ExprEleRef((yyvsp[-4].expr), (yyvsp[-1].expr));
}
#line 1785 "parser.cpp"
    break;

  case 46:
#line 146 "tc.y"
                             {
    (yyval.expr) = context.ExprEleAddr((yyvsp[-4].expr), (yyvsp[-1].expr));
}
#line 1793 "parser.cpp"
    break;

  case 47:
#line 150 "tc.y"
              {
    (yyval.expr) = context.New((yyvsp[0].expr));
}
#line 1801 "parser.cpp"
    break;

  case 50:
#line 158 "tc.y"
           { 
    context.ExprFunArg(Name((yyvsp[-1].sval)), (yyvsp[0].type)); 
}
#line 1809 "parser.cpp"
    break;

  case 52:
#line 161 "tc.y"
               { 
    context.ExprFunRefArg(Name((yyvsp[-1].sval)), (yyvsp[0].type)); 
}
#line 1817 "parser.cpp"
    break;

  case 54:
#line 164 "tc.y"
{ ; }
#line 1823 "parser.cpp"
    break;

  case 55:
#line 167 "tc.y"
                 {
    (yyval.expr) = context.ExprFunExpr((yyvsp[0].expr));
}
#line 1831 "parser.cpp"
    break;

  case 56:
#line 171 "tc.y"
              {context.ExprFunBeg();}
#line 1837 "parser.cpp"
    break;

  case 57:
#line 171 "tc.y"
                                                                         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 1845 "parser.cpp"
    break;

  case 58:
#line 178 "tc.y"
     { context.AppBeg((yyvsp[0].expr)); }
#line 1851 "parser.cpp"
    break;

  case 59:
#line 179 "tc.y"
     { context.AppBeg(nullptr); }
#line 1857 "parser.cpp"
    break;

  case 60:
#line 182 "tc.y"
    { context.AppForceRetRef();}
#line 1863 "parser.cpp"
    break;

  case 61:
#line 183 "tc.y"
{ ; }
#line 1869 "parser.cpp"
    break;

  case 62:
#line 186 "tc.y"
     { context.AppArg((yyvsp[0].expr));}
#line 1875 "parser.cpp"
    break;

  case 64:
#line 187 "tc.y"
     { context.AppArg((yyvsp[0].expr));}
#line 1881 "parser.cpp"
    break;

  case 65:
#line 188 "tc.y"
{ ; }
#line 1887 "parser.cpp"
    break;

  case 66:
#line 190 "tc.y"
                                     { (yyval.expr) = context.ExprAppEnd(); }
#line 1893 "parser.cpp"
    break;

  case 69:
#line 203 "tc.y"
         {
    (yyval.expr) = context.UnOp((yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 1901 "parser.cpp"
    break;

  case 70:
#line 207 "tc.y"
     { (yyval.oper) = Oper::BNot; }
#line 1907 "parser.cpp"
    break;

  case 71:
#line 208 "tc.y"
     { (yyval.oper) = Oper::LNot; }
#line 1913 "parser.cpp"
    break;

  case 72:
#line 209 "tc.y"
     { (yyval.oper) = Oper::Neg; }
#line 1919 "parser.cpp"
    break;

  case 73:
#line 210 "tc.y"
     { (yyval.oper) = Oper::Neg; }
#line 1925 "parser.cpp"
    break;

  case 74:
#line 213 "tc.y"
                {
    (yyval.expr) = context.BinOp((yyvsp[-2].expr), (yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 1933 "parser.cpp"
    break;

  case 75:
#line 216 "tc.y"
         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 1941 "parser.cpp"
    break;

  case 76:
#line 220 "tc.y"
     { (yyval.oper) = Oper::BAnd; }
#line 1947 "parser.cpp"
    break;

  case 77:
#line 221 "tc.y"
    { (yyval.oper) = Oper::BOr; }
#line 1953 "parser.cpp"
    break;

  case 78:
#line 222 "tc.y"
     { (yyval.oper) = Oper::LAnd; }
#line 1959 "parser.cpp"
    break;

  case 79:
#line 223 "tc.y"
    { (yyval.oper) = Oper::LOr;}
#line 1965 "parser.cpp"
    break;

  case 80:
#line 224 "tc.y"
     { (yyval.oper) = Oper::LXOr; }
#line 1971 "parser.cpp"
    break;

  case 81:
#line 227 "tc.y"
                {
    (yyval.expr) = context.BinOp((yyvsp[-2].expr), (yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 1979 "parser.cpp"
    break;

  case 82:
#line 230 "tc.y"
         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 1987 "parser.cpp"
    break;

  case 83:
#line 234 "tc.y"
   { (yyval.oper) = Oper::Lt; }
#line 1993 "parser.cpp"
    break;

  case 84:
#line 235 "tc.y"
   { (yyval.oper) = Oper::Gt; }
#line 1999 "parser.cpp"
    break;

  case 85:
#line 236 "tc.y"
    { (yyval.oper) = Oper::Leq; }
#line 2005 "parser.cpp"
    break;

  case 86:
#line 237 "tc.y"
    { (yyval.oper) = Oper::Geq; }
#line 2011 "parser.cpp"
    break;

  case 87:
#line 238 "tc.y"
   { (yyval.oper) = Oper::Eq; }
#line 2017 "parser.cpp"
    break;

  case 88:
#line 239 "tc.y"
    { (yyval.oper) = Oper::Neq; }
#line 2023 "parser.cpp"
    break;

  case 89:
#line 240 "tc.y"
       { (yyval.oper) = Oper::LShift; }
#line 2029 "parser.cpp"
    break;

  case 90:
#line 241 "tc.y"
       { (yyval.oper) = Oper::RShift; }
#line 2035 "parser.cpp"
    break;

  case 91:
#line 244 "tc.y"
                {
    (yyval.expr) = context.BinOp((yyvsp[-2].expr), (yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 2043 "parser.cpp"
    break;

  case 92:
#line 247 "tc.y"
         {
    (yyval.expr) = (yyvsp[0].expr);
}
#line 2051 "parser.cpp"
    break;

  case 93:
#line 251 "tc.y"
    { (yyval.oper) = Oper::Add; }
#line 2057 "parser.cpp"
    break;

  case 94:
#line 252 "tc.y"
    { (yyval.oper) = Oper::Sub; }
#line 2063 "parser.cpp"
    break;

  case 95:
#line 253 "tc.y"
     { (yyval.oper) = Oper::FAdd; }
#line 2069 "parser.cpp"
    break;

  case 96:
#line 254 "tc.y"
     { (yyval.oper) = Oper::FSub; }
#line 2075 "parser.cpp"
    break;

  case 97:
#line 255 "tc.y"
       { (yyval.oper) = Oper::AddPtr; }
#line 2081 "parser.cpp"
    break;

  case 98:
#line 256 "tc.y"
       { (yyval.oper) = Oper::PtrAdd; }
#line 2087 "parser.cpp"
    break;

  case 99:
#line 257 "tc.y"
       { (yyval.oper) = Oper::PtrSub; }
#line 2093 "parser.cpp"
    break;

  case 100:
#line 260 "tc.y"
                {
    (yyval.expr) = context.BinOp((yyvsp[-2].expr), (yyvsp[-1].oper), (yyvsp[0].expr));
}
#line 2101 "parser.cpp"
    break;

  case 101:
#line 263 "tc.y"
               {
    (yyval.expr) = (yyvsp[-1].expr);
}
#line 2109 "parser.cpp"
    break;

  case 102:
#line 267 "tc.y"
    { (yyval.oper) = Oper::Mul; }
#line 2115 "parser.cpp"
    break;

  case 103:
#line 268 "tc.y"
    { (yyval.oper) = Oper::Div; }
#line 2121 "parser.cpp"
    break;

  case 104:
#line 269 "tc.y"
     { (yyval.oper) = Oper::FMul; }
#line 2127 "parser.cpp"
    break;

  case 105:
#line 270 "tc.y"
     { (yyval.oper) = Oper::FDiv; }
#line 2133 "parser.cpp"
    break;

  case 106:
#line 271 "tc.y"
    { (yyval.oper) = Oper::Mod; }
#line 2139 "parser.cpp"
    break;


#line 2143 "parser.cpp"

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
#line 334 "tc.y"



int main() {
    /* context.BlockBegin(); */
    yyparse();
    /* context.save(context.BlockEnd());
    context.save("tc.hex"); */
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
