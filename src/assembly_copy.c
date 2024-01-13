#include "assembly_copy.h"
#include "assembly_matrix.h"
#include <stdlib.h>

/**
 * @brief symbol->u.id.name = $register_number
 *
 * @param quad
 * @param code
 * @param register_number
 */
void save_int_symbol(struct symbol *symbol, struct assembly_code *code,
                     int register_number) {
    switch (symbol->kind) {
    case NAME:
        fprintf(code->out, "  sw %s, %s\n", registers[register_number],
                symbol->u.id.name);
        break;
    default:
        fprintf(stderr, "Error: can't save symbol of kind %d to int location\n",
                symbol->kind);
        exit(1);
    }
}

/**
 * @brief Essaye de sauvegarder la valeur flottante du registre de numéro
 * register_number à l'emplacement mémoire correspondant au nom du symbole
 *
 * @param symbol
 * @param code
 * @param register_number
 */
void save_float_symbol(struct symbol *symbol, struct assembly_code *code,
                       int register_number) {
    switch (symbol->kind) {
    case NAME:
        fprintf(code->out, "  s.s %s, %s\n", registers[register_number],
                symbol->u.id.name);
        break;
    default:
        fprintf(stderr,
                "Error: can't save symbol of kind %d to float location\n",
                symbol->kind);
        exit(1);
    }
}

/**
 * @brief Essayes de sauvegarder la valeur flottante du registre de numéro
 * register_number_float à l'emplacement mémoire correspondant au nom du symbole
 *
 * @param quad
 * @param code
 * @param register_number_float
 * @param register_number_int
 */
void save_float_as_int_symbol(struct symbol *symbol, struct assembly_code *code,
                              int register_number_float,
                              int register_number_int) {

    switch (symbol->kind) {
    case NAME:
        fprintf(code->out, "  cvt.w.s %s, %s\n",
                registers[register_number_float],
                registers[register_number_float]);
        fprintf(code->out, "  mfc1 %s, %s\n", registers[register_number_int],
                registers[register_number_float]); // move from coprocessor 1 to
                                                   // $register_number_int
        fprintf(code->out, "  sw %s, %s\n", registers[register_number_int],
                symbol->u.id.name);
        break;
    default:
        fprintf(stderr, "Error: can't save symbol of kind %d to int location\n",
                symbol->kind);
        exit(1);
    }
}

// todo s'occuper des branchements conditionnels pour les floats

/**
 * @brief Essayes de sauvegarder la valeur flottante du registre de numéro
 * register_number à l'emplacement mémoire correspondant au nom du symbole
 *
 * @param quad
 * @param code
 * @param register_number_float
 * @param register_number_int
 */
void save_int_as_float_symbol(struct symbol *symbol, struct assembly_code *code,
                              int register_number_float,
                              int register_number_int) {

    switch (symbol->kind) {
    case NAME:
        fprintf(code->out, " mtc1 %s, %s\n", registers[register_number_int],
                registers[register_number_float]);
        fprintf(code->out, " cvt.s.w %s, %s\n",
                registers[register_number_float],
                registers[register_number_float]);
        fprintf(code->out, " s.s %s, %s\n", registers[register_number_float],
                symbol->u.id.name);
        break;
    default:
        fprintf(stderr, "Error: can't save symbol of kind %d to int location\n",
                symbol->kind);
        exit(1);
    }
}

void manage_copy(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "# copy to %s\n", quad->sym1->u.id.name);
    if (quad->sym1->u.id.type == ENTIER) {
        if (is_symbol_int(quad->sym2)) { // sym1 et sym2 sont des entiers
            move_int_symbol(quad->sym2, code, T0);
            save_int_symbol(quad->sym1, code, T0);
        } else if (is_symbol_float(
                       quad->sym2)) { // sym1 est un entier et sym2 un
                                      // flottant
                                      // il faut convertir (sym2) en entier
            move_float_symbol(quad->sym2, code, F0);
            save_float_as_int_symbol(quad->sym1, code, F0, T0);
        }
    } else if (quad->sym1->u.id.type == REEL) {
        if (is_symbol_float(quad->sym2)) { // sym1 et sym2 sont des flottants
            move_float_symbol(quad->sym2, code, F0);
            save_float_symbol(quad->sym1, code, F0);
        } else if (is_symbol_int(
                       quad->sym2)) { // sym1 est un flottant et sym2 un
                                      // entier
                                      // il faut convertir (sym2) en flottant
            move_int_symbol(quad->sym2, code, T0);
            save_int_as_float_symbol(quad->sym1, code, F0, T0);
        }

    } else if (quad->sym2->u.id.type == MATRIX_TYPE) {
        manage_copy_mat(quad, code);
    } else {
        fprintf(stderr, "Error: can't copy a label\n");
        exit(1);
    }
}