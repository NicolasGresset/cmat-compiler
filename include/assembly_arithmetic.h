/* Contient les handlers pour les quads correspondant à 
des opérations arithmétiques*/

#pragma once
#include "lib.h"
#include "assembly.h"

void manage_bop_plus(struct quad *quad, struct assembly_code *code);

void manage_bop_moins(struct quad *quad, struct assembly_code *code);

void manage_bop_mult(struct quad *quad, struct assembly_code *code);

void manage_bop_divise(struct quad *quad, struct assembly_code *code);

void manage_uop_plus(struct quad *quad, struct assembly_code *code) ;

void manage_uop_moins(struct quad *quad, struct assembly_code *code);