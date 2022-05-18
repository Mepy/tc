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
    BNOT = 276,
    LNOT = 277,
    FADD = 278,
    FSUB = 279,
    FMUL = 280,
    FDIV = 281,
    ADD = 282,
    SUB = 283,
    MUL = 284,
    DIV = 285,
    LAND = 286,
    LOR = 287,
    LXOR = 288,
    LEQ = 289,
    GEQ = 290,
    LT = 291,
    GT = 292,
    MOD = 293,
    BAND = 294,
    BOR = 295,
    BXOR = 296,
    LSHIFT = 297,
    RSHIFT = 298,
    EQ = 299,
    NEQ = 300,
    ADDPTR = 301,
    PTRADD = 302,
    PTRSUB = 303,
    LET = 304,
    VAR = 305,
    IF = 306,
    ELSE = 307,
    WHILE = 308,
    BREAK = 309,
    CONT = 310,
    RET = 311,
    DEL = 312,
    TYPE = 313,
    CHECK = 314,
    FUN = 315,
    MATCH = 316,
    WITH = 317,
    NEW = 318,
    INT = 319,
    FLOAT = 320,
    CHAR = 321,
    STRING = 322,
    TN = 323,
    EN = 324
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

#line 140 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
