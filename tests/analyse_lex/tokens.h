#pragma once

#define LONGUEUR_TOKEN_MAX 32 // longueur max d'un token

#define LEX_ERROR 400

// Symboles non-alphanumériques

// Opérateurs
#define PLUS 1
#define MOINS 2
#define FOIS 3
#define DIVISE 4
#define PLUS_PLUS 5
#define MOINS_MOINS 6
#define EGAL 7
#define TRANSPOSITION 8


#define PARENTHESE_OUVRANTE 21
#define PARENTHESE_FERMANTE 22
#define ACCOLADE_OUVRANTE 23
#define ACCOLADE_FERMANTE 24
#define CROCHET_OUVRANT 25
#define CROCHET_FERMANT 26
#define VIRGULE 27
#define APOSTROPHE 28
#define POINT_VIRGULE 29
#define GUILLEMET 30


// Structure de contrôle
#define ELSE 103
#define IF 104
#define FOR 105
#define WHILE 106

// Constantes
#define CONSTANTE_ENTIERE 200
#define CONSTANTE_FLOTTANTE 201
#define CONSTANTE_CARACTERE 202
#define IDENTIFICATEUR 203
#define COMMENTAIRE 204

// Types
#define INT 300
#define FLOAT 301
#define MATRIX 302