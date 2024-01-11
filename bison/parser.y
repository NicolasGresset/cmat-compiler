
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
    RETURN

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
S : INT MAIN PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE liste_instructions RETURN CONSTANTE_ENTIERE ACCOLADE_FERMANTE

liste_instructions
: liste_instructions M instruction {complete($1.next, $2); $$.next = $3.next;}
| instruction {$$.next = $1.next;}

instruction
: declaration {$$.next = NULL;}
| condition {$$.next = $1.next;}
| boucle_while {$$.next = NULL;}
| boucle_for {$$.next = NULL;}
| affectation {$$.next = NULL;}




// Ici declaration

declaration
: declaration_bin
| declaration_mat

// Ici déclaration bin

declaration_bin
: type IDENTIFICATEUR POINT_VIRGULE {
    struct symbol * id = symtable_get(SYMTAB,$2);
     if ( id != NULL )
     {
         fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", $2);
         exit(1);
     }
     id = symtable_put(SYMTAB,$2, $1);
     //gencode(CODE,COPY,id,NULL,NULL);
 }
| type IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE  {
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




// Ici déclaration matrix.

declaration_mat
 // Si tu veux on peut separer encore plus matrice et vecteurs
: MATRIX id_matrix fin_crea_mat 
| MATRIX id_vector fin_crea_mat
| MATRIX id_matrix EGAL creation_matrix fin_crea_mat
| MATRIX id_vector EGAL creation_vector fin_crea_mat
| MATRIX id_matrix EGAL expression_mat fin_crea_mat
// Si on separe matrix et vector, on peut aussi faire expression_mat et expression_vec
| MATRIX id_vector EGAL expression_mat fin_crea_mat 

id_matrix
: IDENTIFICATEUR CROCHET_OUVRANT operande CROCHET_FERMANT CROCHET_OUVRANT operande CROCHET_FERMANT

id_vector
: IDENTIFICATEUR CROCHET_OUVRANT operande CROCHET_FERMANT

creation_mat
: id_matrix fin_crea_mat
| id_vector fin_crea_mat
| id_matrix EGAL creation_matrix fin_crea_mat 
| id_vector EGAL creation_vector fin_crea_mat

fin_crea_mat
: POINT_VIRGULE
| VIRGULE creation_mat


creation_matrix
: expression_mat
| ACCOLADE_OUVRANTE creation_vector creation_matrix_prime ACCOLADE_FERMANTE

creation_matrix_prime
: VIRGULE creation_vector creation_matrix_prime
| %empty

creation_vector
: expression_vector
| ACCOLADE_OUVRANTE expression_bin creation_vector_prime ACCOLADE_FERMANTE

creation_vector_prime
: VIRGULE CONSTANTE_FLOTTANTE creation_vector_prime
| %empty


// Ici affectation

affectation
: affectation_bin
| affectation_mat


// Ici affectation bin 

affectation_bin
: IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE {
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
;

// Ici affectation matrix

affectation_mat
// 2 choses possibles : affectation matrice complète, ou affectation case matrice -> 2e cas = affectation_bin, t'as une préférence sur où le mettre ?
: IDENTIFICATEUR EGAL expression_mat POINT_VIRGULE
| id_matrix EGAL expression_bin POINT_VIRGULE
| id_vector EGAL expression_bin POINT_VIRGULE




// Ici expression

expression 
: expression_bin
| expression_mat

// Ici expression_bin
// A la fin, j'ai mis element de matrice
// Je sais qu'on en a parlé, notamment avec CONSTANTE_FLOTTANTE, mais je ne retrouve plus le fil de pensée
// Dis moi tout de suite s'il faut que je revise un truc pour que ce soit bon pour toi

expression_bin
: expression_bin PLUS expression_bin {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_PLUS,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;
}
| expression_bin MOINS expression_bin {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_MOINS,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;
}
| expression_bin FOIS expression_bin {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_MULT,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;
}
| expression_bin DIVISE expression_bin {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_DIVISE,$$.ptr,$1.ptr,$3.ptr);

    // Type temporaire
    $$.type = $1.type;
}
|  MOINS expression_bin %prec UEXPR   {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,UOP_MOINS,$$.ptr,$2.ptr,NULL);

    // Type temporaire
    $$.type = $2.type;
}
|  PLUS expression_bin %prec UEXPR   {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,UOP_PLUS,$$.ptr,$2.ptr,NULL);

    // Type temporaire
    $$.type = $2.type;
}
// |  POINT_EXCLAMATION expression %prec UEXPR {;}
|  PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE {;}
//| operateur2 IDENTIFICATEUR expression %prec UEXPR {;}
| PLUS_PLUS IDENTIFICATEUR
| MOINS_MOINS IDENTIFICATEUR
| IDENTIFICATEUR PLUS_PLUS
| IDENTIFICATEUR MOINS_MOINS
| operande {$$.type = $1.type;}
// Cas element d'une matrice
| id_matrix
| id_vector


// Ici expression_mat

expression_mat
: TRANSPOSITION expression_mat %prec UEXPR {;}
| expression_mat PLUS expression_mat
| expression_mat MOINS expression_mat
| expression_mat FOIS expression_mat
| expression_mat DIVISE expression_mat
| IDENTIFICATEUR   // Juste pour les IDs associés au type matrix du coup 
// Operation avec constante
| expression_mat PLUS CONSTANTE_FLOTTANTE
| expression_mat MOINS CONSTANTE_FLOTTANTE
| expression_mat FOIS CONSTANTE_FLOTTANTE
| expression_mat DIVISE CONSTANTE_FLOTTANTE
// Dans l'autre sens
| CONSTANTE_FLOTTANTE PLUS expression_mat
| CONSTANTE_FLOTTANTE MOINS expression_mat
| CONSTANTE_FLOTTANTE FOIS expression_mat
| CONSTANTE_FLOTTANTE DIVISE expression_mat
// Autre
| expression_mat PLUS_PLUS
| expression_mat MOINS_MOINS
| PLUS_PLUS expression_mat
| MOINS_MOINS expression_mat
| MOINS expression_mat
// Extraction   --> Je pense partir comme ça, mais avant faut que tu me dises si 
//possible pour toi de regarder les conditions sur les dimensions pour l'extraction
| IDENTIFICATEUR CROCHET_OUVRANT intervalle CROCHET_FERMANT CROCHET_OUVRANT intervalle CROCHET_FERMANT


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


