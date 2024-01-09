
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
            | affectation
            | condition
            | boucle_while 
            | boucle_for 
            





declaration : type IDENTIFICATEUR fin_crea
            | type IDENTIFICATEUR EGAL expression fin_crea
            | declaration_matrix



creation : IDENTIFICATEUR fin_crea
            | IDENTIFICATEUR EGAL expression fin_crea

fin_crea : POINT_VIRGULE
        | VIRGULE creation




declaration_matrix : type id_matrix fin_crea_mat
        | type id_vector fin_crea_mat
        | type id_matrix EGAL creation_matrix fin_crea_mat
        | type id_vector EGAL creation_vector fin_crea_mat

id_matrix : IDENTIFICATEUR CROCHET_OUVRANT expression CROCHET_FERMANT CROCHET_OUVRANT expression CROCHET_FERMANT

id_vector : IDENTIFICATEUR CROCHET_OUVRANT expression CROCHET_FERMANT

creation_mat : id_matrix fin_crea_mat
            | id_vector fin_crea_mat
            | id_matrix EGAL creation_matrix fin_crea_mat
            | id_vector EGAL creation_vector fin_crea_mat

fin_crea_mat : POINT_VIRGULE
        | VIRGULE creation_mat



creation_matrix : ACCOLADE_OUVRANTE creation_vector creation_matrix_prime ACCOLADE_FERMANTE

creation_matrix_prime : VIRGULE creation_vector creation_matrix_prime
                    | %empty

creation_vector : ACCOLADE_OUVRANTE CONSTANTE_ENTIERE creation_vector_prime ACCOLADE_FERMANTE

creation_vector_prime : VIRGULE CONSTANTE_CARACTERE creation_vector_prime
                    | %empty











affectation : IDENTIFICATEUR EGAL expression POINT_VIRGULE
            | id_matrix EGAL expression POINT_VIRGULE
            | id_vector EGAL expression POINT_VIRGULE


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

operateur2 : PLUS
            | MOINS
            | TRANSPOSITION

type : INT
    | FLOAT
    | MATRIX

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

op_test : %empty

op_test2 : %empty

for_init : IDENTIFICATEUR
            | IDENTIFICATEUR EGAL operande
            | type IDENTIFICATEUR EGAL operande

            



%%

void yyerror(const char * msg) {
	fprintf(stderr, "Erreur de syntaxe : %s\n", msg);
}
