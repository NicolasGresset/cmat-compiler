#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lib.h"

struct symtable * symtable_new()
{
    struct symtable * t = malloc(sizeof(struct symtable));
    t->capacity = 1024;
    t->symbols = malloc(t->capacity*sizeof(struct symbol));
    t->temporary = 0;
    t->size = 0;
    return t;
}

static void symtable_grow(struct symtable * t)
{
    t->capacity += 1024;
    t->symbols = realloc(t->symbols,t->capacity*sizeof(struct symbol));
    if(t->symbols == NULL)
    {
      fprintf(stderr,"Error attempting to grow symbol table (actual size is %d)\n",t->size);
        exit(1);
    }
}

struct symbol * symtable_const(struct symtable * t, float v, type_t typeval)
{
    unsigned int i;
    switch (typeval)
    {
    case ENTIER:
            for ( i=0 ; i<t->size && t->symbols[i].u.value.int_value != (int)v; i++ );
            break;
    case REEL:
            for ( i=0 ; i<t->size && t->symbols[i].u.value.int_value != v; i++ );
            break;
    }
    if(i==t->size)
    {
        if(t->size==t->capacity)
            symtable_grow(t);
        struct symbol *s = &(t->symbols[t->size]);
        s->kind = CONSTANT;
        s->type = typeval;
        switch (typeval)
        {
        case ENTIER:
            s->u.value.int_value = (int)v;
            break;
        case REEL:
            s->u.value.float_value = v;
            break;
        }
        ++ (t->size);
        return s;
    }
    else
        return &(t->symbols[i]);
}

struct symbol * symtable_get(struct symtable * t, const char * id)
{
    unsigned int i;
    for ( i=0 ; i<t->size && strcmp(t->symbols[i].u.name,id) != 0; i++ );
    if(i<t->size)
      return &(t->symbols[i]);
    return NULL;
}

struct symbol * symtable_put(struct symtable * t,
                             const char * id,
                             const type_t typeval)
{
    if(t->size==t->capacity)
      symtable_grow(t);
    struct symbol *s = &(t->symbols[t->size]);
    s->kind = NAME;
    s->type = typeval;
    strcpy(s->u.name,id);
    ++ (t->size);
    return s;
}

void symtable_dump(struct symtable * t)
{
    unsigned int i;
    for ( i=0 ; i<t->size; i++ )
    {
      if(t->symbols[i].kind==CONSTANT)
      {
          if ( t->symbols[i].type == ENTIER)
              printf("       %p = %d\n",&(t->symbols[i]),t->symbols[i].u.value.int_value);
          else
              printf("       %p = %f\n",&(t->symbols[i]),t->symbols[i].u.value.float_value);
      }
      if(t->symbols[i].kind==NAME)
          printf("       %p = %s  %d\n",&(t->symbols[i]),t->symbols[i].u.name, t->symbols[i].type);
    }
    printf("       --------\n");
}


void symtable_free(struct symtable * t)
{
    free(t->symbols);
    free(t);
}

struct code * code_new()
{
    struct code * r = malloc(sizeof(struct code));
    r->capacity = 1024;
    r->quads = malloc(r->capacity*sizeof(struct quad));
    r->nextquad = 0;
    return r;
}

static void code_grow(struct code * c)
{
    c->capacity += 1024;
    c->quads = realloc(c->quads,c->capacity*sizeof(struct quad));
    if(c->quads == NULL)
    {
      fprintf(stderr,"Error attempting to grow quad list (actual size is %d)\n",c->nextquad);
        exit(1);
    }
}

void gencode(struct code * c,
              enum quad_kind k,
              struct symbol * s1,
              struct symbol * s2,
              struct symbol * s3)
{
    if ( c->nextquad == c->capacity )
        code_grow(c);
    struct quad * q = &(c->quads[c->nextquad]);
    q->kind = k;
    q->sym1 = s1;
    q->sym2 = s2;
    q->sym3 = s3;
    ++ (c->nextquad);
}

struct symbol *newtemp(struct symtable * t)
{
  struct symbol * s;
  name_t name;
  sprintf(name,"t%d",t->temporary);
  int typeval = ENTIER; //temporaire
  s = symtable_put(t,name, typeval);
  ++ (t->temporary);
  return s;
}

static void symbol_dump(struct symbol * s)
{
    switch ( s->kind )
    {
        case NAME:
            printf("%s",s->u.name);
            break;
        case CONSTANT:
            if (s->type == ENTIER)
                printf("%d",s->u.value.int_value);
            else
                printf("%f", s->u.value.float_value);
            break;
        default:
            break;
    }
}

static void quad_dump(struct quad * q)
{
    switch ( q->kind )
    {
        case BOP_PLUS:
            symbol_dump(q->sym1);
            printf(" := ");
            symbol_dump(q->sym2);
            printf(" + ");
            symbol_dump(q->sym3);
            break;
        case BOP_MINUS:
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
        case UOP_MINUS:
            symbol_dump(q->sym1);
            printf(" := ");
            printf("- ");
            symbol_dump(q->sym2);
            break;
        case CALL_PRINT:
            printf("print ");
            symbol_dump(q->sym1);
            break;
        case COPY:
            symbol_dump(q->sym1);
            printf(" := ");
            symbol_dump(q->sym2);
            break;
        default:
            printf("BUG\n");
            break;
    }
}

void code_dump(struct code * c)
{
    unsigned int i;
    for ( i=0 ; i<c->nextquad ; i++ )
    {
        printf("%4u | ",i);
        quad_dump(&(c->quads[i]));
        printf("\n");
    }
}

void code_free(struct code * c)
{
    free(c->quads);
    free(c);
}
