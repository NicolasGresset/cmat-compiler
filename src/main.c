#include "CMat.h"

struct table_hachage_t *SYMTAB;
struct code *CODE;

extern int yydebug;

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-version") == 0) {
            printf("CABOCHE Félix - CHECCHIN Thomas - GRESSET-BOURGEOIS "
                   "Nicolas - DHIVERT Sarah\n");
        }
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                char *code_resultat = argv[i + 1];
                // le code resultat doit etre ecrit dans ce fichier
            } else {
                fprintf(stderr, "Nom de fichier non précisé\n");
                exit(1);
            }
        }
    }

    // yydebug = 1;
    SYMTAB = table_hachage_init();
    CODE = code_new();
    int r = yyparse();

    // for (int i = 0; i < argc; i++) {
    //     if (strcmp(argv[i], "-tos") == 0) {
    //         table_hachage_print(SYMTAB);
    //     }
    // }
    // pour l'option tos

    table_hachage_print(SYMTAB);
    code_dump(CODE);

    table_hachage_free(SYMTAB);
    code_free(CODE);

    return r;
}
