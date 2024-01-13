#include "assembly_matrix.h"
#include "data_segment.h"

void manage_declare_mat(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "# declare mat %s\n", quad->sym1->u.id.name);

  char declaration[MAX_DATA_SIZE];
  snprintf(declaration, MAX_DATA_SIZE, "  %s: .float ", quad->sym1->u.id.name);
  append_to_data(code, declaration);

  unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;
  for (unsigned int i = 0; i < nelem; i++) {
    append_to_data(code, "0.0");
    if (i < nelem - 1) {
      append_to_data(code, ", ");
    }
  }
  append_to_data(code, "\n");
}

void manage_bop_plus_mat(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "# matop plus %s = %s + %s\n", quad->sym1->u.id.name,
          quad->sym2->u.id.name, quad->sym3->u.id.name);

  char *name1 = quad->sym1->u.id.name;
  char *name2 = quad->sym2->u.id.name;
  char *name3 = quad->sym3->u.id.name;

  unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

  for (unsigned int i = 0; i < nelem; i++) {
    fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i, name2);
    fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F2], 4 * i, name3);
    fprintf(code->out, "  add.s %s, %s, %s\n", registers[F0], registers[F0],
            registers[F2]);
    fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i, name1);
  }
}

void manage_copy_mat(struct quad *quad, struct assembly_code *code) {
  fprintf(code->out, "# copy mat %s = %s\n", quad->sym1->u.id.name,
          quad->sym2->u.id.name);

  char *name1 = quad->sym1->u.id.name;
  char *name2 = quad->sym2->u.id.name;

  unsigned int nelem = quad->sym1->u.id.row * quad->sym1->u.id.col;

  for (unsigned int i = 0; i < nelem; i++) {
    fprintf(code->out, "  l.s %s, %d(%s)\n", registers[F0], 4 * i, name2);
    fprintf(code->out, "  s.s %s, %d(%s)\n", registers[F0], 4 * i, name1);
  }
}