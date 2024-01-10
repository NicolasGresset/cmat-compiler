#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "linked_list.h"
#include "table_symboles.h"

extern struct table_hachage_t * SYMTAB;
extern struct code * CODE;

extern int yyparse();
