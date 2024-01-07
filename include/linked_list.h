#pragma once
#include <stdlib.h>
#include <stdio.h>

/**
 * Librairie de l'implémentation d'une liste chaînée pour les listes
 * d'adresses
 */

/* Liste d'étiquettes */
struct ListLabel {
    unsigned int addr;
    struct ListLabel * next;
};

struct  ListLabel * creerListe(unsigned int address);

void ListLabel_free(struct ListLabel * l);

void ListLabel_print(struct ListLabel * l);

struct ListLabel * concat(struct ListLabel * l1,
                               struct ListLabel * l2);
