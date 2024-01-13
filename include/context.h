#pragma once

/* Header qui définit le contexte du programme */

typedef struct {
    int tos;
    char *code_resultat;
} context_t;

context_t *context_new() ;