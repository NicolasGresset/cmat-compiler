/* Ce fichier contient les handlers pour les quads correspondant
à des instructions de branchement*/

#pragma once
#include "lib.h"
#include "assembly.h"

void manage_q_if_eq(struct quad *quad, struct assembly_code *code) ;

void manage_q_if_neq(struct quad *quad, struct assembly_code *code) ;

void manage_q_if_lt(struct quad *quad, struct assembly_code *code) ;

void manage_q_if_gt(struct quad *quad, struct assembly_code *code) ;

void manage_q_if_le(struct quad *quad, struct assembly_code *code) ;

void manage_q_if_ge(struct quad *quad, struct assembly_code *code) ;

void manage_q_goto(struct quad *quad, struct assembly_code *code) ;

void manage_q_goto_unknown(struct quad *quad, struct assembly_code *code) ;