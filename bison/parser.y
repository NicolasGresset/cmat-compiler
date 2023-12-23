%{
#include "CMat.h"

void yyerror (const char * msg);
extern int yylex();

%}

%union
 {
     struct
     {
         struct symbol * ptr;
     } exprval;

     name_t strval;
     type_t typeval;
     int intval;
     float floatval;
}

%token <strval> IDENTIFICATEUR
%token <intval> CONSTANTE_ENTIERE
%token <floatval> CONSTANTE_FLOTTANTE

%token INT FLOAT MATRIX ELSE IF WHILE FOR
    CONSTANTE_CARACTERE
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

%left PLUS MOINS
%left FOIS DIVISE

%nonassoc UEXPR
 //%nonassoc UMINUS

%start S

%%
S : INT MAIN PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE

liste_instructions : %empty
                    | liste_instructions instruction

instruction : declaration
            | condition
            | boucle_while
            | boucle_for
            | affectation
 // Manque l'affichage --> Simple grammaire comme le main : PRINTF ( un id ici ) ; ?

declaration
: type IDENTIFICATEUR fin_aff {
    struct symbol * id = symtable_get(SYMTAB,$2);
     if ( id != NULL )
     {
         fprintf(stderr, "error: redeclaration of ‘%s’ with no linkage\n", $2);
         exit(1);
     }
     id = symtable_put(SYMTAB,$2, $1);
     gencode(CODE,COPY,id,NULL,NULL);
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
    if (id->type != $3.ptr->type)
    {
        fprintf(stderr, "error: incompatible types\n");
        exit(1);
    }
    gencode(CODE,COPY,id,$3.ptr,NULL);

 }
 //| expression fin_aff
;

fin_aff : POINT_VIRGULE
        | VIRGULE affectation

expression
: expression PLUS expression {
    $$.ptr = newtemp(SYMTAB);
    gencode(CODE,BOP_PLUS,$$.ptr,$1.ptr,$3.ptr);
}
| expression MOINS expression {;}
| expression FOIS expression {;}
| expression DIVISE expression {;}
|  MOINS expression %prec UEXPR {;}
|  PLUS expression %prec UEXPR {;}
|  POINT_EXCLAMATION expression %prec UEXPR {;}
|  TRANSPOSITION expression %prec UEXPR {;}
| PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE {;}
//| operateur2 IDENTIFICATEUR expression %prec UEXPR {;}
| operande
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
}
| CONSTANTE_ENTIERE {$$.ptr = symtable_const(SYMTAB,$1, ENTIER);}
| CONSTANTE_FLOTTANTE {$$.ptr = symtable_const(SYMTAB,$1, REEL);}
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

condition : IF PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE
            ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
            condition_suite

condition_suite : %empty
                | ELSE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE

boucle_while : WHILE PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE
                ACCOLADE_FERMANTE liste_instructions ACCOLADE_FERMANTE

boucle_for : FOR ACCOLADE_OUVRANTE for_init POINT_VIRGULE test POINT_VIRGULE
            expression PARENTHESE_FERMANTE
            ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE

test : //PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE -> dans les expressions
     expression
     | expression op_test expression
 // | op_test2 IDENTIFICATEUR --> dans expression


op_test : INFERIEUR
         | INFERIEUR_EGAL
         | SUPERIEUR
         | SUPERIEUR_EGAL
         | EGAL_EGAL

 // devenu inutile dans test
/* op_test2 : POINT_EXCLAMATION */
/*           | PLUS_PLUS */
/*           | MOINS_MOINS */

for_init : IDENTIFICATEUR
            | IDENTIFICATEUR EGAL operande
            | type IDENTIFICATEUR EGAL operande

%%

void yyerror(const char * msg) {
    fprintf(stderr, "Erreur de syntaxe : %s\n", msg);
}
