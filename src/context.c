#include "context.h"
#include <stdio.h>
#include <stdlib.h>

context_t *context_new() {
    context_t *context = malloc(sizeof(context_t));
    context->tos = 0;
    context->code_resultat = NULL;
    return context;
}