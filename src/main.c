#include "CMat.h"
#include "assembly.h"

struct table_hachage_t *SYMTAB;
struct code *CODE;

extern int yydebug;

typedef struct {
    int tos;
    char *code_resultat;
} context_t;

context_t *context_new() {
    context_t *context = malloc(sizeof(context_t));
    context->tos = 0;
    context->code_resultat = NULL;
    return context;
}

void gestion_arguments(int argc, char **argv, context_t *context) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-version") == 0) {
            printf("CABOCHE Félix - CHECCHIN Thomas - GRESSET-BOURGEOIS "
                   "Nicolas - DHIVERT Sarah\n");
        }
        exit(0);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                context->code_resultat = argv[i + 1];
                // le code resultat doit etre ecrit dans ce fichier
            } else {
                fprintf(stderr, "Nom de fichier non précisé\n");
                exit(1);
            }
        }
    }

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-tos") == 0) {
            context->tos = 1;
        }
    }
}

int main(int argc, char **argv) {
    context_t *context = context_new();
    gestion_arguments(argc, argv, context);

    // yydebug = 1;
    SYMTAB = table_hachage_init();
    CODE = code_new();
    if (context->code_resultat != NULL) {
        CODE->filename = context->code_resultat;
    }
    int r = yyparse();
    generate_mips_code(CODE);

    if (context->tos == 1)
        table_hachage_print(SYMTAB);
    code_dump(CODE);

    table_hachage_free(SYMTAB);
    code_free(CODE);

    free(context);

    return r;
}
