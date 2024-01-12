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

%}
%union
 {
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
         int row;
         int col;
     } taille_mat_t;
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

%type <exprval_t> declaration_bin operande expression_bin id_matrix
%type <typeval> type
%type <taille_mat_t> creation_matrix creation_matrix_prime creation_vector creation_vector_prime
%type <intval> M
%type <N_t> N
%type <for_fin_t> for_fin
%type <typetest> op_test
%type <boolexpr> test test2 test3
%type <instr_type> liste_instructions instruction condition condition_suite boucle_while boucle_for declaration


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
| affectation_bin {$$.next = NULL;}

declaration
: declaration_bin {$$.next = NULL;}
| MATRIX declaration_mat {$$.next = NULL;}

declaration_bin
: type IDENTIFICATEUR POINT_VIRGULE {
    struct id_t * id = table_hachage_get(SYMTAB,$2);
     if ( id != NULL )
     {
         fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", $2);
         exit(1);
     }
     id = id_init($2, $1);
     table_hachage_put(SYMTAB,id);


     struct symbol * sym_id = symbol_id(*id);
     gencode(CODE, Q_DECLARE, sym_id,NULL,NULL);
 }
| type IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE  {
    struct id_t * id = table_hachage_get(SYMTAB, $2);
    if ( id != NULL )
    {
        fprintf(stderr, "error: redefinition of ‘%s’\n", $2);
        exit(1);
    }

    id = id_init($2, $1);
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, Q_DECLARE, sym_id,NULL,NULL);
    gencode(CODE,COPY,sym_id,$4.ptr,NULL);

 }
;

// Ici déclaration matrix.

declaration_mat
 // Si tu veux on peut separer encore plus matrice et vecteurs
: id_matrix fin_crea_mat
| id_vector fin_crea_mat
| id_matrix EGAL creation_matrix fin_crea_mat
| id_vector EGAL creation_vector fin_crea_mat
| MATRIX id_matrix EGAL expression_mat fin_crea_mat
// Si on separe matrix et vector, on peut aussi faire expression_bin_mat et expression_bin_vec
| MATRIX id_vector EGAL expression_mat fin_crea_mat

id_matrix
: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT
{
    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id != NULL )
    {
        fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", $1);
        exit(1);
    }
    id = id_init($1, MATRIX_TYPE);

    id->row = $3;
    id->col = $6;
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, Q_DECLARE_MAT, sym_id,NULL,NULL);
};

id_vector
: IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT
{
    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id != NULL )
    {
        fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", $1);
        exit(1);
    }
    id = id_init($1, MATRIX_TYPE);

    id->row = $3;
    id->col = 1;
    table_hachage_put(SYMTAB,id);

    struct symbol * sym_id = symbol_id(*id);
    gencode(CODE, Q_DECLARE_MAT, sym_id,NULL,NULL);
};

fin_crea_mat
: POINT_VIRGULE
| VIRGULE declaration_mat


creation_matrix
//: expression_mat
: ACCOLADE_OUVRANTE creation_matrix_prime creation_vector ACCOLADE_FERMANTE
{
    if ($2.row != -1 && $2.row != $3.row)
        fprintf(stderr, "error : incompatible column size\n");

    $$.col = 1 + $2.col;
    $$.row = $2.row;
}
creation_matrix_prime
:  creation_matrix_prime creation_vector VIRGULE
{
    if ($1.row != -1 && $1.row != $2.row)
        fprintf(stderr, "error : incompatible column size\n");

    $$.col = 1 + $2.col;
    $$.row = $1.row;
}
| %empty
{
    $$.row = -1;
    $$.col = 0;
};

creation_vector
//: expression_vector
: ACCOLADE_OUVRANTE creation_vector_prime operande ACCOLADE_FERMANTE
{
    $$.row = 1 + $2.row;
    $$.col = 1;
    // newtemp
    struct symbol * sym_temp = newtemp(SYMTAB, REEL);
    gencode(CODE, Q_DECLARE, sym_temp,NULL,NULL);
    gencode(CODE, COPY, sym_temp, $3.ptr, NULL);

};
creation_vector_prime
: creation_vector_prime operande VIRGULE
{
    $$.row = 1 + $1.row;
    $$.col = 1;
    // newtemp
    struct symbol * sym_temp = newtemp(SYMTAB, REEL);
    gencode(CODE, Q_DECLARE, sym_temp,NULL,NULL);
    gencode(CODE, COPY, sym_temp, $2.ptr, NULL);
}
| %empty {$$.row = 0; $$.col = 0;};



// Affectation

affectation_bin
//: IDENTIFICATEUR fin_aff --> affectation_bin sans effet, à garder ?
: IDENTIFICATEUR EGAL expression_bin POINT_VIRGULE {
    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr, "error: ‘%s’ undeclared\n", $1);
        exit(1);
    }
    if (id->type != $3.type)
    {
        fprintf(stderr, "error: incompatible types\n");
        //exit(1);
    }

    struct symbol *  sym_id = symbol_id(*id);
    gencode(CODE,COPY,sym_id,$3.ptr,NULL);

 }


expression_bin
: expression_bin PLUS expression_bin {
    $$ = expression_gestion(CODE, SYMTAB, BOP_PLUS, $$, $1, $3);
}
| expression_bin MOINS expression_bin {
    $$ = expression_gestion(CODE, SYMTAB, BOP_MOINS, $$, $1, $3);
}
| expression_bin FOIS expression_bin {
    $$ = expression_gestion(CODE, SYMTAB, BOP_MULT, $$, $1, $3);
}
| expression_bin DIVISE expression_bin {
    $$ = expression_gestion(CODE, SYMTAB, BOP_DIVISE, $$, $1, $3);
}
|  MOINS expression_bin %prec UEXPR   {
    $$.ptr = newtemp(SYMTAB, $2.type);
    gencode(CODE, Q_DECLARE, $$.ptr, NULL, NULL);

    gencode(CODE,UOP_MOINS,$$.ptr,$2.ptr,NULL);

    // Type temporaire
    $$.type = $2.type;

    $$.num = $2.num + 1;
}
|  PLUS expression_bin %prec UEXPR   {
    $$.ptr = newtemp(SYMTAB, $2.type);
    gencode(CODE, Q_DECLARE, $$.ptr, NULL, NULL);

    gencode(CODE,UOP_PLUS,$$.ptr,$2.ptr,NULL);

    // Type temporaire
    $$.type = $2.type;

    $$.num = $2.num + 1;
}
//|  POINT_EXCLAMATION expression_bin %prec UEXPR {;} // A completer
|  TRANSPOSITION expression_bin %prec UEXPR {;} // Faire un nouveau terminal avec expression_mat pour différencier les 2 dans les conditions ?
|  PARENTHESE_OUVRANTE expression_bin PARENTHESE_FERMANTE {$$.ptr = $2.ptr; $$.type = $2.type; $$.num = $2.num;}
//| operateur2 IDENTIFICATEUR expression_bin %prec UEXPR {;}
| PLUS_PLUS operande
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    $$.ptr = newtemp(SYMTAB, $2.type);
    gencode(CODE, Q_DECLARE, $$.ptr, NULL, NULL);

    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_PLUS,$$.ptr,one,$2.ptr);

    // Type temporaire en fonction de int ou float convertir le type
    $$.type = $2.type;
    $$.num = 1;
}
| MOINS_MOINS operande
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    $$.ptr = newtemp(SYMTAB, $2.type);
    gencode(CODE, Q_DECLARE, $$.ptr, NULL, NULL);

    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_MOINS,$$.ptr,$2.ptr, one);

    // Type temporaire en fonction de int ou float convertir le type
    $$.type = $2.type;
    $$.num += 1;
}
| operande PLUS_PLUS
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    $$.ptr = newtemp(SYMTAB, $1.type);
    gencode(CODE, Q_DECLARE, $$.ptr, NULL, NULL);

    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_PLUS,$$.ptr,one,$1.ptr);

    // Type temporaire en fonction de int ou float convertir le type
    $$.type = $1.type;
    $$.num = 1;
}
| operande MOINS_MOINS
{
    // Le cas où les 2 expressions  n'ont pas le même type n'est pas géré
    $$.ptr = newtemp(SYMTAB, $1.type);
    gencode(CODE, Q_DECLARE, $$.ptr, NULL, NULL);

    struct symbol * one = symbol_const_int(1);
    gencode(CODE,BOP_MOINS,$$.ptr, $1.ptr, one);

    // Type temporaire en fonction de int ou float convertir le type
    $$.type = $1.type;
    $$.num = 1;
}
| operande {$$.type = $1.type; $$.num = 0;};

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
| CONSTANTE_ENTIERE {$$.ptr = symbol_const_int((int)$1); $$.type = ENTIER;}
| CONSTANTE_FLOTTANTE {$$.ptr = symbol_const_float($1); $$.type = REEL;}
| IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT
CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT
{

    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",$1);
        exit(1);
    }
    if (id->type != MATRIX_TYPE)
    {
        fprintf(stderr,"%s is not of type MATRIX\n",$1);
        exit(1);
    }
    // test sur les dimensions du tableau
    if (id->row <= $3 || id->col <= $6)
    {
        fprintf(stderr, "Erreur de dimension pour %s\n", $1);
    }

    // Pour obtenir la valeur du tableau
    /* T3 = T1*20 */
    struct symbol * t3 = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, t3, NULL, NULL);

    struct symbol * t3_temp = symbol_const_int(($3 + 1) * id->col);
    struct symbol * j = symbol_const_int(($6 + 1));
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

    $$.ptr = symbol_composante;
    $$.type = REEL;
}
| IDENTIFICATEUR CROCHET_OUVRANT CONSTANTE_ENTIERE CROCHET_FERMANT
{
    struct id_t * id = table_hachage_get(SYMTAB,$1);
    if ( id == NULL )
    {
        fprintf(stderr,"Name '%s' undeclared\n",$1);
        exit(1);
    }
    if (id->type != MATRIX_TYPE)
    {
        fprintf(stderr,"%s is not of type MATRIX\n",$1);
        exit(1);
    }
    // test sur les dimensions du tableau
    if (id->row >= $3)
    {
        fprintf(stderr, "Erreur de dimension pour %s\n", $1);
    }

    // Pour obtenir la valeur du tableau
    /* T3 = T1*20 */
    struct symbol * t3 = newtemp(SYMTAB, ENTIER);
    gencode(CODE, Q_DECLARE, t3, NULL, NULL);
    struct symbol * t3_temp = symbol_const_int($3 * id->col);
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

    $$.ptr = symbol_composante;
    $$.type = REEL;
};

// Ici expression_mat

expression_mat
: TRANSPOSITION expression_mat %prec UEXPR {;}
| expression_mat PLUS expression_mat
| expression_mat MOINS expression_mat
| expression_mat FOIS expression_mat
| expression_mat DIVISE expression_mat
| IDENTIFICATEUR   // Juste pour les IDs associés au type matrix du coup
| CONSTANTE_FLOTTANTE
  // Pose des problèmes de shift/reduce
/* // Operation avec constante */
/* | expression_mat PLUS CONSTANTE_FLOTTANTE */
/* | expression_mat MOINS CONSTANTE_FLOTTANTE */
/* | expression_mat FOIS CONSTANTE_FLOTTANTE */
/* | expression_mat DIVISE CONSTANTE_FLOTTANTE */
/* // Dans l'autre sens */
/* | CONSTANTE_FLOTTANTE PLUS expression_mat */
/* | CONSTANTE_FLOTTANTE MOINS expression_mat */
/* | CONSTANTE_FLOTTANTE FOIS expression_mat */
/* | CONSTANTE_FLOTTANTE DIVISE expression_mat */
// Autre
| MOINS expression_mat %prec UEXPR
| IDENTIFICATEUR PLUS_PLUS
| IDENTIFICATEUR MOINS_MOINS
| PLUS_PLUS IDENTIFICATEUR
| MOINS_MOINS IDENTIFICATEUR
// Extraction   --> Je pense partir comme ça, mais avant faut que tu me dises si
//possible pour toi de regarder les conditions sur les dimensions pour l'extraction
  //| IDENTIFICATEUR CROCHET_OUVRANT intervalle CROCHET_FERMANT CROCHET_OUVRANT intervalle CROCHET_FERMANT


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
| type IDENTIFICATEUR EGAL expression_bin
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
| IDENTIFICATEUR EGAL expression_bin
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
:  expression_bin op_test expression_bin
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
| expression_bin
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
