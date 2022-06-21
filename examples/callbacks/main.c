#include "SDLW/SDLW.h"

void position_callback (SDLW_Window* window, int x, int y);
void key_callback (SDLW_Window* window, int state, int repeat, SDL_Keysym key);
void mouse_callback (SDLW_Window* window, int x, int y, int button, int action, int clicks);

int main (int argc, const char* argv[]) {
    SDLW_Window* window = SDLW_CreateWindow ("Hello SDLW!", 640, 360, 0, SDL_RENDERER_ACCELERATED);

    SDLW_SetWindowResizable (window, SDLW_TRUE);

    SDLW_SetWindowPositionCallback (window, position_callback);
    SDLW_SetKeyCallback (window, key_callback);
    SDLW_SetMouseButtonCallback (window, mouse_callback);

    while (!SDLW_ShouldWindowClose (window)) {
        SDLW_PollWindowEvents (window);

        SDLW_PresentWindow (window);
    }

    SDLW_DestroyWindow (window);

    SDL_Quit ();

    return 0;
}

void position_callback (SDLW_Window* window, int x, int y) {
    printf ("Window position: %d, %d\n", x, y);
}

void key_callback (SDLW_Window* window, int state, int repeat, SDL_Keysym key) {
    if (state == SDL_PRESSED && !repeat) {
        printf ("Key pressed: %s\n", SDL_GetKeyName (key.sym));
    }
}

void mouse_callback (SDLW_Window* window, int x, int y, int button, int action, int clicks) {
    if (action == SDL_PRESSED) {
        char* buttons[6] = {
            "UNKNOWN",
            "Left",
            "Middle",
            "Right",
            "Extra 1",
            "Extra 2"
        };

        if (button < 6) {
            printf ("Mouse button pressed: %s\n", buttons[button]);
        }
    }
}
