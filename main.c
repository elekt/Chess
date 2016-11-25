
#include "table.h"
#include "piece.h"
#include "color.h"
#include <stdio.h>

int main(int argc, char** argv) {
    table* table = init_table();

    int i, j;
    for(i = 0; i < 8; ++i) { 
        for(j = 0; j < 8; ++j) {
            if(table->blocks[i][j].COLOR == COLOR_NONE){
                printf("x ");
            } else {
                printf("%d ", table->blocks[i][j].PIECE_TYPE);
            }
        }
        printf("\n");
    }

    printf("exit");
    return 0;
}
