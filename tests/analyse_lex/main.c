#include "../../include/compil.tab.h" // à modifier selon le nom du fichier
#include <stdio.h>

int main(char **argv, int argc) {
    int token = 1;

    while (token) {
        token = yylex();
        printf("%d ", token);
    }
    printf("\n");
    return 0;
}