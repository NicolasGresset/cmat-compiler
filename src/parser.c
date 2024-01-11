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


#line 108 "src/parser.c"

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
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_MATRIX = 8,                     /* MATRIX  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_CONSTANTE_CARACTERE = 13,       /* CONSTANTE_CARACTERE  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_NOT = 16,                       /* NOT  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MOINS = 18,                     /* MOINS  */
  YYSYMBOL_FOIS = 19,                      /* FOIS  */
  YYSYMBOL_DIVISE = 20,                    /* DIVISE  */
  YYSYMBOL_PLUS_PLUS = 21,                 /* PLUS_PLUS  */
  YYSYMBOL_MOINS_MOINS = 22,               /* MOINS_MOINS  */
  YYSYMBOL_EGAL = 23,                      /* EGAL  */
  YYSYMBOL_TRANSPOSITION = 24,             /* TRANSPOSITION  */
  YYSYMBOL_PARENTHESE_OUVRANTE = 25,       /* PARENTHESE_OUVRANTE  */
  YYSYMBOL_PARENTHESE_FERMANTE = 26,       /* PARENTHESE_FERMANTE  */
  YYSYMBOL_CROCHET_OUVRANT = 27,           /* CROCHET_OUVRANT  */
  YYSYMBOL_CROCHET_FERMANT = 28,           /* CROCHET_FERMANT  */
  YYSYMBOL_ACCOLADE_OUVRANTE = 29,         /* ACCOLADE_OUVRANTE  */
  YYSYMBOL_ACCOLADE_FERMANTE = 30,         /* ACCOLADE_FERMANTE  */
  YYSYMBOL_VIRGULE = 31,                   /* VIRGULE  */
  YYSYMBOL_POINT_VIRGULE = 32,             /* POINT_VIRGULE  */
  YYSYMBOL_APOSTROPHE = 33,                /* APOSTROPHE  */
  YYSYMBOL_GUILLEMET = 34,                 /* GUILLEMET  */
  YYSYMBOL_MAIN = 35,                      /* MAIN  */
  YYSYMBOL_POINT_EXCLAMATION = 36,         /* POINT_EXCLAMATION  */
  YYSYMBOL_INFERIEUR = 37,                 /* INFERIEUR  */
  YYSYMBOL_INFERIEUR_EGAL = 38,            /* INFERIEUR_EGAL  */
  YYSYMBOL_SUPERIEUR = 39,                 /* SUPERIEUR  */
  YYSYMBOL_SUPERIEUR_EGAL = 40,            /* SUPERIEUR_EGAL  */
  YYSYMBOL_EGAL_EGAL = 41,                 /* EGAL_EGAL  */
  YYSYMBOL_UEXPR = 42,                     /* UEXPR  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_S = 44,                         /* S  */
  YYSYMBOL_liste_instructions = 45,        /* liste_instructions  */
  YYSYMBOL_instruction = 46,               /* instruction  */
  YYSYMBOL_declaration = 47,               /* declaration  */
  YYSYMBOL_declaration_bin = 48,           /* declaration_bin  */
  YYSYMBOL_declaration_mat = 49,           /* declaration_mat  */
  YYSYMBOL_id_matrix = 50,                 /* id_matrix  */
  YYSYMBOL_id_vector = 51,                 /* id_vector  */
  YYSYMBOL_fin_crea_mat = 52,              /* fin_crea_mat  */
  YYSYMBOL_creation_matrix = 53,           /* creation_matrix  */
  YYSYMBOL_creation_matrix_prime = 54,     /* creation_matrix_prime  */
  YYSYMBOL_creation_vector = 55,           /* creation_vector  */
  YYSYMBOL_creation_vector_prime = 56,     /* creation_vector_prime  */
  YYSYMBOL_affectation_bin = 57,           /* affectation_bin  */
  YYSYMBOL_expression_bin = 58,            /* expression_bin  */
  YYSYMBOL_operande = 59,                  /* operande  */
  YYSYMBOL_expression_mat = 60,            /* expression_mat  */
  YYSYMBOL_type = 61,                      /* type  */
  YYSYMBOL_condition = 62,                 /* condition  */
  YYSYMBOL_63_1 = 63,                      /* $@1  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_condition_suite = 65,           /* condition_suite  */
  YYSYMBOL_66_3 = 66,                      /* $@3  */
  YYSYMBOL_67_4 = 67,                      /* $@4  */
  YYSYMBOL_boucle_while = 68,              /* boucle_while  */
  YYSYMBOL_69_5 = 69,                      /* $@5  */
  YYSYMBOL_70_6 = 70,                      /* $@6  */
  YYSYMBOL_boucle_for = 71,                /* boucle_for  */
  YYSYMBOL_72_7 = 72,                      /* $@7  */
  YYSYMBOL_73_8 = 73,                      /* $@8  */
  YYSYMBOL_for_init = 74,                  /* for_init  */
  YYSYMBOL_for_fin = 75,                   /* for_fin  */
  YYSYMBOL_test = 76,                      /* test  */
  YYSYMBOL_test2 = 77,                     /* test2  */
  YYSYMBOL_test3 = 78,                     /* test3  */
  YYSYMBOL_op_test = 79,                   /* op_test  */
  YYSYMBOL_M = 80,                         /* M  */
  YYSYMBOL_N = 81                          /* N  */
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
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  197

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   116,   116,   122,   123,   126,   127,   128,   129,   130,
     133,   134,   137,   151,   173,   174,   175,   176,   177,   179,
     182,   201,   220,   221,   226,   235,   243,   251,   262,   271,
     279,   299,   310,   320,   330,   340,   349,   358,   359,   360,
     362,   373,   384,   395,   406,   409,   427,   428,   429,   475,
     523,   524,   525,   526,   527,   528,   529,   542,   543,   544,
     545,   546,   553,   554,   558,   559,   557,   584,   585,   586,
     585,   596,   597,   595,   613,   617,   613,   637,   644,   660,
     673,   693,   700,   703,   710,   713,   748,   765,   766,   767,
     768,   769,   770,   772,   773
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
  "CONSTANTE_ENTIERE", "CONSTANTE_FLOTTANTE", "INT", "FLOAT", "MATRIX",
  "ELSE", "IF", "WHILE", "FOR", "CONSTANTE_CARACTERE", "AND", "OR", "NOT",
  "PLUS", "MOINS", "FOIS", "DIVISE", "PLUS_PLUS", "MOINS_MOINS", "EGAL",
  "TRANSPOSITION", "PARENTHESE_OUVRANTE", "PARENTHESE_FERMANTE",
  "CROCHET_OUVRANT", "CROCHET_FERMANT", "ACCOLADE_OUVRANTE",
  "ACCOLADE_FERMANTE", "VIRGULE", "POINT_VIRGULE", "APOSTROPHE",
  "GUILLEMET", "MAIN", "POINT_EXCLAMATION", "INFERIEUR", "INFERIEUR_EGAL",
  "SUPERIEUR", "SUPERIEUR_EGAL", "EGAL_EGAL", "UEXPR", "$accept", "S",
  "liste_instructions", "instruction", "declaration", "declaration_bin",
  "declaration_mat", "id_matrix", "id_vector", "fin_crea_mat",
  "creation_matrix", "creation_matrix_prime", "creation_vector",
  "creation_vector_prime", "affectation_bin", "expression_bin", "operande",
  "expression_mat", "type", "condition", "$@1", "$@2", "condition_suite",
  "$@3", "$@4", "boucle_while", "$@5", "$@6", "boucle_for", "$@7", "$@8",
  "for_init", "for_fin", "test", "test2", "test3", "op_test", "M", "N", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-161)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-76)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   -17,    39,    21,  -161,    16,    32,   102,    27,  -161,
    -161,    95,    48,    59,    61,    64,  -161,  -161,  -161,  -161,
     101,  -161,  -161,  -161,     8,    79,   139,  -161,    68,    88,
       8,  -161,  -161,  -161,   102,    -8,    94,  -161,  -161,     8,
       8,   130,   130,     8,     8,     8,    63,   115,   141,   129,
     132,    96,    95,  -161,  -161,   124,  -161,    38,    -7,   142,
    -161,     8,   120,  -161,     8,  -161,   153,  -161,  -161,  -161,
    -161,  -161,    98,  -161,     8,     8,     8,     8,  -161,  -161,
    -161,   133,    42,    42,  -161,   107,  -161,  -161,   107,   135,
    -161,  -161,  -161,  -161,  -161,     8,  -161,   134,  -161,    12,
     136,   157,   137,  -161,    70,   138,  -161,   121,   121,  -161,
    -161,   140,   122,  -161,    42,   159,   161,    42,    17,    17,
     124,  -161,   130,  -161,  -161,   111,     8,  -161,     8,   143,
       8,   145,  -161,  -161,   144,   166,  -161,  -161,  -161,  -161,
    -161,  -161,    42,    42,    42,    42,  -161,  -161,   116,   118,
     142,  -161,  -161,  -161,   111,     8,     8,   169,   146,   131,
     131,  -161,  -161,  -161,  -161,  -161,  -161,   102,  -161,   111,
      -9,   147,  -161,   148,   102,   162,  -161,   149,   150,   151,
    -161,   152,   154,   167,  -161,  -161,   155,  -161,   102,  -161,
     156,   102,   158,   160,  -161,   163,  -161
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,    62,
      63,     0,     0,     0,     0,    93,     4,     5,    10,     9,
       0,     6,     7,     8,     0,     0,     0,    11,     0,     0,
       0,    93,    74,     2,     0,     0,    45,    46,    47,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
       0,     0,     0,    22,    14,     0,    15,    86,     0,    82,
      84,     0,     0,     3,     0,    12,     0,    36,    35,    40,
      41,    38,     0,    37,     0,     0,     0,     0,    30,    42,
      43,     0,     0,     0,    26,     0,    23,    29,     0,     0,
      89,    90,    91,    92,    87,     0,    93,     0,    93,     0,
      79,     0,     0,    77,     0,     0,    39,    31,    32,    33,
      34,    21,    55,    56,     0,     0,     0,     0,     0,     0,
       0,    16,     0,    17,    88,    85,     0,    93,     0,     0,
       0,     0,    93,    13,    49,     0,    58,    59,    57,    60,
      61,    50,     0,     0,     0,     0,    18,    19,     0,     0,
      81,    64,    83,    93,    80,     0,     0,     0,     0,    51,
      52,    53,    54,    24,    25,    27,    28,     0,    71,    78,
       0,     0,    20,    93,     0,     0,    48,     0,    93,     0,
      94,     0,     0,    67,    73,    93,     0,    66,     0,    68,
      93,     0,     0,    93,    76,     0,    70
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -161,  -161,  -160,   164,  -161,  -161,   165,   168,   170,   -26,
    -161,  -161,    65,  -161,  -161,   -23,   -37,   -74,   119,  -161,
    -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,
    -161,  -161,    14,   -59,    66,    67,  -161,   -31,  -161
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    15,    16,    17,    18,    27,    28,    29,    54,
      85,   120,    88,   122,    19,    57,    47,   118,    20,    21,
     167,   177,   187,   191,   195,    22,   174,   181,    23,    62,
     192,   102,   103,    58,    59,    60,    95,    34,   183
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    46,    99,    56,    69,    70,    96,   173,    96,   119,
       1,    36,    37,    38,   178,    64,    67,    68,     3,    97,
      71,    72,    73,   175,    65,    39,    40,    96,   190,    41,
      42,   193,    43,    44,   142,   143,   144,   145,   129,     4,
     138,   104,     6,   141,    45,   112,     5,   113,    52,    53,
      24,   107,   108,   109,   110,    74,    75,    76,    77,   121,
     114,     7,   123,   115,   116,   126,   117,   128,   159,   160,
     161,   162,   125,    30,    89,    90,    91,    92,    93,    94,
      74,    75,    76,    77,    31,   149,    32,    74,    75,    76,
      77,    51,   146,   147,    33,    78,   151,   170,    25,    52,
      53,   156,   133,    26,    35,     8,    48,   154,     9,    10,
      11,    55,    12,    13,    14,    74,    75,    76,    77,    52,
      53,    66,   168,   100,   106,    84,     9,    10,    74,    75,
      76,    77,   169,    36,    37,    38,    79,    80,    52,    53,
      76,    77,    25,   136,   137,    81,   163,   164,   165,   166,
     144,   145,    82,    87,   188,    83,    98,   105,   124,   130,
     131,   111,   139,   127,   140,   100,   134,   135,   155,   132,
     158,   157,   153,   171,   172,   176,   186,   182,   -65,   180,
     -72,   101,   184,   185,   189,   148,   -75,     0,   194,   179,
     -69,     0,   150,   196,    49,   152,    50,     0,    63,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    86
};

static const yytype_int16 yycheck[] =
{
      31,    24,    61,    29,    41,    42,    15,   167,    15,    83,
       6,     3,     4,     5,   174,    23,    39,    40,    35,    26,
      43,    44,    45,    32,    32,    17,    18,    15,   188,    21,
      22,   191,    24,    25,    17,    18,    19,    20,    26,     0,
     114,    64,    26,   117,    36,     3,    25,     5,    31,    32,
      23,    74,    75,    76,    77,    17,    18,    19,    20,    85,
      18,    29,    88,    21,    22,    96,    24,    98,   142,   143,
     144,   145,    95,    25,    36,    37,    38,    39,    40,    41,
      17,    18,    19,    20,    25,   122,    25,    17,    18,    19,
      20,    23,   118,   119,    30,    32,   127,   156,     3,    31,
      32,   132,    32,     8,     3,     3,    27,   130,     6,     7,
       8,    23,    10,    11,    12,    17,    18,    19,    20,    31,
      32,    27,   153,     3,    26,    29,     6,     7,    17,    18,
      19,    20,   155,     3,     4,     5,    21,    22,    31,    32,
      19,    20,     3,    21,    22,     4,    30,    31,    30,    31,
      19,    20,    23,    29,   185,    23,    14,     4,    23,    23,
       3,    28,     3,    29,     3,     3,    28,    27,    23,    32,
       4,    27,    29,     4,    28,    28,     9,    26,    30,    30,
      30,    62,    30,    29,    29,   120,    30,    -1,    30,   175,
      30,    -1,   126,    30,    26,   128,    26,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    44,    35,     0,    25,    26,    29,     3,     6,
       7,     8,    10,    11,    12,    45,    46,    47,    48,    57,
      61,    62,    68,    71,    23,     3,     8,    49,    50,    51,
      25,    25,    25,    30,    80,     3,     3,     4,     5,    17,
      18,    21,    22,    24,    25,    36,    58,    59,    27,    50,
      51,    23,    31,    32,    52,    23,    52,    58,    76,    77,
      78,    80,    72,    46,    23,    32,    27,    58,    58,    59,
      59,    58,    58,    58,    17,    18,    19,    20,    32,    21,
      22,     4,    23,    23,    29,    53,    49,    29,    55,    36,
      37,    38,    39,    40,    41,    79,    15,    26,    14,    76,
       3,    61,    74,    75,    58,     4,    26,    58,    58,    58,
      58,    28,     3,     5,    18,    21,    22,    24,    60,    60,
      54,    52,    56,    52,    23,    58,    80,    29,    80,    26,
      23,     3,    32,    32,    28,    27,    21,    22,    60,     3,
       3,    60,    17,    18,    19,    20,    52,    52,    55,    59,
      77,    80,    78,    29,    58,    23,    80,    27,     4,    60,
      60,    60,    60,    30,    31,    30,    31,    63,    80,    58,
      76,     4,    28,    45,    69,    32,    28,    64,    45,    75,
      30,    70,    26,    81,    30,    29,     9,    65,    80,    29,
      45,    66,    73,    45,    30,    67,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      47,    47,    48,    48,    49,    49,    49,    49,    49,    49,
      50,    51,    52,    52,    53,    54,    54,    55,    56,    56,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    59,    59,    59,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    61,    63,    64,    62,    65,    66,    67,
      65,    69,    70,    68,    72,    73,    71,    74,    74,    75,
      75,    76,    76,    77,    77,    78,    78,    79,    79,    79,
      79,    79,    79,    80,    81
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     5,     2,     2,     4,     4,     5,     5,
       7,     4,     1,     2,     4,     3,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     2,     2,     2,     2,     3,
       2,     2,     2,     2,     1,     1,     1,     1,     7,     4,
       2,     3,     3,     3,     3,     1,     1,     2,     2,     2,
       2,     2,     1,     1,     0,     0,    12,     0,     0,     0,
       6,     0,     0,    11,     0,     0,    15,     1,     4,     1,
       3,     4,     1,     4,     1,     3,     1,     1,     2,     1,
       1,     1,     1,     0,     0
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
  case 2: /* S: INT MAIN PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE  */
#line 117 "bison/parser.y"
{
    ListLabel_free((yyvsp[-1].instr_type).next);
}
#line 1314 "src/parser.c"
    break;

  case 3: /* liste_instructions: liste_instructions M instruction  */
#line 122 "bison/parser.y"
                                   {complete((yyvsp[-2].instr_type).next, (yyvsp[-1].intval));  ListLabel_free((yyvsp[-2].instr_type).next); (yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1320 "src/parser.c"
    break;

  case 4: /* liste_instructions: instruction  */
#line 123 "bison/parser.y"
              {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1326 "src/parser.c"
    break;

  case 5: /* instruction: declaration  */
#line 126 "bison/parser.y"
              {(yyval.instr_type).next = NULL;}
#line 1332 "src/parser.c"
    break;

  case 6: /* instruction: condition  */
#line 127 "bison/parser.y"
            {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1338 "src/parser.c"
    break;

  case 7: /* instruction: boucle_while  */
#line 128 "bison/parser.y"
               {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1344 "src/parser.c"
    break;

  case 8: /* instruction: boucle_for  */
#line 129 "bison/parser.y"
             {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1350 "src/parser.c"
    break;

  case 9: /* instruction: affectation_bin  */
#line 130 "bison/parser.y"
                  {(yyval.instr_type).next = NULL;}
#line 1356 "src/parser.c"
    break;

  case 10: /* declaration: declaration_bin  */
#line 133 "bison/parser.y"
                  {(yyval.instr_type).next = NULL;}
#line 1362 "src/parser.c"
    break;

  case 11: /* declaration: MATRIX declaration_mat  */
#line 134 "bison/parser.y"
                         {(yyval.instr_type).next = NULL;}
#line 1368 "src/parser.c"
    break;

  case 12: /* declaration_bin: type IDENTIFICATEUR POINT_VIRGULE  */
#line 137 "bison/parser.y"
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
#line 1387 "src/parser.c"
    break;

  case 13: /* declaration_bin: type IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE  */
#line 151 "bison/parser.y"
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
    gencode(CODE,COPY,sym_id,(yyvsp[-1].exprval).ptr,NULL);

 }
#line 1408 "src/parser.c"
    break;

  case 20: /* id_matrix: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 183 "bison/parser.y"
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
#line 1429 "src/parser.c"
    break;

  case 21: /* id_vector: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 202 "bison/parser.y"
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
#line 1450 "src/parser.c"
    break;

  case 24: /* creation_matrix: ACCOLADE_OUVRANTE creation_matrix_prime creation_vector ACCOLADE_FERMANTE  */
#line 227 "bison/parser.y"
{
    if ((yyvsp[-2].taille_mat_t).row != -1 && (yyvsp[-2].taille_mat_t).row != (yyvsp[-1].taille_mat_t).row)
        fprintf(stderr, "error : incompatible column size\n");

    (yyval.taille_mat_t).col = 1 + (yyvsp[-2].taille_mat_t).col;
    (yyval.taille_mat_t).row = (yyvsp[-2].taille_mat_t).row;
}
#line 1462 "src/parser.c"
    break;

  case 25: /* creation_matrix_prime: creation_matrix_prime creation_vector VIRGULE  */
#line 236 "bison/parser.y"
{
    if ((yyvsp[-2].taille_mat_t).row != -1 && (yyvsp[-2].taille_mat_t).row != (yyvsp[-1].taille_mat_t).row)
        fprintf(stderr, "error : incompatible column size\n");

    (yyval.taille_mat_t).col = 1 + (yyvsp[-1].taille_mat_t).col;
    (yyval.taille_mat_t).row = (yyvsp[-2].taille_mat_t).row;
}
#line 1474 "src/parser.c"
    break;

  case 26: /* creation_matrix_prime: %empty  */
#line 244 "bison/parser.y"
{
    (yyval.taille_mat_t).row = -1;
    (yyval.taille_mat_t).col = 0;
}
#line 1483 "src/parser.c"
    break;

  case 27: /* creation_vector: ACCOLADE_OUVRANTE creation_vector_prime operande ACCOLADE_FERMANTE  */
#line 252 "bison/parser.y"
{
    (yyval.taille_mat_t).row = 1 + (yyvsp[-2].taille_mat_t).row;
    (yyval.taille_mat_t).col = 1;
    // newtemp
    struct symbol * sym_temp = newtemp(SYMTAB, REEL);
    gencode(CODE, Q_DECLARE, sym_temp,NULL,NULL);
    gencode(CODE, COPY, sym_temp, (yyvsp[-1].exprval).ptr, NULL);

}
#line 1497 "src/parser.c"
    break;

  case 28: /* creation_vector_prime: creation_vector_prime operande VIRGULE  */
#line 263 "bison/parser.y"
{
    (yyval.taille_mat_t).row = 1 + (yyvsp[-2].taille_mat_t).row;
    (yyval.taille_mat_t).col = 1;
    // newtemp
    struct symbol * sym_temp = newtemp(SYMTAB, REEL);
    gencode(CODE, Q_DECLARE, sym_temp,NULL,NULL);
    gencode(CODE, COPY, sym_temp, (yyvsp[-1].exprval).ptr, NULL);
}
#line 1510 "src/parser.c"
    break;

  case 29: /* creation_vector_prime: %empty  */
#line 271 "bison/parser.y"
         {(yyval.taille_mat_t).row = 0; (yyval.taille_mat_t).col = 0;}
#line 1516 "src/parser.c"
    break;

  case 30: /* affectation_bin: IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE  */
#line 279 "bison/parser.y"
                                                   {
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-3].strval));
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", (yyvsp[-3].strval));
        exit(1);
    }
    if (id->type != (yyvsp[-1].exprval).type)
    {
        fprintf(stderr, "error: incompatible types\n");
        //exit(1);
    }

    struct symbol *  sym_id = symbol_id(*id);
    gencode(CODE,COPY,sym_id,(yyvsp[-1].exprval).ptr,NULL);

 }
#line 1538 "src/parser.c"
    break;

  case 31: /* expression_bin: expression_bin PLUS expression_bin  */
#line 299 "bison/parser.y"
                                     {
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-2].exprval).type);
    gencode(CODE,BOP_PLUS,(yyval.exprval).ptr,(yyvsp[-2].exprval).ptr,(yyvsp[0].exprval).ptr);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval).type = (yyvsp[-2].exprval).type;
    // Utile pour la boucle_for savoir où compléter test.true
    (yyval.exprval).num = MAX((yyvsp[-2].exprval).num, (yyvsp[0].exprval).num);
    (yyval.exprval).num += 1;
}
#line 1554 "src/parser.c"
    break;

  case 32: /* expression_bin: expression_bin MOINS expression_bin  */
#line 310 "bison/parser.y"
                                      {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-2].exprval).type);
    gencode(CODE,BOP_MOINS,(yyval.exprval).ptr,(yyvsp[-2].exprval).ptr,(yyvsp[0].exprval).ptr);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[-2].exprval).type;

    (yyval.exprval).num = MAX((yyvsp[-2].exprval).num, (yyvsp[0].exprval).num);
    (yyval.exprval).num += 1;
}
#line 1569 "src/parser.c"
    break;

  case 33: /* expression_bin: expression_bin FOIS expression_bin  */
#line 320 "bison/parser.y"
                                     {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-2].exprval).type);
    gencode(CODE,BOP_MULT,(yyval.exprval).ptr,(yyvsp[-2].exprval).ptr,(yyvsp[0].exprval).ptr);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[-2].exprval).type;

    (yyval.exprval).num = MAX((yyvsp[-2].exprval).num, (yyvsp[0].exprval).num);
    (yyval.exprval).num += 1;
}
#line 1584 "src/parser.c"
    break;

  case 34: /* expression_bin: expression_bin DIVISE expression_bin  */
#line 330 "bison/parser.y"
                                       {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-2].exprval).type);
    gencode(CODE,BOP_DIVISE,(yyval.exprval).ptr,(yyvsp[-2].exprval).ptr,(yyvsp[0].exprval).ptr);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[-2].exprval).type;

    (yyval.exprval).num = MAX((yyvsp[-2].exprval).num, (yyvsp[0].exprval).num);
    (yyval.exprval).num += 1;
}
#line 1599 "src/parser.c"
    break;

  case 35: /* expression_bin: MOINS expression_bin  */
#line 340 "bison/parser.y"
                                      {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[0].exprval).type);
    gencode(CODE,UOP_MOINS,(yyval.exprval).ptr,(yyvsp[0].exprval).ptr,NULL);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[0].exprval).type;

    (yyval.exprval).num = (yyvsp[0].exprval).num + 1;
}
#line 1613 "src/parser.c"
    break;

  case 36: /* expression_bin: PLUS expression_bin  */
#line 349 "bison/parser.y"
                                     {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[0].exprval).type);
    gencode(CODE,UOP_PLUS,(yyval.exprval).ptr,(yyvsp[0].exprval).ptr,NULL);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[0].exprval).type;

    (yyval.exprval).num = (yyvsp[0].exprval).num + 1;
}
#line 1627 "src/parser.c"
    break;

  case 37: /* expression_bin: POINT_EXCLAMATION expression_bin  */
#line 358 "bison/parser.y"
                                                {;}
#line 1633 "src/parser.c"
    break;

  case 38: /* expression_bin: TRANSPOSITION expression_bin  */
#line 359 "bison/parser.y"
                                            {;}
#line 1639 "src/parser.c"
    break;

  case 39: /* expression_bin: PARENTHESE_OUVRANTE expression_bin PARENTHESE_FERMANTE  */
#line 360 "bison/parser.y"
                                                          {(yyval.exprval).ptr = (yyvsp[-1].exprval).ptr; (yyval.exprval).type = (yyvsp[-1].exprval).type; (yyval.exprval).num = (yyvsp[-1].exprval).num;}
#line 1645 "src/parser.c"
    break;

  case 40: /* expression_bin: PLUS_PLUS operande  */
#line 363 "bison/parser.y"
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[0].exprval).type);
    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_PLUS,(yyval.exprval).ptr,one,(yyvsp[0].exprval).ptr);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval).type = (yyvsp[0].exprval).type;
    (yyval.exprval).num = 1;
}
#line 1660 "src/parser.c"
    break;

  case 41: /* expression_bin: MOINS_MOINS operande  */
#line 374 "bison/parser.y"
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[0].exprval).type);
    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_MOINS,(yyval.exprval).ptr,(yyvsp[0].exprval).ptr, one);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval).type = (yyvsp[0].exprval).type;
    (yyval.exprval).num += 1;
}
#line 1675 "src/parser.c"
    break;

  case 42: /* expression_bin: operande PLUS_PLUS  */
#line 385 "bison/parser.y"
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-1].exprval).type);
    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_PLUS,(yyval.exprval).ptr,one,(yyvsp[-1].exprval).ptr);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval).type = (yyvsp[-1].exprval).type;
    (yyval.exprval).num = 1;
}
#line 1690 "src/parser.c"
    break;

  case 43: /* expression_bin: operande MOINS_MOINS  */
#line 396 "bison/parser.y"
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-1].exprval).type);
    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_MOINS,(yyval.exprval).ptr, (yyvsp[-1].exprval).ptr, one);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval).type = (yyvsp[-1].exprval).type;
    (yyval.exprval).num = 1;
}
#line 1705 "src/parser.c"
    break;

  case 44: /* expression_bin: operande  */
#line 406 "bison/parser.y"
           {(yyval.exprval).type = (yyvsp[0].exprval).type; (yyval.exprval).num = 0;}
#line 1711 "src/parser.c"
    break;

  case 45: /* operande: IDENTIFICATEUR  */
#line 410 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[0].strval));
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",(yyvsp[0].strval));
        exit(1);
    }
    if (id->type == MATRIX_TYPE)
    {
        printf("%s is of type MATRIX : pas encore géré\n",(yyvsp[0].strval));
        //exit(1);
    }

    struct symbol * sym_id = symbol_id(*id);
    (yyval.exprval).ptr = sym_id;
    (yyval.exprval).type = sym_id->u.id.type;
}
#line 1733 "src/parser.c"
    break;

  case 46: /* operande: CONSTANTE_ENTIERE  */
#line 427 "bison/parser.y"
                    {(yyval.exprval).ptr = symbol_const_int((int)(yyvsp[0].intval)); (yyval.exprval).type = ENTIER;}
#line 1739 "src/parser.c"
    break;

  case 47: /* operande: CONSTANTE_FLOTTANTE  */
#line 428 "bison/parser.y"
                      {(yyval.exprval).ptr = symbol_const_float((yyvsp[0].floatval)); (yyval.exprval).type = REEL;}
#line 1745 "src/parser.c"
    break;

  case 48: /* operande: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 431 "bison/parser.y"
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
    struct symbol * t3_temp = symbol_const_int(((yyvsp[-4].intval) + 1) * id->col);
    struct symbol * j = symbol_const_int(((yyvsp[-1].intval) + 1));
    /*     T3 = T3+T2 */
    gencode(CODE, BOP_PLUS, t3, j, t3_temp);
    /*     T4 = adr(A) /\* adresse de base de A *\/ */
    struct symbol * t4 = newtemp(SYMTAB, ENTIER);
    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, ADRESSE, t4, sym_id, NULL);
    /*     T4 = T4-84 /\* 84 = nbw*21 *\/ */
    struct symbol * nbw_row = symbol_const_int(4 * (id->col + 1));
    gencode(CODE, BOP_MOINS, t4, t4, nbw_row);
    /*     T5 = 4*T3 */
    struct symbol * t5 = newtemp(SYMTAB, ENTIER);
    struct symbol * nbw = symbol_const_int(4);
    gencode(CODE, BOP_MULT, t5, nbw, t3);
    /*     T6 = T4[T5] /\* = T4+T5 *\/ */
    struct symbol * symbol_composante = newtemp(SYMTAB, ENTIER);
    gencode(CODE, BOP_PLUS, symbol_composante, t4, t5);

    (yyval.exprval).ptr = symbol_composante;
    (yyval.exprval).type = REEL;
}
#line 1794 "src/parser.c"
    break;

  case 49: /* operande: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT  */
#line 476 "bison/parser.y"
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
    struct symbol * t3_temp = symbol_const_int((yyvsp[-1].intval) * id->col);
    struct symbol * j = symbol_const_int(1);
    /*     T3 = T3+T2 */
    gencode(CODE, BOP_PLUS, t3, j, t3_temp);
    /*     T4 = adr(A) /\* adresse de base de A *\/ */
    struct symbol * t4 = newtemp(SYMTAB, ENTIER);
    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, ADRESSE, t4, sym_id, NULL);
    /*     T4 = T4-84 /\* 84 = nbw*21 *\/ */
    struct symbol * nbw_row = symbol_const_int(4 * (id->col + 1));
    gencode(CODE, BOP_MOINS, t4, t4, nbw_row);
    /*     T5 = 4*T3 */
    struct symbol * t5 = newtemp(SYMTAB, ENTIER);
    struct symbol * nbw = symbol_const_int(4);
    gencode(CODE, BOP_MULT, t5, nbw, t3);
    /*     T6 = T4[T5] /\* = T4+T5 *\/ */
    struct symbol * symbol_composante = newtemp(SYMTAB, ENTIER);
    gencode(CODE, BOP_PLUS, symbol_composante, t4, t5);

    (yyval.exprval).ptr = symbol_composante;
    (yyval.exprval).type = REEL;
}
#line 1842 "src/parser.c"
    break;

  case 50: /* expression_mat: TRANSPOSITION expression_mat  */
#line 523 "bison/parser.y"
                                           {;}
#line 1848 "src/parser.c"
    break;

  case 62: /* type: INT  */
#line 553 "bison/parser.y"
      {(yyval.typeval) = ENTIER;}
#line 1854 "src/parser.c"
    break;

  case 63: /* type: FLOAT  */
#line 554 "bison/parser.y"
        {(yyval.typeval) = REEL;}
#line 1860 "src/parser.c"
    break;

  case 64: /* $@1: %empty  */
#line 558 "bison/parser.y"
  { stack_id_push(SYMTAB);}
#line 1866 "src/parser.c"
    break;

  case 65: /* $@2: %empty  */
#line 559 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1872 "src/parser.c"
    break;

  case 66: /* condition: IF PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M $@1 liste_instructions $@2 ACCOLADE_FERMANTE N condition_suite  */
#line 561 "bison/parser.y"
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
#line 1898 "src/parser.c"
    break;

  case 67: /* condition_suite: %empty  */
#line 584 "bison/parser.y"
         {(yyval.instr_type).next = NULL;}
#line 1904 "src/parser.c"
    break;

  case 68: /* $@3: %empty  */
#line 585 "bison/parser.y"
                          { stack_id_push(SYMTAB);}
#line 1910 "src/parser.c"
    break;

  case 69: /* $@4: %empty  */
#line 586 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1916 "src/parser.c"
    break;

  case 70: /* condition_suite: ELSE ACCOLADE_OUVRANTE $@3 liste_instructions $@4 ACCOLADE_FERMANTE  */
#line 587 "bison/parser.y"
{
    (yyval.instr_type).next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());

    (yyval.instr_type).next = concat((yyval.instr_type).next, (yyvsp[-2].instr_type).next);
}
#line 1927 "src/parser.c"
    break;

  case 71: /* $@5: %empty  */
#line 596 "bison/parser.y"
                    {stack_id_push(SYMTAB);}
#line 1933 "src/parser.c"
    break;

  case 72: /* $@6: %empty  */
#line 597 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1939 "src/parser.c"
    break;

  case 73: /* boucle_while: WHILE PARENTHESE_OUVRANTE M test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M $@5 liste_instructions $@6 ACCOLADE_FERMANTE  */
#line 598 "bison/parser.y"
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
#line 1956 "src/parser.c"
    break;

  case 74: /* $@7: %empty  */
#line 613 "bison/parser.y"
                          {stack_id_push(SYMTAB);}
#line 1962 "src/parser.c"
    break;

  case 75: /* $@8: %empty  */
#line 617 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1968 "src/parser.c"
    break;

  case 76: /* boucle_for: FOR PARENTHESE_OUVRANTE $@7 for_init POINT_VIRGULE M test POINT_VIRGULE for_fin PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M liste_instructions $@8 ACCOLADE_FERMANTE  */
#line 618 "bison/parser.y"
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
#line 1990 "src/parser.c"
    break;

  case 77: /* for_init: for_fin  */
#line 638 "bison/parser.y"
{
    if ((yyvsp[0].for_fin_t).ptr != NULL)
    {
        gencode(CODE,COPY,(yyvsp[0].for_fin_t).id,(yyvsp[0].for_fin_t).ptr,NULL);
    }
}
#line 2001 "src/parser.c"
    break;

  case 78: /* for_init: type IDENTIFICATEUR EGAL expression_bin  */
#line 645 "bison/parser.y"
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
    gencode(CODE,COPY,sym_id,(yyvsp[0].exprval).ptr,NULL);
}
#line 2019 "src/parser.c"
    break;

  case 79: /* for_fin: IDENTIFICATEUR  */
#line 661 "bison/parser.y"
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
#line 2036 "src/parser.c"
    break;

  case 80: /* for_fin: IDENTIFICATEUR EGAL expression_bin  */
#line 674 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-2].strval));
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", (yyvsp[-2].strval));
        exit(1);
    }
    if (id->type != (yyvsp[0].exprval).type)
    {
        fprintf(stderr, "error: incompatible types\n");
        exit(1);
    }
    struct symbol * sym_id = symbol_id(*id);
    (yyval.for_fin_t).id = sym_id;
    (yyval.for_fin_t).ptr = (yyvsp[0].exprval).ptr;
    (yyval.for_fin_t).num = (yyvsp[0].exprval).num;
}
#line 2058 "src/parser.c"
    break;

  case 81: /* test: test OR M test2  */
#line 694 "bison/parser.y"
{
    complete((yyvsp[-3].boolexpr).false, (yyvsp[-1].intval));
    ListLabel_free((yyvsp[-3].boolexpr).false);
    (yyval.boolexpr).true = concat((yyvsp[-3].boolexpr).true, (yyvsp[0].boolexpr).true);
    (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;
}
#line 2069 "src/parser.c"
    break;

  case 82: /* test: test2  */
#line 700 "bison/parser.y"
        {(yyval.boolexpr).true = (yyvsp[0].boolexpr).true; (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;}
#line 2075 "src/parser.c"
    break;

  case 83: /* test2: test2 AND M test3  */
#line 704 "bison/parser.y"
{
    complete((yyvsp[-3].boolexpr).true, (yyvsp[-1].intval));
    ListLabel_free((yyvsp[-3].boolexpr).true);
    (yyval.boolexpr).false = concat((yyvsp[-3].boolexpr).false, (yyvsp[0].boolexpr).false);
    (yyval.boolexpr).true = (yyvsp[0].boolexpr).true;
}
#line 2086 "src/parser.c"
    break;

  case 84: /* test2: test3  */
#line 710 "bison/parser.y"
        {(yyval.boolexpr).true = (yyvsp[0].boolexpr).true; (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;}
#line 2092 "src/parser.c"
    break;

  case 85: /* test3: expression_bin op_test expression_bin  */
#line 714 "bison/parser.y"
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
        gencode(CODE, Q_IF_EQ, (yyvsp[-2].exprval).ptr, (yyvsp[0].exprval).ptr, q);
        break;
    case NEQ:
        gencode(CODE, Q_IF_NEQ, (yyvsp[-2].exprval).ptr, (yyvsp[0].exprval).ptr, q);
        break;
    case LT:
        gencode(CODE, Q_IF_LT, (yyvsp[-2].exprval).ptr, (yyvsp[0].exprval).ptr, q);
        break;
    case LE:
        gencode(CODE, Q_IF_LE, (yyvsp[-2].exprval).ptr, (yyvsp[0].exprval).ptr, q);
        break;
    case GT:
        gencode(CODE, Q_IF_GT, (yyvsp[-2].exprval).ptr, (yyvsp[0].exprval).ptr, q);
        break;
    case GE:
        gencode(CODE, Q_IF_GE, (yyvsp[-2].exprval).ptr, (yyvsp[0].exprval).ptr, q);
        break;
    }

    (yyval.boolexpr).false = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());
}
#line 2131 "src/parser.c"
    break;

  case 86: /* test3: expression_bin  */
#line 749 "bison/parser.y"
{
    (yyval.boolexpr).true = NULL;
    (yyval.boolexpr).false = NULL;

    (yyval.boolexpr).true = creerListe(CODE->nextquad);

    struct symbol * q_zero = symbol_const_int(0);

    struct symbol * q = quad_label();
    CODE->quads[CODE->nextquad].sym3 = q;

    // Generate the code associate with op_test
    gencode(CODE, Q_IF_NEQ, (yyvsp[0].exprval).ptr, q_zero, q);
}
#line 2150 "src/parser.c"
    break;

  case 87: /* op_test: EGAL_EGAL  */
#line 765 "bison/parser.y"
            {(yyval.typetest) = EQ;}
#line 2156 "src/parser.c"
    break;

  case 88: /* op_test: POINT_EXCLAMATION EGAL  */
#line 766 "bison/parser.y"
                         {(yyval.typetest) = NEQ;}
#line 2162 "src/parser.c"
    break;

  case 89: /* op_test: INFERIEUR  */
#line 767 "bison/parser.y"
            {(yyval.typetest) = LT;}
#line 2168 "src/parser.c"
    break;

  case 90: /* op_test: INFERIEUR_EGAL  */
#line 768 "bison/parser.y"
                 {(yyval.typetest) = LE;}
#line 2174 "src/parser.c"
    break;

  case 91: /* op_test: SUPERIEUR  */
#line 769 "bison/parser.y"
            {(yyval.typetest) = GT;}
#line 2180 "src/parser.c"
    break;

  case 92: /* op_test: SUPERIEUR_EGAL  */
#line 770 "bison/parser.y"
                 {(yyval.typetest) = GE;}
#line 2186 "src/parser.c"
    break;

  case 93: /* M: %empty  */
#line 772 "bison/parser.y"
           {(yyval.intval) = CODE->nextquad;}
#line 2192 "src/parser.c"
    break;

  case 94: /* N: %empty  */
#line 774 "bison/parser.y"
{
    (yyval.N_t).next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());
    (yyval.N_t).quad = CODE->nextquad;
}
#line 2202 "src/parser.c"
    break;


#line 2206 "src/parser.c"

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

#line 779 "bison/parser.y"

void yyerror(const char * msg) {
    fprintf(stderr, "Erreur de syntaxe : %s\n", msg);

}
