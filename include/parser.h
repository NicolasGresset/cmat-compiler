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

#ifndef YY_YY_INCLUDE_PARSER_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_H_INCLUDED
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
    IDENTIFICATEUR = 258,          /* IDENTIFICATEUR  */
    CONSTANTE_ENTIERE = 259,       /* CONSTANTE_ENTIERE  */
    CONSTANTE_FLOTTANTE = 260,     /* CONSTANTE_FLOTTANTE  */
    INT = 261,                     /* INT  */
    FLOAT = 262,                   /* FLOAT  */
    MATRIX = 263,                  /* MATRIX  */
    ELSE = 264,                    /* ELSE  */
    IF = 265,                      /* IF  */
    WHILE = 266,                   /* WHILE  */
    FOR = 267,                     /* FOR  */
    CONSTANTE_CARACTERE = 268,     /* CONSTANTE_CARACTERE  */
    AND = 269,                     /* AND  */
    OR = 270,                      /* OR  */
    NOT = 271,                     /* NOT  */
    PLUS = 272,                    /* PLUS  */
    MOINS = 273,                   /* MOINS  */
    FOIS = 274,                    /* FOIS  */
    DIVISE = 275,                  /* DIVISE  */
    PLUS_PLUS = 276,               /* PLUS_PLUS  */
    MOINS_MOINS = 277,             /* MOINS_MOINS  */
    EGAL = 278,                    /* EGAL  */
    TRANSPOSITION = 279,           /* TRANSPOSITION  */
    PARENTHESE_OUVRANTE = 280,     /* PARENTHESE_OUVRANTE  */
    PARENTHESE_FERMANTE = 281,     /* PARENTHESE_FERMANTE  */
    CROCHET_OUVRANT = 282,         /* CROCHET_OUVRANT  */
    CROCHET_FERMANT = 283,         /* CROCHET_FERMANT  */
    ACCOLADE_OUVRANTE = 284,       /* ACCOLADE_OUVRANTE  */
    ACCOLADE_FERMANTE = 285,       /* ACCOLADE_FERMANTE  */
    VIRGULE = 286,                 /* VIRGULE  */
    POINT_VIRGULE = 287,           /* POINT_VIRGULE  */
    APOSTROPHE = 288,              /* APOSTROPHE  */
    GUILLEMET = 289,               /* GUILLEMET  */
    MAIN = 290,                    /* MAIN  */
    POINT_EXCLAMATION = 291,       /* POINT_EXCLAMATION  */
    INFERIEUR = 292,               /* INFERIEUR  */
    INFERIEUR_EGAL = 293,          /* INFERIEUR_EGAL  */
    SUPERIEUR = 294,               /* SUPERIEUR  */
    SUPERIEUR_EGAL = 295,          /* SUPERIEUR_EGAL  */
    EGAL_EGAL = 296,               /* EGAL_EGAL  */
    UEXPR = 297                    /* UEXPR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 39 "bison/parser.y"

     struct
     {
         struct symbol * ptr;
         type_t type;
         int num;
     } exprval;

     name_t strval;
     type_t typeval;
     int intval;
     float floatval;

     struct {
         struct ListLabel * next;
     } instr_type;


     struct  {
         struct ListLabel * true;
         struct ListLabel * false;
     } boolexpr;

     struct
     {
         struct ListLabel * next;
         int quad;
     } N_t; // Pour le non terminal N

     enum {EQ, NEQ, LT, LE, GE, GT} typetest;

     struct {
         struct symbol * id;
         struct symbol * ptr;
         int num;
     } for_fin_t;

     struct {
         int row;
         int col;
     } taille_mat_t;

#line 149 "./include/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_PARSER_H_INCLUDED  */
