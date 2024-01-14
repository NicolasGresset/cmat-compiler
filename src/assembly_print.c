#include "assembly_print.h"
#include <stdlib.h>

#define PRINT_INT_SYSCALL_NUMBER 1
#define PRINT_FLOAT_SYSCALL_NUMBER 2
#define PRINT_STRING_SYSCALL_NUMBER 4

void manage_call_print(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "#print \n");
    if (quad->sym1->kind == INT_CONSTANT) {
        move_int_symbol(quad->sym1, code, A0);
        fprintf(code->out, "li $v0, %d\n", PRINT_INT_SYSCALL_NUMBER);
        fprintf(code->out, "syscall\n");
    } else if (quad->sym1->kind == FLOAT_CONSTANT) {
        move_float_symbol(quad->sym1, code, F12);
        fprintf(code->out, "li $v0, %d\n", PRINT_FLOAT_SYSCALL_NUMBER);
        fprintf(code->out, "syscall\n");
    } else if (quad->sym1->kind == NAME) {
        switch (quad->sym1->u.id.type) {
        case ENTIER:
            move_int_symbol(quad->sym1, code, A0);
            fprintf(code->out, "li $v0, %d\n", PRINT_INT_SYSCALL_NUMBER);
            fprintf(code->out, "syscall\n");
            break;
        case REEL:
            move_float_symbol(quad->sym1, code, F12);
            fprintf(code->out, "li $v0, %d\n", PRINT_FLOAT_SYSCALL_NUMBER);
            fprintf(code->out, "syscall\n");
            break;
        default:
            fprintf(stderr, "Error: can not print type : %d\n",
                    quad->sym1->u.id.type);
            exit(1);
        }
    } else {
        fprintf(stderr, "Error: can not print type : %d\n",
                quad->sym1->u.id.type);
        exit(1);
    }
}

/**
 * @brief Apelle printf avec le label donné en paramètre
 *
 * @param code
 * @param label
 */
void call_printf(struct assembly_code *code, char *label) {
  fprintf(code->out, "  li $v0, %d\n", PRINT_STRING_SYSCALL_NUMBER);
  fprintf(code->out, "  la %s, %s\n", registers[A0], label);
  fprintf(code->out, "  syscall\n");
}

void manage_call_print_mat(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "#print_mat %s\n", quad->sym1->u.id.name);

  fprintf(code->out, "  la %s, %s\n", registers[A0],
          quad->sym1->u.id.name); // on charge l'adresse de la matrice dans $a0
  for (int i = 0; i < quad->sym1->u.id.row; i++) {
    for (int j = 0; j < quad->sym1->u.id.col; j++) {
      // print A[i][j]
      fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F12],
              4 * (i * quad->sym1->u.id.col + j),
              registers[A0]); // on charge la valeur dans $f12
      fprintf(code->out, "  li $v0, %d\n", PRINT_FLOAT_SYSCALL_NUMBER);
      fprintf(code->out, "  syscall\n");
      if (j != quad->sym1->u.id.col - 1) {
        call_printf(code, code->string_tab);
      }
    }
    call_printf(code, code->string_newline);
  }
}

void manage_call_printf(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "#printf %s\n", quad->sym1->u.id.name);

    // on recoit une string dans sym1, on veut l'afficher
    // on va la mettre dans le segment data en réécrivant par dessus
    // code->string_constant puis on va appeller le syscall
    // PRINT_STRING_SYSCALL_NUMBER avec $a0 = code->string_constant

    fprintf(code->out, "  la %s %s\n", registers[A0],
            code->string_constant); // on charge l'adresse de la string dans $a0

    // on écrit la string dans le segment data
    quad->sym1->u.id.name[TAILLE_MAX_STRING - 1] =
        '\0'; // on s'assure que la string est bien terminée
    for (int i = 0; quad->sym1->u.id.name[i] != '\0' && i < TAILLE_MAX_STRING;
         i++) {
        fprintf(code->out, "  li %s, %d\n", registers[T0],
                (int)quad->sym1->u.id.name[i]);
        fprintf(code->out, "  sb %s, 0(%s)\n", registers[T0],
                registers[A0]); // store byte
        fprintf(code->out, "  addi %s, %s, 1\n", registers[A0],
                registers[A0]); // on incrémente l'index
    }

    // on appelle la primitive
    fprintf(code->out, "  li $v0, %d\n", PRINT_STRING_SYSCALL_NUMBER);
    fprintf(code->out, "  syscall\n");
}
