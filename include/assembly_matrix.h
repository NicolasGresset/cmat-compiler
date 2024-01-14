#pragma once
/* Ce fichier d'en-tête regroupe les fonctions relatives à la traduction
de code 3 adresse intermédiaire en code mips pour les opérations matricielles*/

#include "assembly.h"
#include "lib.h"

void manage_declare_mat(struct quad *quad, struct assembly_code *code);

void manage_bop_plus_mat(struct quad *quad, struct assembly_code *code);

void manage_bop_moins_mat(struct quad *quad, struct assembly_code *code);

void manage_bop_mult_mat(struct quad *quad, struct assembly_code *code);

void manage_bop_divise_mat(struct quad *quad, struct assembly_code *code);

void manage_uop_plus_mat(struct quad *quad, struct assembly_code *code);

void manage_uop_moins_mat(struct quad *quad, struct assembly_code *code);

void manage_bop_plus_mat_bin(struct quad *quad, struct assembly_code *code);

void manage_bop_moins_mat_bin(struct quad *quad, struct assembly_code *code);

void manage_bop_mult_mat_bin(struct quad *quad, struct assembly_code *code);

void manage_bop_divise_mat_bin(struct quad *quad, struct assembly_code *code);

void manage_transpose_mat(struct quad *quad, struct assembly_code *code);

void manage_copy_mat(struct quad *quad, struct assembly_code *code);

void manage_array_affect(struct quad *quad, struct assembly_code *code);

void manage_deref(struct quad *quad, struct assembly_code *code);