#include "../include/assembly.h"
#include "CMat.h" // pour SYMTAB
#include "assembly_arithmetic.h"
#include "assembly_copy.h"
#include "assembly_jump.h"
#include "assembly_matrix.h"
#include "assembly_print.h"
#include "data_segment.h"
#include "table_symboles.h"
#include <stdio.h>
#include <stdlib.h>

char *registers[] = {
    [T0] = "$t0", [T1] = "$t1", [T2] = "$t2", [F0] = "$f0",
    [A0] = "$a0", [F2] = "$f2", [F4] = "$f4", [F12] = "$f12",
};

int is_symbol_float(struct symbol *symbol) {
  return symbol->kind == FLOAT_CONSTANT ||
         (symbol->kind == NAME && symbol->u.id.type == REEL);
}

int is_symbol_int(struct symbol *symbol) {
  return symbol->kind == INT_CONSTANT ||
         (symbol->kind == NAME && symbol->u.id.type == ENTIER);
}

void move_int_symbol(struct symbol *symbol, struct assembly_code *code,
                     int register_number) {
  switch (symbol->kind) {
  case INT_CONSTANT:
    fprintf(code->out, "  li %s, %d\n", registers[register_number],
            symbol->u.int_value);
    break;
  case NAME:
    // u.id.name va correspondre à une étiquette dans le code MIPS, on les
    // écrira après
    fprintf(code->out, "  lw %s, %s\n", registers[register_number],
            symbol->u.id.name);
    break;
  default:
    fprintf(stderr, "Error: can't move symbol of kind %d to int location\n",
            symbol->kind);
    exit(1);
  }
}

void move_float_symbol(struct symbol *symbol, struct assembly_code *code,
                       int register_number) {
  char float_constant[MAX_DATA_SIZE];
  switch (symbol->kind) {
  case FLOAT_CONSTANT:
    snprintf(float_constant, MAX_DATA_SIZE, "  __float_tmp%d:  .float %f\n",
             code->next_float_constant, symbol->u.float_value);
    append_to_data(code, float_constant);
    fprintf(code->out, "  l.s %s, __float_tmp%d\n", registers[register_number],
            code->next_float_constant);
    code->next_float_constant++;
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

void manage_default_case(struct quad *quad, struct assembly_code *code) {
  (void)code;
  fprintf(stderr, "Error: can't manage quad of kind %d\n", quad->kind);
  exit(1);
}

/**
 * @brief Correspond à la déclaration d'une variable : on va lui associer un
 * emplacement mémoire dans le segment data du code MIPS via une étiquette
 *
 * @param quad
 * @param code
 */
void manage_declare(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of DECLARE is not a NAME\n");
    exit(1);
  }

  fprintf(code->out, "# declare %s\n", quad->sym1->u.id.name);

  char declaration[MAX_DATA_SIZE];

  switch (quad->sym1->u.id.type) {
  case ENTIER:
    snprintf(declaration, MAX_DATA_SIZE, "  %s: .word 0\n",
             quad->sym1->u.id.name);
    append_to_data(code, declaration);
    break;
  case REEL:
    snprintf(declaration, MAX_DATA_SIZE, "  %s: .float 0.0\n",
             quad->sym1->u.id.name);
    append_to_data(code, declaration);
    break;
  default:
    fprintf(stderr, "Error: can't declare a label\n");
    exit(1);
  }
}

// todo tester
void manage_declare_string(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of DECLARE is not a NAME\n");
    exit(1);
  }

  fprintf(code->out, "# declare %s\n", quad->sym1->u.id.name);

  char declaration[MAX_DATA_SIZE];

  snprintf(declaration, MAX_DATA_SIZE, "  %s: .asciiz %s\n",
           quad->sym1->u.id.name, quad->sym2->u.string);
  append_to_data(code, declaration);
}

/**
 * @brief Gère un quadruplet
 *
 * @param quad
 * @param code
 * @param out
 */
void manage_quad(struct quad *quad, struct assembly_code *code) {
  // manage identificateurs
  switch (quad->kind) {
  case BOP_PLUS:
    manage_bop_plus(quad, code);
    break;
  case BOP_MOINS:
    manage_bop_moins(quad, code);
    break;
  case BOP_MULT:
    manage_bop_mult(quad, code);
    break;
  case BOP_DIVISE:
    manage_bop_divise(quad, code);
    break;
  case UOP_PLUS:
    manage_uop_plus(quad, code);
    break;
  case UOP_MOINS:
    manage_uop_moins(quad, code);
    break;
  case Q_IF_EQ:
    manage_q_if_eq(quad, code);
    break;
  case Q_IF_NEQ:
    manage_q_if_neq(quad, code);
    break;
  case Q_IF_LT:
    manage_q_if_lt(quad, code);
    break;
  case Q_IF_LE:
    manage_q_if_le(quad, code);
    break;
  case Q_IF_GT:
    manage_q_if_gt(quad, code);
    break;
  case Q_IF_GE:
    manage_q_if_ge(quad, code);
    break;
  case Q_GOTO:
    manage_q_goto(quad, code);
    break;
  case Q_GOTO_UNKNOWN:
    manage_q_goto_unknown(quad, code);
    break;
  case COPY:
    manage_copy(quad, code);
    break;
  case Q_DECLARE:
    manage_declare(quad, code);
    break;
  case Q_DECLARE_MAT:
    manage_declare_mat(quad, code);
    break;
  case MATOP_PLUS:
    manage_bop_plus_mat(quad, code);
    break;
  case MATOP_MOINS:
    manage_bop_moins_mat(quad, code);
    break;
  case MATOP_MULT:
    manage_bop_mult_mat(quad, code);
    break;
  case MATOP_DIVISE:
    manage_bop_divise_mat(quad, code);
    break;
  case UMATOP_PLUS:
    manage_uop_plus_mat(quad, code);
    break;
  case UMATOP_MOINS:
    manage_uop_moins_mat(quad, code);
    break;
  case UMATOP_TRANSPOSE:
    manage_transpose_mat(quad, code);
    break;
  case CALL_PRINT:
    manage_call_print(quad, code);
    break;
  case CALL_PRINTF:
    manage_call_printf(quad, code);
    break;
  case ARRAY_AFFECT:
    manage_array_affect(quad, code);
    break;
  case DEREF:
    manage_deref(quad, code);
    break;
  case Q_DECLARE_STRING:
    manage_declare_string(quad, code);
    break;
  default:
    manage_default_case(quad, code);
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

void manage_quads(struct code *code, struct assembly_code *assembly_code) {
  fprintf(assembly_code->out, ".text\n");
  for (unsigned int i = 0; i < code->nextquad; i++) {
    fprintf(assembly_code->out, "line%u:\n",
            i); // simule les lignes du code intermédiaire 3 adresses
    // c'est plutôt sale mais ça marche
    manage_quad(&code->quads[i], assembly_code);
  }
}

void initalize_assembly_code(struct assembly_code *assembly_code,
                             struct code *code) {
  memset(assembly_code, 0, sizeof(struct assembly_code));
  assembly_code->out = open_file(code->filename);

  append_to_data(assembly_code, ".data\n");
  assembly_code->float_zero = "__float_zero\n";
  append_to_data(assembly_code, "  __float_zero: .float 0.0\n");
}

/**
 * @brief La fonction qui génère le code MIPS à partir du code 3 adresses
 * passé en paramètre
 *
 * @param code
 */
void generate_mips_code(struct code *code) {
  struct assembly_code assembly_code;
  initalize_assembly_code(&assembly_code, code);

  manage_quads(code, &assembly_code);
  write_data_to_file(&assembly_code);
}
