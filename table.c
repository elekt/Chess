#include "table.h"
#include "piece.h"
#include <stdlib.h>

table* init_table() {
    int i, j;
  
    piece** pieces = (piece**) malloc(8 * sizeof(piece*));
    for(i = 0; i < 8; i++) {
        pieces[i] = (piece*)malloc(8 * sizeof(piece));
    }


    for(i = 0; i < 8; ++i) {
        for(j = 0; j < 8; ++j) {
            // do fancy stuff            
        }
    }
    

    table* table = malloc(sizeof(table));
    table->blocks = pieces;

    return table;
};
