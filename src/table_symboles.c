#include "table_symboles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct table_hachage_t *table_hachage_init(void) {
    struct table_hachage_t *hash_tab = malloc(sizeof(struct table_hachage_t));
    if (hash_tab == NULL) {
        fprintf(stderr, "Erreur lors de la création de la table de hachage\n");
        exit(1);
    }
    hash_tab->alveoles = NULL;
    stack_id_push(hash_tab);
    hash_tab->temporary = 0;
    return hash_tab;
}

void stack_id_push(struct table_hachage_t *hash_tab) {
    struct stack_id_t *new_id_stack = malloc(sizeof(struct stack_id_t));
    if (new_id_stack == NULL) {
        fprintf(stderr, "Erreur lors de la création d'une nouvelle pile "
                        "d'identificateurs\n");
        exit(1);
    }

    new_id_stack->top = 0;

    struct noeud_hachage_t *noeud = malloc(sizeof(struct noeud_hachage_t));
    if (noeud == NULL) {
        fprintf(
            stderr,
            "Erreur lors de la création d'un noeud de la table de hachage\n");
        exit(1);
    }

    noeud->stack_id = new_id_stack; // Faire pointer
    noeud->next = hash_tab->alveoles;
    hash_tab->alveoles = noeud;
}

void stack_id_pop(struct table_hachage_t *hash_tab) {
    if (hash_tab->alveoles == NULL) {
        fprintf(stderr, "Pop impossible pas de pile existante\n");
    }
    // Libérer les id
    struct stack_id_t *current_stack = hash_tab->alveoles->stack_id;

    for (int i = 0; i < current_stack->top; ++i) {
        free(current_stack->items[i]);
    }

    free(current_stack);

    // Changer le pointeur la table de hachage et libérer l'espace
    struct noeud_hachage_t *noeud = hash_tab->alveoles;
    hash_tab->alveoles = noeud->next;
    free(noeud);
}

void table_hachage_put(struct table_hachage_t *hash_tab,
                       struct id_t *identificateur) {
    if (hash_tab->alveoles == NULL) {
        fprintf(stderr, "Ajout impossible pas de pile existante\n");
    }

    struct stack_id_t *current_stack = hash_tab->alveoles->stack_id;
    current_stack->items[current_stack->top] = identificateur;
    current_stack->top++;
}

struct id_t *id_init(const name_t name, const type_t type) {
    struct id_t *id = malloc(sizeof(struct id_t));
    if (id == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire création d'un id_t\n");
        exit(1);
    }

    id->type = type;
    strncpy(id->name, name, TAILLE_MAX_TOKEN);
    return id;
}

struct symbol *newtemp(struct table_hachage_t *hash_tab, type_t type) {
    struct id_t *id;
    name_t name;

    snprintf(name, TAILLE_MAX_TOKEN, ".tmp%d", hash_tab->temporary);
    id = id_init(name, type);

    table_hachage_put(hash_tab, id);
    ++(hash_tab->temporary);

    return symbol_id(*id);
}

struct id_t *table_hachage_get(struct table_hachage_t *hash_tab,
                               const char *name) {
    if (hash_tab->alveoles == NULL) {
        fprintf(stderr,
                "Recherche impossible : Erreur pas de pile existante\n");
    }

    struct noeud_hachage_t *noeud = hash_tab->alveoles;

    while (noeud != NULL && noeud->stack_id != NULL) {
        struct stack_id_t *stack_id = noeud->stack_id;
        for (int i = 0; i < stack_id->top; ++i) {
            if (strncmp(name, stack_id->items[i]->name, TAILLE_MAX_TOKEN) ==
                0) {
                return stack_id->items[i];
            }
        }
        noeud = noeud->next;
    }
    return NULL;
}

void id_print(struct id_t *id) {
    switch (id->type) {
    case ENTIER:
        printf("    %p :     int    %s\n", &(id->name), id->name);
        break;
    case REEL:
        printf("    %p :     float    %s\n", &(id->name), id->name);
        break;
    default:
        printf("    Type non reconnu     %s\n", id->name);
        break;
    }
}

void stack_id_print(struct stack_id_t *stack_id) {
    if (stack_id->top == 0)
        printf("Pile vide\n");

    for (int i = 0; i < stack_id->top; ++i) {
        id_print(stack_id->items[i]);
    }
}

void table_hachage_print(struct table_hachage_t *hash_tab) {
    printf("-----Pile du Contexte Courant-----\n");
    if (hash_tab == NULL) {
        printf("Stack vide\n");
    }

    if (hash_tab->alveoles == NULL) {
        printf("Stack vide\n");
    }

    struct noeud_hachage_t *current = hash_tab->alveoles;
    while (current != NULL) {
        stack_id_print(current->stack_id);
        current = current->next;
    }

    printf("-------------------------------\n");
}

void table_hachage_free(struct table_hachage_t *hash_tab) {
    while (hash_tab->alveoles != NULL) {
        stack_id_pop(hash_tab);
    }

    free(hash_tab);
}
