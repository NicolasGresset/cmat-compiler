#include "assembly_jump.h"
#include "assembly.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

// egalite --------------------------------------------------------

void float_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  c.eq.s %s, %s\n", registers[F0], registers[F2]);
  fprintf(code->out, "  bczt %s\n", quad->sym3->u.addr);
}

void int_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  beq %s, %s, line%i\n", registers[T0], registers[T1],
          quad->sym3->u.addr); // ?
}

void manage_q_if_eq(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_EQ is not a LABEL\n");
    exit(1);
  }

  fprintf(code->out, "# if eq\n");
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

// different --------------------------------------------------------

void float_nequal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  c.eq.s %s, %s\n", registers[F0], registers[F2]);
  fprintf(code->out, "  bczf %s\n", quad->sym3->u.addr);
}

void int_nequal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  bne %s, %s, line%i\n", registers[T0], registers[T1],
          quad->sym3->u.addr);
}

void manage_q_if_neq(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_NEQ is not a LABEL\n");
    exit(1);
  }

  fprintf(code->out, "# if neq\n");
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

// inf --------------------------------------------------------

void float_lower_than_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  c.lt.s %s, %s\n", registers[F0], registers[F2]);
  fprintf(code->out, "  bczt %s\n", quad->sym3->u.addr);
}

void int_lower_than_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  blt %s, %s, line%i\n", registers[T0], registers[T1],
          quad->sym3->u.addr);
}

void manage_q_if_lt(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_LT is not a LABEL\n");
    exit(1);
  }

  fprintf(code->out, "# if lt\n");
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

// inf ou egal --------------------------------------------------------

void float_lower_than_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  c.le.s %s, %s\n", registers[F0], registers[F2]);
  fprintf(code->out, "  bczt %s\n", quad->sym3->u.addr);
}

void int_lower_than_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  ble %s, %s, line%i\n", registers[T0], registers[T1],
          quad->sym3->u.addr);
}

void manage_q_if_le(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_LE is not a LABEL\n");
    exit(1);
  }

  fprintf(code->out, "# if le\n");
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

// sup --------------------------------------------------------
void float_greater_than_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  c.le.s %s, %s\n", registers[F0], registers[F2]);
  fprintf(code->out, "  bczf %s\n", quad->sym3->u.addr);
}

void int_greater_than_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  bgt %s, %s,line%i\n", registers[T0], registers[T1],
          quad->sym3->u.addr);
}

void manage_q_if_gt(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_GT is not a LABEL\n");
    exit(1);
  }

  fprintf(code->out, "# if gt\n");
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

// sup ou egal --------------------------------------------------------

void float_greater_than_equal_goto(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "  c.lt.s %s, %s\n", registers[F0], registers[F2]);
  fprintf(code->out, "  bczf %s\n", quad->sym3->u.addr);
}

void int_greater_than_equal_goto(struct quad *quad,
                                 struct assembly_code *code) {
  fprintf(code->out, "  bge %s, %s, line%i\n", registers[T0], registers[T1],
          quad->sym3->u.addr);
}

void manage_q_if_ge(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: last operand of Q_IF_GE is not a LABEL\n");
    exit(1);
  }

  fprintf(code->out, "# if ge\n");
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

// goto --------------------------------------------------------

void manage_q_goto(struct quad *quad, struct assembly_code *code) {
  if (quad->sym3->kind != LABEL) {
    fprintf(stderr, "Error: first operand of Q_GOTO is not a LABEL\n");
    exit(1);
  }

  fprintf(code->out, "# goto\n");
  fprintf(code->out, "  j line%i\n", quad->sym3->u.addr);
}

// goto unknown --------------------------------------------------------

void manage_q_goto_unknown(struct quad *quad, struct assembly_code *code) {
  (void)quad;
  fprintf(code->out,
          "# goto unknown, considéré comme une sortie propre du programme\n");
  fprintf(code->out, "  li $v0, 10\n");
  fprintf(code->out, "  syscall\n");
}