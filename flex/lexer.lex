%{
#include "../include/tokens.h"
#include <stdio.h>

char token_valeur[LONGUEUR_TOKEN_MAX];

int ecrireToken(int token_code){
    int n;
    if ((n = snprintf(token_valeur, LONGUEUR_TOKEN_MAX, "%s", yytext)) >= LONGUEUR_TOKEN_MAX){
        return LEX_ERROR; //error
    }
    return token_code; // cas normal
}
%}

LETTRE [a-zA-Z_]
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

_CONTROLE for|else|if|while
_SYMBOLE_NON_ALPHANUMERIQUE [\+|\-|\*|\/|\%|!|\|\||&&|==|!=|<=|>=|<|>|=|;|,|\(|\)|\[|\]|\{|\}|\&|\||<<|>>|'|"]

%%

{_CONSTANTE_ENTIERE} return ecrireToken(CONSTANTE_ENTIERE);
{_CONSTANTE_FLOTTANTE} return ecrireToken(CONSTANTE_FLOTTANTE);
{_CONSTANTE_CARACTERE} return ecrireToken(CONSTANTE_CARACTERE);
{_CONTROLE} return ecrireToken(CONTROLE);
{_IDENTIFICATEUR} return ecrireToken(IDENTIFICATEUR);
{_SYMBOLE_NON_ALPHANUMERIQUE} return ecrireToken(SYMBOLE_NON_ALPHANUMERIQUE);

{_COMMENTAIRE} ;
[[:space:]]+ ;
%%
