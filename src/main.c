#include "CMat.h"
#include "assembly.h"
#include "context.h"

struct table_hachage_t *SYMTAB;
struct code *CODE;

extern int yydebug;

void gestion_arguments(int argc, char **argv, context_t *context) {
  if (argc == 1) {
    fprintf(stderr, "usage : %s -o outfile [-version -tos]\n", argv[0]);
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-version") == 0) {
      printf("CABOCHE Félix - CHECCHIN Thomas - GRESSET-BOURGEOIS "
             "Nicolas - DHIVERT Sarah\n");
      exit(0);
    }
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

void set_filename(context_t *context, struct code *code) {
  if (context->code_resultat != NULL) {
    code->filename = context->code_resultat;
  } else {
    code->filename = FILE_NAME;
  }
}

int main(int argc, char **argv) {
  context_t *context = context_new();
  gestion_arguments(argc, argv, context);
  printf("Fichier de sortie : \n");

  SYMTAB = table_hachage_init();
  CODE = code_new();
  set_filename(context, CODE);

  int r = yyparse();
  generate_mips_code(CODE);

  table_hachage_print(SYMTAB);
  code_dump(CODE);

  table_hachage_free(SYMTAB);
  code_free(CODE);

  free(context);
  return r;
}
