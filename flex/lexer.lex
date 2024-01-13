%{
#include "CMat.h"
#include "parser.h"

#define LEX_ERROR 300
//#define LONGUEUR_TOKEN_MAX 32 // longueur max d'un token

char token_valeur[TAILLE_MAX_TOKEN];

/**
 * Ecrit de manière sécurisée la valeur du token dans la variable token_valeur
 * et renvoie un entier correpondant au code du token si il n'y a pas eu troncature,
 * LEX_ERROR sinon
 */
int ecrireToken(int token_code){
    int n;
    if ((n = snprintf(token_valeur, TAILLE_MAX_TOKEN, "%s", yytext)) >= TAILLE_MAX_TOKEN){
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

_CONSTANTE_ENTIERE [0-9]({CHIFFRE})*
_CONSTANTE_CARACTERE '\\?{LETTRE}'
_CONSTANTE_FLOTTANTE {SIGNIFICANT}{EXPONENT}?{SUFFIX}?

COMMENTAIRE_SIMPLE \/\/(.)*
COMMENTAIRE_PLUSIEURS_LIGNES [/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]
_COMMENTAIRE {COMMENTAIRE_SIMPLE}|{COMMENTAIRE_PLUSIEURS_LIGNES}

_SYMBOLE_NON_ALPHANUMERIQUE [\+|\-|\*|\/|\%|!|\|\||&&|==|!=|<=|>=|<|>|=|;|,|\(|\)|\[|\]|\{|\}|\&|\||<<|>>|'|"]

_STRING \"([^\\\n]|(\\.))*?\"

%%
"int" return INT;
"float" return FLOAT;
"matrix" return MATRIX;

"else" return ELSE;
"if" return IF;
"while" return WHILE;
"for" return FOR;
"return" return RETURN;

"main" {symtable_new();return MAIN;}
"printf" return PRINTF;
"print" return PRINT;
"printmat" return PRINTMAT;


{_CONSTANTE_ENTIERE} {
    sscanf(yytext,"%d",&(yylval.intval));
    return CONSTANTE_ENTIERE;
}//return ecrireToken(CONSTANTE_ENTIERE);
{_CONSTANTE_FLOTTANTE} {
    sscanf(yytext,"%f",&(yylval.floatval));
    return CONSTANTE_FLOTTANTE;
}//return ecrireToken(CONSTANTE_FLOTTANTE);
{_CONSTANTE_CARACTERE} return ecrireToken(CONSTANTE_CARACTERE);
{_IDENTIFICATEUR} {
    if ( yyleng > TAILLE_MAX_TOKEN )
        fprintf(stderr,"Identifier '%s' too long, truncated\n",yytext);
    strncpy(yylval.strval,yytext, TAILLE_MAX_TOKEN);
    yylval.strval[TAILLE_MAX_TOKEN] = '\0';
    //return ecrireToken(IDENTIFICATEUR);
    return IDENTIFICATEUR;
}

{_STRING} { return STRING; }

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
"||" return OR;
"&&" return AND;
"." return POINT;

{_COMMENTAIRE} ;
[[:space:]]+ ;
. { fprintf (stderr, "caractère illégal (%c) ignoré\n", yytext[0]); return LEX_ERROR;}
%%