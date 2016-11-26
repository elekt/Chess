#include "table.h"
#include "piece.h"
#include "color.h"
#include <stdio.h>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>

int main(int argc, char *argv[]) {
    SDL_Event ev;
    SDL_Surface *screen;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen=SDL_SetVideoMode(800, 800, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("SDL peldaprogram", "SDL peldaprogram");


    table* table = init_table();

    int i, j;
    for(i = 0; i < 8; ++i) {
        for(j = 0; j < 8; ++j) {
            if (((i % 2 == 0) && (j % 2 == 0)) || ((i % 2 == 1) && (j % 2 == 1))){
                boxRGBA(screen, i*100, j*100, (i+1)*100, (j+1)*100, 240, 217, 181, 255);
            } else {
                boxRGBA(screen, i*100, j*100, (i+1)*100, (j+1)*100, 181, 136, 99, 255);
            }
    }
        /* eddig elvegzett rajzolasok a kepernyore */

    }
    SDL_Flip(screen);
    /* varunk a kilepesre */
    while (SDL_WaitEvent(&ev) && ev.type!=SDL_QUIT) {
    }


    /* ablak bezarasa */
    SDL_Quit();
    return 0;
}


