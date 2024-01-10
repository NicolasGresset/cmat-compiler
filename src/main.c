#include "CMat.h"

struct table_hachage_t * SYMTAB;
struct code * CODE;

extern int yydebug;

int main(void)
{
    //yydebug = 1;
    SYMTAB = table_hachage_init();
    CODE = code_new();
    int r = yyparse();

    table_hachage_print(SYMTAB);
    code_dump(CODE);

    table_hachage_free(SYMTAB);
    code_free(CODE);

    return r;
}
