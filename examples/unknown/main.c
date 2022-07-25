#include "SDLW/SDLW.h"

void unknown_callback (SDLW_Window* window, SDL_Event* event);

int main (int argc, const char* argv[]) {
    SDLW_Window* window = SDLW_CreateWindow ("Hello SDLW!", 640, 360, 0, SDL_RENDERER_ACCELERATED);

    SDLW_SetWindowResizable (window, SDLW_TRUE);

    SDLW_SetUnknownCallback (window, unknown_callback);

    while (!SDLW_ShouldWindowClose (window)) {
        SDLW_PollWindowEvents (window);

        SDLW_PresentWindow (window);
    }

    SDLW_DestroyWindow (window);

    SDL_Quit ();

    return 0;
}

void unknown_callback (SDLW_Window* window, SDL_Event* event) {
    printf ("An unhandled event has occured!\n");
}
