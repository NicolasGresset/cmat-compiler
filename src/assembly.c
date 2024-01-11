#include "../include/assembly.h"
#include <stdio.h>
#include <stdlib.h>

#define T0 0
#define T1 1
#define F0 16
#define F2 17

// pour chaque identificateur rencontré dans le code 3 adresse, on va lui
// associer un emplacement mémoire dans le segment data du code MIPS
// l'asssociation entre un identificateur et un emplacement mémoire se fera via
// une table de symboles ?

char *registers[] = {[T0] = "$t0", [T1] = "$t1", [F0] = "$f0", [F2] = "$f2"};

struct assembly_code {
  int next_int_temporary;   // le procain entier temporaire à utiliser
  int next_float_temporary; // le prochain flottant temporaire à utiliser
  FILE *out; // pointeur vers le fichier de sortie où écrire le code MIPS
};

void move_int_symbol(struct symbol *symbol, struct assembly_code *code,
                     int register_number) {
  switch (symbol->kind) {
  case INT_CONSTANT:
    fprintf(code->out, "  li %s, %d\n", registers[register_number],
            symbol->u.int_value);
    break;
  case NAME:
    fprintf(code->out, "  lw %s, %s\n", registers[register_number],
            symbol->u.id.name);
    break;
  default:
    fprintf(stderr, "Error: can't move symbol of kind %d to int location\n",
            symbol->kind);
    exit(1);
  }
}

/**
 * @brief Met la valeur correspondante au symbole symbol dans le registre
 * flottant de numéro register_number
 *
 * @param symbol
 * @param code
 * @param register_number
 */
void move_float_symbol(struct symbol *symbol, struct assembly_code *code,
                       int register_number) {
  switch (symbol->kind) {
  case FLOAT_CONSTANT:
    fprintf(code->out, "  li.s %s, %f\n", registers[register_number],
            symbol->u.float_value);
    break;
  case NAME:
    fprintf(code->out, "  l.s %s, %s\n", registers[register_number],
            symbol->u.id.name);
    break;
  default:
    fprintf(stderr, "Error: can't move symbol of kind %d to float location\n",
            symbol->kind);
    exit(1);
  }
}

void manage_bop_plus(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of BOP_PLUS is not a NAME\n");
    exit(1);
  }

  if (quad->sym2->kind == FLOAT_CONSTANT) {
    if (quad->sym3->kind == INT_CONSTANT || quad->sym3->kind == LABEL) {
      fprintf(stderr, "Error: can't add a label or a int to a float\n");
      exit(1);
    }

    move_symbol(quad->sym1, code, F0);
  }
}

/**
 * @brief Gère un quadruplet
 *
 * @param quad
 * @param code
 * @param out
 */
void manage_quad(struct quad *quad, struct assembly_code *code) {
  switch (quad->kind) {
  case BOP_PLUS:
    manage_bop_plus(quad, code);
    break;
  }
}

/**
 * @brief Ouvre le fichier file_name en mode écriture et retourne un pointeur
 * vers ce fichier
 *
 * @param file_name
 * @return FILE*
 */
FILE *open_file(const char *file_name) {
  FILE *file = fopen(file_name, "w");
  if (file == NULL) {
    fprintf(stderr, "Error while opening file %s\n", file_name);
    exit(1);
  }
  return file;
}

/**
 * @brief La fonction qui génère le code MIPS à partir du code 3 adresses passé
 * en paramètre
 *
 * @param code
 */
void generate_mips_code(struct code *code) {
  /* On va itérer sur les quads compris dans code et transformer chacun d'eux en
   * code MIPS*/
  struct assembly_code assembly_code;
  assembly_code.out = open_file(FILE_NAME);

  for (int i = 0; i < code->nextquad; i++) {
    manage_quad(&code->quads[i], &assembly_code);
  }
}