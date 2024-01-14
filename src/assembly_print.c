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
    } else {
        fprintf(stderr, "Error: can not print type : %d\n",
                quad->sym1->u.id.type);
        exit(1);
    }
}

void manage_call_printf(struct quad *quad, struct assembly_code *code) {
    fprintf(code->out, "#printf %s\n", quad->sym1->u.id.name);

    fprintf(code->out, "la $a0, %s\n", quad->sym1->u.id.name);
    fprintf(code->out, "li $v0, %d\n", PRINT_STRING_SYSCALL_NUMBER);
}
