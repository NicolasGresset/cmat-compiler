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
    if (id.type == MATRIX_TYPE)
    {
        sym->u.id.row = id.row;
        sym->u.id.col = id.col;
    }
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

struct symtable *symtable_new() {
    struct symtable *t = malloc(sizeof(struct symtable));
    t->capacity = 1024;
    t->symbols = malloc(t->capacity * sizeof(struct symbol));
    t->temporary = 0;
    t->size = 0;
    return t;
}

static void symtable_grow(struct symtable *t) {
    t->capacity += 1024;
    t->symbols = realloc(t->symbols, t->capacity * sizeof(struct symbol));
    if (t->symbols == NULL) {
        fprintf(stderr,
                "Error attempting to grow symbol table (actual size is %d)\n",
                t->size);
        exit(1);
    }
}

struct symbol *symtable_const_int(struct symtable *t, int e) {
    unsigned int i;
    for (i = 0; i < t->size; i++) {
        if (t->symbols[i].kind == INT_CONSTANT &&
            t->symbols[i].u.int_value == e)
            break;
    }

    if (i == t->size) {
        if (t->size == t->capacity)
            symtable_grow(t);
        struct symbol *s = &(t->symbols[t->size]);
        s->kind = INT_CONSTANT;
        s->u.int_value = e;
        ++(t->size);
        return s;
    } else
        return &(t->symbols[i]);
}

struct symbol *symtable_const_float(struct symtable *t, float v) {
    unsigned int i;
    for (i = 0; i < t->size; i++) {
        if (t->symbols[i].kind == FLOAT_CONSTANT &&
            t->symbols[i].u.float_value == v)
            break;
    }

    if (i == t->size) {
        if (t->size == t->capacity)
            symtable_grow(t);
        struct symbol *s = &(t->symbols[t->size]);
        s->kind = FLOAT_CONSTANT;
        s->u.float_value = v;
        ++(t->size);
        return s;
    } else
        return &(t->symbols[i]);
}

struct symbol *symtable_get(struct symtable *t, const char *id) {
    unsigned int i;
    for (i = 0; i < t->size && strcmp(t->symbols[i].u.id.name, id) != 0; i++)
        ;
    if (i < t->size)
        return &(t->symbols[i]);
    return NULL;
}

struct symbol *symtable_put(struct symtable *t, const char *id, type_t type) {
    if (t->size == t->capacity)
        symtable_grow(t);
    struct symbol *s = &(t->symbols[t->size]);
    s->kind = NAME;
    strcpy(s->u.id.name, id);
    s->u.id.type = type;
    ++(t->size);
    return s;
}

void symtable_dump(struct symtable *t) {
    unsigned int i;
    for (i = 0; i < t->size; i++) {
        switch (t->symbols[i].kind) {
        case INT_CONSTANT:
            printf("       %p = %d\n", &(t->symbols[i]),
                   t->symbols[i].u.int_value);
            break;
        case FLOAT_CONSTANT:
            printf("       %p = %f\n", &(t->symbols[i]),
                   t->symbols[i].u.float_value);
            break;
        case NAME:
            printf("       %p = %s  %d\n", &(t->symbols[i]),
                   t->symbols[i].u.id.name, t->symbols[i].u.id.type);
            break;
        case LABEL:
            printf("       %p = %d\n", &(t->symbols[i]), t->symbols[i].u.addr);
            break;
        default:
            break;
        }
    }
    printf("       --------\n");
}

void symtable_free(struct symtable *t) {
    free(t->symbols);
    free(t);
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
        fprintf(stderr,
                "Error attempting to grow quad list (actual size is %d)\n",
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

/* struct symbol *newtemp(struct symtable * t) */
/* { */
/*   struct symbol * s; */
/*   name_t name; */
/*   sprintf(name,"t%d",t->temporary); */
/*   int typeval = ENTIER; //temporaire */
/*   s = symtable_put(t,name, typeval); */
/*   ++ (t->temporary); */
/*   return s; */
/* } */

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

void code_free(struct code *c) {
    free(c->quads->sym1);
    free(c->quads->sym2);
    free(c->quads->sym3);
    free(c->quads);
    free(c);
}
