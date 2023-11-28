#pragma once

typedef struct table table;

/**
 * @brief Alloue une structure de table, et y ajoute les identificateurs de base
 * (char, int, float, void, main) et renvoie un pointeur vers celle-ci
 *
 * @return table*
 */
table *allouer_table(void);

/**
 * @brief Ajoute l'identifieur repéré par la chaîne token dans la table table et
 * renvoie l'indice de ce token dans la table
 *
 * @param table
 * @param token
 * @return int
 */
int ajouter_symbole(table *table, char *token);


/**
 * @brief Libère la table et ses éléments
 *
 * @param table
 */
void free_table(table *table);
