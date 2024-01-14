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
    STRING = 261,                  /* STRING  */
    INT = 262,                     /* INT  */
    FLOAT = 263,                   /* FLOAT  */
    MATRIX = 264,                  /* MATRIX  */
    ELSE = 265,                    /* ELSE  */
    IF = 266,                      /* IF  */
    WHILE = 267,                   /* WHILE  */
    FOR = 268,                     /* FOR  */
    CONSTANTE_CARACTERE = 269,     /* CONSTANTE_CARACTERE  */
    AND = 270,                     /* AND  */
    OR = 271,                      /* OR  */
    NOT = 272,                     /* NOT  */
    PLUS = 273,                    /* PLUS  */
    MOINS = 274,                   /* MOINS  */
    FOIS = 275,                    /* FOIS  */
    DIVISE = 276,                  /* DIVISE  */
    PLUS_PLUS = 277,               /* PLUS_PLUS  */
    MOINS_MOINS = 278,             /* MOINS_MOINS  */
    EGAL = 279,                    /* EGAL  */
    TRANSPOSITION = 280,           /* TRANSPOSITION  */
    PARENTHESE_OUVRANTE = 281,     /* PARENTHESE_OUVRANTE  */
    PARENTHESE_FERMANTE = 282,     /* PARENTHESE_FERMANTE  */
    CROCHET_OUVRANT = 283,         /* CROCHET_OUVRANT  */
    CROCHET_FERMANT = 284,         /* CROCHET_FERMANT  */
    ACCOLADE_OUVRANTE = 285,       /* ACCOLADE_OUVRANTE  */
    ACCOLADE_FERMANTE = 286,       /* ACCOLADE_FERMANTE  */
    VIRGULE = 287,                 /* VIRGULE  */
    POINT_VIRGULE = 288,           /* POINT_VIRGULE  */
    APOSTROPHE = 289,              /* APOSTROPHE  */
    GUILLEMET = 290,               /* GUILLEMET  */
    MAIN = 291,                    /* MAIN  */
    RETURN = 292,                  /* RETURN  */
    POINT_EXCLAMATION = 293,       /* POINT_EXCLAMATION  */
    INFERIEUR = 294,               /* INFERIEUR  */
    INFERIEUR_EGAL = 295,          /* INFERIEUR_EGAL  */
    SUPERIEUR = 296,               /* SUPERIEUR  */
    SUPERIEUR_EGAL = 297,          /* SUPERIEUR_EGAL  */
    EGAL_EGAL = 298,               /* EGAL_EGAL  */
    POINT = 299,                   /* POINT  */
    PRINT = 300,                   /* PRINT  */
    PRINTF = 301,                  /* PRINTF  */
    PRINTMAT = 302,                /* PRINTMAT  */
    UEXPR = 303                    /* UEXPR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 181 "bison/parser.y"

     struct exprval exprval_t;

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
         union {
             float  matval[100][100];
             float  vectval[100];
         } u;
         int row;
         int col;
     } crea_mat_t;

     char string[TAILLE_MAX_STRING];

#line 156 "./include/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_PARSER_H_INCLUDED  */
