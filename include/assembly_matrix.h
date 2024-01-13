#pragma once
/* Ce fichier d'en-tête regroupe les fonctions relatives à la traduction
de code 3 adresse intermédiaire en code mips pour les opérations matricielles*/

#include "lib.h"
#include "assembly.h"

void manage_declare_mat(struct quad *quad, struct assembly_code *code);

void manage_bop_plus_mat(struct quad *quad, struct assembly_code *code);

void manage_copy_mat(struct quad *quad, struct assembly_code *code);