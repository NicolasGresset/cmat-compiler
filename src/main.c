#include "CMat.h"

struct symtable * SYMTAB;
struct code * CODE;

extern int yydebug;

int main(void)
{
    //yydebug = 1;
    SYMTAB = symtable_new();
    CODE = code_new();
    int r = yyparse();
    //printf("-> Analyseur lexical retourne : %d\n", r);
    symtable_dump(SYMTAB);
    code_dump(CODE);
    symtable_free(SYMTAB);
    code_free(CODE);
    return r;
}
