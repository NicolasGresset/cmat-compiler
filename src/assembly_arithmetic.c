#include "assembly_arithmetic.h"
#include "assembly.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

// Addition --------------------------------------------------------

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

// Soustraction --------------------------------------------------------

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

// Multiplication --------------------------------------------------------

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

// Division --------------------------------------------------------

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

// Unary addition --------------------------------------------------------

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

// Unary subtraction --------------------------------------------------------

void unary_subtract_float_and_store(struct quad *quad,
                                    struct assembly_code *code) {
  fprintf(code->out, "  sub.s %s, %%zero, %s\n", registers[F0], registers[F0]);
  fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void unary_subtract_int_and_store(struct quad *quad,
                                  struct assembly_code *code) {
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