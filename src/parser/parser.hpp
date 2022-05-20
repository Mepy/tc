/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 151 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
