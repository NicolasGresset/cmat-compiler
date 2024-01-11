#pragma once

#include "lib.h"
#include "linked_list.h"
#include "table_symboles.h"
#include <stdio.h>
#include <stdlib.h>

extern struct table_hachage_t *SYMTAB;
extern struct code *CODE;

extern int yyparse();
