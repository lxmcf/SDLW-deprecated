#include "SDLW/SDLW.h"

void close_callback (SDLW_Window* window);

int main (int argc, const char* argv[]) {
    SDLW_Window* window = SDLW_CreateWindow ("Hello SDLW!", 640, 360, 0, SDL_RENDERER_ACCELERATED);

    SDLW_SetWindowResizable (window, SDLW_TRUE);

    while (!SDLW_ShouldWindowClose (window)) {
        SDLW_PollWindowEvents (window);

        SDLW_PresentWindow (window);
    }

    SDLW_DestroyWindow (window);

    SDL_Quit ();

    return 0;
}
