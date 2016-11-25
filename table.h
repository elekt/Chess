
#ifndef TABLE_HEADER_FILE_H
#define TABLE_HEADER_FILE_H

#include "piece.h"
#include <stdlib.h>

typedef struct table {
    piece** blocks;
} table;

table* init_table();

table* move(table* table, int x1, int y1, int x2, int y2);

#endif
