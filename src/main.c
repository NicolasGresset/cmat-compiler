#include <stdio.h>
#include "parser.h"

extern int yyparse();


int main(void)
{
    yydebug = 1;
    int r = yyparse();
    printf("-> Analyseur lexical retourne : %d\n", r);
    return r;
}
