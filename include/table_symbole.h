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
 * @brief Renvoie l'indice du symbole token dans la table des symboles table
 * et l'ajoute si il n'existe pas
 *
 * @param table
 * @param token
 * @return int
 */
int get_symbole(table *table, char *token);


/**
 * @brief Libère la table et ses éléments
 *
 * @param table
 */
void free_table(table *table);
