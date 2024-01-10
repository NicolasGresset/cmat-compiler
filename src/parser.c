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
  YYSYMBOL_affectation = 48,               /* affectation  */
  YYSYMBOL_fin_aff = 49,                   /* fin_aff  */
  YYSYMBOL_expression = 50,                /* expression  */
  YYSYMBOL_operande = 51,                  /* operande  */
  YYSYMBOL_type = 52,                      /* type  */
  YYSYMBOL_condition = 53,                 /* condition  */
  YYSYMBOL_54_1 = 54,                      /* $@1  */
  YYSYMBOL_55_2 = 55,                      /* $@2  */
  YYSYMBOL_condition_suite = 56,           /* condition_suite  */
  YYSYMBOL_57_3 = 57,                      /* $@3  */
  YYSYMBOL_58_4 = 58,                      /* $@4  */
  YYSYMBOL_boucle_while = 59,              /* boucle_while  */
  YYSYMBOL_60_5 = 60,                      /* $@5  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_boucle_for = 62,                /* boucle_for  */
  YYSYMBOL_63_7 = 63,                      /* $@7  */
  YYSYMBOL_64_8 = 64,                      /* $@8  */
  YYSYMBOL_for_init = 65,                  /* for_init  */
  YYSYMBOL_for_fin = 66,                   /* for_fin  */
  YYSYMBOL_test = 67,                      /* test  */
  YYSYMBOL_test2 = 68,                     /* test2  */
  YYSYMBOL_test3 = 69,                     /* test3  */
  YYSYMBOL_op_test = 70,                   /* op_test  */
  YYSYMBOL_M = 71,                         /* M  */
  YYSYMBOL_N = 72                          /* N  */
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
typedef yytype_int8 yy_state_t;

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
#define YYLAST   123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  127

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
       0,   110,   110,   113,   114,   117,   118,   119,   120,   121,
     124,   135,   153,   174,   175,   179,   190,   200,   210,   220,
     229,   238,   239,   240,   242,   247,   260,   261,   262,   282,
     283,   287,   288,   286,   312,   313,   314,   313,   324,   325,
     323,   339,   343,   339,   361,   368,   384,   397,   417,   423,
     426,   432,   435,   470,   487,   488,   489,   490,   491,   492,
     494,   495
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
  "liste_instructions", "instruction", "declaration", "affectation",
  "fin_aff", "expression", "operande", "type", "condition", "$@1", "$@2",
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

#define YYPACT_NINF (-96)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,   -29,    42,    18,   -96,    29,    34,    54,    35,   -96,
     -96,    43,    45,    46,    47,   -96,   -96,   -96,    76,   -96,
     -96,   -96,     4,     4,   -96,   -96,   -96,    54,   -12,   -96,
     -96,   -96,   -96,     4,     4,     4,     4,     4,    56,   -96,
      13,    19,    70,   -96,     4,    87,   -96,     4,    82,   -96,
     -96,   -96,   -96,   -96,    63,   -96,     4,     4,     4,     4,
     -96,    69,   -96,   -96,   -96,   -96,   -96,     4,   -96,    57,
     -96,    33,    77,    96,    71,   -96,    56,   -96,   -96,     5,
       5,   -96,   -96,   -96,    78,     4,   -96,     4,    72,     4,
      79,   -96,   -96,    70,   -96,   -96,   -96,    78,     4,     4,
      54,   -96,    78,     3,    74,    54,   102,    80,    81,    83,
     -96,    84,    86,    97,   -96,   -96,    88,   -96,    54,   -96,
      89,    54,    90,    91,   -96,    92,   -96
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,    29,
      30,     0,     0,     0,    60,     4,     5,     9,     0,     6,
       7,     8,     0,     0,    60,    41,     2,     0,     0,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,    24,
      53,     0,    49,    51,     0,     0,     3,     0,     0,    13,
      10,    20,    19,    22,     0,    21,     0,     0,     0,     0,
      12,     0,    56,    57,    58,    59,    54,     0,    60,     0,
      60,     0,    46,     0,     0,    44,     0,    14,    23,    15,
      16,    17,    18,    55,    52,     0,    60,     0,     0,     0,
       0,    60,    11,    48,    31,    50,    60,    47,     0,     0,
       0,    38,    45,     0,    60,     0,     0,     0,    60,     0,
      61,     0,     0,    34,    40,    60,     0,    33,     0,    35,
      60,     0,     0,    60,    43,     0,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   -95,    85,   -96,    59,   -35,   -20,   -96,    68,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,     2,   -43,    31,    36,   -96,   -24,   -96
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    14,    15,    16,    17,    50,    40,    39,    18,
      19,   100,   107,   117,   121,   125,    20,   105,   111,    21,
      45,   122,    74,    75,    41,    42,    43,    67,    27,   113
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    71,    38,    60,     1,   104,     3,    29,    30,    31,
     108,    47,    32,    51,    52,    53,    54,    55,    68,    48,
      49,    33,    34,   120,    58,    59,   123,    76,    35,    36,
      56,    57,    58,    59,    68,   106,    79,    80,    81,    82,
      37,    92,     4,     5,    85,    69,    87,    84,    68,    61,
      62,    63,    64,    65,    66,     6,   103,     8,    22,    88,
       9,    10,    94,     7,    11,    12,    13,    99,    23,    97,
      24,    25,   101,    56,    57,    58,    59,    26,   102,    28,
      56,    57,    58,    59,    70,     8,    86,    48,    49,    78,
      72,   118,    83,     9,    10,    56,    57,    58,    59,    90,
      89,    96,    98,    91,   -32,    72,   116,    77,   109,   112,
     110,   -39,    46,    73,   114,   115,    93,   119,     0,   -42,
     124,   -36,   126,    95
};

static const yytype_int8 yycheck[] =
{
      24,    44,    22,    38,     6,   100,    35,     3,     4,     5,
     105,    23,     8,    33,    34,    35,    36,    37,    15,    31,
      32,    17,    18,   118,    19,    20,   121,    47,    24,    25,
      17,    18,    19,    20,    15,    32,    56,    57,    58,    59,
      36,    76,     0,    25,    68,    26,    70,    67,    15,    36,
      37,    38,    39,    40,    41,    26,    99,     3,    23,    26,
       6,     7,    86,    29,    10,    11,    12,    91,    25,    89,
      25,    25,    96,    17,    18,    19,    20,    30,    98,     3,
      17,    18,    19,    20,    14,     3,    29,    31,    32,    26,
       3,   115,    23,     6,     7,    17,    18,    19,    20,     3,
      23,    29,    23,    32,    30,     3,     9,    48,   106,    26,
      30,    30,    27,    45,    30,    29,    85,    29,    -1,    30,
      30,    30,    30,    87
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    44,    35,     0,    25,    26,    29,     3,     6,
       7,    10,    11,    12,    45,    46,    47,    48,    52,    53,
      59,    62,    23,    25,    25,    25,    30,    71,     3,     3,
       4,     5,     8,    17,    18,    24,    25,    36,    50,    51,
      50,    67,    68,    69,    71,    63,    46,    23,    31,    32,
      49,    50,    50,    50,    50,    50,    17,    18,    19,    20,
      49,    36,    37,    38,    39,    40,    41,    70,    15,    26,
      14,    67,     3,    52,    65,    66,    50,    48,    26,    50,
      50,    50,    50,    23,    50,    71,    29,    71,    26,    23,
       3,    32,    49,    68,    71,    69,    29,    50,    23,    71,
      54,    71,    50,    67,    45,    60,    32,    55,    45,    66,
      30,    61,    26,    72,    30,    29,     9,    56,    71,    29,
      45,    57,    64,    45,    30,    58,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      47,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    51,    51,    51,    51,    52,
      52,    54,    55,    53,    56,    57,    58,    56,    60,    61,
      59,    63,    64,    62,    65,    65,    66,    66,    67,    67,
      68,    68,    69,    69,    70,    70,    70,    70,    70,    70,
      71,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     3,     1,     1,     1,     1,     1,     1,
       3,     5,     4,     1,     2,     3,     3,     3,     3,     2,
       2,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     0,    12,     0,     0,     0,     6,     0,     0,
      11,     0,     0,    15,     1,     4,     1,     3,     4,     1,
       4,     1,     3,     1,     1,     2,     1,     1,     1,     1,
       0,     0
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
  case 3: /* liste_instructions: liste_instructions M instruction  */
#line 113 "bison/parser.y"
                                   {complete((yyvsp[-2].instr_type).next, (yyvsp[-1].intval)); (yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1251 "src/parser.c"
    break;

  case 4: /* liste_instructions: instruction  */
#line 114 "bison/parser.y"
              {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1257 "src/parser.c"
    break;

  case 5: /* instruction: declaration  */
#line 117 "bison/parser.y"
              {(yyval.instr_type).next = NULL;}
#line 1263 "src/parser.c"
    break;

  case 6: /* instruction: condition  */
#line 118 "bison/parser.y"
            {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1269 "src/parser.c"
    break;

  case 7: /* instruction: boucle_while  */
#line 119 "bison/parser.y"
               {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1275 "src/parser.c"
    break;

  case 8: /* instruction: boucle_for  */
#line 120 "bison/parser.y"
             {(yyval.instr_type).next = (yyvsp[0].instr_type).next;}
#line 1281 "src/parser.c"
    break;

  case 9: /* instruction: affectation  */
#line 121 "bison/parser.y"
              {(yyval.instr_type).next = NULL;}
#line 1287 "src/parser.c"
    break;

  case 10: /* declaration: type IDENTIFICATEUR fin_aff  */
#line 124 "bison/parser.y"
                              {
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[-1].strval));
     if ( id != NULL )
     {
         fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", (yyvsp[-1].strval));
         exit(1);
     }
     id = id_init((yyvsp[-1].strval), (yyvsp[-2].typeval));
     table_hachage_put(SYMTAB,id);
     //gencode(CODE,COPY,id,NULL,NULL);
 }
#line 1303 "src/parser.c"
    break;

  case 11: /* declaration: type IDENTIFICATEUR EGAL expression fin_aff  */
#line 135 "bison/parser.y"
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
    gencode(CODE,COPY,sym_id,(yyvsp[-1].exprval).ptr,NULL);

 }
#line 1322 "src/parser.c"
    break;

  case 12: /* affectation: IDENTIFICATEUR EGAL expression fin_aff  */
#line 153 "bison/parser.y"
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
        exit(1);
    }

    struct symbol *  sym_id = symbol_id(*id);
    gencode(CODE,COPY,sym_id,(yyvsp[-1].exprval).ptr,NULL);

 }
#line 1344 "src/parser.c"
    break;

  case 15: /* expression: expression PLUS expression  */
#line 179 "bison/parser.y"
                             {
    // Le cas où les 2 expressions n'ont pas le même type n'est pas géré
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-2].exprval).type);
    gencode(CODE,BOP_PLUS,(yyval.exprval).ptr,(yyvsp[-2].exprval).ptr,(yyvsp[0].exprval).ptr);

    // Type temporaire en fonction de int ou float convertir le type
    (yyval.exprval).type = (yyvsp[-2].exprval).type;
    // Utile pour la boucle_for savoir où compléter test.true
    (yyval.exprval).num = MAX((yyvsp[-2].exprval).num, (yyvsp[0].exprval).num);
    (yyval.exprval).num += 1;
}
#line 1360 "src/parser.c"
    break;

  case 16: /* expression: expression MOINS expression  */
#line 190 "bison/parser.y"
                              {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-2].exprval).type);
    gencode(CODE,BOP_MOINS,(yyval.exprval).ptr,(yyvsp[-2].exprval).ptr,(yyvsp[0].exprval).ptr);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[-2].exprval).type;

    (yyval.exprval).num = MAX((yyvsp[-2].exprval).num, (yyvsp[0].exprval).num);
    (yyval.exprval).num += 1;
}
#line 1375 "src/parser.c"
    break;

  case 17: /* expression: expression FOIS expression  */
#line 200 "bison/parser.y"
                             {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-2].exprval).type);
    gencode(CODE,BOP_MULT,(yyval.exprval).ptr,(yyvsp[-2].exprval).ptr,(yyvsp[0].exprval).ptr);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[-2].exprval).type;

    (yyval.exprval).num = MAX((yyvsp[-2].exprval).num, (yyvsp[0].exprval).num);
    (yyval.exprval).num += 1;
}
#line 1390 "src/parser.c"
    break;

  case 18: /* expression: expression DIVISE expression  */
#line 210 "bison/parser.y"
                               {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[-2].exprval).type);
    gencode(CODE,BOP_DIVISE,(yyval.exprval).ptr,(yyvsp[-2].exprval).ptr,(yyvsp[0].exprval).ptr);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[-2].exprval).type;

    (yyval.exprval).num = MAX((yyvsp[-2].exprval).num, (yyvsp[0].exprval).num);
    (yyval.exprval).num += 1;
}
#line 1405 "src/parser.c"
    break;

  case 19: /* expression: MOINS expression  */
#line 220 "bison/parser.y"
                                  {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[0].exprval).type);
    gencode(CODE,UOP_MOINS,(yyval.exprval).ptr,(yyvsp[0].exprval).ptr,NULL);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[0].exprval).type;

    (yyval.exprval).num = (yyvsp[0].exprval).num + 1;
}
#line 1419 "src/parser.c"
    break;

  case 20: /* expression: PLUS expression  */
#line 229 "bison/parser.y"
                                 {
    (yyval.exprval).ptr = newtemp(SYMTAB, (yyvsp[0].exprval).type);
    gencode(CODE,UOP_PLUS,(yyval.exprval).ptr,(yyvsp[0].exprval).ptr,NULL);

    // Type temporaire
    (yyval.exprval).type = (yyvsp[0].exprval).type;

    (yyval.exprval).num = (yyvsp[0].exprval).num + 1;
}
#line 1433 "src/parser.c"
    break;

  case 21: /* expression: POINT_EXCLAMATION expression  */
#line 238 "bison/parser.y"
                                            {;}
#line 1439 "src/parser.c"
    break;

  case 22: /* expression: TRANSPOSITION expression  */
#line 239 "bison/parser.y"
                                        {;}
#line 1445 "src/parser.c"
    break;

  case 23: /* expression: PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE  */
#line 240 "bison/parser.y"
                                                      {(yyval.exprval).ptr = (yyvsp[-1].exprval).ptr; (yyval.exprval).type = (yyvsp[-1].exprval).type; (yyval.exprval).num = (yyvsp[-1].exprval).num;}
#line 1451 "src/parser.c"
    break;

  case 24: /* expression: operande  */
#line 242 "bison/parser.y"
           {(yyval.exprval).type = (yyvsp[0].exprval).type; (yyval.exprval).num = 0;}
#line 1457 "src/parser.c"
    break;

  case 25: /* operande: IDENTIFICATEUR  */
#line 248 "bison/parser.y"
{
    struct id_t * id = table_hachage_get(SYMTAB,(yyvsp[0].strval));
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",(yyvsp[0].strval));
        exit(1);
    }

    struct symbol * sym_id = symbol_id(*id);
    (yyval.exprval).ptr = sym_id;
    (yyval.exprval).type = sym_id->u.id.type;
}
#line 1474 "src/parser.c"
    break;

  case 26: /* operande: CONSTANTE_ENTIERE  */
#line 260 "bison/parser.y"
                    {(yyval.exprval).ptr = symbol_const_int((yyvsp[0].intval)); (yyval.exprval).type = ENTIER;}
#line 1480 "src/parser.c"
    break;

  case 27: /* operande: CONSTANTE_FLOTTANTE  */
#line 261 "bison/parser.y"
                      {(yyval.exprval).ptr = symbol_const_float((yyvsp[0].floatval)); (yyval.exprval).type = REEL;}
#line 1486 "src/parser.c"
    break;

  case 29: /* type: INT  */
#line 282 "bison/parser.y"
      {(yyval.typeval) = ENTIER;}
#line 1492 "src/parser.c"
    break;

  case 30: /* type: FLOAT  */
#line 283 "bison/parser.y"
        {(yyval.typeval) = REEL;}
#line 1498 "src/parser.c"
    break;

  case 31: /* $@1: %empty  */
#line 287 "bison/parser.y"
  { stack_id_push(SYMTAB);}
#line 1504 "src/parser.c"
    break;

  case 32: /* $@2: %empty  */
#line 288 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1510 "src/parser.c"
    break;

  case 33: /* condition: IF PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M $@1 liste_instructions $@2 ACCOLADE_FERMANTE N condition_suite  */
#line 290 "bison/parser.y"
{
    complete((yyvsp[-9].boolexpr).true, (yyvsp[-6].intval));
    ListLabel_free((yyvsp[-9].boolexpr).true);

    (yyval.instr_type).next = concat((yyvsp[-4].instr_type).next, (yyvsp[-1].N_t).next);

    if ((yyvsp[0].instr_type).next != NULL)
    {
        complete((yyvsp[-9].boolexpr).false, (yyvsp[-1].N_t).quad);
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
#line 1535 "src/parser.c"
    break;

  case 34: /* condition_suite: %empty  */
#line 312 "bison/parser.y"
         {(yyval.instr_type).next = NULL;}
#line 1541 "src/parser.c"
    break;

  case 35: /* $@3: %empty  */
#line 313 "bison/parser.y"
                          { stack_id_push(SYMTAB);}
#line 1547 "src/parser.c"
    break;

  case 36: /* $@4: %empty  */
#line 314 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1553 "src/parser.c"
    break;

  case 37: /* condition_suite: ELSE ACCOLADE_OUVRANTE $@3 liste_instructions $@4 ACCOLADE_FERMANTE  */
#line 315 "bison/parser.y"
{
    (yyval.instr_type).next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());

    (yyval.instr_type).next = concat((yyval.instr_type).next, (yyvsp[-2].instr_type).next);
}
#line 1564 "src/parser.c"
    break;

  case 38: /* $@5: %empty  */
#line 324 "bison/parser.y"
                    {stack_id_push(SYMTAB);}
#line 1570 "src/parser.c"
    break;

  case 39: /* $@6: %empty  */
#line 325 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1576 "src/parser.c"
    break;

  case 40: /* boucle_while: WHILE PARENTHESE_OUVRANTE M test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M $@5 liste_instructions $@6 ACCOLADE_FERMANTE  */
#line 326 "bison/parser.y"
{
    complete((yyvsp[-7].boolexpr).true, (yyvsp[-4].intval));
    complete((yyvsp[-2].instr_type).next, (yyvsp[-8].intval));
    (yyval.instr_type).next = (yyvsp[-7].boolexpr).false;

    struct symbol * q = quad_label();
    q->u.addr = (yyvsp[-8].intval);
    CODE->quads[CODE->nextquad].sym3 = q;
    gencode(CODE, Q_GOTO, NULL, NULL, q);
}
#line 1591 "src/parser.c"
    break;

  case 41: /* $@7: %empty  */
#line 339 "bison/parser.y"
                          {stack_id_push(SYMTAB);}
#line 1597 "src/parser.c"
    break;

  case 42: /* $@8: %empty  */
#line 343 "bison/parser.y"
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
#line 1603 "src/parser.c"
    break;

  case 43: /* boucle_for: FOR PARENTHESE_OUVRANTE $@7 for_init POINT_VIRGULE M test POINT_VIRGULE for_fin PARENTHESE_FERMANTE ACCOLADE_OUVRANTE M liste_instructions $@8 ACCOLADE_FERMANTE  */
#line 344 "bison/parser.y"
{
    complete((yyvsp[-8].boolexpr).true, (yyvsp[-3].intval) - (yyvsp[-6].for_fin_t).num);
    complete((yyvsp[-2].instr_type).next, (yyvsp[-9].intval));
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
#line 1623 "src/parser.c"
    break;

  case 44: /* for_init: for_fin  */
#line 362 "bison/parser.y"
{
    if ((yyvsp[0].for_fin_t).ptr != NULL)
    {
        gencode(CODE,COPY,(yyvsp[0].for_fin_t).id,(yyvsp[0].for_fin_t).ptr,NULL);
    }
}
#line 1634 "src/parser.c"
    break;

  case 45: /* for_init: type IDENTIFICATEUR EGAL expression  */
#line 369 "bison/parser.y"
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
#line 1652 "src/parser.c"
    break;

  case 46: /* for_fin: IDENTIFICATEUR  */
#line 385 "bison/parser.y"
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
#line 1669 "src/parser.c"
    break;

  case 47: /* for_fin: IDENTIFICATEUR EGAL expression  */
#line 398 "bison/parser.y"
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
#line 1691 "src/parser.c"
    break;

  case 48: /* test: test OR M test2  */
#line 418 "bison/parser.y"
{
    complete((yyvsp[-3].boolexpr).false, (yyvsp[-1].intval));
    (yyval.boolexpr).true = concat((yyvsp[-3].boolexpr).true, (yyvsp[0].boolexpr).true);
    (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;
}
#line 1701 "src/parser.c"
    break;

  case 49: /* test: test2  */
#line 423 "bison/parser.y"
        {(yyval.boolexpr).true = (yyvsp[0].boolexpr).true; (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;}
#line 1707 "src/parser.c"
    break;

  case 50: /* test2: test2 AND M test3  */
#line 427 "bison/parser.y"
{
    complete((yyvsp[-3].boolexpr).true, (yyvsp[-1].intval));
    (yyval.boolexpr).false = concat((yyvsp[-3].boolexpr).false, (yyvsp[0].boolexpr).false);
    (yyval.boolexpr).true = (yyvsp[0].boolexpr).true;
}
#line 1717 "src/parser.c"
    break;

  case 51: /* test2: test3  */
#line 432 "bison/parser.y"
        {(yyval.boolexpr).true = (yyvsp[0].boolexpr).true; (yyval.boolexpr).false = (yyvsp[0].boolexpr).false;}
#line 1723 "src/parser.c"
    break;

  case 52: /* test3: expression op_test expression  */
#line 436 "bison/parser.y"
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
#line 1762 "src/parser.c"
    break;

  case 53: /* test3: expression  */
#line 471 "bison/parser.y"
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
#line 1781 "src/parser.c"
    break;

  case 54: /* op_test: EGAL_EGAL  */
#line 487 "bison/parser.y"
            {(yyval.typetest) = EQ;}
#line 1787 "src/parser.c"
    break;

  case 55: /* op_test: POINT_EXCLAMATION EGAL  */
#line 488 "bison/parser.y"
                         {(yyval.typetest) = NEQ;}
#line 1793 "src/parser.c"
    break;

  case 56: /* op_test: INFERIEUR  */
#line 489 "bison/parser.y"
            {(yyval.typetest) = LT;}
#line 1799 "src/parser.c"
    break;

  case 57: /* op_test: INFERIEUR_EGAL  */
#line 490 "bison/parser.y"
                 {(yyval.typetest) = LE;}
#line 1805 "src/parser.c"
    break;

  case 58: /* op_test: SUPERIEUR  */
#line 491 "bison/parser.y"
            {(yyval.typetest) = GT;}
#line 1811 "src/parser.c"
    break;

  case 59: /* op_test: SUPERIEUR_EGAL  */
#line 492 "bison/parser.y"
                 {(yyval.typetest) = GE;}
#line 1817 "src/parser.c"
    break;

  case 60: /* M: %empty  */
#line 494 "bison/parser.y"
           {(yyval.intval) = CODE->nextquad;}
#line 1823 "src/parser.c"
    break;

  case 61: /* N: %empty  */
#line 496 "bison/parser.y"
{
    (yyval.N_t).next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());
    (yyval.N_t).quad = CODE->nextquad;
}
#line 1833 "src/parser.c"
    break;


#line 1837 "src/parser.c"

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

#line 501 "bison/parser.y"

void yyerror(const char * msg) {
    fprintf(stderr, "Erreur de syntaxe : %s\n", msg);

}
