#pragma once
/* Ce fichier d'en tête contient des fonctions permettant de gérer l'appel des fonctions
de la bibliothèque standard */

#include "lib.h"
#include "assembly.h"

void manage_call_print(struct quad *quad, struct assembly_code *code);

void manage_call_print_mat(struct quad *quad, struct assembly_code *code);

void manage_call_printf(struct quad *quad, struct assembly_code *code);