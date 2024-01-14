#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symbol *symbol_id(const struct id_t id) {
  struct symbol *sym = malloc(sizeof(struct symbol));
  sym->kind = NAME;
  // snprintf(sym->u.id.name, TAILLE_MAX_TOKEN, "%s", id.name);
  strncpy(sym->u.id.name, id.name, TAILLE_MAX_TOKEN);
  sym->u.id.type = id.type;
  if (id.type == MATRIX_TYPE) {
    sym->u.id.row = id.row;
    sym->u.id.col = id.col;
  }
  return sym;
}

struct symbol *symbol_string(char *s) {
  struct symbol *sym = malloc(sizeof(struct symbol));
  sym->kind = STRING_CONSTANT;
  strncpy(sym->u.string, s, TAILLE_MAX_STRING);
  return sym;
}

struct symbol *symbol_const_int(int intval) {
  struct symbol *sym = malloc(sizeof(struct symbol));
  sym->kind = INT_CONSTANT;
  sym->u.int_value = intval;
  return sym;
}

struct symbol *symbol_const_float(float floatval) {
  struct symbol *sym = malloc(sizeof(struct symbol));
  sym->kind = FLOAT_CONSTANT;
  sym->u.float_value = floatval;
  return sym;
}


struct code *code_new() {
  struct code *r = malloc(sizeof(struct code));
  r->filename = NULL;
  r->capacity = 1024;
  r->quads = malloc(r->capacity * sizeof(struct quad));
  r->nextquad = 0;
  return r;
}

static void code_grow(struct code *c) {
  c->capacity += 1024;
  c->quads = realloc(c->quads, c->capacity * sizeof(struct quad));
  if (c->quads == NULL) {
    fprintf(stderr, "Error attempting to grow quad list (actual size is %d)\n",
            c->nextquad);
    exit(1);
  }
}

void gencode(struct code *c, enum quad_kind k, struct symbol *s1,
             struct symbol *s2, struct symbol *s3) {
  if (c->nextquad == c->capacity)
    code_grow(c);
  struct quad *q = &(c->quads[c->nextquad]);
  q->kind = k;
  q->sym1 = s1;
  q->sym2 = s2;
  q->sym3 = s3;
  ++(c->nextquad);
}

static void symbol_dump(struct symbol *s) {
  switch (s->kind) {
  case NAME:
    printf("%s", s->u.id.name);
    break;
  case INT_CONSTANT:
    printf("%d", s->u.int_value);
    break;
  case FLOAT_CONSTANT:
    printf("%f", s->u.float_value);
    break;
  case LABEL:
    printf("%d ", s->u.addr);
    break;
  case STRING_CONSTANT:
    printf("%s", s->u.string);
  default:
    break;
  }
}

struct symbol *quad_label(void) {
  struct symbol *q = malloc(sizeof(struct symbol));
  if (q == NULL)
    exit(1);
  q->kind = LABEL;
  return q;
}

static void quad_dump(struct quad *q) {
  switch (q->kind) {
  case BOP_PLUS:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" + ");
    symbol_dump(q->sym3);
    break;
  case BOP_MOINS:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" - ");
    symbol_dump(q->sym3);
    break;
  case BOP_MULT:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" * ");
    symbol_dump(q->sym3);
    break;
  case BOP_DIVISE:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" / ");
    symbol_dump(q->sym3);
    break;
  case UOP_PLUS:
    symbol_dump(q->sym1);
    printf(" := ");
    printf("+ ");
    symbol_dump(q->sym2);
    break;
  case UOP_MOINS:
    symbol_dump(q->sym1);
    printf(" := ");
    printf("- ");
    symbol_dump(q->sym2);
    break;

  case MATOP_PLUS:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" + ");
    symbol_dump(q->sym3);
    break;
  case MATOP_MOINS:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" - ");
    symbol_dump(q->sym3);
    break;
  case MATOP_MULT:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" * ");
    symbol_dump(q->sym3);
    break;
  case MATOP_DIVISE:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" / ");
    symbol_dump(q->sym3);
    break;
  case UMATOP_PLUS:
    symbol_dump(q->sym1);
    printf(" := ");
    printf("+ ");
    symbol_dump(q->sym2);
    break;
  case UMATOP_MOINS:
    symbol_dump(q->sym1);
    printf(" := ");
    printf("- ");
    symbol_dump(q->sym2);
    break;

  case MAT_BIN_PLUS:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" + ");
    symbol_dump(q->sym3);
    break;
  case MAT_BIN_MOINS:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" - ");
    symbol_dump(q->sym3);
    break;
  case MAT_BIN_MULT:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" * ");
    symbol_dump(q->sym3);
    break;
  case MAT_BIN_DIVISE:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf(" / ");
    symbol_dump(q->sym3);
    break;

  case ARRAY_AFFECT:
    symbol_dump(q->sym1);
    printf("[");
    symbol_dump(q->sym2);
    printf("]");
    printf(" := ");
    symbol_dump(q->sym3);
    break;

  case DEREF:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    printf("[");
    symbol_dump(q->sym3);
    printf("]");
    break;

  case UMATOP_TRANSPOSE:
    symbol_dump(q->sym1);
    printf(" := ~");
    symbol_dump(q->sym2);
    break;
  case CALL_PRINT:
    printf("print ");
    symbol_dump(q->sym1);
    break;

  case Q_DECLARE:
    printf("DECLARE ");
    symbol_dump(q->sym1);
    break;
  case Q_DECLARE_MAT:
    printf("DECLARE ");
    symbol_dump(q->sym1);
    break;

  case COPY:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    break;
  case ADRESSE:
    symbol_dump(q->sym1);
    printf(" := ");
    symbol_dump(q->sym2);
    break;

  case Q_IF_EQ:
    printf("if ");
    symbol_dump(q->sym1);
    printf(" == ");
    symbol_dump(q->sym2);
    printf(" goto ");
    symbol_dump(q->sym3);
    break;
  case Q_IF_NEQ:
    printf("if ");
    symbol_dump(q->sym1);
    printf(" != ");
    symbol_dump(q->sym2);
    printf(" goto ");
    symbol_dump(q->sym3);
    break;
  case Q_IF_LT:
    printf("if ");
    symbol_dump(q->sym1);
    printf(" < ");
    symbol_dump(q->sym2);
    printf(" goto ");
    symbol_dump(q->sym3);
    break;
  case Q_IF_LE:
    printf("if ");
    symbol_dump(q->sym1);
    printf(" <= ");
    symbol_dump(q->sym2);
    printf(" goto ");
    symbol_dump(q->sym3);
    break;
  case Q_IF_GE:
    printf("if ");
    symbol_dump(q->sym1);
    printf(" >= ");
    symbol_dump(q->sym2);
    printf(" goto ");
    symbol_dump(q->sym3);
    break;
  case Q_IF_GT:
    printf("if ");
    symbol_dump(q->sym1);
    printf(" > ");
    symbol_dump(q->sym2);
    printf(" goto ");
    symbol_dump(q->sym3);
    break;
  case Q_GOTO:
    printf("goto ");
    symbol_dump(q->sym3);
    break;
  case Q_GOTO_UNKNOWN:
    printf("goto ?");
    break;
  case Q_RETURN:
    printf("return ");
    symbol_dump(q->sym1);
    printf("\n");
    break;
  case CALL_PRINTF:
    symbol_dump(q->sym1);
    break;

  case CALL_PRINT_MAT:
    printf("printmat(");
    symbol_dump(q->sym1);
    printf(")");
    break;

  default:
    printf("BUG\n");
    break;
  }
}

void code_dump(struct code *c) {
  unsigned int i;
  for (i = 0; i < c->nextquad; i++) {
    printf("%4u | ", i);
    quad_dump(&(c->quads[i]));
    printf("\n");
  }
}

void safe_free(struct symbol *s) {
  if (s != NULL) {
    free(s);
  }
}

void code_free(struct code *c) {
  for (unsigned int i = 0; i < c->nextquad; i++) {
    safe_free(c->quads[i].sym1);
    safe_free(c->quads[i].sym2);
    safe_free(c->quads[i].sym3);
  }
  free(c->quads);
  free(c);
}
