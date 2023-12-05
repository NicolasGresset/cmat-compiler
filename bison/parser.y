
%{
#include <stdio.h>
extern int yylex();
void yyerror (const char * msg);

%}

%token INT FLOAT MATRIX ELSE IF WHILE FOR \
    CONSTANTE_ENTIERE CONSTANTE_FLOTTANTE \
    CONSTANTE_CARACTERE IDENTIFICATEUR \
    PLUS MOINS FOIS DIVISE PLUS_PLUS \
    MOINS_MOINS EGAL TRANSPOSITION \
    PARENTHESE_OUVRANTE PARENTHESE_FERMANTE \
    CROCHET_OUVRANT CROCHET_FERMANT \
    ACCOLADE_OUVRANTE ACCOLADE_FERMANTE \
    VIRGULE POINT_VIRGULE APOSTROPHE \
    GUILLEMET

%start S


%%

S : INT MAIN OPAR FPAR OACC liste_instructions FACC

liste_instructions : %empty
                    | liste_instructions instruction

instruction : %empty
            | declaration
            | condition
            | boucle_while 
            | boucle_for 
            
declaration : type IDENTIFICATEUR fin_aff
            | type IDENTIFICATEUR EGAL expression fin_aff

affectation : IDENTIFICATEUR fin_aff
            | IDENTIFICATEUR EGAL expression fin_aff

fin_aff : POINT_VIRGULE
        | VIRGULE affectation

expression : op_fin IDENTIFICATEUR
            | IDENTIFICATEUR op_fin
            | operateur2 expression
            | expression operateur expression
            | PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE
            | operande

operande : IDENTIFICATEUR
        | CONSTANTE_ENTIERE
        | CONSTANTE_FLOTTANTE
        | MATRIX

op_fin : %empty
        |PLUS_PLUS
        | MOINS_MOINS

operateur : PLUS
            | MOINS
            | FOIS
            | DIVISE

operateur2 : 

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

test : PARENTHESE_OUVRANTE test PARENTHESE_FERMANTE
    | expression
    | op_test2 test
    | test op_test test

op_test : 

op_test2 :

for_init : IDENTIFICATEUR
            | IDENTIFICATEUR EGAL operande
            | type IDENTIFICATEUR EGAL operande

            



%%

void yyerror(const char * msg) {
	fprintf(stderr, "Erreur de syntaxe : %s\n", msg);
}
