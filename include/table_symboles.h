#pragma once
#include "lib.h"

//#define TAILLE_TABLE_HACHAGE 100
#define MAX_TAILLE_CONTEXTE 1024 // Que des tableaux statiques pour simplifier

/**
 * Structure pour un nœud de la liste chaînée dans la table de hachage (pile de blocks)
 */
struct noeud_hachage_t {
    struct stack_id_t * stack_id;
    struct noeud_hachage_t * next;
};

/**
 * Structure pour la table de hachage
 */
struct table_hachage_t{
    struct noeud_hachage_t * alveoles;
    unsigned int temporary;
};

/**
 * Structure pour la pile d'identificateurs
 */
struct stack_id_t{
    struct id_t * items[MAX_TAILLE_CONTEXTE];
    int top;
};

/**
 * Nouvel identificateur temporaire
 */
struct symbol * newtemp(struct table_hachage_t * hash_tab, type_t type);

/**
 * Initialiser la table de symboles
 */
struct table_hachage_t * table_hachage_init(void);

/**
 * Création d'une nouvelle pile d'identificateur et la placer dans la pile globale
 */
void stack_id_push(struct table_hachage_t * current_stack);

/**
 * Libérer l'espace de la structure struct stack_id et des identificateurs id_t et libérer de la pile
 */
void stack_id_pop(struct table_hachage_t * hash_tab);

/**
 * Mettre un identificateur dans la table de symboles
 */
void table_hachage_put(struct table_hachage_t * hash_tab,
                       struct id_t * identificateur);
/**
 * Générer un élément de la structure id_t
 */
struct id_t * id_init(const name_t name, const type_t type);

/**
 * Chercher le nom de la variable name dans la table de symboles
 * return: NULL si l'id n'a pas été trouvé
*/
struct id_t *  table_hachage_get(struct table_hachage_t * hash_tab,
                                 const char * name);

void id_print(struct id_t * id);

void table_hachage_print(struct table_hachage_t * hash_tab);

void table_hachage_free(struct table_hachage_t * hash_tab);
