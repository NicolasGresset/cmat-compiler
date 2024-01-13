#include "assembly_arithmetic.h"
#include "assembly.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

// Addition --------------------------------------------------------

void add_floats_into_float_and_store(struct quad *quad,
                                     struct assembly_code *code) {
    fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void add_int_float_into_float_and_store(struct quad *quad,
                                        struct assembly_code *code) {
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F2]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F2], registers[F2]);
    fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void add_ints_into_float_and_store(struct quad *quad,
                                   struct assembly_code *code) {
    fprintf(code->out, "  add %s, %s, %s\n", registers[T0], registers[T0],
            registers[T1]);
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void add_ints_into_int_and_store(struct quad *quad,
                                 struct assembly_code *code) {
    fprintf(code->out, "  add %s, %s, %s\n", registers[T0], registers[T0],
            registers[T1]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void add_int_float_into_int_and_store(struct quad *quad,
                                      struct assembly_code *code) {
    fprintf(code->out, "  cvt.w.s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T1], registers[F0]);
    fprintf(code->out, "  add %s, %s, %s\n", registers[T0], registers[T1],
            registers[T1]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void add_floats_into_int_and_store(struct quad *quad,
                                   struct assembly_code *code) {
    fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  cvt.w.s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[T0], quad->sym1->u.id.name);
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

void manage_bop_plus(struct quad *quad, struct assembly_code *code) {
    if (quad->sym1->kind != NAME) {
        fprintf(stderr, "Error: first operand of BOP_PLUS is not a NAME\n");
        exit(1);
    }

    if (quad->sym1->u.id.type == REEL) {

        if (is_symbol_float(quad->sym2)) {
            if (is_symbol_float(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_float_symbol(quad->sym3, code, F2);
                add_floats_into_float_and_store(quad, code);
            }

            else if (is_symbol_int(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_int_symbol(quad->sym3, code, T0);
                add_int_float_into_float_and_store(quad, code);
            }

            else {
                fprintf(stderr, "Error: can't add a label to a float\n");
                exit(1);
            }

        } else if (is_symbol_int(quad->sym2)) {
            if (is_symbol_int(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_int_symbol(quad->sym3, code, T1);
                add_ints_into_float_and_store(quad, code);
            } else if (is_symbol_float(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_float_symbol(quad->sym3, code, F0);
                add_int_float_into_float_and_store(quad, code);
            } else {
                fprintf(stderr, "Error: can't add a label to an int\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: can't add a label to a label\n");
            exit(1);
        }
    }

    else if (quad->sym1->u.id.type == ENTIER) {

        if (is_symbol_float(quad->sym2)) {
            if (is_symbol_float(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_float_symbol(quad->sym3, code, F2);
                add_floats_into_int_and_store(quad, code);
            }

            else if (is_symbol_int(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_int_symbol(quad->sym3, code, T0);
                add_int_float_into_int_and_store(quad, code);
            }

            else {
                fprintf(stderr, "Error: can't add a label to a float\n");
                exit(1);
            }

        } else if (is_symbol_int(quad->sym2)) {
            if (is_symbol_int(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_int_symbol(quad->sym3, code, T1);
                add_ints_into_int_and_store(quad, code);
            } else if (is_symbol_float(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_float_symbol(quad->sym3, code, F0);
                add_int_float_into_int_and_store(quad, code);
            } else {
                fprintf(stderr, "Error: can't add a label to an int\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: can't add a label to a label\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Error: type MATRIX in binary addition\n");
        exit(1);
    }
}

// Soustraction --------------------------------------------------------

void subtract_floats_into_float_and_store(struct quad *quad,
                                          struct assembly_code *code) {
    fprintf(code->out, "  sub.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void subtract_int_float_into_float_and_store(struct quad *quad,
                                             struct assembly_code *code) {
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F2]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F2], registers[F2]);
    fprintf(code->out, "  sub.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void subtract_ints_into_float_and_store(struct quad *quad,
                                        struct assembly_code *code) {
    fprintf(code->out, "  sub %s, %s, %s\n", registers[T0], registers[T0],
            registers[T1]);
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void subtract_ints_into_int_and_store(struct quad *quad,
                                      struct assembly_code *code) {
    fprintf(code->out, "  sub %s, %s, %s\n", registers[T0], registers[T0],
            registers[T1]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void subtract_int_float_into_int_and_store(struct quad *quad,
                                           struct assembly_code *code) {
    fprintf(code->out, "  cvt.w.s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T1], registers[F0]);
    fprintf(code->out, "  sub %s, %s, %s\n", registers[T0], registers[T1],
            registers[T1]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void subtract_floats_into_int_and_store(struct quad *quad,
                                        struct assembly_code *code) {
    fprintf(code->out, "  sub.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  cvt.w.s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_bop_moins(struct quad *quad, struct assembly_code *code) {
    if (quad->sym1->kind != NAME) {
        fprintf(stderr, "Error: first operand of BOP_MOINS is not a NAME\n");
        exit(1);
    }

    if (quad->sym1->u.id.type == REEL) {

        if (is_symbol_float(quad->sym2)) {
            if (is_symbol_float(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_float_symbol(quad->sym3, code, F2);
                subtract_floats_into_float_and_store(quad, code);
            }

            else if (is_symbol_int(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_int_symbol(quad->sym3, code, T0);
                subtract_int_float_into_float_and_store(quad, code);
            }

            else {
                fprintf(stderr, "Error: can't subtract a label to a float\n");
                exit(1);
            }

        } else if (is_symbol_int(quad->sym2)) {
            if (is_symbol_int(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_int_symbol(quad->sym3, code, T1);
                subtract_ints_into_float_and_store(quad, code);
            } else if (is_symbol_float(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_float_symbol(quad->sym3, code, F0);
                subtract_int_float_into_float_and_store(quad, code);
            } else {
                fprintf(stderr, "Error: can't subtract a label to an int\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: can't subtract a label to a label\n");
            exit(1);
        }
    }

    else if (quad->sym1->u.id.type == ENTIER) {

        if (is_symbol_float(quad->sym2)) {
            if (is_symbol_float(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_float_symbol(quad->sym3, code, F2);
                subtract_floats_into_int_and_store(quad, code);
            }

            else if (is_symbol_int(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_int_symbol(quad->sym3, code, T0);
                subtract_int_float_into_int_and_store(quad, code);
            }

            else {
                fprintf(stderr, "Error: can't subtract a label to a float\n");
                exit(1);
            }

        } else if (is_symbol_int(quad->sym2)) {
            if (is_symbol_int(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_int_symbol(quad->sym3, code, T1);
                subtract_ints_into_int_and_store(quad, code);
            } else if (is_symbol_float(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_float_symbol(quad->sym3, code, F0);
                subtract_int_float_into_int_and_store(quad, code);
            } else {
                fprintf(stderr, "Error: can't subtract a label to an int\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: can't subtract a label to a label\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Error: type MATRIX in binary subtraction\n");
        exit(1);
    }
}

// Multiplication --------------------------------------------------------

void multiply_floats_into_float_and_store(struct quad *quad,
                                          struct assembly_code *code) {
    fprintf(code->out, "  mul.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void multiply_int_float_into_float_and_store(struct quad *quad,
                                             struct assembly_code *code) {
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F2]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F2], registers[F2]);
    fprintf(code->out, "  mul.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void multiply_ints_into_float_and_store(struct quad *quad,
                                        struct assembly_code *code) {
    fprintf(code->out, "  mul %s, %s, %s\n", registers[T0], registers[T0],
            registers[T1]);
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void multiply_ints_into_int_and_store(struct quad *quad,
                                      struct assembly_code *code) {
    fprintf(code->out, "  mul %s, %s, %s\n", registers[T0], registers[T0],
            registers[T1]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void multiply_int_float_into_int_and_store(struct quad *quad,
                                           struct assembly_code *code) {
    fprintf(code->out, "  cvt.w.s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T1], registers[F0]);
    fprintf(code->out, "  mul %s, %s, %s\n", registers[T0], registers[T1],
            registers[T1]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void multiply_floats_into_int_and_store(struct quad *quad,
                                        struct assembly_code *code) {
    fprintf(code->out, "  mul.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  cvt.w.s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_bop_mult(struct quad *quad, struct assembly_code *code) {
    if (quad->sym1->kind != NAME) {
        fprintf(stderr, "Error: first operand of BOP_MOINS is not a NAME\n");
        exit(1);
    }

    if (quad->sym1->u.id.type == REEL) {

        if (is_symbol_float(quad->sym2)) {
            if (is_symbol_float(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_float_symbol(quad->sym3, code, F2);
                multiply_floats_into_float_and_store(quad, code);
            }

            else if (is_symbol_int(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_int_symbol(quad->sym3, code, T0);
                multiply_int_float_into_float_and_store(quad, code);
            }

            else {
                fprintf(stderr, "Error: can't multiply a label to a float\n");
                exit(1);
            }

        } else if (is_symbol_int(quad->sym2)) {
            if (is_symbol_int(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_int_symbol(quad->sym3, code, T1);
                multiply_ints_into_float_and_store(quad, code);
            } else if (is_symbol_float(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_float_symbol(quad->sym3, code, F0);
                multiply_int_float_into_float_and_store(quad, code);
            } else {
                fprintf(stderr, "Error: can't multiply a label to an int\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: can't multiply a label to a label\n");
            exit(1);
        }
    }

    else if (quad->sym1->u.id.type == ENTIER) {

        if (is_symbol_float(quad->sym2)) {
            if (is_symbol_float(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_float_symbol(quad->sym3, code, F2);
                multiply_floats_into_int_and_store(quad, code);
            }

            else if (is_symbol_int(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_int_symbol(quad->sym3, code, T0);
                multiply_int_float_into_int_and_store(quad, code);
            }

            else {
                fprintf(stderr, "Error: can't multiply a label to a float\n");
                exit(1);
            }

        } else if (is_symbol_int(quad->sym2)) {
            if (is_symbol_int(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_int_symbol(quad->sym3, code, T1);
                multiply_ints_into_int_and_store(quad, code);
            } else if (is_symbol_float(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_float_symbol(quad->sym3, code, F0);
                multiply_int_float_into_int_and_store(quad, code);
            } else {
                fprintf(stderr, "Error: can't multiply a label to an int\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: can't multiply a label to a label\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Error: type MATRIX in binary multiplication\n");
        exit(1);
    }
}

// Division --------------------------------------------------------

void divide_floats_into_float_and_store(struct quad *quad,
                                        struct assembly_code *code) {
    fprintf(code->out, "  div.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void divide_int_float_into_float_and_store(struct quad *quad,
                                           struct assembly_code *code) {
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F2]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F2], registers[F2]);
    fprintf(code->out, "  div.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void divide_ints_into_float_and_store(struct quad *quad,
                                      struct assembly_code *code) {
    fprintf(code->out, "  div %s, %s, %s\n", registers[T0], registers[T0],
            registers[T1]);
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void divide_ints_into_int_and_store(struct quad *quad,
                                    struct assembly_code *code) {
    fprintf(code->out, "  div %s, %s, %s\n", registers[T0], registers[T0],
            registers[T1]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void divide_int_float_into_int_and_store(struct quad *quad,
                                         struct assembly_code *code) {
    fprintf(code->out, "  cvt.w.s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T1], registers[F0]);
    fprintf(code->out, "  div %s, %s, %s\n", registers[T0], registers[T1],
            registers[T1]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void divide_floats_into_int_and_store(struct quad *quad,
                                      struct assembly_code *code) {
    fprintf(code->out, "  div.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  cvt.w.s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_bop_divise(struct quad *quad, struct assembly_code *code) {
    if (quad->sym1->kind != NAME) {
        fprintf(stderr, "Error: first operand of BOP_DIVISE is not a NAME\n");
        exit(1);
    }

    if (quad->sym1->u.id.type == REEL) {

        if (is_symbol_float(quad->sym2)) {
            if (is_symbol_float(quad->sym3)) {
                if (quad->sym3->u.float_value == 0) {
                    fprintf(stderr,
                            "Error : division using zero is impossible\n");
                    exit(1);
                }

                move_float_symbol(quad->sym2, code, F0);
                move_float_symbol(quad->sym3, code, F2);
                divide_floats_into_float_and_store(quad, code);
            }

            else if (is_symbol_int(quad->sym3)) {
                if (quad->sym3->u.int_value == 0) {
                    fprintf(stderr,
                            "Error : division using zero is impossible\n");
                    exit(1);
                }

                move_float_symbol(quad->sym2, code, F0);
                move_int_symbol(quad->sym3, code, T0);
                divide_int_float_into_float_and_store(quad, code);
            }

            else {
                fprintf(stderr, "Error: can't divide a label to a float\n");
                exit(1);
            }

        } else if (is_symbol_int(quad->sym2)) {
            if (is_symbol_int(quad->sym3)) {
                if (quad->sym3->u.int_value == 0) {
                    fprintf(stderr,
                            "Error : division using zero is impossible\n");
                    exit(1);
                }

                move_int_symbol(quad->sym2, code, T0);
                move_int_symbol(quad->sym3, code, T1);
                divide_ints_into_float_and_store(quad, code);
            } else if (is_symbol_float(quad->sym3)) {
                if (quad->sym3->u.float_value == 0) {
                    fprintf(stderr,
                            "Error : division using zero is impossible\n");
                    exit(1);
                }

                move_int_symbol(quad->sym2, code, T0);
                move_float_symbol(quad->sym3, code, F0);
                divide_int_float_into_float_and_store(quad, code);
            } else {
                fprintf(stderr, "Error: can't divide a label to an int\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: can't divide a label to a label\n");
            exit(1);
        }
    }

    else if (quad->sym1->u.id.type == ENTIER) {

        if (is_symbol_float(quad->sym2)) {
            if (is_symbol_float(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_float_symbol(quad->sym3, code, F2);
                divide_floats_into_int_and_store(quad, code);
            }

            else if (is_symbol_int(quad->sym3)) {
                move_float_symbol(quad->sym2, code, F0);
                move_int_symbol(quad->sym3, code, T0);
                divide_int_float_into_int_and_store(quad, code);
            }

            else {
                fprintf(stderr, "Error: can't divide a label to a float\n");
                exit(1);
            }

        } else if (is_symbol_int(quad->sym2)) {
            if (is_symbol_int(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_int_symbol(quad->sym3, code, T1);
                divide_ints_into_int_and_store(quad, code);
            } else if (is_symbol_float(quad->sym3)) {
                move_int_symbol(quad->sym2, code, T0);
                move_float_symbol(quad->sym3, code, F0);
                divide_int_float_into_int_and_store(quad, code);
            } else {
                fprintf(stderr, "Error: can't divide a label to an int\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: can't divide a label to a label\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Error: type MATRIX in binary division\n");
        exit(1);
    }
}

// Unary addition --------------------------------------------------------

void unary_add_float_into_float_and_store(struct quad *quad,
                                          struct assembly_code *code) {
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void unary_add_int_into_float_and_store(struct quad *quad,
                                        struct assembly_code *code) {
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void unary_add_int_into_int_and_store(struct quad *quad,
                                      struct assembly_code *code) {
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void unary_add_float_into_int_and_store(struct quad *quad,
                                        struct assembly_code *code) {
    fprintf(code->out, "  cvt,w,s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_uop_plus(struct quad *quad, struct assembly_code *code) {
    if (quad->sym1->kind != NAME) {
        fprintf(stderr, "Error: first operand of UOP_PLUS is not a NAME\n");
        exit(1);
    }

    if (is_symbol_float(quad->sym2)) {
        if (is_symbol_float(quad->sym1)) {
            move_float_symbol(quad->sym2, code, F0);
            unary_add_float_into_float_and_store(quad, code);
        } else {
            move_float_symbol(quad->sym2, code, F0);
            unary_add_float_into_int_and_store(quad, code);
        }

    } else if (is_symbol_int(quad->sym2)) {
        if (is_symbol_int(quad->sym1)) {
            move_int_symbol(quad->sym2, code, T0);
            unary_add_int_into_int_and_store(quad, code);
        } else {
            move_int_symbol(quad->sym2, code, T0);
            unary_add_int_into_int_and_store(quad, code);
        }
    } else {
        fprintf(stderr, "Error: can't use unary addition with a label\n");
        exit(1);
    }
}

// Unary subtraction --------------------------------------------------------

void unary_subtract_float_into_float_and_store(struct quad *quad,
                                               struct assembly_code *code) {
    fprintf(code->out, "  sub.s %s, $zero, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void unary_subtract_int_into_float_and_store(struct quad *quad,
                                             struct assembly_code *code) {
    fprintf(code->out, "  sub %s, $zero, %s\n", registers[T0], registers[T0]);
    fprintf(code->out, "  mtc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  s.s %s, %s\n", registers[F0], quad->sym1->u.id.name);
}

void unary_subtract_int_into_int_and_store(struct quad *quad,
                                           struct assembly_code *code) {
    fprintf(code->out, "  sub %s, $zero, %s\n", registers[T0], registers[T0]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void unary_subtract_float_into_int_and_store(struct quad *quad,
                                             struct assembly_code *code) {
    fprintf(code->out, "  cvt,w,s %s, %s\n", registers[F0], registers[F0]);
    fprintf(code->out, "  mfc1 %s, %s\n", registers[T0], registers[F0]);
    fprintf(code->out, "  sub %s, $zero, %s\n", registers[T0], registers[T0]);
    fprintf(code->out, "  sw %s, %s\n", registers[T0], quad->sym1->u.id.name);
}

void manage_uop_moins(struct quad *quad, struct assembly_code *code) {
    if (quad->sym1->kind != NAME) {
        fprintf(stderr, "Error: first operand of UOP_MOINS is not a NAME\n");
        exit(1);
    }

    if (is_symbol_float(quad->sym2)) {
        if (is_symbol_float(quad->sym1)) {
            move_float_symbol(quad->sym2, code, F0);
            unary_subtract_float_into_float_and_store(quad, code);
        } else {
            move_float_symbol(quad->sym2, code, F0);
            unary_subtract_float_into_int_and_store(quad, code);
        }

    } else if (is_symbol_int(quad->sym2)) {
        if (is_symbol_int(quad->sym1)) {
            move_int_symbol(quad->sym2, code, T0);
            unary_subtract_int_into_int_and_store(quad, code);
        } else {
            move_int_symbol(quad->sym2, code, T0);
            unary_subtract_int_into_int_and_store(quad, code);
        }
    } else {
        fprintf(stderr, "Error: can't use unary subtraction with a label\n");
        exit(1);
    }
}