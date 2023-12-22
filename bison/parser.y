%{
#include <stdio.h>
#include "lexer.h"

void yyerror (const char * msg);

%}

%token INT FLOAT MATRIX ELSE IF WHILE FOR
    CONSTANTE_ENTIERE CONSTANTE_FLOTTANTE
    CONSTANTE_CARACTERE IDENTIFICATEUR
    PLUS MOINS FOIS DIVISE PLUS_PLUS
    MOINS_MOINS EGAL TRANSPOSITION
    PARENTHESE_OUVRANTE PARENTHESE_FERMANTE
    CROCHET_OUVRANT CROCHET_FERMANT
    ACCOLADE_OUVRANTE ACCOLADE_FERMANTE
    VIRGULE POINT_VIRGULE APOSTROPHE
    GUILLEMET MAIN POINT_EXCLAMATION
    INFERIEUR INFERIEUR_EGAL SUPERIEUR SUPERIEUR_EGAL EGAL_EGAL

%left PLUS MOINS
%left FOIS DIVISE

%nonassoc UEXPR
%nonassoc UMINUS

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

declaration : type IDENTIFICATEUR fin_aff
            | type IDENTIFICATEUR EGAL expression fin_aff

affectation : IDENTIFICATEUR fin_aff
            | IDENTIFICATEUR EGAL expression fin_aff
 //| expression fin_aff

fin_aff : POINT_VIRGULE
        | VIRGULE affectation

expression
: expression PLUS expression {;}
| expression MOINS expression {;}
| expression FOIS expression {;}
| expression DIVISE expression {;}
|  MOINS expression %prec UMINUS {;}
|  PLUS expression %prec UMINUS {;}
|  POINT_EXCLAMATION expression %prec UMINUS {;}
|  TRANSPOSITION expression %prec UMINUS {;}
| PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE {;}
//| operateur2 IDENTIFICATEUR expression %prec UEXPR {;}
| operande
 //| op_fin IDENTIFICATEUR
 //| IDENTIFICATEUR op_fin

operande : IDENTIFICATEUR
        | CONSTANTE_ENTIERE
        | CONSTANTE_FLOTTANTE
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


type : INT
    | FLOAT

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
