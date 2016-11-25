#include "table.h"
#include "error_type.h"
#include "piece.h"
#include "piece_type.h"
#include <stdlib.h>
#include <stdbool.h>

table* init_table() {
    int i, j;
  
    piece** pieces = (piece**) malloc(8 * sizeof(piece*));
    for(i = 0; i < 8; i++) {
        pieces[i] = (piece*)malloc(8 * sizeof(piece));
    }


    for(i = 0; i < 8; ++i) {
        for(j = 0; j < 8; ++j) {
            
            if(i == 1) {
                // black pawn line
                pieces[i][j].COLOR = COLOR_BLACK;
                pieces[i][j].PIECE_TYPE = PAWN;
            } else if(i == 0 || i == 7) {
                pieces[i][j].COLOR = i == 0 ? COLOR_BLACK : COLOR_WHITE;
                switch(j) {
                    case 0:
                    case 7:
                        pieces[i][j].PIECE_TYPE = ROOK;
                        break;
                    case 1:
                    case 6:
                        pieces[i][j].PIECE_TYPE = KNIGHT;
                        break;
                    case 2:
                    case 5: 
                        pieces[i][j].PIECE_TYPE = BISHOP;
                        break;
                    case 3:
                        pieces[i][j].PIECE_TYPE = QUEEN;
                        break;
                    case 4:
                        pieces[i][j].PIECE_TYPE = KING;
                        break;
                }
            } else if(i == 6) {
                // white pawn line
                pieces[i][j].COLOR = COLOR_WHITE;
                pieces[i][j].PIECE_TYPE = PAWN;
            } else {
                pieces[i][j].COLOR = COLOR_NONE;
                pieces[i][j].PIECE_TYPE = TYPE_NONE;
            }
        }
    }
    

    table* table = malloc(sizeof(table));
    table->blocks = pieces;

    return table;
};

bool is_valid_move(table* table, int x1, int y1, int x2, int y2) {
    return true;
}

table* move(table* table, int x1, int y1, int x2, int y2) {
    piece current_piece = table->blocks[x1][y1];

    if(current_piece.COLOR == COLOR_NONE) {
        exit(ERROR_INVALID_STEP);
    } 


    if(is_valid_move(table, x1, y1, x2, y2)) {
        table->blocks[x2][y1] = table->blocks[x1][y1];
        table->blocks[x1][y1].COLOR = COLOR_NONE;
        table->blocks[x1][y1].PIECE_TYPE = TYPE_NONE;
    }

    return table;
}
