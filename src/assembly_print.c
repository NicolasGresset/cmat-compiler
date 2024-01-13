#include "assembly_print.h"
#include <stdlib.h>

#define PRINT_INT_SYSCALL_NUMBER 1
#define PRINT_FLOAT_SYSCALL_NUMBER 2

void manage_call_print(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "#print %s\n", quad->sym1->u.id.name);
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
        fprintf(stderr, "Error: can not print type : %d\n", quad->sym1->u.id.type);
        exit(1);
  }
}

