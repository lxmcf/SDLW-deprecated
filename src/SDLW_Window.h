#ifndef SDLW_WINDOW_H
#define SDLW_WINDOW_H

#include "SDL2/SDL.h"

// Import user facing functions
#include "SDLW/SDLW.h"

typedef struct _SDLW_Window {
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Event event;

    SDL_Surface* icon;

    int should_close;

    int bordered;
    int fullscreen;
    int resizable;

    struct {
        SDLW_PositionFunction position;
        SDLW_ResizeFunction resize;
        SDLW_CloseFunction close;
        SDLW_FocusFunction focus;
        SDLW_MaximiseFunction maximise;

        SDLW_MouseButtonFunction mouse_button;
        SDLW_MouseScrollFunction mouse_scroll;
        SDLW_MouseEnterFunction mouse_enter;
        SDLW_MouseCursorFunction cursor;
        SDLW_KeyFunction key;

        SDLW_UnknownFunction unkown;
    } callbacks;
} _SDLW_Window;

/*************************************************************************
 *                      Private/Internal API
 *************************************************************************/
void _SDLW_PositionCallback (_SDLW_Window* window, int x, int y);
void _SDLW_ResizeCallback (_SDLW_Window* window, int width, int height);
void _SDLW_CloseCallback (_SDLW_Window* window);
void _SDLW_FocusCallback (_SDLW_Window* cs, int focused);
void _SDLW_MaximiseCallback (_SDLW_Window* cs, int maximised);

void _SDLW_MouseButtonCallback (_SDLW_Window* window, int x, int y, int button, int action, int clicks);
void _SDLW_MouseCursorCallback (_SDLW_Window* window, int x, int y);
void _SDLW_MouseEnterCallback (_SDLW_Window* window, int entered);
void _SDLW_MouseScrollCallback (_SDLW_Window* window, int xscroll, int yscroll);
void _SDLW_KeyCallback (_SDLW_Window* window, int state, int repeat, SDL_Keycode key);

void _SDLW_UnknownCallback (_SDLW_Window* window, SDL_Event* event);

#endif // SDLW_WINDOW_H
