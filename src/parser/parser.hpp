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

#line 141 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
