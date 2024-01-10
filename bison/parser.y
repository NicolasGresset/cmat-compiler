 %{
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

%}

%union
 {
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
}

%token <strval> IDENTIFICATEUR
%token <intval> CONSTANTE_ENTIERE
%token <floatval> CONSTANTE_FLOTTANTE

%token INT FLOAT MATRIX ELSE IF WHILE FOR
    CONSTANTE_CARACTERE AND OR NOT
    PLUS MOINS FOIS DIVISE PLUS_PLUS
    MOINS_MOINS EGAL TRANSPOSITION
    PARENTHESE_OUVRANTE PARENTHESE_FERMANTE
    CROCHET_OUVRANT CROCHET_FERMANT
    ACCOLADE_OUVRANTE ACCOLADE_FERMANTE
    VIRGULE POINT_VIRGULE APOSTROPHE
    GUILLEMET MAIN POINT_EXCLAMATION
    INFERIEUR INFERIEUR_EGAL SUPERIEUR SUPERIEUR_EGAL EGAL_EGAL

%type <exprval> declaration operande expression
%type <typeval> type
%type <intval> M
%type <N_t> N
%type <for_fin_t> for_fin
%type <typetest> op_test
%type <boolexpr> test test2 test3
%type <instr_type> liste_instructions instruction condition condition_suite boucle_while boucle_for


%left PLUS MOINS
%left FOIS DIVISE

%nonassoc UEXPR

%start S

%%
S : INT MAIN PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
{
    ListLabel_free($6.next);
}

liste_instructions
: liste_instructions M instruction {complete($1.next, $2);  ListLabel_free($1.next); $$.next = $3.next;}
| instruction {$$.next = $1.next;}

instruction
: declaration {$$.next = NULL;}
| condition {$$.next = $1.next;}
| boucle_while {$$.next = $1.next;}
| boucle_for {$$.next = $1.next;}
| affectation {$$.next = NULL;}

declaration
: type IDENTIFICATEUR fin_aff {
    struct id_t * id = table_hachage_get(SYMTAB,$2);
     if ( id != NULL )
     {
         fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", $2);
         exit(1);
     }
     id = id_init($2, $1);
     table_hachage_put(SYMTAB,id);
     //gencode(CODE,COPY,id,NULL,NULL);
 }
| type IDENTIFICATEUR EGAL expression fin_aff  {
    struct id_t * id = table_hachage_get(SYMTAB, $2);
    if ( id != NULL )
    {
        fprintf(stderr, "error: redefinition of ‘%s’\n", $2);
        exit(1);
    }

    id = id_init($2, $1);
    table_hachage_put(SYMTAB,id);
    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE,COPY,sym_id,$4.ptr,NULL);

 }
;

affectation
//: IDENTIFICATEUR fin_aff --> affectation sans effet, à garder ?
: IDENTIFICATEUR EGAL expression fin_aff {
    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", $1);
        exit(1);
    }
    if (id->type != $3.type)
    {
        fprintf(stderr, "error: incompatible types\n");
        exit(1);
    }

    struct symbol *  sym_id = symbol_id(*id);
    gencode(CODE,COPY,sym_id,$3.ptr,NULL);

 }
 //| expression fin_aff
;

fin_aff
: POINT_VIRGULE
| VIRGULE affectation

// Changer expression en ecpreesion_bin puis mettre dans la grammaire expression : expression_bin | expression_mat
expression
: expression PLUS expression {
    // Le cas où les 2 expressions n'ont pas le même type n'est pas géré
    $$.ptr = newtemp(SYMTAB, $1.type);
    gencode(CODE,BOP_PLUS,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire en fonction de int ou float convertir le type
    $$.type = $1.type;
    // Utile pour la boucle_for savoir où compléter test.true
    $$.num = MAX($1.num, $3.num);
    $$.num += 1;
}
| expression MOINS expression {
    $$.ptr = newtemp(SYMTAB, $1.type);
    gencode(CODE,BOP_MOINS,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;

    $$.num = MAX($1.num, $3.num);
    $$.num += 1;
}
| expression FOIS expression {
    $$.ptr = newtemp(SYMTAB, $1.type);
    gencode(CODE,BOP_MULT,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;

    $$.num = MAX($1.num, $3.num);
    $$.num += 1;
}
| expression DIVISE expression {
    $$.ptr = newtemp(SYMTAB, $1.type);
    gencode(CODE,BOP_DIVISE,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;

    $$.num = MAX($1.num, $3.num);
    $$.num += 1;
}
|  MOINS expression %prec UEXPR   {
    $$.ptr = newtemp(SYMTAB, $2.type);
    gencode(CODE,UOP_MOINS,$$.ptr,$2.ptr,NULL);

    // Type temporaire
    $$.type = $2.type;

    $$.num = $2.num + 1;
}
|  PLUS expression %prec UEXPR   {
    $$.ptr = newtemp(SYMTAB, $2.type);
    gencode(CODE,UOP_PLUS,$$.ptr,$2.ptr,NULL);

    // Type temporaire
    $$.type = $2.type;

    $$.num = $2.num + 1;
}
|  POINT_EXCLAMATION expression %prec UEXPR {;} // A completer
|  TRANSPOSITION expression %prec UEXPR {;} // Faire un nouveau terminal avec expression_mat pour différencier les 2 dans les conditions ?
|  PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE {$$.ptr = $2.ptr; $$.type = $2.type; $$.num = $2.num;}
//| operateur2 IDENTIFICATEUR expression %prec UEXPR {;}
| operande {$$.type = $1.type; $$.num = 0;}
 //| op_fin IDENTIFICATEUR
 //| IDENTIFICATEUR op_fin

operande
: IDENTIFICATEUR
{
    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",$1);
        exit(1);
    }

    struct symbol * sym_id = symbol_id(*id);
    $$.ptr = sym_id;
    $$.type = sym_id->u.id.type;
}
| CONSTANTE_ENTIERE {$$.ptr = symbol_const_int($1); $$.type = ENTIER;}
| CONSTANTE_FLOTTANTE {$$.ptr = symbol_const_float($1); $$.type = REEL;}
| MATRIX

 // POUR SIMPLIFIER
/* op_fin : PLUS_PLUS */
/*         | MOINS_MOINS */


type
: INT {$$ = ENTIER;}
| FLOAT {$$ = REEL;}

condition
: IF  PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE
M { stack_id_push(SYMTAB);} liste_instructions
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}
ACCOLADE_FERMANTE N condition_suite
{
    complete($3.true, $6);
    ListLabel_free($3.true);

    $$.next = concat($8.next, $11.next);

    if ($12.next != NULL)
    {
        complete($3.false, $11.quad);
        ListLabel_free($3.false);
        $$.next = concat($$.next, $12.next);
    }
    else
    {
        $$.next = concat($$.next, $3.false);
    }

    printf("if.next : ");
    ListLabel_print($$.next);
    printf("\n");
}

condition_suite
: %empty {$$.next = NULL;}
| ELSE ACCOLADE_OUVRANTE  { stack_id_push(SYMTAB);} liste_instructions
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);}ACCOLADE_FERMANTE
{
    $$.next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());

    $$.next = concat($$.next, $4.next);
}

boucle_while :
WHILE PARENTHESE_OUVRANTE M test PARENTHESE_FERMANTE
ACCOLADE_OUVRANTE M {stack_id_push(SYMTAB);} liste_instructions
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);} ACCOLADE_FERMANTE
{
    complete($4.true, $7);
    ListLabel_free($4.true);
    complete($9.next, $3);
    ListLabel_free($9.next);
    $$.next = $4.false;

    struct symbol * q = quad_label();
    q->u.addr = $3;
    CODE->quads[CODE->nextquad].sym3 = q;
    gencode(CODE, Q_GOTO, NULL, NULL, q);
}

// Pas fait comme en cours mais ça a l'air de marcher ?
boucle_for
: FOR PARENTHESE_OUVRANTE {stack_id_push(SYMTAB);} for_init POINT_VIRGULE
M test POINT_VIRGULE
for_fin PARENTHESE_FERMANTE
ACCOLADE_OUVRANTE M liste_instructions
{table_hachage_print(SYMTAB); stack_id_pop(SYMTAB);} ACCOLADE_FERMANTE
{
    complete($7.true, $12 - $9.num);
    ListLabel_free($7.true);
    complete($13.next, $6);
    ListLabel_free($13.next);
    $$.next = $7.false;

    if ($9.ptr != NULL)
    {
        gencode(CODE,COPY,$9.id,$9.ptr,NULL);
    }

    struct symbol * q = quad_label();
    q->u.addr = $6;
    CODE->quads[CODE->nextquad].sym3 = q;
    gencode(CODE, Q_GOTO, NULL, NULL, q);
}

for_init
: for_fin
{
    if ($1.ptr != NULL)
    {
        gencode(CODE,COPY,$1.id,$1.ptr,NULL);
    }
}
| type IDENTIFICATEUR EGAL expression
{
    struct id_t * id = table_hachage_get(SYMTAB,$2);
    if ( id != NULL )
    {
        fprintf(stderr, "error: redefinition of ‘%s’\n", $2);
        exit(1);
    }
    id = id_init($2, $1);
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE,COPY,sym_id,$4.ptr,NULL);
}

for_fin
: IDENTIFICATEUR
{
    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", $1);
        exit(1);
    }

    struct symbol * sym_id = symbol_id(*id);
    $$.id = sym_id;
    $$.ptr = NULL;
}
| IDENTIFICATEUR EGAL expression
{
    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", $1);
        exit(1);
    }
    if (id->type != $3.type)
    {
        fprintf(stderr, "error: incompatible types\n");
        exit(1);
    }
    struct symbol * sym_id = symbol_id(*id);
    $$.id = sym_id;
    $$.ptr = $3.ptr;
    $$.num = $3.num;
}

test
: test OR M test2
{
    complete($1.false, $3);
    ListLabel_free($1.false);
    $$.true = concat($1.true, $4.true);
    $$.false = $4.false;
}
| test2 {$$.true = $1.true; $$.false = $1.false;}

test2
: test2 AND M test3
{
    complete($1.true, $3);
    ListLabel_free($1.true);
    $$.false = concat($1.false, $4.false);
    $$.true = $4.true;
}
| test3 {$$.true = $1.true; $$.false = $1.false;}

test3
:  expression op_test expression
{
    $$.true = NULL;
    $$.false = NULL;

    $$.true = creerListe(CODE->nextquad);

    struct symbol * q = quad_label();
    CODE->quads[CODE->nextquad].sym3 = q;
    // Generate the code associate with op_test
    switch ($2)
    {
    case EQ:
        gencode(CODE, Q_IF_EQ, $1.ptr, $3.ptr, q);
        break;
    case NEQ:
        gencode(CODE, Q_IF_NEQ, $1.ptr, $3.ptr, q);
        break;
    case LT:
        gencode(CODE, Q_IF_LT, $1.ptr, $3.ptr, q);
        break;
    case LE:
        gencode(CODE, Q_IF_LE, $1.ptr, $3.ptr, q);
        break;
    case GT:
        gencode(CODE, Q_IF_GT, $1.ptr, $3.ptr, q);
        break;
    case GE:
        gencode(CODE, Q_IF_GE, $1.ptr, $3.ptr, q);
        break;
    }

    $$.false = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());
}
| expression
{
    $$.true = NULL;
    $$.false = NULL;

    $$.true = creerListe(CODE->nextquad);

    struct symbol * q_zero = symbol_const_int(0);

    struct symbol * q = quad_label();
    CODE->quads[CODE->nextquad].sym3 = q;

    // Generate the code associate with op_test
    gencode(CODE, Q_IF_NEQ, $1.ptr, q_zero, q);
}

op_test
: EGAL_EGAL {$$ = EQ;}
| POINT_EXCLAMATION EGAL {$$ = NEQ;}
| INFERIEUR {$$ = LT;}
| INFERIEUR_EGAL {$$ = LE;}
| SUPERIEUR {$$ = GT;}
| SUPERIEUR_EGAL {$$ = GE;}

M : %empty {$$ = CODE->nextquad;}
N : %empty
{
    $$.next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());
    $$.quad = CODE->nextquad;
}
%%
void yyerror(const char * msg) {
    fprintf(stderr, "Erreur de syntaxe : %s\n", msg);

}
