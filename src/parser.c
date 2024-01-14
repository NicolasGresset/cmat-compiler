/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "bison/parser.y"

#include "CMat.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void yyerror (const char * msg);
extern int yylex();

void complete(struct ListLabel * l, unsigned int addr)
{
    struct ListLabel * current = l;
    printf("complete : ");
    ListLabel_print(l);
    printf(" %d\n", addr);
    while(current != NULL)
    {
        if (CODE->quads[current->addr].kind == Q_IF_EQ ||
            CODE->quads[current->addr].kind == Q_IF_NEQ ||
            CODE->quads[current->addr].kind == Q_IF_LT ||
            CODE->quads[current->addr].kind == Q_IF_LE ||
            CODE->quads[current->addr].kind == Q_IF_GT ||
            CODE->quads[current->addr].kind == Q_IF_GE ||
            CODE->quads[current->addr].kind == Q_GOTO_UNKNOWN ||
            CODE->quads[current->addr].kind == Q_GOTO)
        {
            CODE->quads[current->addr].sym3->u.addr = addr;
            CODE->quads[current->addr].sym3->kind = LABEL;
            if (CODE->quads[current->addr].kind == Q_GOTO_UNKNOWN)
            {
                CODE->quads[current->addr].kind = Q_GOTO;
            }
        }
        current = current->next;
    }
}

 struct exprval expression_gestion(struct code * CODE,
                                   struct table_hachage_t * SYMTAB,
                                   enum quad_kind k,
                                   struct exprval expr1,
                                   struct exprval expr2,
                                   struct exprval expr3)
 {
     // Affecter le bon quad pour les opérations matricielles si nécessaire
     enum quad_kind k1;
     enum quad_kind k2;
     switch (k)
     {
     case BOP_PLUS:
         k1 = MATOP_PLUS;
         k2 = MAT_BIN_PLUS;
         break;

     case BOP_MOINS:
         k1 = MATOP_MOINS;
         k2 = MAT_BIN_MOINS;
         break;
     case BOP_MULT:
         k1 = MATOP_MULT;
         k2 = MAT_BIN_MULT;
         break;
     case BOP_DIVISE:
         k1 = MATOP_DIVISE;
         k2 = MAT_BIN_DIVISE;
         break;
     case UOP_PLUS:
         k1 = UMATOP_PLUS;
         break;
     case UOP_MOINS:
         k1 = UMATOP_MOINS;
         break;

     default:
         printf("wrong operation quad\n");
     }

     if (k == UOP_PLUS || k == UOP_MOINS)
     {

         if (expr2.type == MATRIX_TYPE)
         {
             expr1.ptr = newtemp_mat(SYMTAB, MATRIX_TYPE, expr2.ptr->u.id.col, expr2.ptr->u.id.row);

             gencode(CODE, Q_DECLARE_MAT, expr1.ptr, NULL, NULL);

             gencode(CODE, k1, expr1.ptr, expr2.ptr, NULL);
         }
         else
         {
             expr1.ptr = newtemp(SYMTAB, expr2.type);
             gencode(CODE, Q_DECLARE, expr1.ptr, NULL, NULL);

             gencode(CODE, k, expr1.ptr,expr2.ptr,NULL);
         }
         expr1.type = expr2.type;

         expr1.num = expr2.num + 1;
         return expr1;
     }

     else if (expr2.type == MATRIX_TYPE && expr3.type == MATRIX_TYPE)
     {
         // Pour l'addition et la soustraction matricielles
         if ( (k == BOP_PLUS || k == BOP_MOINS) && (expr2.ptr->u.id.col != expr3.ptr->u.id.col || expr2.ptr->u.id.row != expr3.ptr->u.id.row))
         {
             fprintf(stderr, "error : dimensional error on matrix %s and %s\n", expr2.ptr->u.id.name, expr3.ptr->u.id.name);
             exit(1);
         }
         // Pour multiplication et division matricielles
         if ( (k == BOP_MULT || k == BOP_DIVISE) && (expr2.ptr->u.id.col != expr3.ptr->u.id.row))
         {
             fprintf(stderr, "error : dimensional error on matrix %s and %s\n", expr2.ptr->u.id.name, expr3.ptr->u.id.name);
             printf("col : %d %d row : %d %d", expr2.ptr->u.id.row, expr2.ptr->u.id.col, expr3.ptr->u.id.row, expr3.ptr->u.id.col);
             exit(1);
         }
         expr1.ptr = newtemp_mat(SYMTAB, MATRIX_TYPE, expr2.ptr->u.id.col, expr2.ptr->u.id.row);

         gencode(CODE, Q_DECLARE_MAT, expr1.ptr, NULL, NULL);

         gencode(CODE, k1, expr1.ptr, expr2.ptr, expr3.ptr);

         expr1.type = expr2.type;

     }
     // Operération avec 1 matrice et 1 float
     else if (expr2.type == MATRIX_TYPE)
     {
         expr1.ptr = newtemp_mat(SYMTAB, MATRIX_TYPE, expr2.ptr->u.id.col, expr2.ptr->u.id.row);

         gencode(CODE, Q_DECLARE_MAT, expr1.ptr, NULL, NULL);
         gencode(CODE, k2, expr1.ptr, expr2.ptr, expr3.ptr);

         expr1.type = expr2.type;
     }
    // Opératione entre 1 float et 1 matrice
    else if (expr3.type == MATRIX_TYPE)
    {
        expr1.ptr = newtemp_mat(SYMTAB, MATRIX_TYPE, expr3.ptr->u.id.col, expr3.ptr->u.id.row);

        gencode(CODE, Q_DECLARE_MAT, expr1.ptr, NULL, NULL);
        gencode(CODE, k2, expr1.ptr, expr3.ptr, expr2.ptr);

        expr1.type = expr3.type;
    }
    // Operation entre 2 entiers
    else if (expr2.type == ENTIER && expr3.type == ENTIER)
    {
        // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
        expr1.ptr = newtemp(SYMTAB, expr2.type);
        gencode(CODE, Q_DECLARE, expr1.ptr, NULL, NULL);

        gencode(CODE, k,expr1.ptr,expr2.ptr,expr3.ptr);

        expr1.type = expr2.type;
    }
    // Operation entre au moins 1 flottant (conversion gérée plus tard)
    else
    {
        expr1.ptr = newtemp(SYMTAB, REEL);
        gencode(CODE, Q_DECLARE, expr1.ptr, NULL, NULL);

        gencode(CODE, k,expr1.ptr,expr2.ptr,expr3.ptr);

        expr1.type = REEL;
    }

    // Utile pour la boucle_for savoir où compléter test.true
    expr1.num = MAX(expr2.num, expr3.num);
    expr1.num += 1;

    return expr1;
 }


#line 245 "src/parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFICATEUR = 3,             /* IDENTIFICATEUR  */
  YYSYMBOL_CONSTANTE_ENTIERE = 4,          /* CONSTANTE_ENTIERE  */
  YYSYMBOL_CONSTANTE_FLOTTANTE = 5,        /* CONSTANTE_FLOTTANTE  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_FLOAT = 8,                      /* FLOAT  */
  YYSYMBOL_MATRIX = 9,                     /* MATRIX  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_CONSTANTE_CARACTERE = 14,       /* CONSTANTE_CARACTERE  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_NOT = 17,                       /* NOT  */
  YYSYMBOL_PLUS = 18,                      /* PLUS  */
  YYSYMBOL_MOINS = 19,                     /* MOINS  */
  YYSYMBOL_FOIS = 20,                      /* FOIS  */
  YYSYMBOL_DIVISE = 21,                    /* DIVISE  */
  YYSYMBOL_PLUS_PLUS = 22,                 /* PLUS_PLUS  */
  YYSYMBOL_MOINS_MOINS = 23,               /* MOINS_MOINS  */
  YYSYMBOL_EGAL = 24,                      /* EGAL  */
  YYSYMBOL_TRANSPOSITION = 25,             /* TRANSPOSITION  */
  YYSYMBOL_PARENTHESE_OUVRANTE = 26,       /* PARENTHESE_OUVRANTE  */
  YYSYMBOL_PARENTHESE_FERMANTE = 27,       /* PARENTHESE_FERMANTE  */
  YYSYMBOL_CROCHET_OUVRANT = 28,           /* CROCHET_OUVRANT  */
  YYSYMBOL_CROCHET_FERMANT = 29,           /* CROCHET_FERMANT  */
  YYSYMBOL_ACCOLADE_OUVRANTE = 30,         /* ACCOLADE_OUVRANTE  */
  YYSYMBOL_ACCOLADE_FERMANTE = 31,         /* ACCOLADE_FERMANTE  */
  YYSYMBOL_VIRGULE = 32,                   /* VIRGULE  */
  YYSYMBOL_POINT_VIRGULE = 33,             /* POINT_VIRGULE  */
  YYSYMBOL_APOSTROPHE = 34,                /* APOSTROPHE  */
  YYSYMBOL_GUILLEMET = 35,                 /* GUILLEMET  */
  YYSYMBOL_MAIN = 36,                      /* MAIN  */
  YYSYMBOL_RETURN = 37,                    /* RETURN  */
  YYSYMBOL_POINT_EXCLAMATION = 38,         /* POINT_EXCLAMATION  */
  YYSYMBOL_INFERIEUR = 39,                 /* INFERIEUR  */
  YYSYMBOL_INFERIEUR_EGAL = 40,            /* INFERIEUR_EGAL  */
  YYSYMBOL_SUPERIEUR = 41,                 /* SUPERIEUR  */
  YYSYMBOL_SUPERIEUR_EGAL = 42,            /* SUPERIEUR_EGAL  */
  YYSYMBOL_EGAL_EGAL = 43,                 /* EGAL_EGAL  */
  YYSYMBOL_POINT = 44,                     /* POINT  */
  YYSYMBOL_PRINT = 45,                     /* PRINT  */
  YYSYMBOL_PRINTF = 46,                    /* PRINTF  */
  YYSYMBOL_PRINTMAT = 47,                  /* PRINTMAT  */
  YYSYMBOL_UEXPR = 48,                     /* UEXPR  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_S = 50,                         /* S  */
  YYSYMBOL_liste_instructions = 51,        /* liste_instructions  */
  YYSYMBOL_instruction = 52,               /* instruction  */
  YYSYMBOL_declaration = 53,               /* declaration  */
  YYSYMBOL_declaration_bin = 54,           /* declaration_bin  */
  YYSYMBOL_declaration_mat = 55,           /* declaration_mat  */
  YYSYMBOL_id_matrix = 56,                 /* id_matrix  */
  YYSYMBOL_id_vector = 57,                 /* id_vector  */
  YYSYMBOL_fin_crea_mat = 58,              /* fin_crea_mat  */
  YYSYMBOL_creation_matrix = 59,           /* creation_matrix  */
  YYSYMBOL_creation_matrix_prime = 60,     /* creation_matrix_prime  */
  YYSYMBOL_creation_vector = 61,           /* creation_vector  */
  YYSYMBOL_creation_vector_prime = 62,     /* creation_vector_prime  */
  YYSYMBOL_affectation_bin = 63,           /* affectation_bin  */
  YYSYMBOL_expression_bin = 64,            /* expression_bin  */
  YYSYMBOL_operande = 65,                  /* operande  */
  YYSYMBOL_type = 66,                      /* type  */
  YYSYMBOL_condition = 67,                 /* condition  */
  YYSYMBOL_68_1 = 68,                      /* $@1  */
  YYSYMBOL_69_2 = 69,                      /* $@2  */
  YYSYMBOL_condition_suite = 70,           /* condition_suite  */
  YYSYMBOL_71_3 = 71,                      /* $@3  */
  YYSYMBOL_72_4 = 72,                      /* $@4  */
  YYSYMBOL_boucle_while = 73,              /* boucle_while  */
  YYSYMBOL_74_5 = 74,                      /* $@5  */
  YYSYMBOL_75_6 = 75,                      /* $@6  */
  YYSYMBOL_boucle_for = 76,                /* boucle_for  */
  YYSYMBOL_77_7 = 77,                      /* $@7  */
  YYSYMBOL_78_8 = 78,                      /* $@8  */
  YYSYMBOL_for_init = 79,                  /* for_init  */
  YYSYMBOL_for_fin = 80,                   /* for_fin  */
  YYSYMBOL_test = 81,                      /* test  */
  YYSYMBOL_test2 = 82,                     /* test2  */
  YYSYMBOL_test3 = 83,                     /* test3  */
  YYSYMBOL_op_test = 84,                   /* op_test  */
  YYSYMBOL_M = 85,                         /* M  */
  YYSYMBOL_N = 86                          /* N  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   264

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  206

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   255,   255,   266,   267,   270,   271,   272,   273,   274,
     275,   281,   285,   307,   308,   311,   325,   346,   347,   348,
     369,   384,   395,   408,   431,   454,   455,   460,   477,   492,
     500,   514,   528,   536,   553,   582,   614,   617,   620,   623,
     626,   630,   635,   651,   653,   666,   679,   692,   705,   708,
     721,   722,   723,   753,   814,   815,   819,   820,   818,   845,
     846,   847,   846,   857,   858,   856,   874,   878,   874,   898,
     905,   922,   935,   955,   962,   965,   972,   975,  1010,  1027,
    1028,  1029,  1030,  1031,  1032,  1034,  1035
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFICATEUR",
  "CONSTANTE_ENTIERE", "CONSTANTE_FLOTTANTE", "STRING", "INT", "FLOAT",
  "MATRIX", "ELSE", "IF", "WHILE", "FOR", "CONSTANTE_CARACTERE", "AND",
  "OR", "NOT", "PLUS", "MOINS", "FOIS", "DIVISE", "PLUS_PLUS",
  "MOINS_MOINS", "EGAL", "TRANSPOSITION", "PARENTHESE_OUVRANTE",
  "PARENTHESE_FERMANTE", "CROCHET_OUVRANT", "CROCHET_FERMANT",
  "ACCOLADE_OUVRANTE", "ACCOLADE_FERMANTE", "VIRGULE", "POINT_VIRGULE",
  "APOSTROPHE", "GUILLEMET", "MAIN", "RETURN", "POINT_EXCLAMATION",
  "INFERIEUR", "INFERIEUR_EGAL", "SUPERIEUR", "SUPERIEUR_EGAL",
  "EGAL_EGAL", "POINT", "PRINT", "PRINTF", "PRINTMAT", "UEXPR", "$accept",
  "S", "liste_instructions", "instruction", "declaration",
  "declaration_bin", "declaration_mat", "id_matrix", "id_vector",
  "fin_crea_mat", "creation_matrix", "creation_matrix_prime",
  "creation_vector", "creation_vector_prime", "affectation_bin",
  "expression_bin", "operande", "type", "condition", "$@1", "$@2",
  "condition_suite", "$@3", "$@4", "boucle_while", "$@5", "$@6",
  "boucle_for", "$@7", "$@8", "for_init", "for_fin", "test", "test2",
  "test3", "op_test", "M", "N", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-129)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-68)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,   -25,    33,    21,  -129,    24,    26,    29,   -16,  -129,
    -129,     1,    44,    54,    74,    94,   105,   108,  -129,  -129,
    -129,  -129,  -129,    86,  -129,  -129,  -129,   107,   132,    95,
     143,  -129,    49,    89,   107,  -129,  -129,   145,   149,   163,
      18,    10,   139,  -129,  -129,   107,   107,   145,   145,   107,
     107,    -5,    39,   141,   164,   148,   150,   147,     1,  -129,
    -129,   151,  -129,    65,    -9,   154,  -129,   107,    46,   152,
     153,   155,   171,  -129,   107,  -129,   174,  -129,  -129,  -129,
    -129,  -129,   144,   107,   107,   107,   107,  -129,  -129,  -129,
      63,   156,   107,   107,  -129,    45,  -129,  -129,    45,   159,
    -129,  -129,  -129,  -129,  -129,   107,  -129,   157,  -129,    23,
     160,   183,   158,  -129,   161,   162,   165,   166,    76,   167,
    -129,    72,    72,  -129,  -129,   107,   184,   169,   124,   124,
     151,  -129,   185,  -129,  -129,    97,   107,  -129,   107,   170,
     107,   168,  -129,  -129,  -129,  -129,   172,  -129,   173,   119,
     175,   189,  -129,  -129,    96,   122,   154,  -129,  -129,  -129,
      97,   107,   107,  -129,   198,  -129,   181,   177,  -129,  -129,
    -129,  -129,    29,  -129,    97,   -11,   178,   107,  -129,   179,
      29,   186,  -129,   140,   180,    29,   182,   187,  -129,  -129,
     188,   190,   199,  -129,  -129,   191,  -129,    29,  -129,   192,
      29,   193,   194,  -129,   195,  -129
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,    54,
      55,     0,     0,     0,     0,     0,     0,     0,    85,     4,
       5,    13,     9,     0,     6,     7,     8,     0,     0,     0,
       0,    14,     0,     0,     0,    85,    66,     0,     0,     0,
       0,     0,    49,    50,    51,     0,     0,     0,     0,     0,
       0,     0,    48,     0,     0,     0,     0,     0,     0,    25,
      17,     0,    18,    78,     0,    74,    76,     0,     0,     0,
       0,     0,     0,     3,     0,    15,     0,    41,    40,    44,
      45,    42,     0,     0,     0,     0,     0,    33,    46,    47,
       0,     0,     0,     0,    29,     0,    26,    32,     0,     0,
      81,    82,    83,    84,    79,     0,    85,     0,    85,     0,
      71,     0,     0,    69,     0,     0,     0,     0,     0,     0,
      43,    36,    37,    38,    39,     0,     0,    24,     0,     0,
       0,    19,     0,    20,    80,    77,     0,    85,     0,     0,
       0,     0,    85,    11,    10,    12,     0,    16,    53,     0,
       0,     0,    21,    22,     0,     0,    73,    56,    75,    85,
      72,     0,     0,     2,     0,    35,     0,     0,    27,    28,
      30,    31,     0,    63,    70,     0,     0,     0,    23,    85,
       0,     0,    52,     0,     0,     0,    85,     0,    34,    86,
       0,     0,    59,    65,    85,     0,    58,     0,    60,    85,
       0,     0,    85,    68,     0,    62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -129,  -129,  -128,   -38,  -129,  -129,   176,   197,   200,   -27,
    -129,  -129,    78,  -129,  -129,   -26,    -2,   196,  -129,  -129,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,
    -129,    31,   -64,    79,    80,  -129,   -18,  -129
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    18,    19,    20,    21,    31,    32,    33,    60,
      95,   130,    98,   132,    22,    63,    52,    23,    24,   172,
     184,   196,   200,   204,    25,   180,   190,    26,    68,   201,
     112,   113,    64,    65,    66,   105,   185,   192
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,    51,    73,   109,    29,   106,    62,   106,    27,     1,
      30,     3,    28,    83,    84,    85,    86,    67,   107,    77,
      78,     8,   181,    81,    82,     9,    10,    11,    87,    12,
      13,    14,     8,     4,    74,    69,     9,    10,    11,   106,
      12,    13,    14,    75,   179,    79,    80,     5,   118,   110,
     139,     6,   186,     9,    10,    72,     7,   121,   122,   123,
     124,    88,    89,    15,    16,    17,   128,   129,   131,   199,
      34,   133,   202,    57,    15,    16,    17,    58,    59,   135,
      35,    58,    59,    83,    84,    85,    86,   125,   136,    41,
     138,   126,    85,    86,    83,    84,    85,    86,   175,   149,
      36,   152,   153,    99,   100,   101,   102,   103,   104,   147,
      42,    43,    44,    61,   160,    83,    84,    85,    86,   157,
      37,    58,    59,    54,   162,    45,    46,   168,   169,    47,
      48,    38,    49,    50,    39,   174,    53,    83,    84,    85,
      86,   173,    83,    84,    85,    86,    29,    73,    42,    43,
      44,   183,   165,   170,   171,    70,    58,    59,    83,    84,
      85,    86,    83,    84,    85,    86,    71,    76,    91,   108,
      90,   120,    92,   188,    93,   117,   197,    94,   119,   114,
     115,    97,   116,   134,   140,   127,   141,   137,   150,   110,
     155,   142,   161,   167,   143,   144,   148,   151,   145,   146,
     159,   164,   176,   163,   166,   177,   178,   182,   154,   195,
     -57,   189,   187,   -64,   191,   156,     0,     0,   158,   193,
     194,   198,     0,   -67,   203,   -61,   205,    55,     0,     0,
      56,     0,     0,     0,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111
};

static const yytype_int16 yycheck[] =
{
      18,    27,    40,    67,     3,    16,    33,    16,    24,     7,
       9,    36,    28,    18,    19,    20,    21,    35,    27,    45,
      46,     3,    33,    49,    50,     7,     8,     9,    33,    11,
      12,    13,     3,     0,    24,    37,     7,     8,     9,    16,
      11,    12,    13,    33,   172,    47,    48,    26,    74,     3,
      27,    27,   180,     7,     8,    37,    30,    83,    84,    85,
      86,    22,    23,    45,    46,    47,    92,    93,    95,   197,
      26,    98,   200,    24,    45,    46,    47,    32,    33,   105,
      26,    32,    33,    18,    19,    20,    21,    24,   106,     3,
     108,    28,    20,    21,    18,    19,    20,    21,   162,   125,
      26,   128,   129,    38,    39,    40,    41,    42,    43,    33,
       3,     4,     5,    24,   140,    18,    19,    20,    21,   137,
      26,    32,    33,    28,   142,    18,    19,    31,    32,    22,
      23,    26,    25,    26,    26,   161,     4,    18,    19,    20,
      21,   159,    18,    19,    20,    21,     3,   185,     3,     4,
       5,   177,    33,    31,    32,     6,    32,    33,    18,    19,
      20,    21,    18,    19,    20,    21,     3,    28,     4,    15,
      29,    27,    24,    33,    24,     4,   194,    30,     4,    27,
      27,    30,    27,    24,    24,    29,     3,    30,     4,     3,
       5,    33,    24,     4,    33,    33,    29,    28,    33,    33,
      30,    28,     4,    31,    29,    24,    29,    29,   130,    10,
      31,    31,   181,    31,    27,   136,    -1,    -1,   138,    31,
      30,    30,    -1,    31,    31,    31,    31,    30,    -1,    -1,
      30,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    50,    36,     0,    26,    27,    30,     3,     7,
       8,     9,    11,    12,    13,    45,    46,    47,    51,    52,
      53,    54,    63,    66,    67,    73,    76,    24,    28,     3,
       9,    55,    56,    57,    26,    26,    26,    26,    26,    26,
      85,     3,     3,     4,     5,    18,    19,    22,    23,    25,
      26,    64,    65,     4,    28,    56,    57,    24,    32,    33,
      58,    24,    58,    64,    81,    82,    83,    85,    77,    65,
       6,     3,    37,    52,    24,    33,    28,    64,    64,    65,
      65,    64,    64,    18,    19,    20,    21,    33,    22,    23,
      29,     4,    24,    24,    30,    59,    55,    30,    61,    38,
      39,    40,    41,    42,    43,    84,    16,    27,    15,    81,
       3,    66,    79,    80,    27,    27,    27,     4,    64,     4,
      27,    64,    64,    64,    64,    24,    28,    29,    64,    64,
      60,    58,    62,    58,    24,    64,    85,    30,    85,    27,
      24,     3,    33,    33,    33,    33,    33,    33,    29,    64,
       4,    28,    58,    58,    61,     5,    82,    85,    83,    30,
      64,    24,    85,    31,    28,    33,    29,     4,    31,    32,
      31,    32,    68,    85,    64,    81,     4,    24,    29,    51,
      74,    33,    29,    64,    69,    85,    51,    80,    33,    31,
      75,    27,    86,    31,    30,    10,    70,    85,    30,    51,
      71,    78,    51,    31,    72,    31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    53,    53,    54,    54,    55,    55,    55,
      55,    55,    55,    56,    57,    58,    58,    59,    60,    60,
      61,    62,    62,    63,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      65,    65,    65,    65,    66,    66,    68,    69,    67,    70,
      71,    72,    70,    74,    75,    73,    77,    78,    76,    79,
      79,    80,    80,    81,    81,    82,    82,    83,    83,    84,
      84,    84,    84,    84,    84,    85,    86
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,    11,     3,     1,     1,     1,     1,     1,     1,
       5,     5,     5,     1,     2,     3,     5,     2,     2,     4,
       4,     5,     5,     7,     4,     1,     2,     4,     3,     0,
       4,     3,     0,     4,    10,     7,     3,     3,     3,     3,
       2,     2,     2,     3,     2,     2,     2,     2,     1,     1,
       1,     1,     7,     4,     1,     1,     0,     0,    12,     0,
       0,     0,     6,     0,     0,    11,     0,     0,    15,     1,
       4,     1,     3,     4,     1,     4,     1,     3,     1,     1,
       2,     1,     1,     1,     1,     0,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* S: INT MAIN PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE liste_instructions M RETURN CONSTANTE_ENTIERE POINT_VIRGULE ACCOLADE_FERMANTE  */
#line 256 "bison/parser.y"
{
    complete((yyvsp[-5].instr_type).next, (yyvsp[-4].intval));
    // Pour sortir proprement
    struct symbol * sym1 = symbol_const_int((yyvsp[-2].intval));
    gencode(CODE, Q_RETURN, sym1, NULL, NULL);
    ListLabel_free((yyvsp[-5].instr_type).next);

}
#line 1474 "src/parser.c"
    break;

  case 3: /* liste_instructions: liste_instructions M instruction  */
#line 266 "bison/parser.y"
                                   {complete((yyvsp[-2].instr_type).next, (yyvsp[-1].intval));  ListLabel_free((yyvsp[-2].instr_type).next); (yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1480 "src/parser.c"
    break;

  case 4: /* liste_instructions: instruction  */
#line 267 "bison/parser.y"
              {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1486 "src/parser.c"
    break;

  case 5: /* instruction: declaration  */
#line 270 "bison/parser.y"
              {(yyval.instr_type).next = NULL;}
#line 1492 "src/parser.c"
    break;

  case 6: /* instruction: condition  */
#line 271 "bison/parser.y"
            {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1498 "src/parser.c"
    break;

  case 7: /* instruction: boucle_while  */
#line 272 "bison/parser.y"
               {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1504 "src/parser.c"
    break;

  case 8: /* instruction: boucle_for  */
#line 273 "bison/parser.y"
             {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1510 "src/parser.c"
    break;

  case 9: /* instruction: affectation_bin  */
#line 274 "bison/parser.y"
                  {(yyval.instr_type).next = NULL;}
#line 1516 "src/parser.c"
    break;

  case 10: /* instruction: PRINTF PARENTHESE_OUVRANTE STRING PARENTHESE_FERMANTE POINT_VIRGULE  */
#line 276 "bison/parser.y"
{
    struct symbol * sym_str = symbol_string((yyvsp[-2].string));
    gencode(CODE, Q_DECLARE_STRING, sym_str, NULL, NULL);
    (yyval.instr_type).next = NULL;
}
#line 1526 "src/parser.c"
    break;

  case 11: /* instruction: PRINT PARENTHESE_OUVRANTE operande PARENTHESE_FERMANTE POINT_VIRGULE  */
#line 281 "bison/parser.y"
                                                                       {
    (yyval.instr_type).next = NULL;
    gencode(CODE, CALL_PRINT, (yyvsp[-2].exprval_t).ptr, NULL, NULL);
}
#line 1535 "src/parser.c"
    break;

  case 12: /* instruction: PRINTMAT PARENTHESE_OUVRANTE IDENTIFICATEUR PARENTHESE_FERMANTE POINT_VIRGULE  */
#line 286 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-2].strval));
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", (yyvsp[-2].strval));
        exit(1);
    }
    if (id->type != MATRIX_TYPE)
    {
        fprintf(stderr, "error: incompatible types, should be a matrix\n");
        exit(1);
    }

    struct symbol *  sym_id = symbol_id(*id);
    gencode(CODE,CALL_PRINT_MAT,sym_id,NULL,NULL);
    (yyval.instr_type).next = NULL;
}
#line 1557 "src/parser.c"
    break;

  case 13: /* declaration: declaration_bin  */
#line 307 "bison/parser.y"
                  {(yyval.instr_type).next = NULL;}
#line 1563 "src/parser.c"
    break;

  case 14: /* declaration: MATRIX declaration_mat  */
#line 308 "bison/parser.y"
                         {(yyval.instr_type).next = NULL;}
#line 1569 "src/parser.c"
    break;

  case 15: /* declaration_bin: type IDENTIFICATEUR POINT_VIRGULE  */
#line 311 "bison/parser.y"
                                    {
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-1].strval));
     if ( id != NULL )
     {
         fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", (yyvsp[-1].strval));
         exit(1);
     }
     id = id_init((yyvsp[-1].strval), (yyvsp[-2].typeval));
     table_hachage_put(SYMTAB,id);


     struct symbol * sym_id = symbol_id(*id);
     gencode(CODE, Q_DECLARE, sym_id,NULL,NULL);
 }
#line 1588 "src/parser.c"
    break;

  case 16: /* declaration_bin: type IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE  */
#line 325 "bison/parser.y"
                                                         {
    struct id_t * id = table_hachage_get(SYMTAB, (yyvsp[-3].strval));
    if ( id != NULL )
    {
        fprintf(stderr, "error: redefinition of ‘%s’\n", (yyvsp[-3].strval));
        exit(1);
    }

    id = id_init((yyvsp[-3].strval), (yyvsp[-4].typeval));
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, Q_DECLARE, sym_id,NULL,NULL);
    gencode(CODE,COPY,sym_id,(yyvsp[-1].exprval_t).ptr,NULL);
 }
#line 1608 "src/parser.c"
    break;

  case 19: /* declaration_mat: id_matrix EGAL creation_matrix fin_crea_mat  */
#line 349 "bison/parser.y"
{
    // Ici gérer si les valeurs entre {} respectent la taille de id_matrix
    if ((yyvsp[-3].exprval_t).ptr->u.id.row < (yyvsp[-1].crea_mat_t).row || (yyvsp[-3].exprval_t).ptr->u.id.col < (yyvsp[-1].crea_mat_t).col)
    {

        fprintf(stderr, "error: incompatible matrix size in the matrix declaration\n");
        exit(1);
    }

    for (int i = 0; i < (yyvsp[-3].exprval_t).ptr->u.id.row; ++i)
    {
        for (int j = 0; j < (yyvsp[-3].exprval_t).ptr->u.id.col; ++j)
        {
            struct symbol * sym_idx = symbol_const_int((i)*(yyvsp[-3].exprval_t).ptr->u.id.col + j);
            struct symbol * sym_val = symbol_const_float((yyvsp[-1].crea_mat_t).u.matval[i][j]);
            gencode(CODE, ARRAY_AFFECT, (yyvsp[-3].exprval_t).ptr, sym_idx, sym_val);
        }
    }

}
#line 1633 "src/parser.c"
    break;

  case 20: /* declaration_mat: id_vector EGAL creation_vector fin_crea_mat  */
#line 370 "bison/parser.y"
{
    // Ici gérer si les valeurs entre {} respectent la taille de id_matrix
    if ((yyvsp[-3].exprval_t).ptr->u.id.row < (yyvsp[-1].crea_mat_t).row || (yyvsp[-3].exprval_t).ptr->u.id.col < (yyvsp[-1].crea_mat_t).col)
    {
        fprintf(stderr, "error: incompatible matrix size in the matrix declaration\n");
        exit(1);
    }
    for (int j = 0; j < (yyvsp[-3].exprval_t).ptr->u.id.col; ++j)
    {
        struct symbol * sym_idx = symbol_const_int(j);
        struct symbol * sym_val = symbol_const_float((yyvsp[-1].crea_mat_t).u.vectval[j]);
        gencode(CODE, ARRAY_AFFECT, (yyvsp[-3].exprval_t).ptr, sym_idx, sym_val);
    }
}
#line 1652 "src/parser.c"
    break;

  case 21: /* declaration_mat: MATRIX id_matrix EGAL expression_bin fin_crea_mat  */
#line 385 "bison/parser.y"
{
    // id_matrix regarde si l'identificateur existe

    if ((yyvsp[-1].exprval_t).type != MATRIX_TYPE)
    {
        fprintf(stderr, "error : incorrect type in declaration matrix\n");
        exit(1);
    }
}
#line 1666 "src/parser.c"
    break;

  case 22: /* declaration_mat: MATRIX id_vector EGAL expression_bin fin_crea_mat  */
#line 396 "bison/parser.y"
{
    // id_vector regarde si l'identificateur existe
    if ((yyvsp[-1].exprval_t).type != MATRIX_TYPE)
    {
        fprintf(stderr, "error : incorrect type in declaration matrix\n");
        exit(1);
    }

}
#line 1680 "src/parser.c"
    break;

  case 23: /* id_matrix: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 409 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-6].strval));
    if ( id != NULL )
    {
        fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", (yyvsp[-6].strval));
        exit(1);
    }
    id = id_init((yyvsp[-6].strval), MATRIX_TYPE);

    id->row = (yyvsp[-4].intval);
    id->col = (yyvsp[-1].intval);
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, Q_DECLARE_MAT, sym_id,NULL,NULL);

    (yyval.exprval_t).ptr = sym_id;
    (yyval.exprval_t).num = 0;
    (yyval.exprval_t).type = MATRIX_TYPE;
}
#line 1705 "src/parser.c"
    break;

  case 24: /* id_vector: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 432 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-3].strval));
    if ( id != NULL )
    {
        fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", (yyvsp[-3].strval));
        exit(1);
    }
    id = id_init((yyvsp[-3].strval), MATRIX_TYPE);

    id->col = (yyvsp[-1].intval);
    id->row = 1;
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, Q_DECLARE_MAT, sym_id,NULL,NULL);

    (yyval.exprval_t).ptr = sym_id;
    (yyval.exprval_t).num = 0;
    (yyval.exprval_t).type = MATRIX_TYPE;
}
#line 1730 "src/parser.c"
    break;

  case 27: /* creation_matrix: ACCOLADE_OUVRANTE creation_matrix_prime creation_vector ACCOLADE_FERMANTE  */
#line 461 "bison/parser.y"
{
    (yyval.crea_mat_t) = (yyvsp[-2].crea_mat_t);
    // Ce test est obsolète pour la déclaration de matrice incomplète
    /* if ($3.col != 0 && $2.col != $3.col) */
    /* { */
    /*     fprintf(stderr, "error : incompatible column size\n"); */
    /*     exit(1); */
    /* } */

    for (int j = 0; j < (yyvsp[-1].crea_mat_t).col; ++j)
        (yyval.crea_mat_t).u.matval[(yyvsp[-2].crea_mat_t).row][j] = (yyvsp[-1].crea_mat_t).u.vectval[j];
    (yyval.crea_mat_t).col = MAX((yyvsp[-1].crea_mat_t).col, (yyvsp[-2].crea_mat_t).col);
    (yyval.crea_mat_t).row = 1 + (yyvsp[-2].crea_mat_t).row;
}
#line 1749 "src/parser.c"
    break;

  case 28: /* creation_matrix_prime: creation_matrix_prime creation_vector VIRGULE  */
#line 478 "bison/parser.y"
{
    (yyval.crea_mat_t) = (yyvsp[-2].crea_mat_t);
    // Ce test est obsolète pour la déclaration de matrice incomplète
    /* if ($1.col != 0 && $1.col != $2.col) */
    /* { */
    /*     fprintf(stderr, "error : incompatible column size\n"); */
    /*     exit(1); */
    /* } */

   for (int j = 0; j < (yyvsp[-1].crea_mat_t).col; ++j)
       (yyval.crea_mat_t).u.matval[(yyvsp[-2].crea_mat_t).row][j] = (yyvsp[-1].crea_mat_t).u.vectval[j];
   (yyval.crea_mat_t).col = (yyvsp[-1].crea_mat_t).col;
   (yyval.crea_mat_t).row = 1 + (yyvsp[-2].crea_mat_t).row;
}
#line 1768 "src/parser.c"
    break;

  case 29: /* creation_matrix_prime: %empty  */
#line 493 "bison/parser.y"
{
    (yyval.crea_mat_t).row = 0;
    (yyval.crea_mat_t).col = 0;
}
#line 1777 "src/parser.c"
    break;

  case 30: /* creation_vector: ACCOLADE_OUVRANTE creation_vector_prime CONSTANTE_FLOTTANTE ACCOLADE_FERMANTE  */
#line 501 "bison/parser.y"
{
    // test inutile
    /* if ($2.type != ENTIER && $2.type != REEL) */
    /* { */
    /*     fprintf(stderr, "error : operations sur des identificateurs non gérées %d\n", $2.type); */
    /*     exit(1); */
    /* } */
    (yyval.crea_mat_t) = (yyvsp[-2].crea_mat_t);
    (yyval.crea_mat_t).u.vectval[(yyvsp[-2].crea_mat_t).col] = (yyvsp[-1].floatval);
    (yyval.crea_mat_t).col = 1 + (yyvsp[-2].crea_mat_t).col;
    (yyval.crea_mat_t).row = 1;
}
#line 1794 "src/parser.c"
    break;

  case 31: /* creation_vector_prime: creation_vector_prime CONSTANTE_FLOTTANTE VIRGULE  */
#line 515 "bison/parser.y"
{
    // test inutile
    /* if ($2.type != ENTIER && $2.type != REEL) */
    /* { */
    /*     fprintf(stderr, "error : operations sur des identificateurs non gérées %d\n", $2.type); */
    /*     exit(1); */
    /* } */

    (yyval.crea_mat_t) = (yyvsp[-2].crea_mat_t);
    (yyval.crea_mat_t).u.vectval[(yyvsp[-2].crea_mat_t).col] = (yyvsp[-1].floatval);
    (yyval.crea_mat_t).col = 1 + (yyvsp[-2].crea_mat_t).col;
    (yyval.crea_mat_t).row = 1;
}
#line 1812 "src/parser.c"
    break;

  case 32: /* creation_vector_prime: %empty  */
#line 528 "bison/parser.y"
         {(yyval.crea_mat_t).row = 0; (yyval.crea_mat_t).col = 0;}
#line 1818 "src/parser.c"
    break;

  case 33: /* affectation_bin: IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE  */
#line 536 "bison/parser.y"
                                                   {
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-3].strval));
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", (yyvsp[-3].strval));
        exit(1);
    }
    if (id->type != (yyvsp[-1].exprval_t).type)
    {
        fprintf(stderr, "error: incompatible types\n");
        //exit(1);
    }

    struct symbol *  sym_id = symbol_id(*id);
    gencode(CODE,COPY,sym_id,(yyvsp[-1].exprval_t).ptr,NULL);

 }
#line 1840 "src/parser.c"
    break;

  case 34: /* affectation_bin: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT EGAL expression_bin POINT_VIRGULE  */
#line 554 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-9].strval));
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", (yyvsp[-9].strval));
        exit(1);
    }
    if (id->type != MATRIX_TYPE)
    {
        fprintf(stderr, "error: incompatible types, it should be a matrix\n");
        exit(1);
    }
    // Vérifier que le type de expression_bin n'est pas unr matrix
    if ((yyvsp[-1].exprval_t).type == MATRIX_TYPE)
    {
        fprintf(stderr, "error : incompatible types, cannot be a matrix\n");
        exit(1);
    }
    if (id->row <= (yyvsp[-7].intval) || id->col <= (yyvsp[-4].intval))
    {
        fprintf(stderr, "error : incorrect dimensions");
        exit(1);
    }

    struct symbol *  sym_id = symbol_id(*id);
    struct symbol * sym_idx = symbol_const_int(((yyvsp[-7].intval))*id->col + (yyvsp[-4].intval));
    gencode(CODE, ARRAY_AFFECT, sym_id, sym_idx, (yyvsp[-1].exprval_t).ptr);
}
#line 1873 "src/parser.c"
    break;

  case 35: /* affectation_bin: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT EGAL expression_bin POINT_VIRGULE  */
#line 583 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-6].strval));
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", (yyvsp[-6].strval));
        exit(1);
    }
    if (id->type != MATRIX_TYPE)
    {
        fprintf(stderr, "error: incompatible types, it should be a matrix\n");
        exit(1);
    }
    // Vérifier que le type de expression_bin n'est pas unr matrix
    if ((yyvsp[-1].exprval_t).type == MATRIX_TYPE)
    {
        fprintf(stderr, "error : incompatible types, cannot be a matrix\n");
        exit(1);
    }
    // Pas le bon nombre de colonnes ou pas un vecteur
    if (id->row <= (yyvsp[-4].intval) || id->col > 1)
    {
        fprintf(stderr, "error : incorrect dimensions");
        exit(1);
    }

    struct symbol *  sym_id = symbol_id(*id);
    struct symbol * sym_idx = symbol_const_int(((yyvsp[-4].intval)));
    gencode(CODE, ARRAY_AFFECT, sym_id, sym_idx, (yyvsp[-1].exprval_t).ptr);
}
#line 1907 "src/parser.c"
    break;

  case 36: /* expression_bin: expression_bin PLUS expression_bin  */
#line 614 "bison/parser.y"
                                     {
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, BOP_PLUS, (yyval.exprval_t), (yyvsp[-2].exprval_t), (yyvsp[0].exprval_t));
}
#line 1915 "src/parser.c"
    break;

  case 37: /* expression_bin: expression_bin MOINS expression_bin  */
#line 617 "bison/parser.y"
                                      {
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, BOP_MOINS, (yyval.exprval_t), (yyvsp[-2].exprval_t), (yyvsp[0].exprval_t));
}
#line 1923 "src/parser.c"
    break;

  case 38: /* expression_bin: expression_bin FOIS expression_bin  */
#line 620 "bison/parser.y"
                                     {
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, BOP_MULT, (yyval.exprval_t), (yyvsp[-2].exprval_t), (yyvsp[0].exprval_t));
}
#line 1931 "src/parser.c"
    break;

  case 39: /* expression_bin: expression_bin DIVISE expression_bin  */
#line 623 "bison/parser.y"
                                       {
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, BOP_DIVISE, (yyval.exprval_t), (yyvsp[-2].exprval_t), (yyvsp[0].exprval_t));
}
#line 1939 "src/parser.c"
    break;

  case 40: /* expression_bin: MOINS expression_bin  */
#line 626 "bison/parser.y"
                                      {
    struct exprval expr_null;
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, UOP_MOINS, (yyval.exprval_t), (yyvsp[0].exprval_t), expr_null);
}
#line 1948 "src/parser.c"
    break;

  case 41: /* expression_bin: PLUS expression_bin  */
#line 630 "bison/parser.y"
                                     {
    struct exprval expr_null;
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, UOP_PLUS, (yyval.exprval_t), (yyvsp[0].exprval_t), expr_null);
}
#line 1957 "src/parser.c"
    break;

  case 42: /* expression_bin: TRANSPOSITION expression_bin  */
#line 636 "bison/parser.y"
{
    if ((yyvsp[0].exprval_t).type != MATRIX_TYPE)
    {
        fprintf(stderr, "error: impossible to transpose a non matrix type\n");
        exit(1);
    }
    // Inverser nombre colonnes et lignes
    struct symbol * sym_temp = newtemp_mat(SYMTAB, MATRIX_TYPE, (yyvsp[0].exprval_t).ptr->u.id.row, (yyvsp[0].exprval_t).ptr->u.id.col);
    gencode(CODE, UMATOP_TRANSPOSE, sym_temp, (yyvsp[0].exprval_t).ptr, NULL);

    (yyval.exprval_t).ptr = sym_temp;
    (yyval.exprval_t).type = MATRIX_TYPE;

    (yyval.exprval_t).num = 1 + (yyvsp[0].exprval_t).num;
}
#line 1977 "src/parser.c"
    break;

  case 43: /* expression_bin: PARENTHESE_OUVRANTE expression_bin PARENTHESE_FERMANTE  */
#line 651 "bison/parser.y"
                                                          {(yyval.exprval_t).ptr = (yyvsp[-1].exprval_t).ptr; (yyval.exprval_t).type = (yyvsp[-1].exprval_t).type; (yyval.exprval_t).num = (yyvsp[-1].exprval_t).num;}
#line 1983 "src/parser.c"
    break;

  case 44: /* expression_bin: PLUS_PLUS operande  */
#line 654 "bison/parser.y"
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval_t).ptr = newtemp(SYMTAB, (yyvsp[0].exprval_t).type);
    gencode(CODE, Q_DECLARE, (yyval.exprval_t).ptr, NULL, NULL);

    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_PLUS,(yyval.exprval_t).ptr,one,(yyvsp[0].exprval_t).ptr);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval_t).type = (yyvsp[0].exprval_t).type;
    (yyval.exprval_t).num = 1;
}
#line 2000 "src/parser.c"
    break;

  case 45: /* expression_bin: MOINS_MOINS operande  */
#line 667 "bison/parser.y"
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval_t).ptr = newtemp(SYMTAB, (yyvsp[0].exprval_t).type);
    gencode(CODE, Q_DECLARE, (yyval.exprval_t).ptr, NULL, NULL);

    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_MOINS,(yyval.exprval_t).ptr,(yyvsp[0].exprval_t).ptr, one);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval_t).type = (yyvsp[0].exprval_t).type;
    (yyval.exprval_t).num += 1;
}
#line 2017 "src/parser.c"
    break;

  case 46: /* expression_bin: operande PLUS_PLUS  */
#line 680 "bison/parser.y"
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval_t).ptr = newtemp(SYMTAB, (yyvsp[-1].exprval_t).type);
    gencode(CODE, Q_DECLARE, (yyval.exprval_t).ptr, NULL, NULL);

    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_PLUS,(yyval.exprval_t).ptr,one,(yyvsp[-1].exprval_t).ptr);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval_t).type = (yyvsp[-1].exprval_t).type;
    (yyval.exprval_t).num = 1;
}
#line 2034 "src/parser.c"
    break;

  case 47: /* expression_bin: operande MOINS_MOINS  */
#line 693 "bison/parser.y"
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval_t).ptr = newtemp(SYMTAB, (yyvsp[-1].exprval_t).type);
    gencode(CODE, Q_DECLARE, (yyval.exprval_t).ptr, NULL, NULL);

    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_MOINS,(yyval.exprval_t).ptr, (yyvsp[-1].exprval_t).ptr, one);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval_t).type = (yyvsp[-1].exprval_t).type;
    (yyval.exprval_t).num = 1;
}
#line 2051 "src/parser.c"
    break;

  case 48: /* expression_bin: operande  */
#line 705 "bison/parser.y"
           {(yyval.exprval_t).type = (yyvsp[0].exprval_t).type; (yyval.exprval_t).num = 0;}
#line 2057 "src/parser.c"
    break;

  case 49: /* operande: IDENTIFICATEUR  */
#line 709 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[0].strval));
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",(yyvsp[0].strval));
        exit(1);
    }

    struct symbol * sym_id = symbol_id(*id);
    (yyval.exprval_t).ptr = sym_id;
    (yyval.exprval_t).type = sym_id->u.id.type;
}
#line 2074 "src/parser.c"
    break;

  case 50: /* operande: CONSTANTE_ENTIERE  */
#line 721 "bison/parser.y"
                    {(yyval.exprval_t).ptr = symbol_const_int((yyvsp[0].intval)); (yyval.exprval_t).type = ENTIER;}
#line 2080 "src/parser.c"
    break;

  case 51: /* operande: CONSTANTE_FLOTTANTE  */
#line 722 "bison/parser.y"
                      {(yyval.exprval_t).ptr = symbol_const_float((yyvsp[0].floatval)); (yyval.exprval_t).type = REEL;}
#line 2086 "src/parser.c"
    break;

  case 52: /* operande: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 725 "bison/parser.y"
{

    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-6].strval));
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",(yyvsp[-6].strval));
        exit(1);
    }
    if (id->type != MATRIX_TYPE)
    {
        fprintf(stderr,"%s is not of type MATRIX\n",(yyvsp[-6].strval));
        exit(1);
    }
    // test sur les dimensions du tableau
    if (id->row <= (yyvsp[-4].intval) || id->col <= (yyvsp[-1].intval))
    {
        fprintf(stderr, "Erreur de dimension pour %s\n", (yyvsp[-6].strval));
        exit(1);
    }

    struct symbol * sym_float = newtemp(SYMTAB, REEL);
    struct symbol *  sym_id = symbol_id(*id);
    struct symbol * sym_idx = symbol_const_int(((yyvsp[-4].intval))*id->col + (yyvsp[-1].intval));
    gencode(CODE, DEREF, sym_float, sym_id, sym_idx);

    (yyval.exprval_t).ptr = sym_float;
    (yyval.exprval_t).type = REEL;
}
#line 2119 "src/parser.c"
    break;

  case 53: /* operande: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 754 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-3].strval));
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",(yyvsp[-3].strval));
        exit(1);
    }
    if (id->type != MATRIX_TYPE)
    {
        fprintf(stderr,"%s is not of type MATRIX\n",(yyvsp[-3].strval));
        exit(1);
    }
    // test sur les dimensions du tableau
    if (id->row >= (yyvsp[-1].intval))
    {
        fprintf(stderr, "Erreur de dimension pour %s\n", (yyvsp[-3].strval));
    }

    struct symbol * sym_float = newtemp(SYMTAB, REEL);
    struct symbol *  sym_id = symbol_id(*id);
    struct symbol * sym_idx = symbol_const_int((yyvsp[-1].intval));
    gencode(CODE, DEREF, sym_float, sym_id, sym_idx);

    (yyval.exprval_t).ptr = sym_float;
    (yyval.exprval_t).type = REEL;
}
#line 2150 "src/parser.c"
    break;

  case 54: /* type: INT  */
#line 814 "bison/parser.y"
      {(yyval.typeval) = ENTIER;}
#line 2156 "src/parser.c"
    break;

  case 55: /* type: FLOAT  */
#line 815 "bison/parser.y"
        {(yyval.typeval) = REEL;}
#line 2162 "src/parser.c"
    break;

  case 56: /* $@1: %empty  */
#line 819 "bison/parser.y"
  { stack_id_push(SYMTAB);}
#line 2168 "src/parser.c"
    break;

  case 57: /* $@2: %empty  */
#line 820 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 2174 "src/parser.c"
    break;

  case 58: /* condition: IF PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M $@1 liste_instructions $@2 ACCOLADE_FERMANTE N condition_suite  */
#line 822 "bison/parser.y"
{
    complete((yyvsp[-9].boolexpr).true, (yyvsp[-6].intval));
    ListLabel_free((yyvsp[-9].boolexpr).true);

    (yyval.instr_type).next = concat((yyvsp[-4].instr_type).next, (yyvsp[-1].N_t).next);

    if ((yyvsp[0].instr_type).next != NULL)
    {
        complete((yyvsp[-9].boolexpr).false, (yyvsp[-1].N_t).quad);
        ListLabel_free((yyvsp[-9].boolexpr).false);
        (yyval.instr_type).next = concat((yyval.instr_type).next, (yyvsp[0].instr_type).next);
    }
    else
    {
        (yyval.instr_type).next = concat((yyval.instr_type).next, (yyvsp[-9].boolexpr).false);
    }

    printf("if.next : ");
    ListLabel_print((yyval.instr_type).next);
    printf("\n");
}
#line 2200 "src/parser.c"
    break;

  case 59: /* condition_suite: %empty  */
#line 845 "bison/parser.y"
         {(yyval.instr_type).next = NULL;}
#line 2206 "src/parser.c"
    break;

  case 60: /* $@3: %empty  */
#line 846 "bison/parser.y"
                          { stack_id_push(SYMTAB);}
#line 2212 "src/parser.c"
    break;

  case 61: /* $@4: %empty  */
#line 847 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 2218 "src/parser.c"
    break;

  case 62: /* condition_suite: ELSE ACCOLADE_OUVRANTE $@3 liste_instructions $@4 ACCOLADE_FERMANTE  */
#line 848 "bison/parser.y"
{
    (yyval.instr_type).next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());

    (yyval.instr_type).next = concat((yyval.instr_type).next, (yyvsp[-2].instr_type).next);
}
#line 2229 "src/parser.c"
    break;

  case 63: /* $@5: %empty  */
#line 857 "bison/parser.y"
                    {stack_id_push(SYMTAB);}
#line 2235 "src/parser.c"
    break;

  case 64: /* $@6: %empty  */
#line 858 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 2241 "src/parser.c"
    break;

  case 65: /* boucle_while: WHILE PARENTHESE_OUVRANTE M test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M $@5 liste_instructions $@6 ACCOLADE_FERMANTE  */
#line 859 "bison/parser.y"
{
    complete((yyvsp[-7].boolexpr).true, (yyvsp[-4].intval));
    ListLabel_free((yyvsp[-7].boolexpr).true);
    complete((yyvsp[-2].instr_type).next, (yyvsp[-8].intval));
    ListLabel_free((yyvsp[-2].instr_type).next);
    (yyval.instr_type).next = (yyvsp[-7].boolexpr).false;

    struct symbol * q = quad_label();
    q->u.addr = (yyvsp[-8].intval);
    CODE->quads[CODE->nextquad].sym3 = q;
    gencode(CODE, Q_GOTO, NULL, NULL, q);
}
#line 2258 "src/parser.c"
    break;

  case 66: /* $@7: %empty  */
#line 874 "bison/parser.y"
                          {stack_id_push(SYMTAB);}
#line 2264 "src/parser.c"
    break;

  case 67: /* $@8: %empty  */
#line 878 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 2270 "src/parser.c"
    break;

  case 68: /* boucle_for: FOR PARENTHESE_OUVRANTE $@7 for_init POINT_VIRGULE M test POINT_VIRGULE for_fin PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M liste_instructions $@8 ACCOLADE_FERMANTE  */
#line 879 "bison/parser.y"
{
    complete((yyvsp[-8].boolexpr).true, (yyvsp[-3].intval) - (yyvsp[-6].for_fin_t).num);
    ListLabel_free((yyvsp[-8].boolexpr).true);
    complete((yyvsp[-2].instr_type).next, (yyvsp[-9].intval));
    ListLabel_free((yyvsp[-2].instr_type).next);
    (yyval.instr_type).next = (yyvsp[-8].boolexpr).false;

    if ((yyvsp[-6].for_fin_t).ptr != NULL)
    {
        gencode(CODE,COPY,(yyvsp[-6].for_fin_t).id,(yyvsp[-6].for_fin_t).ptr,NULL);
    }

    struct symbol * q = quad_label();
    q->u.addr = (yyvsp[-9].intval);
    CODE->quads[CODE->nextquad].sym3 = q;
    gencode(CODE, Q_GOTO, NULL, NULL, q);
}
#line 2292 "src/parser.c"
    break;

  case 69: /* for_init: for_fin  */
#line 899 "bison/parser.y"
{
    if ((yyvsp[0].for_fin_t).ptr != NULL)
    {
        gencode(CODE,COPY,(yyvsp[0].for_fin_t).id,(yyvsp[0].for_fin_t).ptr,NULL);
    }
}
#line 2303 "src/parser.c"
    break;

  case 70: /* for_init: type IDENTIFICATEUR EGAL expression_bin  */
#line 906 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-2].strval));
    if ( id != NULL )
    {
        fprintf(stderr, "error: redefinition of ‘%s’\n", (yyvsp[-2].strval));
        exit(1);
    }
    id = id_init((yyvsp[-2].strval), (yyvsp[-3].typeval));
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, Q_DECLARE, sym_id, NULL, NULL);
    gencode(CODE,COPY,sym_id,(yyvsp[0].exprval_t).ptr,NULL);

}
#line 2323 "src/parser.c"
    break;

  case 71: /* for_fin: IDENTIFICATEUR  */
#line 923 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[0].strval));
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", (yyvsp[0].strval));
        exit(1);
    }

    struct symbol * sym_id = symbol_id(*id);
    (yyval.for_fin_t).id = sym_id;
    (yyval.for_fin_t).ptr = NULL;
}
#line 2340 "src/parser.c"
    break;

  case 72: /* for_fin: IDENTIFICATEUR EGAL expression_bin  */
#line 936 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-2].strval));
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", (yyvsp[-2].strval));
        exit(1);
    }
    if (id->type != (yyvsp[0].exprval_t).type)
    {
        fprintf(stderr, "error: incompatible types\n");
        exit(1);
    }
    struct symbol * sym_id = symbol_id(*id);
    (yyval.for_fin_t).id = sym_id;
    (yyval.for_fin_t).ptr = (yyvsp[0].exprval_t).ptr;
    (yyval.for_fin_t).num = (yyvsp[0].exprval_t).num;
}
#line 2362 "src/parser.c"
    break;

  case 73: /* test: test OR M test2  */
#line 956 "bison/parser.y"
{
    complete((yyvsp[-3].boolexpr).false, (yyvsp[-1].intval));
    ListLabel_free((yyvsp[-3].boolexpr).false);
    (yyval.boolexpr).true = concat((yyvsp[-3].boolexpr).true, (yyvsp[0].boolexpr).true);
    (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;
}
#line 2373 "src/parser.c"
    break;

  case 74: /* test: test2  */
#line 962 "bison/parser.y"
        {(yyval.boolexpr).true = (yyvsp[0].boolexpr).true; (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;}
#line 2379 "src/parser.c"
    break;

  case 75: /* test2: test2 AND M test3  */
#line 966 "bison/parser.y"
{
    complete((yyvsp[-3].boolexpr).true, (yyvsp[-1].intval));
    ListLabel_free((yyvsp[-3].boolexpr).true);
    (yyval.boolexpr).false = concat((yyvsp[-3].boolexpr).false, (yyvsp[0].boolexpr).false);
    (yyval.boolexpr).true = (yyvsp[0].boolexpr).true;
}
#line 2390 "src/parser.c"
    break;

  case 76: /* test2: test3  */
#line 972 "bison/parser.y"
        {(yyval.boolexpr).true = (yyvsp[0].boolexpr).true; (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;}
#line 2396 "src/parser.c"
    break;

  case 77: /* test3: expression_bin op_test expression_bin  */
#line 976 "bison/parser.y"
{
    (yyval.boolexpr).true = NULL;
    (yyval.boolexpr).false = NULL;

    (yyval.boolexpr).true = creerListe(CODE->nextquad);

    struct symbol * q = quad_label();
    CODE->quads[CODE->nextquad].sym3 = q;
    // Generate the code associate with op_test
    switch ((yyvsp[-1].typetest))
    {
    case EQ:
        gencode(CODE, Q_IF_EQ, (yyvsp[-2].exprval_t).ptr, (yyvsp[0].exprval_t).ptr, q);
        break;
    case NEQ:
        gencode(CODE, Q_IF_NEQ, (yyvsp[-2].exprval_t).ptr, (yyvsp[0].exprval_t).ptr, q);
        break;
    case LT:
        gencode(CODE, Q_IF_LT, (yyvsp[-2].exprval_t).ptr, (yyvsp[0].exprval_t).ptr, q);
        break;
    case LE:
        gencode(CODE, Q_IF_LE, (yyvsp[-2].exprval_t).ptr, (yyvsp[0].exprval_t).ptr, q);
        break;
    case GT:
        gencode(CODE, Q_IF_GT, (yyvsp[-2].exprval_t).ptr, (yyvsp[0].exprval_t).ptr, q);
        break;
    case GE:
        gencode(CODE, Q_IF_GE, (yyvsp[-2].exprval_t).ptr, (yyvsp[0].exprval_t).ptr, q);
        break;
    }

    (yyval.boolexpr).false = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());
}
#line 2435 "src/parser.c"
    break;

  case 78: /* test3: expression_bin  */
#line 1011 "bison/parser.y"
{
    (yyval.boolexpr).true = NULL;
    (yyval.boolexpr).false = NULL;

    (yyval.boolexpr).true = creerListe(CODE->nextquad);

    struct symbol * q_zero = symbol_const_int(0);

    struct symbol * q = quad_label();
    CODE->quads[CODE->nextquad].sym3 = q;

    // Generate the code associate with op_test
    gencode(CODE, Q_IF_NEQ, (yyvsp[0].exprval_t).ptr, q_zero, q);
}
#line 2454 "src/parser.c"
    break;

  case 79: /* op_test: EGAL_EGAL  */
#line 1027 "bison/parser.y"
            {(yyval.typetest) = EQ;}
#line 2460 "src/parser.c"
    break;

  case 80: /* op_test: POINT_EXCLAMATION EGAL  */
#line 1028 "bison/parser.y"
                         {(yyval.typetest) = NEQ;}
#line 2466 "src/parser.c"
    break;

  case 81: /* op_test: INFERIEUR  */
#line 1029 "bison/parser.y"
            {(yyval.typetest) = LT;}
#line 2472 "src/parser.c"
    break;

  case 82: /* op_test: INFERIEUR_EGAL  */
#line 1030 "bison/parser.y"
                 {(yyval.typetest) = LE;}
#line 2478 "src/parser.c"
    break;

  case 83: /* op_test: SUPERIEUR  */
#line 1031 "bison/parser.y"
            {(yyval.typetest) = GT;}
#line 2484 "src/parser.c"
    break;

  case 84: /* op_test: SUPERIEUR_EGAL  */
#line 1032 "bison/parser.y"
                 {(yyval.typetest) = GE;}
#line 2490 "src/parser.c"
    break;

  case 85: /* M: %empty  */
#line 1034 "bison/parser.y"
           {(yyval.intval) = CODE->nextquad;}
#line 2496 "src/parser.c"
    break;

  case 86: /* N: %empty  */
#line 1036 "bison/parser.y"
{
    (yyval.N_t).next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());
    (yyval.N_t).quad = CODE->nextquad;
}
#line 2506 "src/parser.c"
    break;


#line 2510 "src/parser.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1041 "bison/parser.y"

void yyerror(const char * msg) {
    fprintf(stderr, "Erreur de syntaxe : %s\n", msg);
}
