#include "table.h"
#include "error_type.h"
#include "piece.h"
#include "piece_type.h"
#include "coordinate.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

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
    table->LAST_COLOR = COLOR_NONE;
    table->blocks = pieces;

    return table;
};

bool is_empty_way(table* table, coordinate coord_way, coordinate coord_start, coordinate coord_final) {
    if(!((coord_way.x == 0 || (coord_start.x - coord_final.x) % coord_way.x == 0) && (coord_way.y == 0 || (coord_start.y - coord_final.y) % coord_way.y == 0))){
        exit(ERROR_INVALID_STEP);
    }

    coordinate coord_temp;
    coord_temp.x = coord_start.x;
    coord_temp.y = coord_start.y;
    bool is_arrived = false;
    while(!is_arrived) {
        coord_temp.x += coord_way.x;
        coord_temp.y += coord_way.y;
        if(coord_temp.x == coord_final.x && coord_temp.y == coord_final.y) {
            return true;
        }
        if(table->blocks[coord_temp.x][coord_temp.y].PIECE_TYPE != TYPE_NONE) {
            return false;
        }
    }

    return true;
}

bool is_valid_move(table* table, coordinate coord_start, coordinate coord_final) {
    if(coord_start.x < 0 || coord_start.x > 7 || coord_start.y < 0 || coord_start.y > 7 || coord_final.x < 0 || coord_final.x > 7 || coord_final.y < 0 || coord_final.y > 7) {
        exit(ERROR_OUT_OF_TABLE);
    }

    if(coord_start.x == coord_final.x && coord_start.y == coord_final.y){
        return false;
    }

    coordinate coord_way;
    int delta_x = coord_final.x - coord_start.x;
    coord_way.x = delta_x == 0 ? 0 : 1;
    int delta_y = coord_final.y - coord_start.y;
    coord_way.y = delta_y == 0 ? 0 : 1;
    if(!is_empty_way(table, coord_way, coord_start, coord_final)) {
        return false;
    }   
    switch(table->blocks[coord_start.x][coord_start.y].PIECE_TYPE) {
	    case KING:
            // TODO check if wont be in hit
            return((abs(coord_start.x-coord_final.x) == 0 || abs(coord_start.x-coord_final.x) == 0) && (abs(coord_start.y-coord_final.y) == 0 || abs(coord_start.y-coord_final.y) == 1));
        case QUEEN:
            return abs(coord_start.x-coord_final.x) == abs(coord_start.y-coord_final.y) || abs(coord_start.x-coord_final.x) == 0 || abs(coord_start.y-coord_final.y) == 0;
        case ROOK:
            return abs(coord_start.x-coord_final.x) == 0 || abs(coord_start.y-coord_final.y) == 0;
        case BISHOP:
             return abs(coord_start.x-coord_final.x) == abs(coord_start.y-coord_final.y); 
            break;
        case KNIGHT:
            return (abs(coord_start.x-coord_final.x) == 2 && abs(coord_start.y-coord_final.y) == 1) || (abs(coord_start.x-coord_final.x) == 1 && abs(coord_start.y-coord_final.y) == 2);
        case PAWN:
            return (abs(coord_start.x-coord_final.x) == 1 && abs(coord_start.y-coord_final.y) == 0 && table->blocks[coord_final.x][coord_final.y].PIECE_TYPE == TYPE_NONE) || (abs(coord_start.x-coord_final.x) == abs(coord_start.y-coord_final.y) == 1 && table->blocks[coord_final.x][coord_final.y].PIECE_TYPE != TYPE_NONE);            
        case TYPE_NONE:
            exit(ERROR_INVALID_PIECE_TYPE);
            break;
    }

    return false;
}

table* move(table* table, coordinate coord_start, coordinate coord_final) {
    piece current_piece = table->blocks[coord_start.x][coord_start.y];

    if(current_piece.COLOR == COLOR_NONE) {
        exit(ERROR_INVALID_STEP);
    } 


    if(is_valid_move(table, coord_start, coord_final)) {
        table->blocks[coord_final.x][coord_start.y] = table->blocks[coord_start.x][coord_start.y];
        table->blocks[coord_start.x][coord_start.y].COLOR = COLOR_NONE;
        table->blocks[coord_start.x][coord_start.y].PIECE_TYPE = TYPE_NONE;
    }

    return table;
}


