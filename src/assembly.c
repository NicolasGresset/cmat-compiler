#include "../include/assembly.h"
#include <stdio.h>

void manage_bop_plus(struct quad *quad, FILE *out){
    fprintf(out, "add $t0, $t1, $t2\n");
}

void manage_quad(struct quad *quad, FILE *out){
    switch(quad->kind){
    case BOP_PLUS:
        manage_bop_plus(quad, out);
        break;
    }
}

FILE * open_file(const char *file_name){
    FILE *file = fopen(file_name, "w");
    if (file == NULL){
        fprintf(stderr, "Error while opening file %s\n", file_name);
        exit(1);
    }
    return file;
    
}



void generate_mips_code(struct code *code) {
  /* On va itérer sur les quads compris dans code et transformer chacun d'eux en
   * code MIPS*/
  FILE * out = open_file(FILE_NAME);

  struct quad quad;
  int i;
  for (i = 0; i<code->nextquad; i++){
    quad = code->quads[i];
    manage_quad(&quad, out);
  }
}