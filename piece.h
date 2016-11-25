
#ifndef PIECE_H
#define PIECE_H

#include "piece_type.h"
#include "color.h"

typedef struct piece {
    color COLOR;
    piece_type PIECE_TYPE;
} piece;

#endif
