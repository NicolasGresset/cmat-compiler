/* Ce fichier contient un ensemble de méthodes pour traduire la représentation
du code 3 adresses intermédiaires en code machine interprétable par une architecture MIPS*/

#pragma once
#include "lib.h"
#include <stdio.h>

// taille maximale du segment data
#define MAX_DATA_SIZE 2048

// nom du fichier contenant le code MIPS
#define FILE_NAME "out/mips_code.s"

/**
 * @brief Convertit le code 3 adresses en code MIPS
 * 
 * @param code 
 */
void generate_mips_code(struct code *code);

struct assembly_code {
  int next_float_constant;
  FILE *out; // pointeur vers le fichier de sortie où écrire le code MIPS
  char data[MAX_DATA_SIZE]; // le segment data du code MIPS
  int current_data_offset; // l'offset courant dans le segment data pour pouvoir
                           // écrire à la suite
};

#define T0 0
#define T1 1
#define F0 16
#define F2 17
#define F4 18

#define N_REGISTERS 18

extern char *registers[N_REGISTERS];


/**
 * @brief Met la valeur correspondante au symbole symbol dans le registre entier register_number
 * Si symbol est un entier, on utilise l'instruction li
 * Sinon, (symbol est un identificateur), on va récupérer la valeur dans le segment data
 * 
 * @param symbol 
 * @param code 
 * @param register_number 
 */
void move_int_symbol(struct symbol *symbol, struct assembly_code *code,
                     int register_number) ;


/**
 * @brief Met la valeur correspondante au symbole symbol dans le registre
 * flottant de numéro register_number
 *
 * @param symbol
 * @param code
 * @param register_number
 */
void move_float_symbol(struct symbol *symbol, struct assembly_code *code,
                       int register_number);


/**
 * @brief Renvoie 1 si le symbole symbole correspond à une constante flottante ou un
 * identificateur de type flottant, 0 sinon
 * 
 * @param symbol 
 * @return int 
 */
int is_symbol_float(struct symbol *symbol);


/**
 * @brief Renvoie 1 si le symbole symbole correspond à une constante entière ou un
 * identificateur de type entier, 0 sinon
 * @param symbol 
 * @return int 
 */
int is_symbol_int(struct symbol *symbol);