/* Ce fichier contient un ensemble de méthodes pour traduire la représentation
du code 3 adresses intermédiaires en code machine interprétable par une architecture MIPS*/

#pragma once
#include "lib.h"

// nom du fichier contenant le code MIPS
#define FILE_NAME "mips_code.s"

/**
 * @brief Convertit le code 3 adresses en code MIPS
 * 
 * @param code 
 */
void generate_mips_code(struct code *code);