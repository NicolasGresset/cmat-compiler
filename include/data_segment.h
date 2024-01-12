/* Ce fichier comprend un ensemble de méthodes pour manipuler
et écrire dans le segment data de l'éxécutable MIPS*/
#pragma once
#include "assembly.h"

/**
 * @brief Ecrit la chaine data à la suite de code->data représentant le segment
 * data du code MIPS
 *
 * @param code
 * @param data
 */
void append_to_data(struct assembly_code *code, char *data);

/**
 * @brief Ecrit effectivement le segment data à la fin du fichier de sortie
 *
 * @param code
 */
void write_data_to_file(struct assembly_code *code);