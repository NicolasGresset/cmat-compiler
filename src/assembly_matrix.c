#include "assembly_matrix.h"
#include "data_segment.h"

#include <stdlib.h>

void manage_declare_mat(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# declare mat %s\n", quad->sym1->u.id.name);

    char declaration[MAX_DATA_SIZE];
    snprintf(declaration, MAX_DATA_SIZE, "  %s: .float ",
             quad->sym1->u.id.name);
    append_to_data(code, declaration);

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;
    for (unsigned int i = 0; i < nelem; i++) {
        append_to_data(code, "0.0");
        if (i < nelem - 1) {
            append_to_data(code, ", ");
        }
    }
    append_to_data(code, "\n");
}

void manage_bop_plus_mat(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# matop plus %s = %s + %s\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name, quad->sym3->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;
    char *name3 = quad->sym3->u.id.name;

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2
    fprintf(code->out, "  la %s, %s\n", registers[T2], name3); // T2 = &id3

    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F2], 4 * i,
                registers[T2]);
        fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0], registers[F0],
                registers[F2]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T0]);
    }
}

// todo tester
void manage_bop_moins_mat(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# matop moins %s = %s - %s\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name, quad->sym3->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;
    char *name3 = quad->sym3->u.id.name;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2
    fprintf(code->out, "  la %s, %s\n", registers[T2], name3); // T2 = &id3

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F2], 4 * i,
                registers[T2]);
        fprintf(code->out, "  sub.s %s, %s, %s\n", registers[F0], registers[F0],
                registers[F2]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T0]);
    }
}

/**
 * @brief Met 0.0 dans le registre flottant register_number
 *
 * @param register_number
 * @param code
 */
void put_float_zero_in_reg(int register_number, struct assembly_code *code) {
    fprintf(code->out, "  l.s %s, %s\n", registers[register_number],
            code->float_zero);
}

void manage_bop_mult_mat(struct quad *quad, struct assembly_code *code) {
    // A = B * C
    fprintf(code->out, "# matop mult %s = %s * %s\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name, quad->sym3->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;
    char *name3 = quad->sym3->u.id.name;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2
    fprintf(code->out, "  la %s, %s\n", registers[T2], name3); // T2 = &id3

    for (int ligne = 0; ligne < quad->sym1->u.id.row; ligne++) {
        for (int colonne = 0; colonne < quad->sym1->u.id.col; colonne++) {
            put_float_zero_in_reg(F0, code); // F0 = 0
            for (int k = 0; k < quad->sym2->u.id.col; k++) {
                fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F2],
                        4 * (ligne * quad->sym2->u.id.col + k),
                        registers[T1]); // F2 = B[ligne][k]
                fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F4],
                        4 * (k * quad->sym3->u.id.col + colonne),
                        registers[T2]); // F4 = C[k][colonne]
                fprintf(code->out, "  mul.s %s, %s, %s\n", registers[F2],
                        registers[F2],
                        registers[F4]); // F2 = B[ligne][k] * C[k][colonne]
                fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0],
                        registers[F0],
                        registers[F2]); // F0 += B[ligne][k] * C[k][colonne]
            }
            fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0],
                    4 * (ligne * quad->sym1->u.id.col + colonne),
                    registers[T0]); // A[ligne][colonne] = F0
        }
    }
}

// todo tester
void manage_bop_divise_mat(struct quad *quad, struct assembly_code *code) {
    // A = B / C
    fprintf(code->out, "# matop div %s = %s / %s\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name, quad->sym3->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;
    char *name3 = quad->sym3->u.id.name;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2
    fprintf(code->out, "  la %s, %s\n", registers[T2], name3); // T2 = &id3

    for (int ligne = 0; ligne < quad->sym1->u.id.row; ligne++) {
        for (int colonne = 0; colonne < quad->sym1->u.id.col; colonne++) {
            put_float_zero_in_reg(F0, code); // F0 = 0
            for (int k = 0; k < quad->sym2->u.id.col; k++) {
                fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F2],
                        4 * (ligne * quad->sym2->u.id.col + k),
                        registers[T1]); // F2 = B[ligne][k]
                fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F4],
                        4 * (k * quad->sym3->u.id.col + colonne),
                        registers[T2]); // F4 = C[k][colonne]
                fprintf(code->out, "  div.s %s, %s, %s\n", registers[F2],
                        registers[F2],
                        registers[F4]); // F2 = B[ligne][k] * C[k][colonne]
                fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0],
                        registers[F0],
                        registers[F2]); // F0 += B[ligne][k] * C[k][colonne]
            }
            fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0],
                    4 * (ligne * quad->sym1->u.id.col + colonne),
                    registers[T0]); // A[ligne][colonne] = F0
        }
    }
}

void manage_uop_plus_mat(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# uop plus %s = + %s\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name);

    // copie simple et méchante de la matrice sym2 dans sym1
    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T0]);
    }
}

void manage_uop_moins_mat(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# uop moins %s = - %s\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name);
    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);
        fprintf(code->out, "  neg.s %s, %s\n", registers[F2], registers[F0]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F2], 4 * i,
                registers[T0]);
    }
}

void manage_bop_plus_mat_bin(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# matop plus %s = %s + scalaire\n",
            quad->sym1->u.id.name, quad->sym2->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2

    if (is_symbol_float(quad->sym3)) {
    	move_float_symbol(quad->sym3, code, F2);
    }
	else if (is_symbol_int(quad->sym3)) {
		move_int_symbol(quad->sym3, code, T2);
		fprintf(code->out, "  mtc1 %s, %s\n", registers[T2], registers[F2]);
		fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F2], registers[F2]);
	}
	else {
        fprintf(stderr, "Error : Addition of matrix with something which "
                        "is not a number\n");
        exit(1);
	}

    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);

        fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0], registers[F0],
                registers[F2]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T0]);
    }
}

void manage_bop_moins_mat_bin(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# matop plus %s = %s - scalaire\n",
            quad->sym1->u.id.name, quad->sym2->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2

    if (is_symbol_float(quad->sym3)) {
    	move_float_symbol(quad->sym3, code, F2);
    }
	else if (is_symbol_int(quad->sym3)) {
		move_int_symbol(quad->sym3, code, T2);
		fprintf(code->out, "  mtc1 %s, %s\n", registers[T2], registers[F2]);
		fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F2], registers[F2]);
	}
	else {
        fprintf(stderr, "Error : Subtraction of matrix with something which "
                        "is not a number\n");
        exit(1);
	}
    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);

        fprintf(code->out, "  sub.s %s, %s, %s\n", registers[F0], registers[F0],
                registers[F2]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T0]);
    }
}

void manage_bop_mult_mat_bin(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# matop plus %s = %s * scalaire\n",
            quad->sym1->u.id.name, quad->sym2->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2

    if (is_symbol_float(quad->sym3)) {
    	move_float_symbol(quad->sym3, code, F2);
    }
	else if (is_symbol_int(quad->sym3)) {
		move_int_symbol(quad->sym3, code, T2);
		fprintf(code->out, "  mtc1 %s, %s\n", registers[T2], registers[F2]);
		fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F2], registers[F2]);
	}
	else {
        fprintf(stderr, "Error : Multiplication of matrix with something which "
                        "is not a number\n");
        exit(1);
	}

    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);

        fprintf(code->out, "  mul.s %s, %s, %s\n", registers[F0], registers[F0],
                registers[F2]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T0]);
    }
}

void manage_bop_divise_mat_bin(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# matop plus %s = %s / scalaire\n",
            quad->sym1->u.id.name, quad->sym2->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2

    if (is_symbol_float(quad->sym3)) {
    	move_float_symbol(quad->sym3, code, F2);
    }
	else if (is_symbol_int(quad->sym3)) {
		move_int_symbol(quad->sym3, code, T2);
		fprintf(code->out, "  mtc1 %s, %s\n", registers[T2], registers[F2]);
		fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F2], registers[F2]);
	}
	else {
        fprintf(stderr, "Error : Division of matrix with something which "
                        "is not a number\n");
        exit(1);
	}

    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);

        fprintf(code->out, "  div.s %s, %s, %s\n", registers[F0], registers[F0],
                registers[F2]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T0]);
    }
}

void manage_copy_mat(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# copy mat %s = %s\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;

    unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2

    for (unsigned int i = 0; i < nelem; i++) {
        fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T1]);
        fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i,
                registers[T0]);
    }
}

// todo tester
void manage_transpose_mat(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# transpose mat %s = ~%s\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name);

    char *name1 = quad->sym1->u.id.name;
    char *name2 = quad->sym2->u.id.name;

    fprintf(code->out, "  la %s, %s\n", registers[T0], name1); // T0 = &id1
    fprintf(code->out, "  la %s, %s\n", registers[T1], name2); // T1 = &id2

    for (int ligne = 0; ligne < quad->sym1->u.id.row; ligne++) {
        for (int colonne = 0; colonne < quad->sym1->u.id.col; colonne++) {
            fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0],
                    4 * (ligne * quad->sym1->u.id.col + colonne),
                    registers[T1]); // F0 = B[ligne][colonne]
            fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0],
                    4 * (colonne * quad->sym1->u.id.row + ligne),
                    registers[T0]); // A[colonne][ligne] = F0
        }
    }
}

// todo tester
void manage_array_affect(struct quad *quad, struct assembly_code *code) {
    // on assume ici que quad->sym1 est un tableau, et quad->sym2 est un entier
    // représentant l'indice et quad->sym3 est la valeur à affecter
    // quad->sym1 étant un tableau, il pointe vers un emplacement de flottants
    // !!!

    fprintf(code->out, "# array affect %s[%d] = ...\n", quad->sym1->u.id.name,
            quad->sym2->u.int_value);

    fprintf(code->out, "  la %s, %s\n", registers[T0],
            quad->sym1->u.id.name); // T0 = &id
    if (is_symbol_int(quad->sym3)) {
        move_int_symbol(quad->sym3, code, T1);
        fprintf(code->out, "  mtc1 %s, %s\n", registers[T1], registers[F0]);
        fprintf(code->out, "  cvt.s.w %s, %s\n", registers[F0], registers[F0]);
    } else if (is_symbol_float(quad->sym3)) {
        move_float_symbol(quad->sym3, code, F0); // F0 = sym3->value
    } else {
        fprintf(stderr, "Error: array affect: sym3 is not a float or int\n");
    }

    fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0],
            4 * quad->sym2->u.int_value, registers[T0]); // *id = F0
}

// todo tester
void manage_deref(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# deref %s = *(%s + %d)\n", quad->sym1->u.id.name,
            quad->sym2->u.id.name, quad->sym3->u.int_value);

    fprintf(code->out, "  la %s, %s\n", registers[T0],
            quad->sym2->u.id.name); // T0 = &id2

    fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0],
            4 * quad->sym3->u.int_value, registers[T0]); // F0 = *(id2 + i)

    fprintf(code->out, "  s.s %s, %s\n", registers[F0],
            quad->sym1->u.id.name); // id1 = F0
}