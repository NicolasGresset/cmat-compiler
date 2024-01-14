#include "assembly_print.h"
#include "data_segment.h"
#include <stdlib.h>

#define PRINT_INT_SYSCALL_NUMBER 1
#define PRINT_FLOAT_SYSCALL_NUMBER 2
#define PRINT_STRING_SYSCALL_NUMBER 4

void manage_call_print(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "#print \n");
  if (is_symbol_int(quad->sym1)) {
    move_int_symbol(quad->sym1, code, A0);
    fprintf(code->out, "  li $v0, %d\n", PRINT_INT_SYSCALL_NUMBER);
    fprintf(code->out, "  syscall\n");
  } else if (is_symbol_float(quad->sym1)) {
    move_float_symbol(quad->sym1, code, F12);
    fprintf(code->out, "  li $v0, %d\n", PRINT_FLOAT_SYSCALL_NUMBER);
    fprintf(code->out, "  syscall\n");
  } else {
    fprintf(stderr, "Error: can not print type : %d\n", quad->sym1->u.id.type);
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

// safe_call_printf

void manage_call_print_mat(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "#print_mat %s\n", quad->sym1->u.id.name);

  fprintf(code->out, "  la %s, %s\n", registers[T0],
          quad->sym1->u.id.name); // on charge l'adresse de la matrice dans $t0
  for (int i = 0; i < quad->sym1->u.id.row; i++) {
    call_printf(code, code->string_tab);
    for (int j = 0; j < quad->sym1->u.id.col; j++) {
      // print A[i][j]
      fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F12],
              4 * (i * quad->sym1->u.id.col + j),
              registers[T0]); // A[i][j] dans $f12
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
  fprintf(code->out, "#printf %s\n", quad->sym1->u.string);

  char declaration[MAX_DATA_SIZE];
  snprintf(declaration, MAX_DATA_SIZE, "  %s%d: .asciiz %s\n",
           code->string_constant, code->next_string_constant,
           quad->sym1->u.string);
  append_to_data(code, declaration);

  fprintf(
      code->out, "  la %s %s%d\n", registers[A0], code->string_constant,
      code->next_string_constant); // on charge l'adresse de la string dans $a0

  code->next_string_constant++;
  // on appelle la primitive
  fprintf(code->out, "  li $v0, %d\n", PRINT_STRING_SYSCALL_NUMBER);
  fprintf(code->out, "  syscall\n");
}