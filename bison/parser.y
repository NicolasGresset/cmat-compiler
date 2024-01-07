%{
#include "CMat.h"

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
%type <typetest> op_test
%type <boolexpr> test
%type <instr_type> liste_instructions instruction condition condition_suite


%left PLUS MOINS
%left FOIS DIVISE

%nonassoc UEXPR

%start S

%%
S : INT MAIN PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE

liste_instructions
: liste_instructions M instruction {complete($1.next, $2); $$.next = $3.next;}
| instruction {$$.next = $1.next;}

instruction
: declaration {$$.next = NULL;}
| condition {$$.next = $1.next;}
| boucle_while {$$.next = NULL;}
| boucle_for {$$.next = NULL;}
| affectation {$$.next = NULL;}

declaration
: type IDENTIFICATEUR fin_aff {
    struct symbol * id = symtable_get(SYMTAB,$2);
     if ( id != NULL )
     {
         fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", $2);
         exit(1);
     }
     id = symtable_put(SYMTAB,$2, $1);
     //gencode(CODE,COPY,id,NULL,NULL);
 }
| type IDENTIFICATEUR EGAL expression fin_aff  {
    struct symbol * id = symtable_get(SYMTAB,$2);
    if ( id != NULL )
    {
        fprintf(stderr, "error: redefinition of ‘%s’\n", $2);
        exit(1);
    }
    id = symtable_put(SYMTAB,$2, $1);
    gencode(CODE,COPY,id,$4.ptr,NULL);
 }
;

affectation
//: IDENTIFICATEUR fin_aff --> affectation sans effet, à garder ?
: IDENTIFICATEUR EGAL expression fin_aff {
    struct symbol * id = symtable_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", $1);
        exit(1);
    }
    if (id->u.id.type != $3.type)
    {
        fprintf(stderr, "error: incompatible types\n");
        exit(1);
    }
    gencode(CODE,COPY,id,$3.ptr,NULL);

 }
 //| expression fin_aff
;

fin_aff
: POINT_VIRGULE
| VIRGULE affectation

// Changer expression en ecpreesion_bin puis mettre dans la grammaire expression : expression_bin | expression_mat
expression
: expression PLUS expression {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_PLUS,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;
}
| expression MOINS expression {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_MOINS,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;
}
| expression FOIS expression {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_MULT,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;
}
| expression DIVISE expression {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_DIVISE,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;
}
|  MOINS expression %prec UEXPR   {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,UOP_MOINS,$$.ptr,$2.ptr,NULL);

    // Type temporaire
    $$.type = $2.type;
}
|  PLUS expression %prec UEXPR   {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,UOP_PLUS,$$.ptr,$2.ptr,NULL);

    // Type temporaire
    $$.type = $2.type;
}
|  POINT_EXCLAMATION expression %prec UEXPR {;}
|  TRANSPOSITION expression %prec UEXPR {;} // Faire un nouveau terminal avec expression_mat pour différencier les 2 dans les conditions ?
|  PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE {;}
//| operateur2 IDENTIFICATEUR expression %prec UEXPR {;}
| operande {$$.type = $1.type;}
 //| op_fin IDENTIFICATEUR
 //| IDENTIFICATEUR op_fin

operande
: IDENTIFICATEUR
{
    struct symbol * id = symtable_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",$1);
        exit(1);
    }
    $$.ptr = id;
    $$.type = id->u.id.type;
}
| CONSTANTE_ENTIERE {$$.ptr = symtable_const_int(SYMTAB,$1); $$.type = ENTIER;}
| CONSTANTE_FLOTTANTE {$$.ptr = symtable_const_float(SYMTAB,$1); $$.type = REEL;}
| MATRIX

 // POUR SIMPLIFIER
/* op_fin : PLUS_PLUS */
/*         | MOINS_MOINS */

 // On doit les mettre tous un par un sinon on se souvient pas de quel
 // token a été utiliisé est ça crée des confits shift/reduce
/* operateur : PLUS */
/*             | MOINS */
/*             | FOIS */
/*             | DIVISE */

/* operateur2 : PLUS */
/*             | MOINS */
/*             | POINT_EXCLAMATION */
/*             | TRANSPOSITION */


type
: INT {$$ = ENTIER;}
| FLOAT {$$ = REEL;}

condition
: IF PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE ACCOLADE_OUVRANTE
M liste_instructions ACCOLADE_FERMANTE N condition_suite
{
    complete($3.true, $6);
    ListLabel_free($3.true);

    /* $$.next = concat($7.next, $9.next); */
    /* $$.next = NULL; */
    /* $$.next = concat($3.false, $$.next); */
    /* $$.next = concat($$.next, creerListe(CODE->nextquad)); */

    $$.next = concat($7.next, $9.next);

    if ($10.next != NULL)
    {
        complete($3.false, $9.quad);
        $$.next = concat($$.next, $10.next);
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
| ELSE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
{
    $$.next = creerListe(CODE->nextquad);
    gencode(CODE, Q_GOTO_UNKNOWN, NULL, NULL, quad_label());

    $$.next = concat($$.next, $3.next);
}

boucle_while : WHILE PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE
                ACCOLADE_FERMANTE liste_instructions ACCOLADE_FERMANTE

boucle_for : FOR ACCOLADE_OUVRANTE for_init POINT_VIRGULE test POINT_VIRGULE
            expression PARENTHESE_FERMANTE
            ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE

test : //PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE -> dans les expressions
expression {;} // Comment générer le code pour : if (a) => equivalent à if (a!=0)
| expression op_test expression
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
//| test op_test2 test {;}


op_test
: EGAL_EGAL {$$ = EQ;}
| POINT_EXCLAMATION EGAL {$$ = NEQ;}
| INFERIEUR {$$ = LT;}
| INFERIEUR_EGAL {$$ = LE;}
| SUPERIEUR {$$ = GT;}
| SUPERIEUR_EGAL {$$ = GE;}

/* op_test2 */
/* : AND */
/* | OR */
/* | NOT */

for_init : IDENTIFICATEUR
            | IDENTIFICATEUR EGAL operande
            | type IDENTIFICATEUR EGAL operande


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
