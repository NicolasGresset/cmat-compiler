#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "linked_list.h"

extern struct symtable * SYMTAB;
extern struct code * CODE;

extern int yyparse();
