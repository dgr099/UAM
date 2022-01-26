/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/alfa.y" /* yacc.c:339  */

    #include "alfa.h"
    #include "y.tab.h"
    #include "sym_t.h"
    #include "sym_info.h"
    #include "generacion.h"

    #include <stdio.h>
    #include <stdlib.h>

    /* Imprime err_msg si no se cumple la condicion cond */
    #define CHECK_ERROR(cond, err_msg) \
        F_BLOCK( \
            if(!(cond)){ \
            fprintf(alfa_utils_T.ferr, "****Error semantico en lin %d[%d]: %s\n", \
                    (alfa_utils_T.line), \
                    (alfa_utils_T.col), \
                    (err_msg)); \
             YYABORT; \
            } \
        )

    #define TAM_ERRMSG 200
    #define INT_TO_CHAR 16
    
    /* Imprime regla gramatical en un fichero de debug */
    #define P_RULE(n, msg) \
        F_BLOCK( \
            fprintf(alfa_utils_T.fdbg, ";R%d:\t%s\n", (n), (msg)); \
        )

    int yyerror(char *s)
    {
        NO_USO(s);
        /* Si imprime un error morfologico, no debe imprimir uno sintactico */
        if (alfa_utils_T.error == ERR_MORFOLOGICO)
            return 0;

        alfa_utils_T.error = ERR_SINTACTICO;
        manage_error(NULL, NULL);
        return 1;
    }

    /* Para declaraciones */
    static Tipo tipo_actual;
    static Categoria clase_actual;

    /* Para vectores */
    static int tamanio_vector_actual = 0;

    /* Etiquetas */
    static int etiqueta = 1;

    /* Funciones */
    static int pos_parametro_actual = UNDEFINED;
    static int num_parametros_actual = 0;
    static int num_variables_locales_actual = 0;
	static int pos_variable_local_actual = 0;
    static Tipo tipo_retorno_actual = UNDEFINED;

    /* 
    Para ver que toda funcion tiene al menos un return
    Y que un return solo puede estar en el cuerpo de una funcion
    */
	static int hay_return = 0;
    static int dentro_de_fun = 0;

    /*
    Para evitar llamadas a funciones como parametros
    */
	static int en_explist = 0;

#line 139 "alfa.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "alfa.tab.h".  */
#ifndef YY_YY_ALFA_TAB_H_INCLUDED
# define YY_YY_ALFA_TAB_H_INCLUDED
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
    TOK_MAIN = 258,
    TOK_INT = 259,
    TOK_BOOLEAN = 260,
    TOK_ARRAY = 261,
    TOK_FUNCTION = 262,
    TOK_IF = 263,
    TOK_ELSE = 264,
    TOK_WHILE = 265,
    TOK_SCANF = 266,
    TOK_PRINTF = 267,
    TOK_RETURN = 268,
    TOK_COMPARE = 269,
    TOK_WITH = 270,
    TOK_LESS = 271,
    TOK_EQUAL = 272,
    TOK_GREATER = 273,
    TOK_AND = 274,
    TOK_OR = 275,
    TOK_IGUAL = 276,
    TOK_DISTINTO = 277,
    TOK_MENORIGUAL = 278,
    TOK_MAYORIGUAL = 279,
    TOK_IDENTIFICADOR = 280,
    TOK_CONSTANTE_ENTERA = 281,
    TOK_TRUE = 282,
    TOK_FALSE = 283,
    TOK_ERROR = 284,
    NEG = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 74 "src/alfa.y" /* yacc.c:355  */

    tipo_atributos atributos;

#line 214 "alfa.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ALFA_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "alfa.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   164

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  154

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,     2,     2,     2,     2,     2,
      42,    43,    32,    30,    41,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
      45,    44,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   135,   135,   137,   144,   149,   161,   163,   164,   166,
     168,   172,   177,   179,   183,   188,   196,   197,   199,   200,
     202,   215,   224,   243,   244,   246,   247,   249,   254,   269,
     270,   272,   273,   275,   276,   278,   279,   280,   281,   283,
     284,   286,   315,   327,   344,   349,   358,   363,   369,   374,
     379,   384,   406,   411,   421,   430,   439,   448,   457,   467,
     476,   485,   494,   522,   532,   538,   544,   553,   571,   580,
     584,   589,   593,   598,   607,   616,   625,   634,   643,   653,
     658,   664,   670,   677,   684,   690
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_MAIN", "TOK_INT", "TOK_BOOLEAN",
  "TOK_ARRAY", "TOK_FUNCTION", "TOK_IF", "TOK_ELSE", "TOK_WHILE",
  "TOK_SCANF", "TOK_PRINTF", "TOK_RETURN", "TOK_COMPARE", "TOK_WITH",
  "TOK_LESS", "TOK_EQUAL", "TOK_GREATER", "TOK_AND", "TOK_OR", "TOK_IGUAL",
  "TOK_DISTINTO", "TOK_MENORIGUAL", "TOK_MAYORIGUAL", "TOK_IDENTIFICADOR",
  "TOK_CONSTANTE_ENTERA", "TOK_TRUE", "TOK_FALSE", "TOK_ERROR", "'+'",
  "'-'", "'*'", "'/'", "NEG", "'!'", "'{'", "'}'", "';'", "'['", "']'",
  "','", "'('", "')'", "'='", "'<'", "'>'", "$accept", "programa",
  "iniciar", "final", "dec_vars", "wrt_main", "declaraciones",
  "declaracion", "clase", "clase_escalar", "tipo", "clase_vector",
  "identificadores", "funciones", "funcion", "fn_declaration", "fn_name",
  "parametros_funcion", "resto_parametros_funcion", "idpf",
  "parametro_funcion", "declaraciones_funcion", "sentencias", "sentencia",
  "sentencia_simple", "bloque", "asignacion", "elemento_vector",
  "condicional", "if_sentencias", "if_exp", "bucle", "bucle_exp",
  "bucle_tok", "lectura", "escritura", "retorno_funcion", "exp",
  "llamada_funcion", "lista_expresiones", "resto_lista_expresiones",
  "comparacion", "constante", "constante_logica", "constante_entera",
  "identificador_use", "identificador_new", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      43,    45,    42,    47,   285,    33,   123,   125,    59,    91,
      93,    44,    40,    41,    61,    60,    62
};
# endif

#define YYPACT_NINF -38

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-38)))

#define YYTABLE_NINF -69

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,   -28,    18,   -38,   -38,    68,   -38,   -38,     7,   -38,
      68,    -3,   -38,   -38,   -38,   -13,    20,   -38,   -38,     4,
      -8,    26,     7,   -38,    20,    28,     9,   -38,    -3,     6,
      29,    28,   -38,    24,   -38,    29,   118,   118,   -38,    30,
      28,    31,   -38,   -38,    34,   -38,    61,    28,   -38,    28,
      33,   -38,   -38,   -38,   -37,     7,   -38,   -38,   -38,   -38,
     118,   -38,   -38,   -38,   -38,   118,   118,   118,   -38,   131,
      37,   -38,   -38,   -38,   -33,   131,   -38,   -38,   -38,   118,
      48,    50,    63,   118,   118,   118,    29,    58,    64,    76,
      25,   -38,   -38,    73,    71,   118,   118,   118,   118,   118,
     118,   118,   131,    28,   -38,   -38,    79,   107,   131,   -38,
     -38,    81,     7,   -38,   -38,    87,   118,   118,   118,   118,
     -38,   118,   118,   -38,   -38,    57,    57,    57,   -38,   -38,
     101,    72,    91,    88,   -38,    68,    64,   -38,   131,   131,
     131,   131,   131,   131,   118,   -38,   -38,   -38,   -38,   -38,
     -38,   -38,   101,   -38
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,    13,    14,     0,     5,
       7,     0,    10,    12,    11,     0,    19,     8,    85,     0,
      16,     0,     0,     6,    19,     0,     0,     9,     0,     0,
       0,     0,    18,     0,    50,     0,     0,     0,    84,     0,
      31,     0,    34,    35,     0,    39,    44,     0,    40,     0,
       0,    36,    37,    38,     0,    24,    17,    15,    22,     4,
       0,    51,    83,    81,    82,     0,     0,     0,    66,    52,
       0,    63,    79,    80,    62,    53,    20,    32,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,    58,    61,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    42,     0,    46,    48,     0,     0,    41,    28,
      27,     0,     0,    23,     2,     0,     0,     0,     0,     0,
      64,     0,     0,    65,    59,    60,    54,    55,    57,    56,
      72,     0,     0,     0,    43,    30,    26,    47,    73,    74,
      75,    76,    77,    78,     0,    69,    67,    45,    49,    29,
      21,    25,    72,    71
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -38,   -38,   -38,   -38,   -38,   -38,   -10,   -38,   -38,   -38,
      -5,   -38,   102,   105,   -38,   -38,   -38,   -38,    -1,   -38,
      36,   -38,   -26,   -38,   -38,   -38,   -38,   -12,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -36,   -38,   -38,
     -16,   -38,   -38,   -38,   -38,   -15,   -38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    89,    16,    31,     9,    10,    11,    12,
      13,    14,    19,    23,    24,    25,    26,    87,   113,   109,
      88,   150,    39,    40,    41,    42,    43,    68,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    69,    70,   131,
     145,    94,    71,    72,    73,    74,    20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    75,    84,    15,     1,    59,    84,    85,     3,   -68,
      54,     6,     7,    44,    77,    58,    54,    30,     4,    44,
      61,    81,    18,    82,    90,    54,    21,    22,    44,    91,
      92,    93,    54,    28,    54,    44,    33,    44,    34,    35,
      36,    37,    27,   102,    95,    96,    57,   106,   107,   108,
      86,    55,    29,    38,    38,    97,    98,    99,   100,   124,
     125,   126,   127,   128,   129,   130,    60,    76,   115,    78,
      80,   110,     6,     7,     8,    83,    95,   132,    79,   101,
     138,   139,   140,   141,   103,   142,   143,   104,    54,    99,
     100,    44,    95,    96,   116,   117,   118,   119,    95,    96,
     105,   111,   112,    97,    98,    99,   100,    86,   152,    97,
      98,    99,   100,   114,   123,   146,   120,   135,   121,   122,
      95,    96,   133,   137,   148,   149,    95,    96,   147,    32,
      56,    97,    98,    99,   100,   151,   153,    97,    98,    99,
     100,     0,   144,    38,    62,    63,    64,   134,   136,    65,
      95,    96,     0,    66,     0,     0,     0,     0,     0,     0,
      67,    97,    98,    99,   100
};

static const yytype_int16 yycheck[] =
{
      10,    37,    39,     8,     3,    31,    39,    44,    36,    42,
      25,     4,     5,    25,    40,    30,    31,    22,     0,    31,
      35,    47,    25,    49,    60,    40,    39,     7,    40,    65,
      66,    67,    47,    41,    49,    47,     8,    49,    10,    11,
      12,    13,    38,    79,    19,    20,    40,    83,    84,    85,
      55,    42,    26,    25,    25,    30,    31,    32,    33,    95,
      96,    97,    98,    99,   100,   101,    42,    37,    43,    38,
       9,    86,     4,     5,     6,    42,    19,   103,    44,    42,
     116,   117,   118,   119,    36,   121,   122,    37,   103,    32,
      33,   103,    19,    20,    21,    22,    23,    24,    19,    20,
      37,    43,    38,    30,    31,    32,    33,   112,   144,    30,
      31,    32,    33,    37,    43,    43,    43,    36,    45,    46,
      19,    20,    43,    36,    36,   135,    19,    20,    37,    24,
      28,    30,    31,    32,    33,   136,   152,    30,    31,    32,
      33,    -1,    41,    25,    26,    27,    28,    40,   112,    31,
      19,    20,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    30,    31,    32,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    48,    36,     0,    49,     4,     5,     6,    53,
      54,    55,    56,    57,    58,    57,    51,    53,    25,    59,
      93,    39,     7,    60,    61,    62,    63,    38,    41,    26,
      57,    52,    60,     8,    10,    11,    12,    13,    25,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    92,    42,    59,    40,    92,    69,
      42,    92,    26,    27,    28,    31,    35,    42,    74,    84,
      85,    89,    90,    91,    92,    84,    37,    69,    38,    44,
       9,    69,    69,    42,    39,    44,    57,    64,    67,    50,
      84,    84,    84,    84,    88,    19,    20,    30,    31,    32,
      33,    42,    84,    36,    37,    37,    84,    84,    84,    66,
      92,    43,    38,    65,    37,    43,    21,    22,    23,    24,
      43,    45,    46,    43,    84,    84,    84,    84,    84,    84,
      84,    86,    69,    43,    40,    36,    67,    36,    84,    84,
      84,    84,    84,    84,    41,    87,    43,    37,    36,    53,
      68,    65,    84,    87
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    50,    51,    52,    53,    53,    54,
      55,    55,    56,    57,    57,    58,    59,    59,    60,    60,
      61,    62,    63,    64,    64,    65,    65,    66,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    71,    71,    72,
      72,    73,    73,    74,    75,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    85,    86,
      86,    87,    87,    88,    88,    88,    88,    88,    88,    89,
      89,    90,    90,    91,    92,    93
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    10,     0,     0,     0,     0,     1,     2,     3,
       1,     1,     1,     1,     1,     5,     1,     3,     2,     0,
       3,     6,     3,     2,     0,     3,     0,     1,     2,     1,
       0,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     4,     1,     5,     3,     5,     3,     5,
       1,     2,     2,     2,     3,     3,     3,     3,     2,     3,
       3,     2,     1,     1,     3,     3,     1,     4,     1,     2,
       0,     3,     0,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 135 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(1,"<programa> ::= main { <declaraciones> <funciones> <sentencias> }");}
#line 1429 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 137 "src/alfa.y" /* yacc.c:1646  */
    {
                sym_t_create();
                escribir_cabecera_presentacion(alfa_utils_T.fasm, alfa_utils_T.fin_name);
                escribir_subseccion_data(alfa_utils_T.fasm);
                escribir_cabecera_bss(alfa_utils_T.fasm);
            }
#line 1440 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 144 "src/alfa.y" /* yacc.c:1646  */
    {
                sym_t_free();
                escribir_fin(alfa_utils_T.fasm);
            }
#line 1449 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 149 "src/alfa.y" /* yacc.c:1646  */
    {
                char** simbolos = sym_t_getGlobalSymbols();
                int i = 0;
                sym_info* sym = NULL;
                for (i = 0; simbolos[i] != NULL; i++) {
                    sym = sym_t_get_symb(simbolos[i]);
                    if (sym && VARIABLE == sym->elem)
                        declarar_variable(alfa_utils_T.fasm, sym->lexema, sym->tipo, sym->size);
                }
                escribir_segmento_codigo(alfa_utils_T.fasm);
            }
#line 1465 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 161 "src/alfa.y" /* yacc.c:1646  */
    {   escribir_inicio_main(alfa_utils_T.fasm);}
#line 1471 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 163 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(2,"<declaraciones> ::= <declaracion>");}
#line 1477 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 164 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(3,"<declaraciones> ::= <declaracion> <declaraciones>");}
#line 1483 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 166 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(4,"<declaracion> ::= <clase> <identificadores> ;");}
#line 1489 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 168 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(5,"<clase> ::= <clase_escalar>");
            clase_actual = ESCALAR;
        }
#line 1498 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 172 "src/alfa.y" /* yacc.c:1646  */
    {
          P_RULE(7,"<clase> ::= <clase_vector>");
          clase_actual = VECTOR;
        }
#line 1507 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 177 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(9,"<clase_escalar> ::= <tipo>");}
#line 1513 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 179 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(10,"<tipo> ::= int"); 
            tipo_actual = INT;
        }
#line 1522 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 183 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(11,"<tipo> ::= boolean");
            tipo_actual = BOOLEAN;
        }
#line 1531 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 188 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(15,"<clase_vector> ::= array <tipo> [ constante_entera ]");
        tamanio_vector_actual = (yyvsp[-1].atributos).valor_entero;
        CHECK_ERROR(tamanio_vector_actual >= 1, "El tamanyo del vector excede los limites permitidos (1,64)");
        CHECK_ERROR(tamanio_vector_actual <= MAX_LONG_VECTOR, "El tamanyo del vector excede los limites permitidos (1,64)");
        CHECK_ERROR(dentro_de_fun == 0, "Variable local de tipo no escalar");
    }
#line 1543 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 196 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(18,"<identificadores> ::= <identificador>");}
#line 1549 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 197 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(19,"<identificadores> ::= <identificador> , <identificadores>");}
#line 1555 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 199 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(20,"<funciones> ::= <funcion> <funciones>");}
#line 1561 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 200 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(21,"<funciones> ::=");}
#line 1567 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 202 "src/alfa.y" /* yacc.c:1646  */
    {
            char err_msg[TAM_ERRMSG] = "";
            P_RULE(22,"<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }");

            /* Cerrar ambito actual */
            close_scope();
            dentro_de_fun = 0;

            sprintf(err_msg, "Funcion [%s] sin sentencia de retorno", (yyvsp[-2].atributos).lexema);
            /* Comprobar si hay al menos un retorno */
            CHECK_ERROR(hay_return != 0, err_msg);
        }
#line 1584 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 215 "src/alfa.y" /* yacc.c:1646  */
    {
                    sym_info *sym = sym_t_get_symb((yyvsp[-5].atributos).lexema);
                    
                    sym->num_params = num_parametros_actual;
                    sym->num_vars_loc = num_variables_locales_actual;
                    (yyval.atributos) = (yyvsp[-5].atributos);
                    declararFuncion(alfa_utils_T.fasm, (yyvsp[-5].atributos).lexema, num_variables_locales_actual);
                }
#line 1597 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 224 "src/alfa.y" /* yacc.c:1646  */
    {
            sym_info *sym = sym_t_get_symb((yyvsp[0].atributos).lexema);
            CHECK_ERROR(sym == NULL, "Funcion declarada previamente");

            /* Abrimos un nuevo ambito */
            open_scope((yyvsp[0].atributos).lexema, UNDEFINED, tipo_actual);
            
            /* Inicializar variables globales */
            num_variables_locales_actual = 0;
            pos_variable_local_actual = 0;
            num_parametros_actual = 0;
            pos_parametro_actual = 0;
            tipo_retorno_actual = tipo_actual;

            (yyval.atributos) = (yyvsp[0].atributos);
            dentro_de_fun = 1;
            hay_return = 0;
        }
#line 1620 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 243 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(23,"<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
#line 1626 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 244 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(24,"<parametros_funcion> ::=");}
#line 1632 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 246 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(25,"<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
#line 1638 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 247 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(26,"<resto_parametros_funcion> ::=");}
#line 1644 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 249 "src/alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos) = (yyvsp[0].atributos);
        clase_actual = ESCALAR;
     }
#line 1653 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 254 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(27,"<parametro_funcion> ::= <tipo> <identificador>");
            
            sym_info *sym = sym_t_check((yyvsp[0].atributos).lexema);
            CHECK_ERROR(sym == NULL, "Parametro declarado previamente");

            sym = sym_info_create((yyvsp[0].atributos).lexema, PARAMETRO, tipo_actual, clase_actual, 0, pos_parametro_actual);
            CHECK_ERROR(sym, "Sin memoria");
            
            sym_t_add_symb(sym);

            pos_parametro_actual++;
            num_parametros_actual++;
        }
#line 1672 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 269 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(28,"<declaraciones_funcion> ::= <declaraciones>");}
#line 1678 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 270 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(29,"<declaraciones_funcion> ::=");}
#line 1684 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 272 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(30,"<sentencias> ::= <sentencia>");}
#line 1690 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 273 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(31,"<sentencias> ::= <sentencia> <sentencias>");}
#line 1696 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 275 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(32,"<sentencia> ::= <sentencia_simple> ;");}
#line 1702 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 276 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(33,"<sentencia> ::= <bloque>");}
#line 1708 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 278 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(34,"<sentencia_simple> ::= <asignacion>");}
#line 1714 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 279 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(35,"<sentencia_simple> ::= <lectura>");}
#line 1720 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 280 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(36,"<sentencia_simple> ::= <escritura>");}
#line 1726 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 281 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(38,"<sentencia_simple> ::= <retorno_funcion>");}
#line 1732 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 283 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(40,"<bloque> ::= <condicional>");}
#line 1738 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 284 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(41,"<bloque> ::= <bucle>");}
#line 1744 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 286 "src/alfa.y" /* yacc.c:1646  */
    {
                char err_msg[TAM_ERRMSG] = "";
                sym_info* sym = NULL;

                P_RULE(43,"<asignacion> ::= identificador = <exp>");

                /* Comprueba que exista el identificador */
                sprintf(err_msg, "Identificador [%s] inexistente", (yyvsp[-2].atributos).lexema);
                sym = sym_t_get_symb((yyvsp[-2].atributos).lexema);
                CHECK_ERROR(sym != NULL, err_msg);

                /* Comprueba que no sea ni FUNCION ni VECTOR */
                sprintf(err_msg, "Identificador [%s] no es variable", (yyvsp[-2].atributos).lexema);
                CHECK_ERROR(sym->catg != VECTOR, err_msg);
                CHECK_ERROR(sym->elem != FUNCION, err_msg);

                /* Comprueba que el tipo sea el mismo */
                CHECK_ERROR((yyvsp[0].atributos).tipo == sym->tipo, "Asignacion incompatible");

                /* Asignar */
                if (sym->is_var_loc == UNDEFINED) { /*comprueba si es variable local */
                    asignar(alfa_utils_T.fasm, (yyvsp[-2].atributos).lexema, (yyvsp[0].atributos).es_direccion);

                } else if (sym->elem == PARAMETRO) {
                    asignarParametro(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion, sym->pos_param, num_parametros_actual);
                } else {
                    asignarVariableLocal(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion, sym->pos_var_loc);
                }
            }
#line 1778 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 315 "src/alfa.y" /* yacc.c:1646  */
    {
                sym_info* sym = NULL;
                P_RULE(44,"<asignacion> ::= <elemento_vector> = <exp>");

                sym = sym_t_get_symb((yyvsp[-2].atributos).lexema);
                CHECK_ERROR(sym != NULL, "Identificador inexistente");
                /* Comprueba que el tipo sea el mismo */
                CHECK_ERROR((yyvsp[0].atributos).tipo == sym->tipo, "Asignacion incompatible");

                escribir_elemento_vector(alfa_utils_T.fasm, (yyvsp[0].atributos).lexema, sym->size, sym->elem);
            }
#line 1794 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 327 "src/alfa.y" /* yacc.c:1646  */
    {
                    sym_info* info = NULL;
                    char err_msg[TAM_ERRMSG] = "";
                    P_RULE(48,"<elemento_vector> ::= identificador [ <exp> ]");
                    
                    sprintf(err_msg, "Identificador [%s] inexistente", (yyvsp[-3].atributos).lexema);
                    info = sym_t_get_symb((yyvsp[-3].atributos).lexema);
                    CHECK_ERROR(info != NULL, err_msg); 
                    CHECK_ERROR(info->catg == VECTOR, "Intento de indexacion de una variable que no es de tipo vector");
                    CHECK_ERROR((yyvsp[-1].atributos).tipo == INT, "El indice en una operacion de indexacion tiene que ser de tipo entero");

                    comprobar_indice_vector(alfa_utils_T.fasm, (yyvsp[-3].atributos).lexema, (yyvsp[-1].atributos).es_direccion, info->size);

                    (yyval.atributos).tipo = info->tipo;
                    (yyval.atributos).es_direccion = 1;
                }
#line 1815 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 344 "src/alfa.y" /* yacc.c:1646  */
    {
                /* IF THEN, ELSE VACIO */
                P_RULE(50,"<condicional> ::= if ( <exp> ) { <sentencias> }");
                ifthenelse_fin(alfa_utils_T.fasm, (yyvsp[0].atributos).etiqueta);
            }
#line 1825 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 349 "src/alfa.y" /* yacc.c:1646  */
    {
                /* IF THEN, ELSE CON COSAS */
                P_RULE(51,"<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");
                ifthenelse_fin(alfa_utils_T.fasm, (yyvsp[-4].atributos).etiqueta);
            }
#line 1835 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 358 "src/alfa.y" /* yacc.c:1646  */
    {
                    (yyval.atributos).etiqueta = (yyvsp[-2].atributos).etiqueta;
                    ifthenelse_fin_then(alfa_utils_T.fasm, (yyval.atributos).etiqueta);
                }
#line 1844 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 363 "src/alfa.y" /* yacc.c:1646  */
    {
                CHECK_ERROR((yyvsp[-2].atributos).tipo == BOOLEAN, "Condicional con condicion de tipo int");
                (yyval.atributos).etiqueta = etiqueta++;
                ifthen_inicio(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyval.atributos).etiqueta);
            }
#line 1854 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 369 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(52,"<bucle> ::= while ( <exp> ) { <sentencias> }");
            while_fin(alfa_utils_T.fasm, (yyvsp[-2].atributos).etiqueta);
        }
#line 1863 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 374 "src/alfa.y" /* yacc.c:1646  */
    {
            CHECK_ERROR((yyvsp[-2].atributos).tipo == BOOLEAN, "Bucle con condicion de tipo int");
            while_exp_pila(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyval.atributos).etiqueta);
          }
#line 1872 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 379 "src/alfa.y" /* yacc.c:1646  */
    {
            (yyval.atributos).etiqueta = etiqueta++;
            while_inicio(alfa_utils_T.fasm, (yyval.atributos).etiqueta);
          }
#line 1881 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 384 "src/alfa.y" /* yacc.c:1646  */
    {
            char err_msg[TAM_ERRMSG] = "";
            P_RULE(54,"<lectura> ::= scanf identificador"); 

            sprintf(err_msg, "Identificador [%s] no existe", (yyvsp[0].atributos).lexema);
            sym_info* info = sym_t_check((yyvsp[0].atributos).lexema);
            CHECK_ERROR(info, err_msg);
            CHECK_ERROR((info->elem != FUNCION), "scanf no admite funciones como entrada");
            CHECK_ERROR((info->catg != VECTOR), "scanf no admite vectores como entrada");

            if (info->is_var_loc == UNDEFINED) {
                leer(alfa_utils_T.fasm, info->lexema, info->tipo, 1);
            }
            else if (info->elem == PARAMETRO) {
                escribirParametro(alfa_utils_T.fasm, 1, info->pos_param, num_parametros_actual);
                leer(alfa_utils_T.fasm, info->lexema, info->tipo, 0);
            } else if (info->elem == VARIABLE && info->is_var_loc == 1) {
                escribirVariableLocal(alfa_utils_T.fasm, 1, info->pos_var_loc);
                leer(alfa_utils_T.fasm, info->lexema, info->tipo, 0);
            }
        }
#line 1907 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 406 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(56,"<escritura> ::= printf <exp>");
                escribir(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion, (yyvsp[0].atributos).tipo);
          }
#line 1916 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 411 "src/alfa.y" /* yacc.c:1646  */
    {
                    P_RULE(61,"<retorno_funcion> ::= return <exp>");
                    
                    CHECK_ERROR(dentro_de_fun == 1, "Sentencia de retorno fuera del cuerpo de una funcion");
                    CHECK_ERROR((yyvsp[0].atributos).tipo == tipo_retorno_actual, "Retorno de funcion de tipo incompatible");
                    
                    retornarFuncion(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion);
                    hay_return++;
                }
#line 1930 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 421 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(72,"<exp> ::= <exp> + <exp>");
        
        CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Operacion aritmetica con operandos boolean");
        sumar(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
    }
#line 1944 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 430 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(73,"<exp> ::= <exp> - <exp>");

        CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Operacion aritmetica con operandos boolean");
        restar(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
    }
#line 1958 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 439 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(74,"<exp> ::= <exp> / <exp>");
        
        CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Operacion aritmetica con operandos boolean");
        dividir(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
    }
#line 1972 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 448 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(75,"<exp> ::= <exp> * <exp>");
        
        CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Operacion aritmetica con operandos boolean");
        multiplicar(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
    }
#line 1986 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 457 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(76,"<exp> ::= - <exp>");

        CHECK_ERROR((yyvsp[0].atributos).tipo == INT, "Operacion aritmetica con operando boolean");
        /*check*/
        cambiar_signo(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion);

        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;    
    }
#line 2001 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 467 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(77,"<exp> ::= <exp> && <exp>");

        CHECK_ERROR((yyvsp[-2].atributos).tipo == BOOLEAN && (yyvsp[0].atributos).tipo == BOOLEAN, "Operacion logica con operandos int");
        y(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0; 
    }
#line 2015 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 476 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(78,"<exp> ::= <exp> || <exp>");
        
        CHECK_ERROR((yyvsp[-2].atributos).tipo == BOOLEAN && (yyvsp[0].atributos).tipo == BOOLEAN, "Operacion logica con operandos int");
        o(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
    }
#line 2029 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 485 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(79,"<exp> ::= ! <exp>");
        
        CHECK_ERROR((yyvsp[0].atributos).tipo == BOOLEAN, "Operacion logica con operando int");
        no(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion, etiqueta++);

        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;  
    }
#line 2043 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 494 "src/alfa.y" /* yacc.c:1646  */
    {
        char err_msg[TAM_ERRMSG] = "";
        sym_info* sym = NULL;

        P_RULE(80,"<exp> ::= identificador");

        sym = sym_t_get_symb((yyvsp[0].atributos).lexema);
        sprintf(err_msg, "Variable [%s] no declarada", (yyvsp[0].atributos).lexema);
        CHECK_ERROR(sym != NULL, err_msg);
        /* Comprueba que no sea ni FUNCION ni VECTOR */
        sprintf(err_msg, "Identificador [%s] no es variable", (yyvsp[0].atributos).lexema);
        CHECK_ERROR(sym->catg != VECTOR, err_msg);
        CHECK_ERROR(sym->elem != FUNCION, err_msg);

        (yyval.atributos).tipo = sym->tipo;
        (yyval.atributos).es_direccion = 0;

        /* Variable global */
        if (sym->elem == VARIABLE && sym->is_var_loc == UNDEFINED) {
            escribir_operando(alfa_utils_T.fasm, (yyvsp[0].atributos).lexema, 1);
        /* Parametro */
        } else if (sym->elem == PARAMETRO) {
            escribirParametro(alfa_utils_T.fasm, 0, sym->pos_param, num_parametros_actual);
        /* Variable local */
        } else if (sym->elem == VARIABLE && sym->is_var_loc != UNDEFINED) {
            escribirVariableLocal(alfa_utils_T.fasm, 0, sym->pos_var_loc);
        }
    }
#line 2076 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 522 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(81,"<exp> ::= <constante>");

            (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
            (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
            
            char valor[INT_TO_CHAR];
            sprintf(valor, "%d", (yyvsp[0].atributos).valor_entero);
            escribir_operando(alfa_utils_T.fasm, valor, 0);
    }
#line 2091 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 532 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(82,"<exp> ::= ( <exp> )");

            (yyval.atributos).tipo = (yyvsp[-1].atributos).tipo;
            (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
    }
#line 2102 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 538 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(83,"<exp> ::= ( <comparacion> )");

            (yyval.atributos).tipo = (yyvsp[-1].atributos).tipo;
            (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
    }
#line 2113 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 544 "src/alfa.y" /* yacc.c:1646  */
    {
            P_RULE(85,"<exp> ::= <elemento_vector>");

            apilar_valor_elemento_vector(alfa_utils_T.fasm);

            (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
            (yyval.atributos).es_direccion = 0;

    }
#line 2127 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 553 "src/alfa.y" /* yacc.c:1646  */
    {
            sym_info* sym = NULL;

            P_RULE(88,"<identificador> ( <lista_expresiones> )");

            sym = sym_t_check((yyvsp[-3].atributos).lexema);
            CHECK_ERROR(sym != NULL, "Identificador de funcion no declarada");
            CHECK_ERROR(sym->elem == FUNCION, "No es una funcion");
            CHECK_ERROR((yyvsp[-1].atributos).num_parametros_llamada_actual == sym->num_params, "Numero incorrecto de parametros en llamada a funcion");
            
            llamarFuncion(alfa_utils_T.fasm, (yyvsp[-3].atributos).lexema, (yyvsp[-1].atributos).num_parametros_llamada_actual);
            
            en_explist = 0;

            (yyval.atributos).tipo = sym->tipo;
            (yyval.atributos).es_direccion = 0;
    }
#line 2149 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 571 "src/alfa.y" /* yacc.c:1646  */
    {
                        /* 
                        Para contorlar que no se invoque a funciones en una
                        lista de paramteros de otra invocacion
                        */
                        CHECK_ERROR(en_explist == 0, "No esta permitido el uso de llamadas a funciones como parametros de otras funciones");
                        en_explist = 1;
                    }
#line 2162 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 580 "src/alfa.y" /* yacc.c:1646  */
    {
                        P_RULE(89,"<lista_expresiones> ::= <exp> <resto_lista_expresiones>");
                        (yyval.atributos).num_parametros_llamada_actual = (yyvsp[0].atributos).num_parametros_llamada_actual + 1;
                    }
#line 2171 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 584 "src/alfa.y" /* yacc.c:1646  */
    {
                      P_RULE(90,"<lista_expresiones> ::=");
                      (yyval.atributos).num_parametros_llamada_actual = 0;
                    }
#line 2180 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 589 "src/alfa.y" /* yacc.c:1646  */
    {
                        P_RULE(91,"<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>");
                        (yyval.atributos).num_parametros_llamada_actual = (yyvsp[0].atributos).num_parametros_llamada_actual + 1;
                    }
#line 2189 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 593 "src/alfa.y" /* yacc.c:1646  */
    {
                            P_RULE(92,"<resto_lista_expresiones> ::=");
                            (yyval.atributos).num_parametros_llamada_actual = 0;
                        }
#line 2198 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 598 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(93,"<comparacion> ::= <exp> == <exp>");

                CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Comparacion con operandos boolean");
                igual(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta++);

                (yyval.atributos).tipo = BOOLEAN;
                (yyval.atributos).es_direccion = 0;
            }
#line 2212 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 607 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(94,"<comparacion> ::= <exp> != <exp>");
                
                CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Comparacion con operandos boolean");
                distinto(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta++);
                
                (yyval.atributos).tipo = BOOLEAN;
                (yyval.atributos).es_direccion = 0;
            }
#line 2226 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 616 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(95,"<comparacion> ::= <exp> <= <exp>");
                
                CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Comparacion con operandos boolean");
                menor_igual(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta++);
                
                (yyval.atributos).tipo = BOOLEAN;
                (yyval.atributos).es_direccion = 0;
            }
#line 2240 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 625 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(96,"<comparacion> ::= <exp> >= <exp>");

                CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Comparacion con operandos boolean");
                mayor_igual(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta++);

                (yyval.atributos).tipo = BOOLEAN;
                (yyval.atributos).es_direccion = 0;
            }
#line 2254 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 634 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(97,"<comparacion> ::= <exp> < <exp>");
                
                CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Comparacion con operandos boolean");
                menor(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta++);
                
                (yyval.atributos).tipo = BOOLEAN;
                (yyval.atributos).es_direccion = 0;
            }
#line 2268 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 643 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(98,"<comparacion> ::= <exp> > <exp>");

                CHECK_ERROR((yyvsp[-2].atributos).tipo == INT && (yyvsp[0].atributos).tipo == INT, "Comparacion con operandos boolean");
                mayor(alfa_utils_T.fasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta++);
                
                (yyval.atributos).tipo = BOOLEAN;
                (yyval.atributos).es_direccion = 0;
            }
#line 2282 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 653 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(99,"<constante> ::= <constante_logica>");
                (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
                (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
            }
#line 2292 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 658 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(100,"<comparacion> ::= <constante_entera>");
                (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
                (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
            }
#line 2302 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 664 "src/alfa.y" /* yacc.c:1646  */
    {
                        P_RULE(102,"<constante_logica> ::= true");
                        (yyval.atributos).tipo = BOOLEAN;
                        (yyval.atributos).es_direccion = 0;
                        (yyval.atributos).valor_entero = 1;
                    }
#line 2313 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 670 "src/alfa.y" /* yacc.c:1646  */
    {
                        P_RULE(103,"<constante_logica> ::= false");
                        (yyval.atributos).tipo = BOOLEAN;
                        (yyval.atributos).es_direccion = 0;
                        (yyval.atributos).valor_entero = 0;
                    }
#line 2324 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 677 "src/alfa.y" /* yacc.c:1646  */
    {
                        P_RULE(104,"<constante_entera> ::= TOK_CONSTANTE_ENTERA");
                        (yyval.atributos).tipo = INT;
                        (yyval.atributos).es_direccion = 0;
                        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
                    }
#line 2335 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 685 "src/alfa.y" /* yacc.c:1646  */
    {
                    P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
                    (yyval.atributos) = (yyvsp[0].atributos);
                }
#line 2344 "alfa.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 690 "src/alfa.y" /* yacc.c:1646  */
    {
        char err_msg[TAM_ERRMSG] = "";
        sym_info* sym = NULL;
        
        P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
        sprintf(err_msg, "Identificador [%s] duplicado", (yyvsp[0].atributos).lexema);
        CHECK_ERROR(sym_t_check((yyvsp[0].atributos).lexema) == NULL, err_msg);
        
        sym = sym_info_create((yyvsp[0].atributos).lexema, VARIABLE, tipo_actual, clase_actual, tamanio_vector_actual, pos_variable_local_actual);
        CHECK_ERROR(sym, "Sin memoria");
        
        sym_t_add_symb(sym);
        if(sym->is_var_loc){
            pos_variable_local_actual++;
            sym->pos_var_loc = pos_variable_local_actual;
            num_variables_locales_actual++;
        }
        tamanio_vector_actual = 0;
    }
#line 2368 "alfa.tab.c" /* yacc.c:1646  */
    break;


#line 2372 "alfa.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 710 "src/alfa.y" /* yacc.c:1906  */
