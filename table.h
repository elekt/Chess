
#ifndef TABLE_HEADER_FILE_H
#define TABLE_HEADER_FILE_H

#include "piece.h"
#include <stdlib.h>

typedef struct table {
    piece** blocks;
} table;

table* init_table();

#endif
