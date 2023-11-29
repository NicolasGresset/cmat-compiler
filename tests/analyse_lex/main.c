#include "tokens.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern int yylex();

#define CHK(op)           \
    do {                  \
        if ((op) == (-1)) \
            raler(#op);   \
    } while (0)

void raler(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

/**
 * @brief Programme de test de l'analyseur lexical
 * Prend un unique argument en ligne de commande corresopndant au
 * fichier à analyser
 * Ecrit sur la sortie standard les tokens reconnus
 * Le code des tokens est confrme au contenu de tokens.h
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <file to parse>\n", argv[0]);
        printf("Un fichier de test est disponible sous le nom de test.txt\n");
        return 1;
    }
    int fd;
    CHK((fd = open(argv[1], O_RDONLY)));
    CHK(dup2(fd, 0));
    CHK(close(fd));

    // printf("Ceci est un test de l'analyseur lexical\n");
    // printf("---------------------------------------\n");
    // printf("Le fichier à analyser est %s\n", argv[1]);
    // printf("le fichier attendu pour test.txt est attendu.txt\n");
    // printf("---------------------------------------\n\n");
    int token = 1;

    while (token) {
        token = yylex();
        if (token == LEX_ERROR) {
            // afficher le token en rouge
            printf("\033[1;31merreur \033[0m\n");
            continue;
        }
        printf("%d\n", token);
    }
    printf("\n");
    return 0;
}