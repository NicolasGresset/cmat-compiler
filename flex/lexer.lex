%{
#include <stdio.h>
#include "parser.h"

#define LEX_ERROR 300
#define LONGUEUR_TOKEN_MAX 32 // longueur max d'un token

char token_valeur[LONGUEUR_TOKEN_MAX];

/**
 * Ecrit de manière sécurisée la valeur du token dans la variable token_valeur
 * et renvoie un entier correpondant au code du token si il n'y a pas eu troncature,
 * LEX_ERROR sinon
 */
int ecrireToken(int token_code){
    int n;
    if ((n = snprintf(token_valeur, LONGUEUR_TOKEN_MAX, "%s", yytext)) >= LONGUEUR_TOKEN_MAX){
        return LEX_ERROR; //error
    }
    return token_code; // cas normal
}
%}

%option nounput
%option noinput

LETTRE [a-zA-Z]
CHIFFRE [0-9]

SIGNIFICANT [0-9]+|[0-9]+\.[0-9]*|[0-9]*\.[0-9]+
EXPONENT [eE][-+]?{CHIFFRE}+
SUFFIX [fFlL]

_IDENTIFICATEUR {LETTRE}({LETTRE}|{CHIFFRE})*

_CONSTANTE_ENTIERE [1-9]({CHIFFRE})*
_CONSTANTE_CARACTERE '\\?{LETTRE}'
_CONSTANTE_FLOTTANTE {SIGNIFICANT}{EXPONENT}?{SUFFIX}?

COMMENTAIRE_SIMPLE \/\/(.)*
COMMENTAIRE_PLUSIEURS_LIGNES \/\*([^\*]|\**[^\/])*\*\/
_COMMENTAIRE {COMMENTAIRE_SIMPLE}|{COMMENTAIRE_PLUSIEURS_LIGNES}

_SYMBOLE_NON_ALPHANUMERIQUE [\+|\-|\*|\/|\%|!|\|\||&&|==|!=|<=|>=|<|>|=|;|,|\(|\)|\[|\]|\{|\}|\&|\||<<|>>|'|"]

%%
"int" return INT;
"float" return FLOAT;
"matrix" return MATRIX;

"else" return ELSE;
"if" return IF;
"while" return WHILE;
"for" return FOR;

"main" return MAIN;

{_CONSTANTE_ENTIERE} return ecrireToken(CONSTANTE_ENTIERE);
{_CONSTANTE_FLOTTANTE} return ecrireToken(CONSTANTE_FLOTTANTE);
{_CONSTANTE_CARACTERE} return ecrireToken(CONSTANTE_CARACTERE);
{_IDENTIFICATEUR} return ecrireToken(IDENTIFICATEUR);
"+" return PLUS;
"-" return MOINS;
"*" return FOIS;
"/" return DIVISE;
"++" return PLUS_PLUS;
"--" return MOINS_MOINS;
"=" return EGAL;
"~" return TRANSPOSITION;
"(" return PARENTHESE_OUVRANTE;
")" return PARENTHESE_FERMANTE;
"[" return CROCHET_OUVRANT;
"]" return CROCHET_FERMANT;
"{" return ACCOLADE_OUVRANTE;
"}" return ACCOLADE_FERMANTE;
"," return VIRGULE;
";" return POINT_VIRGULE;
"'" return APOSTROPHE;
"\"" return GUILLEMET;
">" return SUPERIEUR;
"<" return INFERIEUR;
"<=" return INFERIEUR_EGAL;
">=" return SUPERIEUR_EGAL;
"!" return POINT_EXCLAMATION;
"==" return EGAL_EGAL;


{_COMMENTAIRE} ;
[[:space:]]+ ;
. { fprintf (stderr, "caractère illégal (%c) ignoré\n", yytext[0]); return LEX_ERROR;}
%%
