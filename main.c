#include "table.h"
#include "piece.h"
#include "color.h"
#include <stdio.h>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_image.h>
#include <math.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    SDL_Event event;
    SDL_Surface *screen;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen=SDL_SetVideoMode(800, 800, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("SDL peldaprogram", "SDL peldaprogram");


    table* table = init_table();
    bool is_quit = false;
    while (!is_quit) {
    int i, j;
    for(i = 0; i < 8; ++i) {
        for(j = 0; j < 8; ++j) {
            if (((i % 2 == 0) && (j % 2 == 0)) || ((i % 2 == 1) && (j % 2 == 1))){
                boxRGBA(screen, i*100, j*100, (i+1)*100, (j+1)*100, 240, 217, 181, 255);
            } else {
                boxRGBA(screen, i*100, j*100, (i+1)*100, (j+1)*100, 181, 136, 99, 255);
            }
        }
    }
    SDL_Surface *image = IMG_Load("Chess_Pieces_Sprite.png");
    for(i = 0; i < 8; ++i) {
        for(j = 0; j < 8; ++j) {

            if(i == 1) {
                // black pawn line
                table->blocks[i][j].COLOR = COLOR_BLACK;
                table->blocks[i][j].PIECE_TYPE = PAWN;
                SDL_Rect source = {j*100, i*100, (j+1)*100, (i+1)*100};
                SDL_Rect destination = {600*5/6, 100, 100, 100};
                SDL_BlitSurface (image, &destination, screen, &source);
            } else if(i == 0 || i == 7) {
                table->blocks[i][j].COLOR = i == 0 ? COLOR_BLACK : COLOR_WHITE;
                SDL_Rect source = {j*100, i*100, (j+1)*100, (i+1)*100};
                SDL_Rect destination = {600*4/6, 100, 100, 100};
                switch(j) {
                    case 0:
                    case 7:
                        table->blocks[i][j].PIECE_TYPE = ROOK;
                        if (table->blocks[i][j].COLOR == COLOR_BLACK){
                            SDL_BlitSurface (image, &destination, screen, &source);
                        } else {
                            destination.y = 0;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        }
                        break;
                    case 1:
                    case 6:
                        table->blocks[i][j].PIECE_TYPE = KNIGHT;
                        if (table->blocks[i][j].COLOR == COLOR_BLACK){
                            destination.x = 300;
                            destination.y = 100;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        } else {
                            destination.y = 0;
                            destination.x = 300;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        }
                        break;
                    case 2:
                    case 5:
                        table->blocks[i][j].PIECE_TYPE = BISHOP;
                        if (table->blocks[i][j].COLOR == COLOR_BLACK){
                            destination.x = 200;
                            destination.y = 100;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        } else {
                            destination.x = 200;
                            destination.y = 0;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        }
                        break;
                    case 3:
                        table->blocks[i][j].PIECE_TYPE = QUEEN;
                        if (table->blocks[i][j].COLOR == COLOR_BLACK){
                            destination.x = 100;
                            destination.y = 100;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        } else {
                            destination.x = 100;
                            destination.y = 0;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        }
                        break;
                    case 4:
                        table->blocks[i][j].PIECE_TYPE = KING;
                        if (table->blocks[i][j].COLOR == COLOR_BLACK){
                            destination.x = 0;
                            destination.y = 100;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        } else {
                            destination.x = 0;
                            destination.y = 0;
                            SDL_BlitSurface (image, &destination, screen, &source);
                        }
                        break;
                }
            } else if(i == 6) {
                // white pawn line
                table->blocks[i][j].COLOR = COLOR_WHITE;
                table->blocks[i][j].PIECE_TYPE = PAWN;
                SDL_Rect source = {j*100, i*100, (j+1)*100, (i+1)*100};
                SDL_Rect destination = {600*5/6, 0, 100, 100};
                SDL_BlitSurface (image, &destination, screen, &source);
                } else {
                table->blocks[i][j].COLOR = COLOR_NONE;
                table->blocks[i][j].PIECE_TYPE = TYPE_NONE;
            }
        }
    }
        /* varunk a kilepesre */
            SDL_WaitEvent(&event);
            printf("%d %d\n", event.button.x, event.button.y);
            switch (event.type){
                case SDL_QUIT:
                    is_quit = true;
                    break;
                case SDL_USEREVENT:
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        for (i=0; i<8; i++){
                            for (j=0; j<8; j++){
                                if ((event.button.x % 100 == j) && (event.button.y % 100 == i)){
                                    boxRGBA(screen, i*100, j*100, (i+1)*100, (j+1)*100, 101, 111, 62, 255);

                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
        }
    SDL_Flip(screen);
    }
    /* ablak bezarasa */
    SDL_Quit();
    return 0;
}
