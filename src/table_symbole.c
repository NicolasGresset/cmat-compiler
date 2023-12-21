#include "../include/table_symbole.h"
#include "../include/tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_INITIALE 16
typedef unsigned int uint;

typedef struct table {
    unsigned int allocated;
    unsigned int size;
    char *tokens;
} table;

char *get_nth_token(table *table, uint n) {
    if (table->size == 0) {
        fprintf(stderr, "Table empty, returned NULL pointer\n");
        return NULL;
    }
    if (n >= table->size) {
        fprintf(stderr, "Trying to access out of boundaries, assuming you "
                        "wanted the last element\n");
        n = table->size - 1;
    }
    return table->tokens + LONGUEUR_TOKEN_MAX * n;
}

/**
 * @brief Ajoute les identificateurs prédifinis du langage à la table des
 * symboles
 *
 * @param table
 */
void ajouter_id_predifini(table *table) {
    //ajouter_symbole(table, "int");
    //ajouter_symbole(table, "float");
    //ajouter_symbole(table, "void");
    //ajouter_symbole(table, "main");
    (void)table;
}

table * allouer_table(void) {
    table *table_des_symboles = malloc(sizeof(*table_des_symboles));
    if (table_des_symboles == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        free(table_des_symboles);
        exit(1);
    }
    table_des_symboles->allocated = TAILLE_INITIALE;
    table_des_symboles->size = 0;
    table_des_symboles->tokens =
        malloc(table_des_symboles->allocated * LONGUEUR_TOKEN_MAX *
               sizeof(*(table_des_symboles->tokens)));
    ajouter_id_predifini(table_des_symboles);
    return table_des_symboles;
}

/**
 * @brief Ajoute le token token à la table des symboles table
 *
 * @param table
 * @param token
 */
void table_append(table *table, char *token) {
    if (table->size == table->allocated) {
        table->allocated *= 2;
        table->tokens =
            reallocarray(table->tokens, table->allocated, LONGUEUR_TOKEN_MAX);
        if (table->tokens == NULL) {
            fprintf(stderr, "Erreur de ré-allocation\n");
            free(table);
            exit(1);
        }
    }

    table->size++;
    if (snprintf(get_nth_token(table, table->size - 1), LONGUEUR_TOKEN_MAX,
                 "%s", token) >= LONGUEUR_TOKEN_MAX) {
        fprintf(stderr, "Chaine trop longue : résultat tronqué\n");
    }
}

int get_symbole(table *table, char *token) {
    uint index = 0;
    for (; index < table->size; index++) {
        if (strcmp(get_nth_token(table, index), token) == 0) {
            return index;
        }
    }
    table_append(table, token);
    return index;
}

void free_table(table *table) {
    free(table->tokens);
    free(table);
}
