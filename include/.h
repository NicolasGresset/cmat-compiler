/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INCLUDE_H_INCLUDED
# define YY_YY_INCLUDE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    FLOAT = 259,                   /* FLOAT  */
    MATRIX = 260,                  /* MATRIX  */
    ELSE = 261,                    /* ELSE  */
    IF = 262,                      /* IF  */
    WHILE = 263,                   /* WHILE  */
    FOR = 264,                     /* FOR  */
    CONSTANTE_ENTIERE = 265,       /* CONSTANTE_ENTIERE  */
    CONSTANTE_FLOTTANTE = 266,     /* CONSTANTE_FLOTTANTE  */
    CONSTANTE_CARACTERE = 267,     /* CONSTANTE_CARACTERE  */
    IDENTIFICATEUR = 268,          /* IDENTIFICATEUR  */
    PLUS = 269,                    /* PLUS  */
    MOINS = 270,                   /* MOINS  */
    FOIS = 271,                    /* FOIS  */
    DIVISE = 272,                  /* DIVISE  */
    PLUS_PLUS = 273,               /* PLUS_PLUS  */
    MOINS_MOINS = 274,             /* MOINS_MOINS  */
    EGAL = 275,                    /* EGAL  */
    TRANSPOSITION = 276,           /* TRANSPOSITION  */
    PARENTHESE_OUVRANTE = 277,     /* PARENTHESE_OUVRANTE  */
    PARENTHESE_FERMANTE = 278,     /* PARENTHESE_FERMANTE  */
    CROCHET_OUVRANT = 279,         /* CROCHET_OUVRANT  */
    CROCHET_FERMANT = 280,         /* CROCHET_FERMANT  */
    ACCOLADE_OUVRANTE = 281,       /* ACCOLADE_OUVRANTE  */
    ACCOLADE_FERMANTE = 282,       /* ACCOLADE_FERMANTE  */
    VIRGULE = 283,                 /* VIRGULE  */
    POINT_VIRGULE = 284,           /* POINT_VIRGULE  */
    APOSTROPHE = 285,              /* APOSTROPHE  */
    GUILLEMET = 286,               /* GUILLEMET  */
    MAIN = 287,                    /* MAIN  */
    OPAR = 288,                    /* OPAR  */
    FACC = 289,                    /* FACC  */
    FPAR = 290,                    /* FPAR  */
    OACC = 291,                    /* OACC  */
    EXCLAMATION = 292,             /* EXCLAMATION  */
    INF = 293,                     /* INF  */
    INF_EGAL = 294,                /* INF_EGAL  */
    SUP = 295,                     /* SUP  */
    SUP_EGAL = 296,                /* SUP_EGAL  */
    EGAL_EGAL = 297                /* EGAL_EGAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_H_INCLUDED  */
