
#ifndef TABLE_HEADER_FILE_H
#define TABLE_HEADER_FILE_H

#include "piece.h"
#include "coordinate.h"
#include <stdlib.h>

typedef struct table {
    color LAST_COLOR;
    piece** blocks;
} table;

table* init_table();

table* move(table* table, coordinate coord_start, coordinate coord_final);

#endif
