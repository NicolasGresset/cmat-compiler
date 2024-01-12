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
  struct symtable *symtable; // la table des symboles : permet de savoir un
                             // symbole a déjà été rencontré ou non
};

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

void add_floats_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0], registers[F0],
          registers[F2]);
  fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void add_ints_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  add %s, %s, %s\n", registers[T0], registers[T0],
          registers[T1]);
  fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

int is_symbol_float(struct symbol *symbol) {
  return symbol->kind == FLOAT_CONSTANT ||
         (symbol->kind == NAME && symbol->u.id.type == REEL);
}

int is_symbol_int(struct symbol *symbol) {
  return symbol->kind == INT_CONSTANT ||
         (symbol->kind == NAME && symbol->u.id.type == ENTIER);
}

void manage_bop_plus(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of BOP_PLUS is not a NAME\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym3)) {
      fprintf(stderr, "Error: can't add a label or a int to a float\n");
      exit(1);
    }

    move_float_symbol(quad->sym2, code, F0);
    move_float_symbol(quad->sym3, code, F2);
    add_floats_and_store(quad, code);
  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym3)) {
      fprintf(stderr, "Error: can't add a label or a float to an int\n");
      exit(1);
    }

    move_int_symbol(quad->sym2, code, T0);
    move_int_symbol(quad->sym3, code, T1);
    add_ints_and_store(quad, code);
  } else {
    fprintf(stderr, "Error: can't add a label to a label\n");
    exit(1);
  }
}

void subtract_floats_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  sub.s %s, %s, %s\n", registers[F0], registers[F0],
          registers[F2]);
  fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void subtract_ints_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  sub %s, %s, %s\n", registers[T0], registers[T0],
          registers[T1]);
  fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_bop_moins(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of BOP_MOINS is not a NAME\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a float to a non float\n");
      exit(1);
    }

    if (!is_symbol_float(quad->sym3)) {
      fprintf(stderr, "Error: can't subtract a label or a int to a float\n");
      exit(1);
    }

    move_float_symbol(quad->sym2, code, F0);
    move_float_symbol(quad->sym3, code, F2);
    subtract_floats_and_store(quad, code);
  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a int to a non int\n");
      exit(1);
    }

    if (!is_symbol_int(quad->sym3)) {
      fprintf(stderr, "Error: can't subtract a label or a float to an int\n");
      exit(1);
    }

    move_int_symbol(quad->sym2, code, T0);
    move_int_symbol(quad->sym3, code, T1);
    subtract_ints_and_store(quad, code);
  } else {
    fprintf(stderr, "Error: can't subtract a label to a label\n");
    exit(1);
  }
}

void multiply_floats_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  mul.s %s, %s, %s\n", registers[F0], registers[F0],
          registers[F2]);
  fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void multiply_ints_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  mult %s, %s, %s\n", registers[T0], registers[T0],
          registers[T1]);
  fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_bop_mult(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of BOP_MULT is not a NAME\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a float to a non float\n");
      exit(1);
    }

    if (!is_symbol_float(quad->sym3)) {
      fprintf(stderr, "Error: can't multiply a label or a int to a float\n");
      exit(1);
    }

    move_float_symbol(quad->sym2, code, F0);
    move_float_symbol(quad->sym3, code, F2);
    multiply_floats_and_store(quad, code);
  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a int to a non int\n");
      exit(1);
    }

    if (!is_symbol_int(quad->sym3)) {
      fprintf(stderr, "Error: can't multiply a label or a float to an int\n");
      exit(1);
    }

    move_int_symbol(quad->sym2, code, T0);
    move_int_symbol(quad->sym3, code, T1);
    multiply_ints_and_store(quad, code);
  } else {
    fprintf(stderr, "Error: can't multiply a label to a label\n");
    exit(1);
  }
}

void divide_floats_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  div.s %s, %s, %s\n", registers[F0], registers[F0],
          registers[F2]);
  fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void divide_ints_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  div %s, %s, %s\n", registers[T0], registers[T0],
          registers[T1]);
  fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_bop_divise(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of BOP_DIVISE is not a NAME\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a float to a non float\n");
      exit(1);
    }

    if (!is_symbol_float(quad->sym3)) {
      fprintf(stderr, "Error: can't divide a label or a int to a float\n");
      exit(1);
    }

    move_float_symbol(quad->sym2, code, F0);
    move_float_symbol(quad->sym3, code, F2);
    divide_floats_and_store(quad, code);
  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a int to a non int\n");
      exit(1);
    }

    if (!is_symbol_int(quad->sym3)) {
      fprintf(stderr, "Error: can't divide a label or a float to an int\n");
      exit(1);
    }

    move_int_symbol(quad->sym2, code, T0);
    move_int_symbol(quad->sym3, code, T1);
    divide_ints_and_store(quad, code);
  } else {
    fprintf(stderr, "Error: can't divide a label to a label\n");
    exit(1);
  }
}

void unary_add_float_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void unary_add_int_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_uop_plus(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of UOP_PLUS is not a NAME\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a float to a non float\n");
      exit(1);
    }

    move_float_symbol(quad->sym2, code, F0);
    unary_add_float_and_store(quad, code);

  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a int to a non int\n");
      exit(1);
    }

    move_int_symbol(quad->sym2, code, T0);
    unary_add_int_and_store(quad, code);

  } else {
    fprintf(stderr, "Error: can't use unary addition with a label\n");
    exit(1);
  }
}

void unary_subtract_float_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  sub.s %s, %%zero, %s\n", registers[F0], registers[F0]);
  fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void unary_subtract_int_and_store(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  sub %s, %%zero, %s\n", registers[F0], registers[F0]);
  fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_uop_moins(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind != NAME) {
    fprintf(stderr, "Error: first operand of UOP_MOINS is not a NAME\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a float to a non float\n");
      exit(1);
    }

    move_float_symbol(quad->sym2, code, F0);
    unary_add_float_and_store(quad, code);

  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't affect a int to a non int\n");
      exit(1);
    }
    move_int_symbol(quad->sym2, code, T0);
    unary_add_int_and_store(quad, code);

  } else {
    fprintf(stderr, "Error: can't use unary subtraction with a label\n");
    exit(1);
  }
}

void float_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  beq %s, %s, %i\n", registers[F0], registers[F2], quad->sym1->u.addr);
}

void int_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  beq %s, %s, %i\n", registers[T0], registers[T1], quad->sym1->u.addr);
}

void manage_q_if_eq(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_EQ is not a LABEL\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a float to a non float\n");
      exit(1);
    }

    move_float_symbol(quad->sym1, code, F0);
    move_float_symbol(quad->sym2, code, F2);
    float_equal_goto(quad, code);

  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a int to a non int\n");
      exit(1);
    }
    move_int_symbol(quad->sym1, code, T0);
    move_int_symbol(quad->sym2, code, T1);
    int_equal_goto(quad, code);

  } else {
    fprintf(stderr, "Error: can't compare using a label\n");
    exit(1);
  }
}

void float_nequal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  bne %s, %s, %i\n", registers[F0], registers[F2], quad->sym1->u.addr);
}

void int_nequal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  bne %s, %s, %i\n", registers[T0], registers[T1], quad->sym1->u.addr);
}

void manage_q_if_neq(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_NEQ is not a LABEL\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a float to a non float\n");
      exit(1);
    }

    move_float_symbol(quad->sym1, code, F0);
    move_float_symbol(quad->sym2, code, F2);
    float_nequal_goto(quad, code);

  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a int to a non int\n");
      exit(1);
    }
    move_int_symbol(quad->sym1, code, T0);
    move_int_symbol(quad->sym2, code, T1);
    int_nequal_goto(quad, code);

  } else {
    fprintf(stderr, "Error: can't compare using a label\n");
    exit(1);
  }
}

void float_lower_than_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  blt %s, %s, %i\n", registers[F0], registers[F2], quad->sym1->u.addr);
}

void int_lower_than_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  blt %s, %s, %i\n", registers[T0], registers[T1], quad->sym1->u.addr);
}

void manage_q_if_lt(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_LT is not a LABEL\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a float to a non float\n");
      exit(1);
    }

    move_float_symbol(quad->sym1, code, F0);
    move_float_symbol(quad->sym2, code, F2);
    float_lower_than_goto(quad, code);

  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a int to a non int\n");
      exit(1);
    }
    move_int_symbol(quad->sym1, code, T0);
    move_int_symbol(quad->sym2, code, T1);
    int_lower_than_goto(quad, code);

  } else {
    fprintf(stderr, "Error: can't compare using a label\n");
    exit(1);
  }
}

void float_lower_than_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  ble %s, %s, %i\n", registers[F0], registers[F2], quad->sym1->u.addr);
}

void int_lower_than_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  ble %s, %s, %i\n", registers[T0], registers[T1], quad->sym1->u.addr);
}

void manage_q_if_le(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_LE is not a LABEL\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a float to a non float\n");
      exit(1);
    }

    move_float_symbol(quad->sym1, code, F0);
    move_float_symbol(quad->sym2, code, F2);
    float_lower_than_equal_goto(quad, code);

  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a int to a non int\n");
      exit(1);
    }
    move_int_symbol(quad->sym1, code, T0);
    move_int_symbol(quad->sym2, code, T1);
    int_lower_than_equal_goto(quad, code);

  } else {
    fprintf(stderr, "Error: can't compare using a label\n");
    exit(1);
  }
}

void float_greater_than_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  bgt %s, %s, %i\n", registers[F0], registers[F2], quad->sym1->u.addr);
}

void int_greater_than_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  bgt %s, %s, %i\n", registers[T0], registers[T1], quad->sym1->u.addr);
}

void manage_q_if_gt(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_GT is not a LABEL\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a float to a non float\n");
      exit(1);
    }

    move_float_symbol(quad->sym1, code, F0);
    move_float_symbol(quad->sym2, code, F2);
    float_greater_than_goto(quad, code);

  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a int to a non int\n");
      exit(1);
    }
    move_int_symbol(quad->sym1, code, T0);
    move_int_symbol(quad->sym2, code, T1);
    int_greater_than_goto(quad, code);

  } else {
    fprintf(stderr, "Error: can't compare using a label\n");
    exit(1);
  }
}

void float_lower_than_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  bge %s, %s, %i\n", registers[F0], registers[F2], quad->sym1->u.addr);
}

void int_lower_than_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  bge %s, %s, %i\n", registers[T0], registers[T1], quad->sym1->u.addr);
}

void manage_q_if_ge(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_GE is not a LABEL\n");
    exit(1);
  }

  if (is_symbol_float(quad->sym2)) {
    if (!is_symbol_float(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a float to a non float\n");
      exit(1);
    }

    move_float_symbol(quad->sym1, code, F0);
    move_float_symbol(quad->sym2, code, F2);
    float_greater_than_equal_goto(quad, code);

  } else if (is_symbol_int(quad->sym2)) {
    if (!is_symbol_int(quad->sym1)) {
      fprintf(stderr, "Error: can't compare a int to a non int\n");
      exit(1);
    }
    move_int_symbol(quad->sym1, code, T0);
    move_int_symbol(quad->sym2, code, T1);
    int_greater_than_equal_goto(quad, code);

  } else {
    fprintf(stderr, "Error: can't compare using a label\n");
    exit(1);
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
  // manage identificateurs
  switch (quad->kind) {
  case BOP_PLUS:
    manage_bop_plus(quad, code);
    break;
  case BOP_MOINS:
    manage_bop_moins(quad,code);
    break;
  case BOP_MULT:
    manage_bop_mult(quad, code);
    break;
  case BOP_DIVISE:
    manage_bop_divise(quad,code);
    break;
  case UOP_PLUS:
    manage_uop_plus(quad, code);
    break;
  case UOP_MOINS:
    manage_uop_moins(quad,code);
    break;
  case Q_IF_EQ:
    manage_q_if_eq(quad,code);
    break;
  case Q_IF_NEQ:
    manage_q_if_neq(quad,code);
    break;
  case Q_IF_LT:
    manage_q_if_lt(quad,code);
    break;
  case Q_IF_LE:
    manage_q_if_le(quad,code);
    break;
  case Q_IF_GT:
    manage_q_if_gt(quad,code);
    break;
  case Q_IF_GE:
    manage_q_if_ge(quad,code);
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
  assembly_code.symtable = symtable_new();

  assembly_code.out = open_file(FILE_NAME);

  for (int i = 0; i < code->nextquad; i++) {
    manage_quad(&code->quads[i], &assembly_code);
  }
}



/**
 * @brief Gère un identificateur rencontré dans le code 3 adresses
 *
 * @param symbol
 * @param code
 */
/*
void manage_identificateur(struct symbol *symbol, struct assembly_code *code) {
  if (symtable_get(code->symtable, symbol->u.id.name) == NULL) {
    // l'identificateur n'a pas encore été rencontré
    // on doit donc lui associe un emplacement mémoire dans le segment data du code MIPS
    // via une étiquette

    symtable_put(code->symtable, symbol->u.id.name, symbol->u.id.type);
  }
}
*/
/**
 * @brief Parcourt les différents identificateurs rencontrés dans le code 3
 * adresses Si ils ont déjà étés rencontrés, on ne fait rien sinon, on leur
 * associe un emplacement mémoire dans le segment data du code MIPS via
 * l'étiquette correspondante au nom de l'identificateur
 *
 * @param quad
 */

/*
void manage_identificateurs(struct quad *quad, struct assembly_code *code) {
  if (quad->sym1->kind == NAME) {
    manage_identificateur(quad->sym1, code);
  }
  if (quad->sym2->kind == NAME) {
    manage_identificateur(quad->sym2, code);
  }
  if (quad->sym3->kind == NAME) {
    manage_identificateur(quad->sym3, code);
  }
}

*/