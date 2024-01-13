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

     if (expr2.type == MATRIX_TYPE && expr3.type == MATRIX_TYPE)
     {
        if (expr2.ptr->u.id.col != expr3.ptr->u.id.col || expr2.ptr->u.id.row != expr3.ptr->u.id.row)
        {
            fprintf(stderr, "error : dimensional error on matrix %s and %s\n", expr2.ptr->u.id.name, expr3.ptr->u.id.name);
            exit(1);
        }
        expr1.ptr = newtemp_mat(SYMTAB, MATRIX_TYPE, expr2.ptr->u.id.col, expr2.ptr->u.id.row);

        gencode(CODE, Q_DECLARE_MAT, expr1.ptr, NULL, NULL);


        gencode(CODE, k1, expr1.ptr, expr2.ptr, expr3.ptr);
    }
    // Operération avec 1 matrice et 1 float
    else if (expr2.type == MATRIX_TYPE)
    {
        expr1.ptr = newtemp_mat(SYMTAB, MATRIX_TYPE, expr2.ptr->u.id.col, expr2.ptr->u.id.row);

        gencode(CODE, Q_DECLARE_MAT, expr1.ptr, NULL, NULL);
        gencode(CODE, k2, expr1.ptr, expr2.ptr, expr3.ptr);
    }
    // Opératione entre 1 float et 1 matrice
    else if (expr3.type == MATRIX_TYPE)
    {
        expr1.ptr = newtemp_mat(SYMTAB, MATRIX_TYPE, expr3.ptr->u.id.col, expr3.ptr->u.id.row);

        gencode(CODE, Q_DECLARE_MAT, expr1.ptr, NULL, NULL);
        gencode(CODE, k2, expr1.ptr, expr3.ptr, expr2.ptr);
    }
    // Operation entre 2 entiers
    else if (expr2.type == ENTIER && expr3.type == ENTIER)
    {
        // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
        expr1.ptr = newtemp(SYMTAB, expr2.type);
        gencode(CODE, Q_DECLARE, expr1.ptr, NULL, NULL);

        gencode(CODE, k,expr1.ptr,expr2.ptr,expr3.ptr);
    }
    // Operation entre au moins 1 flottant (conversion gérée plus tard)
    else
    {
        expr1.ptr = newtemp(SYMTAB, REEL);
        gencode(CODE, Q_DECLARE, expr1.ptr, NULL, NULL);

        gencode(CODE, k,expr1.ptr,expr2.ptr,expr3.ptr);
    }

    // Utile pour la boucle_for savoir où compléter test.true
    expr1.num = MAX(expr2.num, expr3.num);
    expr1.num += 1;

     return expr1;
 }


#line 203 "src/parser.c"

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
  YYSYMBOL_POINT_EXCLAMATION = 37,         /* POINT_EXCLAMATION  */
  YYSYMBOL_INFERIEUR = 38,                 /* INFERIEUR  */
  YYSYMBOL_INFERIEUR_EGAL = 39,            /* INFERIEUR_EGAL  */
  YYSYMBOL_SUPERIEUR = 40,                 /* SUPERIEUR  */
  YYSYMBOL_SUPERIEUR_EGAL = 41,            /* SUPERIEUR_EGAL  */
  YYSYMBOL_EGAL_EGAL = 42,                 /* EGAL_EGAL  */
  YYSYMBOL_RETURN = 43,                    /* RETURN  */
  YYSYMBOL_POINT = 44,                     /* POINT  */
  YYSYMBOL_PRINT = 45,                     /* PRINT  */
  YYSYMBOL_PRINTF = 46,                    /* PRINTF  */
  YYSYMBOL_PRINTMAT = 47,                  /* PRINTMAT  */
  YYSYMBOL_UEXPR = 48,                     /* UEXPR  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_S = 50,                         /* S  */
  YYSYMBOL_liste_instructions = 51,        /* liste_instructions  */
  YYSYMBOL_instruction = 52,               /* instruction  */
  YYSYMBOL_expression_seule = 53,          /* expression_seule  */
  YYSYMBOL_declaration = 54,               /* declaration  */
  YYSYMBOL_declaration_bin = 55,           /* declaration_bin  */
  YYSYMBOL_declaration_mat = 56,           /* declaration_mat  */
  YYSYMBOL_id_matrix = 57,                 /* id_matrix  */
  YYSYMBOL_id_vector = 58,                 /* id_vector  */
  YYSYMBOL_fin_crea_mat = 59,              /* fin_crea_mat  */
  YYSYMBOL_creation_matrix = 60,           /* creation_matrix  */
  YYSYMBOL_creation_matrix_prime = 61,     /* creation_matrix_prime  */
  YYSYMBOL_creation_vector = 62,           /* creation_vector  */
  YYSYMBOL_creation_vector_prime = 63,     /* creation_vector_prime  */
  YYSYMBOL_affectation_bin = 64,           /* affectation_bin  */
  YYSYMBOL_expression_bin = 65,            /* expression_bin  */
  YYSYMBOL_operande = 66,                  /* operande  */
  YYSYMBOL_affectation_mat = 67,           /* affectation_mat  */
  YYSYMBOL_expression_mat = 68,            /* expression_mat  */
  YYSYMBOL_type = 69,                      /* type  */
  YYSYMBOL_condition = 70,                 /* condition  */
  YYSYMBOL_71_1 = 71,                      /* $@1  */
  YYSYMBOL_72_2 = 72,                      /* $@2  */
  YYSYMBOL_condition_suite = 73,           /* condition_suite  */
  YYSYMBOL_74_3 = 74,                      /* $@3  */
  YYSYMBOL_75_4 = 75,                      /* $@4  */
  YYSYMBOL_boucle_while = 76,              /* boucle_while  */
  YYSYMBOL_77_5 = 77,                      /* $@5  */
  YYSYMBOL_78_6 = 78,                      /* $@6  */
  YYSYMBOL_boucle_for = 79,                /* boucle_for  */
  YYSYMBOL_80_7 = 80,                      /* $@7  */
  YYSYMBOL_81_8 = 81,                      /* $@8  */
  YYSYMBOL_for_init = 82,                  /* for_init  */
  YYSYMBOL_for_fin = 83,                   /* for_fin  */
  YYSYMBOL_test = 84,                      /* test  */
  YYSYMBOL_test2 = 85,                     /* test2  */
  YYSYMBOL_test3 = 86,                     /* test3  */
  YYSYMBOL_op_test = 87,                   /* op_test  */
  YYSYMBOL_M = 88,                         /* M  */
  YYSYMBOL_N = 89                          /* N  */
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
#define YYLAST   289

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  231

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
       0,   207,   207,   213,   214,   217,   218,   219,   220,   221,
     223,   225,   227,   228,   229,   231,   235,   236,   239,   240,
     243,   257,   279,   280,   281,   282,   283,   285,   288,   307,
     326,   327,   332,   341,   349,   357,   368,   377,   385,   405,
     408,   411,   414,   417,   428,   440,   441,   443,   456,   469,
     482,   495,   498,   511,   512,   513,   565,   617,   618,   621,
     622,   623,   624,   625,   626,   627,   640,   641,   642,   643,
     644,   662,   663,   667,   668,   666,   693,   694,   695,   694,
     705,   706,   704,   722,   726,   722,   746,   753,   769,   782,
     802,   809,   812,   819,   822,   857,   874,   875,   876,   877,
     878,   879,   881,   882
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
  "APOSTROPHE", "GUILLEMET", "MAIN", "POINT_EXCLAMATION", "INFERIEUR",
  "INFERIEUR_EGAL", "SUPERIEUR", "SUPERIEUR_EGAL", "EGAL_EGAL", "RETURN",
  "POINT", "PRINT", "PRINTF", "PRINTMAT", "UEXPR", "$accept", "S",
  "liste_instructions", "instruction", "expression_seule", "declaration",
  "declaration_bin", "declaration_mat", "id_matrix", "id_vector",
  "fin_crea_mat", "creation_matrix", "creation_matrix_prime",
  "creation_vector", "creation_vector_prime", "affectation_bin",
  "expression_bin", "operande", "affectation_mat", "expression_mat",
  "type", "condition", "$@1", "$@2", "condition_suite", "$@3", "$@4",
  "boucle_while", "$@5", "$@6", "boucle_for", "$@7", "$@8", "for_init",
  "for_fin", "test", "test2", "test3", "op_test", "M", "N", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-195)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-85)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,     1,    34,    51,  -195,    58,    61,   127,   119,  -195,
    -195,  -195,  -195,    75,    72,    74,    81,    17,   158,   194,
     202,   158,    17,    97,   107,   122,    77,  -195,  -195,  -195,
    -195,  -195,    32,     7,  -195,   183,   151,  -195,  -195,  -195,
     134,  -195,  -195,   158,   147,   143,   189,  -195,    55,   132,
      17,  -195,  -195,   154,  -195,    17,   205,   205,    17,  -195,
     168,  -195,  -195,   154,  -195,   154,  -195,  -195,  -195,   148,
     205,   211,   192,   214,   127,    17,    17,    17,    17,  -195,
    -195,    71,    71,    71,    71,    -6,    71,    36,    62,   190,
     216,   197,   198,   193,    75,  -195,  -195,   195,  -195,    26,
      -3,   209,  -195,    17,   186,  -195,   199,   200,   201,   196,
    -195,    -4,    -4,  -195,  -195,   104,  -195,    71,   227,   228,
      71,    94,    94,  -195,  -195,    17,  -195,    92,  -195,  -195,
     204,   206,    71,    71,  -195,   179,  -195,  -195,   179,   210,
    -195,  -195,  -195,  -195,  -195,    17,  -195,   203,  -195,    -2,
     212,   234,   207,  -195,   208,   213,   215,   218,  -195,  -195,
     167,  -195,   235,   217,    84,    84,   195,  -195,   205,  -195,
    -195,    32,    17,  -195,    17,   220,    17,   219,  -195,  -195,
    -195,  -195,  -195,  -195,   222,   238,  -195,  -195,   182,   184,
     209,  -195,  -195,  -195,    32,    17,    17,  -195,   223,  -195,
    -195,  -195,  -195,   127,  -195,    32,   -10,  -195,   224,   127,
     241,   225,   226,   231,  -195,   229,   232,   237,  -195,  -195,
     233,  -195,   127,  -195,   230,   127,   236,   239,  -195,   240,
    -195
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,    15,    52,    53,
      54,    71,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,     4,    11,     5,
      18,     9,    16,    51,    10,    17,     0,     6,     7,     8,
       0,    67,    68,     0,     0,     0,     0,    19,     0,     0,
       0,   102,    83,    52,    54,     0,     0,     0,     0,    44,
      52,    43,    66,    52,    47,    52,    48,    45,    59,     0,
       0,     0,     0,     0,    15,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    22,     0,    23,    95,
       0,    91,    93,     0,     0,    46,     0,     0,     0,     0,
       3,    39,    40,    41,    42,    64,    65,     0,     0,     0,
       0,    60,    61,    62,    63,     0,    20,     0,    38,    57,
      56,     0,     0,     0,    34,     0,    31,    37,     0,     0,
      98,    99,   100,   101,    96,     0,   102,     0,   102,     0,
      88,     0,     0,    86,     0,     0,     0,     0,    69,    70,
       0,    58,     0,    29,     0,     0,     0,    24,     0,    25,
      97,    94,     0,   102,     0,     0,     0,     0,   102,    13,
      12,    14,     2,    21,     0,     0,    26,    27,     0,     0,
      90,    73,    92,   102,    89,     0,     0,    55,     0,    32,
      33,    35,    36,    15,    80,    87,     0,    28,   102,    15,
       0,     0,   102,     0,   103,     0,     0,    76,    82,   102,
       0,    75,    15,    77,   102,    15,     0,   102,    85,     0,
      79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -195,  -195,  -194,   164,  -195,  -195,  -195,   159,   242,   243,
     -46,  -195,  -195,    88,  -195,  -195,   -17,    -8,  -195,   -11,
     155,  -195,  -195,  -195,  -195,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,    54,   -95,    93,    95,  -195,   -49,
    -195
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    26,    27,    28,    29,    30,    47,    48,    49,
      96,   135,   166,   138,   168,    31,    32,    33,    34,    35,
      36,    37,   203,   211,   221,   225,   229,    38,   209,   215,
      39,   104,   226,   152,   153,   100,   101,   102,   145,    74,
     217
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      59,    61,   103,    98,    67,    69,   146,    62,   149,   208,
      68,    64,    66,   146,   146,   212,    77,    78,   125,     1,
      53,     9,    54,   210,   147,   175,    87,   126,   224,    79,
      80,   227,    88,    99,     4,    17,    55,     3,    61,    56,
      57,    67,    58,    22,    75,    76,    77,    78,    64,    66,
      75,    76,    77,    78,    75,    76,    77,    78,   111,   112,
     113,   114,   106,   139,   140,   141,   142,   143,   144,   128,
     121,   122,   123,   124,   115,   127,   116,     5,    45,    93,
      81,    82,    83,    84,    46,     6,    99,    94,    95,   167,
     117,     7,   169,   118,   119,   129,   120,   172,    50,   174,
      51,   206,    81,    82,    83,    84,    62,    52,   160,    68,
      81,    82,    83,    84,    83,    84,    94,    95,   186,   187,
      73,   164,   165,    70,   191,   161,    41,    42,   171,   196,
       8,     9,    10,    71,    11,    12,    13,    40,    14,    15,
      16,    41,    42,    43,   204,    17,    18,    44,    72,    19,
      20,    89,    21,    22,    85,    99,    97,    99,    86,   194,
     189,    60,     9,    10,    94,    95,    75,    76,    77,    78,
     222,    90,    23,    24,    25,   105,    17,    18,   205,    99,
      19,    20,    44,    21,    22,    75,    76,    77,    78,   150,
      41,    42,    45,    11,    12,   108,    44,    63,     9,    54,
     183,    81,    82,    83,    84,    65,     9,    54,    53,     9,
      54,    94,    95,   199,   200,   201,   202,   107,   109,   130,
     131,   132,   133,   134,   148,   137,   154,   155,   156,   157,
     158,   159,   162,   173,   170,   163,   176,   177,   110,   184,
     178,   179,   198,   195,   150,   185,   180,   220,   181,   182,
     193,   197,   207,   136,   188,   -74,   214,   -81,   216,   151,
     218,   -84,   219,   223,   213,   190,     0,   228,     0,   192,
     -78,   230,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,    92
};

static const yytype_int16 yycheck[] =
{
      17,    18,    51,    49,    21,    22,    16,    18,   103,   203,
      21,    19,    20,    16,    16,   209,    20,    21,    24,     7,
       3,     4,     5,    33,    27,    27,    43,    33,   222,    22,
      23,   225,    43,    50,     0,    18,    19,    36,    55,    22,
      23,    58,    25,    26,    18,    19,    20,    21,    56,    57,
      18,    19,    20,    21,    18,    19,    20,    21,    75,    76,
      77,    78,    70,    37,    38,    39,    40,    41,    42,    33,
      81,    82,    83,    84,     3,    86,     5,    26,     3,    24,
      18,    19,    20,    21,     9,    27,   103,    32,    33,   135,
      19,    30,   138,    22,    23,    33,    25,   146,    26,   148,
      26,   196,    18,    19,    20,    21,   117,    26,   125,   120,
      18,    19,    20,    21,    20,    21,    32,    33,   164,   165,
      43,   132,   133,    26,   173,    33,    22,    23,   145,   178,
       3,     4,     5,    26,     7,     8,     9,    18,    11,    12,
      13,    22,    23,    24,   193,    18,    19,    28,    26,    22,
      23,     4,    25,    26,     3,   172,    24,   174,    24,   176,
     168,     3,     4,     5,    32,    33,    18,    19,    20,    21,
     219,    28,    45,    46,    47,    27,    18,    19,   195,   196,
      22,    23,    28,    25,    26,    18,    19,    20,    21,     3,
      22,    23,     3,     7,     8,     3,    28,     3,     4,     5,
      33,    18,    19,    20,    21,     3,     4,     5,     3,     4,
       5,    32,    33,    31,    32,    31,    32,     6,     4,    29,
       4,    24,    24,    30,    15,    30,    27,    27,    27,    33,
       3,     3,    28,    30,    24,    29,    24,     3,    74,     4,
      33,    33,     4,    24,     3,    28,    33,    10,    33,    31,
      30,    29,    29,    94,   166,    31,    31,    31,    27,   104,
      31,    31,    30,    30,   210,   172,    -1,    31,    -1,   174,
      31,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    50,    36,     0,    26,    27,    30,     3,     4,
       5,     7,     8,     9,    11,    12,    13,    18,    19,    22,
      23,    25,    26,    45,    46,    47,    51,    52,    53,    54,
      55,    64,    65,    66,    67,    68,    69,    70,    76,    79,
      18,    22,    23,    24,    28,     3,     9,    56,    57,    58,
      26,    26,    26,     3,     5,    19,    22,    23,    25,    65,
       3,    65,    68,     3,    66,     3,    66,    65,    68,    65,
      26,    26,    26,    43,    88,    18,    19,    20,    21,    22,
      23,    18,    19,    20,    21,     3,    24,    65,    68,     4,
      28,    57,    58,    24,    32,    33,    59,    24,    59,    65,
      84,    85,    86,    88,    80,    27,    66,     6,     3,     4,
      52,    65,    65,    65,    65,     3,     5,    19,    22,    23,
      25,    68,    68,    68,    68,    24,    33,    68,    33,    33,
      29,     4,    24,    24,    30,    60,    56,    30,    62,    37,
      38,    39,    40,    41,    42,    87,    16,    27,    15,    84,
       3,    69,    82,    83,    27,    27,    27,    33,     3,     3,
      65,    33,    28,    29,    68,    68,    61,    59,    63,    59,
      24,    65,    88,    30,    88,    27,    24,     3,    33,    33,
      33,    33,    31,    33,     4,    28,    59,    59,    62,    66,
      85,    88,    86,    30,    65,    24,    88,    29,     4,    31,
      32,    31,    32,    71,    88,    65,    84,    29,    51,    77,
      33,    72,    51,    83,    31,    78,    27,    89,    31,    30,
      10,    73,    88,    30,    51,    74,    81,    51,    31,    75,
      31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    56,    56,    56,    56,    57,    58,
      59,    59,    60,    61,    61,    62,    63,    63,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    66,    66,    66,    66,    66,    67,    67,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    71,    72,    70,    73,    74,    75,    73,
      77,    78,    76,    80,    81,    79,    82,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    87,    87,    87,
      87,    87,    88,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,    10,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     5,     5,     0,     1,     1,     1,     2,
       3,     5,     2,     2,     4,     4,     5,     5,     7,     4,
       1,     2,     4,     3,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     2,     2,     2,     3,     2,     2,     2,
       2,     1,     1,     1,     1,     7,     4,     4,     5,     2,
       3,     3,     3,     3,     1,     1,     2,     2,     2,     2,
       2,     1,     1,     0,     0,    12,     0,     0,     0,     6,
       0,     0,    11,     0,     0,    15,     1,     4,     1,     3,
       4,     1,     4,     1,     3,     1,     1,     2,     1,     1,
       1,     1,     0,     0
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
  case 2: /* S: INT MAIN PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE liste_instructions RETURN CONSTANTE_ENTIERE POINT_VIRGULE ACCOLADE_FERMANTE  */
#line 208 "bison/parser.y"
{
    ListLabel_free((yyvsp[-4].instr_type).next);
}
#line 1451 "src/parser.c"
    break;

  case 3: /* liste_instructions: liste_instructions M instruction  */
#line 213 "bison/parser.y"
                                   {complete((yyvsp[-2].instr_type).next, (yyvsp[-1].intval));  ListLabel_free((yyvsp[-2].instr_type).next); (yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1457 "src/parser.c"
    break;

  case 4: /* liste_instructions: instruction  */
#line 214 "bison/parser.y"
              {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1463 "src/parser.c"
    break;

  case 5: /* instruction: declaration  */
#line 217 "bison/parser.y"
              {(yyval.instr_type).next = NULL;}
#line 1469 "src/parser.c"
    break;

  case 6: /* instruction: condition  */
#line 218 "bison/parser.y"
            {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1475 "src/parser.c"
    break;

  case 7: /* instruction: boucle_while  */
#line 219 "bison/parser.y"
               {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1481 "src/parser.c"
    break;

  case 8: /* instruction: boucle_for  */
#line 220 "bison/parser.y"
             {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1487 "src/parser.c"
    break;

  case 9: /* instruction: affectation_bin  */
#line 221 "bison/parser.y"
                  {(yyval.instr_type).next = NULL;}
#line 1493 "src/parser.c"
    break;

  case 15: /* instruction: %empty  */
#line 231 "bison/parser.y"
         {(yyval.instr_type).next = NULL;}
#line 1499 "src/parser.c"
    break;

  case 18: /* declaration: declaration_bin  */
#line 239 "bison/parser.y"
                  {(yyval.instr_type).next = NULL;}
#line 1505 "src/parser.c"
    break;

  case 19: /* declaration: MATRIX declaration_mat  */
#line 240 "bison/parser.y"
                         {(yyval.instr_type).next = NULL;}
#line 1511 "src/parser.c"
    break;

  case 20: /* declaration_bin: type IDENTIFICATEUR POINT_VIRGULE  */
#line 243 "bison/parser.y"
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
#line 1530 "src/parser.c"
    break;

  case 21: /* declaration_bin: type IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE  */
#line 257 "bison/parser.y"
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
#line 1551 "src/parser.c"
    break;

  case 28: /* id_matrix: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 289 "bison/parser.y"
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
}
#line 1572 "src/parser.c"
    break;

  case 29: /* id_vector: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 308 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-3].strval));
    if ( id != NULL )
    {
        fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", (yyvsp[-3].strval));
        exit(1);
    }
    id = id_init((yyvsp[-3].strval), MATRIX_TYPE);

    id->row = (yyvsp[-1].intval);
    id->col = 1;
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, Q_DECLARE_MAT, sym_id,NULL,NULL);
}
#line 1593 "src/parser.c"
    break;

  case 32: /* creation_matrix: ACCOLADE_OUVRANTE creation_matrix_prime creation_vector ACCOLADE_FERMANTE  */
#line 333 "bison/parser.y"
{
    if ((yyvsp[-2].taille_mat_t).row != -1 && (yyvsp[-2].taille_mat_t).row != (yyvsp[-1].taille_mat_t).row)
        fprintf(stderr, "error : incompatible column size\n");

    (yyval.taille_mat_t).col = 1 + (yyvsp[-2].taille_mat_t).col;
    (yyval.taille_mat_t).row = (yyvsp[-2].taille_mat_t).row;
}
#line 1605 "src/parser.c"
    break;

  case 33: /* creation_matrix_prime: creation_matrix_prime creation_vector VIRGULE  */
#line 342 "bison/parser.y"
{
    if ((yyvsp[-2].taille_mat_t).row != -1 && (yyvsp[-2].taille_mat_t).row != (yyvsp[-1].taille_mat_t).row)
        fprintf(stderr, "error : incompatible column size\n");

    (yyval.taille_mat_t).col = 1 + (yyvsp[-1].taille_mat_t).col;
    (yyval.taille_mat_t).row = (yyvsp[-2].taille_mat_t).row;
}
#line 1617 "src/parser.c"
    break;

  case 34: /* creation_matrix_prime: %empty  */
#line 350 "bison/parser.y"
{
    (yyval.taille_mat_t).row = -1;
    (yyval.taille_mat_t).col = 0;
}
#line 1626 "src/parser.c"
    break;

  case 35: /* creation_vector: ACCOLADE_OUVRANTE creation_vector_prime operande ACCOLADE_FERMANTE  */
#line 358 "bison/parser.y"
{
    (yyval.taille_mat_t).row = 1 + (yyvsp[-2].taille_mat_t).row;
    (yyval.taille_mat_t).col = 1;
    // newtemp
    struct symbol * sym_temp = newtemp(SYMTAB, REEL);
    gencode(CODE, Q_DECLARE, sym_temp,NULL,NULL);
    gencode(CODE, COPY, sym_temp, (yyvsp[-1].exprval_t).ptr, NULL);

}
#line 1640 "src/parser.c"
    break;

  case 36: /* creation_vector_prime: creation_vector_prime operande VIRGULE  */
#line 369 "bison/parser.y"
{
    (yyval.taille_mat_t).row = 1 + (yyvsp[-2].taille_mat_t).row;
    (yyval.taille_mat_t).col = 1;
    // newtemp
    struct symbol * sym_temp = newtemp(SYMTAB, REEL);
    gencode(CODE, Q_DECLARE, sym_temp,NULL,NULL);
    gencode(CODE, COPY, sym_temp, (yyvsp[-1].exprval_t).ptr, NULL);
}
#line 1653 "src/parser.c"
    break;

  case 37: /* creation_vector_prime: %empty  */
#line 377 "bison/parser.y"
         {(yyval.taille_mat_t).row = 0; (yyval.taille_mat_t).col = 0;}
#line 1659 "src/parser.c"
    break;

  case 38: /* affectation_bin: IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE  */
#line 385 "bison/parser.y"
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
#line 1681 "src/parser.c"
    break;

  case 39: /* expression_bin: expression_bin PLUS expression_bin  */
#line 405 "bison/parser.y"
                                     {
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, BOP_PLUS, (yyval.exprval_t), (yyvsp[-2].exprval_t), (yyvsp[0].exprval_t));
}
#line 1689 "src/parser.c"
    break;

  case 40: /* expression_bin: expression_bin MOINS expression_bin  */
#line 408 "bison/parser.y"
                                      {
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, BOP_MOINS, (yyval.exprval_t), (yyvsp[-2].exprval_t), (yyvsp[0].exprval_t));
}
#line 1697 "src/parser.c"
    break;

  case 41: /* expression_bin: expression_bin FOIS expression_bin  */
#line 411 "bison/parser.y"
                                     {
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, BOP_MULT, (yyval.exprval_t), (yyvsp[-2].exprval_t), (yyvsp[0].exprval_t));
}
#line 1705 "src/parser.c"
    break;

  case 42: /* expression_bin: expression_bin DIVISE expression_bin  */
#line 414 "bison/parser.y"
                                       {
    (yyval.exprval_t) = expression_gestion(CODE, SYMTAB, BOP_DIVISE, (yyval.exprval_t), (yyvsp[-2].exprval_t), (yyvsp[0].exprval_t));
}
#line 1713 "src/parser.c"
    break;

  case 43: /* expression_bin: MOINS expression_bin  */
#line 417 "bison/parser.y"
                                      {
    (yyval.exprval_t).ptr = newtemp(SYMTAB, (yyvsp[0].exprval_t).type);
    gencode(CODE, Q_DECLARE, (yyval.exprval_t).ptr, NULL, NULL);

    gencode(CODE,UOP_MOINS,(yyval.exprval_t).ptr,(yyvsp[0].exprval_t).ptr,NULL);

    // Type temporaire
    (yyval.exprval_t).type = (yyvsp[0].exprval_t).type;

    (yyval.exprval_t).num = (yyvsp[0].exprval_t).num + 1;
}
#line 1729 "src/parser.c"
    break;

  case 44: /* expression_bin: PLUS expression_bin  */
#line 428 "bison/parser.y"
                                     {
    (yyval.exprval_t).ptr = newtemp(SYMTAB, (yyvsp[0].exprval_t).type);
    gencode(CODE, Q_DECLARE, (yyval.exprval_t).ptr, NULL, NULL);

    gencode(CODE,UOP_PLUS,(yyval.exprval_t).ptr,(yyvsp[0].exprval_t).ptr,NULL);

    // Type temporaire
    (yyval.exprval_t).type = (yyvsp[0].exprval_t).type;

    (yyval.exprval_t).num = (yyvsp[0].exprval_t).num + 1;
}
#line 1745 "src/parser.c"
    break;

  case 45: /* expression_bin: TRANSPOSITION expression_bin  */
#line 440 "bison/parser.y"
                                            {;}
#line 1751 "src/parser.c"
    break;

  case 46: /* expression_bin: PARENTHESE_OUVRANTE expression_bin PARENTHESE_FERMANTE  */
#line 441 "bison/parser.y"
                                                          {(yyval.exprval_t).ptr = (yyvsp[-1].exprval_t).ptr; (yyval.exprval_t).type = (yyvsp[-1].exprval_t).type; (yyval.exprval_t).num = (yyvsp[-1].exprval_t).num;}
#line 1757 "src/parser.c"
    break;

  case 47: /* expression_bin: PLUS_PLUS operande  */
#line 444 "bison/parser.y"
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
#line 1774 "src/parser.c"
    break;

  case 48: /* expression_bin: MOINS_MOINS operande  */
#line 457 "bison/parser.y"
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
#line 1791 "src/parser.c"
    break;

  case 49: /* expression_bin: operande PLUS_PLUS  */
#line 470 "bison/parser.y"
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
#line 1808 "src/parser.c"
    break;

  case 50: /* expression_bin: operande MOINS_MOINS  */
#line 483 "bison/parser.y"
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
#line 1825 "src/parser.c"
    break;

  case 51: /* expression_bin: operande  */
#line 495 "bison/parser.y"
           {(yyval.exprval_t).type = (yyvsp[0].exprval_t).type; (yyval.exprval_t).num = 0;}
#line 1831 "src/parser.c"
    break;

  case 52: /* operande: IDENTIFICATEUR  */
#line 499 "bison/parser.y"
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
#line 1848 "src/parser.c"
    break;

  case 53: /* operande: CONSTANTE_ENTIERE  */
#line 511 "bison/parser.y"
                    {(yyval.exprval_t).ptr = symbol_const_int((int)(yyvsp[0].intval)); (yyval.exprval_t).type = ENTIER;}
#line 1854 "src/parser.c"
    break;

  case 54: /* operande: CONSTANTE_FLOTTANTE  */
#line 512 "bison/parser.y"
                      {(yyval.exprval_t).ptr = symbol_const_float((yyvsp[0].floatval)); (yyval.exprval_t).type = REEL;}
#line 1860 "src/parser.c"
    break;

  case 55: /* operande: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 515 "bison/parser.y"
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
    }

    // Pour obtenir la valeur du tableau
    /* T3 = T1*20 */
    struct symbol * t3 = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, t3, NULL, NULL);

    struct symbol * t3_temp = symbol_const_int(((yyvsp[-4].intval) + 1) * id->col);
    struct symbol * j = symbol_const_int(((yyvsp[-1].intval) + 1));
    /*     T3 = T3+T2 */
    gencode(CODE, BOP_PLUS, t3, j, t3_temp);
    /*     T4 = adr(A) /\* adresse de base de A *\/ */
    struct symbol * t4 = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, t4, NULL, NULL);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, ADRESSE, t4, sym_id, NULL);
    /*     T4 = T4-84 /\* 84 = nbw*21 *\/ */
    struct symbol * nbw_row = symbol_const_int(4 * (id->col + 1));
    gencode(CODE, BOP_MOINS, t4, t4, nbw_row);
    /*     T5 = 4*T3 */
    struct symbol * t5 = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, t5, NULL, NULL);
    struct symbol * nbw = symbol_const_int(4);
    gencode(CODE, BOP_MULT, t5, nbw, t3);
    /*     T6 = T4[T5] /\* = T4+T5 *\/ */
    struct symbol * symbol_composante = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, symbol_composante, NULL, NULL);
    gencode(CODE, BOP_PLUS, symbol_composante, t4, t5);

    (yyval.exprval_t).ptr = symbol_composante;
    (yyval.exprval_t).type = REEL;
}
#line 1915 "src/parser.c"
    break;

  case 56: /* operande: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 566 "bison/parser.y"
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

    // Pour obtenir la valeur du tableau
    /* T3 = T1*20 */
    struct symbol * t3 = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, t3, NULL, NULL);
    struct symbol * t3_temp = symbol_const_int((yyvsp[-1].intval) * id->col);
    struct symbol * j = symbol_const_int(1);
    /*     T3 = T3+T2 */
    gencode(CODE, BOP_PLUS, t3, j, t3_temp);
    /*     T4 = adr(A) /\* adresse de base de A *\/ */
    struct symbol * t4 = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, t4, NULL, NULL);
    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, ADRESSE, t4, sym_id, NULL);
    /*     T4 = T4-84 /\* 84 = nbw*21 *\/ */
    struct symbol * nbw_row = symbol_const_int(4 * (id->col + 1));
    gencode(CODE, BOP_MOINS, t4, t4, nbw_row);
    /*     T5 = 4*T3 */
    struct symbol * t5 = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, t5, NULL, NULL);
    struct symbol * nbw = symbol_const_int(4);
    gencode(CODE, BOP_MULT, t5, nbw, t3);
    /*     T6 = T4[T5] /\* = T4+T5 *\/ */
    struct symbol * symbol_composante = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, symbol_composante, NULL, NULL);
    gencode(CODE, BOP_PLUS, symbol_composante, t4, t5);

    (yyval.exprval_t).ptr = symbol_composante;
    (yyval.exprval_t).type = REEL;
}
#line 1967 "src/parser.c"
    break;

  case 59: /* expression_mat: TRANSPOSITION expression_mat  */
#line 621 "bison/parser.y"
                                           {;}
#line 1973 "src/parser.c"
    break;

  case 71: /* type: INT  */
#line 662 "bison/parser.y"
      {(yyval.typeval) = ENTIER;}
#line 1979 "src/parser.c"
    break;

  case 72: /* type: FLOAT  */
#line 663 "bison/parser.y"
        {(yyval.typeval) = REEL;}
#line 1985 "src/parser.c"
    break;

  case 73: /* $@1: %empty  */
#line 667 "bison/parser.y"
  { stack_id_push(SYMTAB);}
#line 1991 "src/parser.c"
    break;

  case 74: /* $@2: %empty  */
#line 668 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1997 "src/parser.c"
    break;

  case 75: /* condition: IF PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M $@1 liste_instructions $@2 ACCOLADE_FERMANTE N condition_suite  */
#line 670 "bison/parser.y"
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
#line 2023 "src/parser.c"
    break;

  case 76: /* condition_suite: %empty  */
#line 693 "bison/parser.y"
         {(yyval.instr_type).next = NULL;}
#line 2029 "src/parser.c"
    break;

  case 77: /* $@3: %empty  */
#line 694 "bison/parser.y"
                          { stack_id_push(SYMTAB);}
#line 2035 "src/parser.c"
    break;

  case 78: /* $@4: %empty  */
#line 695 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 2041 "src/parser.c"
    break;

  case 79: /* condition_suite: ELSE ACCOLADE_OUVRANTE $@3 liste_instructions $@4 ACCOLADE_FERMANTE  */
#line 696 "bison/parser.y"
{
    (yyval.instr_type).next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());

    (yyval.instr_type).next = concat((yyval.instr_type).next, (yyvsp[-2].instr_type).next);
}
#line 2052 "src/parser.c"
    break;

  case 80: /* $@5: %empty  */
#line 705 "bison/parser.y"
                    {stack_id_push(SYMTAB);}
#line 2058 "src/parser.c"
    break;

  case 81: /* $@6: %empty  */
#line 706 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 2064 "src/parser.c"
    break;

  case 82: /* boucle_while: WHILE PARENTHESE_OUVRANTE M test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M $@5 liste_instructions $@6 ACCOLADE_FERMANTE  */
#line 707 "bison/parser.y"
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
#line 2081 "src/parser.c"
    break;

  case 83: /* $@7: %empty  */
#line 722 "bison/parser.y"
                          {stack_id_push(SYMTAB);}
#line 2087 "src/parser.c"
    break;

  case 84: /* $@8: %empty  */
#line 726 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 2093 "src/parser.c"
    break;

  case 85: /* boucle_for: FOR PARENTHESE_OUVRANTE $@7 for_init POINT_VIRGULE M test POINT_VIRGULE for_fin PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M liste_instructions $@8 ACCOLADE_FERMANTE  */
#line 727 "bison/parser.y"
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
#line 2115 "src/parser.c"
    break;

  case 86: /* for_init: for_fin  */
#line 747 "bison/parser.y"
{
    if ((yyvsp[0].for_fin_t).ptr != NULL)
    {
        gencode(CODE,COPY,(yyvsp[0].for_fin_t).id,(yyvsp[0].for_fin_t).ptr,NULL);
    }
}
#line 2126 "src/parser.c"
    break;

  case 87: /* for_init: type IDENTIFICATEUR EGAL expression_bin  */
#line 754 "bison/parser.y"
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
    gencode(CODE,COPY,sym_id,(yyvsp[0].exprval_t).ptr,NULL);
}
#line 2144 "src/parser.c"
    break;

  case 88: /* for_fin: IDENTIFICATEUR  */
#line 770 "bison/parser.y"
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
#line 2161 "src/parser.c"
    break;

  case 89: /* for_fin: IDENTIFICATEUR EGAL expression_bin  */
#line 783 "bison/parser.y"
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
#line 2183 "src/parser.c"
    break;

  case 90: /* test: test OR M test2  */
#line 803 "bison/parser.y"
{
    complete((yyvsp[-3].boolexpr).false, (yyvsp[-1].intval));
    ListLabel_free((yyvsp[-3].boolexpr).false);
    (yyval.boolexpr).true = concat((yyvsp[-3].boolexpr).true, (yyvsp[0].boolexpr).true);
    (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;
}
#line 2194 "src/parser.c"
    break;

  case 91: /* test: test2  */
#line 809 "bison/parser.y"
        {(yyval.boolexpr).true = (yyvsp[0].boolexpr).true; (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;}
#line 2200 "src/parser.c"
    break;

  case 92: /* test2: test2 AND M test3  */
#line 813 "bison/parser.y"
{
    complete((yyvsp[-3].boolexpr).true, (yyvsp[-1].intval));
    ListLabel_free((yyvsp[-3].boolexpr).true);
    (yyval.boolexpr).false = concat((yyvsp[-3].boolexpr).false, (yyvsp[0].boolexpr).false);
    (yyval.boolexpr).true = (yyvsp[0].boolexpr).true;
}
#line 2211 "src/parser.c"
    break;

  case 93: /* test2: test3  */
#line 819 "bison/parser.y"
        {(yyval.boolexpr).true = (yyvsp[0].boolexpr).true; (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;}
#line 2217 "src/parser.c"
    break;

  case 94: /* test3: expression_bin op_test expression_bin  */
#line 823 "bison/parser.y"
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
#line 2256 "src/parser.c"
    break;

  case 95: /* test3: expression_bin  */
#line 858 "bison/parser.y"
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
#line 2275 "src/parser.c"
    break;

  case 96: /* op_test: EGAL_EGAL  */
#line 874 "bison/parser.y"
            {(yyval.typetest) = EQ;}
#line 2281 "src/parser.c"
    break;

  case 97: /* op_test: POINT_EXCLAMATION EGAL  */
#line 875 "bison/parser.y"
                         {(yyval.typetest) = NEQ;}
#line 2287 "src/parser.c"
    break;

  case 98: /* op_test: INFERIEUR  */
#line 876 "bison/parser.y"
            {(yyval.typetest) = LT;}
#line 2293 "src/parser.c"
    break;

  case 99: /* op_test: INFERIEUR_EGAL  */
#line 877 "bison/parser.y"
                 {(yyval.typetest) = LE;}
#line 2299 "src/parser.c"
    break;

  case 100: /* op_test: SUPERIEUR  */
#line 878 "bison/parser.y"
            {(yyval.typetest) = GT;}
#line 2305 "src/parser.c"
    break;

  case 101: /* op_test: SUPERIEUR_EGAL  */
#line 879 "bison/parser.y"
                 {(yyval.typetest) = GE;}
#line 2311 "src/parser.c"
    break;

  case 102: /* M: %empty  */
#line 881 "bison/parser.y"
           {(yyval.intval) = CODE->nextquad;}
#line 2317 "src/parser.c"
    break;

  case 103: /* N: %empty  */
#line 883 "bison/parser.y"
{
    (yyval.N_t).next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());
    (yyval.N_t).quad = CODE->nextquad;
}
#line 2327 "src/parser.c"
    break;


#line 2331 "src/parser.c"

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

#line 888 "bison/parser.y"

void yyerror(const char * msg) {
    fprintf(stderr, "Erreur de syntaxe : %s\n", msg);

}
