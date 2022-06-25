#include "SDLW_Window.h"

SDLW_Window* SDLW_CreateWindow (char* title, int width, int height, Uint32 window_flags, Uint32 renderer_flags) {
    // NOTE: Consider creating dedicated memory pool and create global object to handle further expansion
    _SDLW_Window* handle = malloc (sizeof (_SDLW_Window));

    // Automatically initialise required SDL subsystems
    if (!SDL_WasInit (SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_Init (SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    }

    handle->window = SDL_CreateWindow (title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
    if (handle->window == NULL) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());

        return NULL;
    } // handle->window

    handle->renderer = SDL_CreateRenderer (handle->window, -1, renderer_flags);
    if (handle->renderer == NULL) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());

        return NULL;
    } // handle->renderer

    handle->should_close = SDLW_FALSE;
    handle->fullscreen = SDLW_FALSE;
    handle->icon = NULL;

    int value = SDL_SetRenderDrawColor (handle->renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
    if (value) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());

        SDL_DestroyRenderer (handle->renderer);
        SDL_DestroyWindow (handle->window);

        return NULL;
    }

    return (SDLW_Window*)handle;
}

int SDLW_ShouldWindowClose (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->should_close;
}

int SDLW_SetWindowShouldClose (SDLW_Window* window, int value) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    if (handle->should_close == value)
        return 1;

    handle->should_close = value;

    return 0;
}

void SDLW_PollWindowEvents (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_RenderClear (handle->renderer);

    // Main SDL Events
    while (SDL_PollEvent (&handle->event)) {
        switch (handle->event.type) {
            case SDL_QUIT:
                _SDLW_CloseCallback (handle);
            break; // SDL_QUIT

            case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
                _SDLW_MouseButtonCallback(handle, handle->event.button.x, handle->event.button.y, handle->event.button.button, handle->event.button.state, handle->event.button.clicks);
            break; // SDL_MOUSEBUTTONDOWN && SDL_MOUSEBUTTONUP

            case SDL_MOUSEMOTION:
                _SDLW_MouseCursorCallback (handle, handle->event.motion.x, handle->event.motion.x);
            break; // SDL_MOUSEMOTION

            case SDL_MOUSEWHEEL:
                _SDLW_MouseScrollCallback (handle, handle->event.wheel.x, handle->event.wheel.y);
            break; // SDL_MOUSEWHEEL

            case SDL_KEYDOWN: case SDL_KEYUP:
                _SDLW_KeyCallback (handle, handle->event.key.state, handle->event.key.repeat, handle->event.key.keysym);
            break; // SDL_KEYDOWN && SDL_KEYUP

            case SDL_WINDOWEVENT:
                switch (handle->event.window.event) {
                    case SDL_WINDOWEVENT_MOVED:
                        _SDLW_PositionCallback (handle, handle->event.window.data1, handle->event.window.data2);
                    break; // SDL_WINDOWEVENT_MOVED

                    case SDL_WINDOWEVENT_RESIZED:
                        _SDLW_ResizeCallback (handle, handle->event.window.data1, handle->event.window.data2);
                    break; // SDL_WINDOWEVENT_RESIZED

                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        _SDLW_FocusCallback (handle, SDLW_TRUE);
                    break; // SDL_WINDOWEVENT_FOCUS_GAINED

                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        _SDLW_FocusCallback (handle, SDLW_FALSE);
                    break; // SDL_WINDOWEVENT_FOCUS_LOST

                    case SDL_WINDOWEVENT_MAXIMIZED:
                        _SDLW_MaximiseCallback (handle, SDLW_TRUE);
                    break; // SDL_WINDOWEVENT_MAXIMIZED

                    case SDL_WINDOWEVENT_MINIMIZED:
                        _SDLW_MaximiseCallback (handle, SDLW_FALSE);
                    break; // SDL_WINDOWEVENT_MINIMIZED

                    case SDL_WINDOWEVENT_ENTER:
                        _SDLW_MouseEnterCallback (handle, SDLW_TRUE);
                    break; // SDL_WINDOWEVENT_ENTER

                    case SDL_WINDOWEVENT_LEAVE:
                        _SDLW_MouseEnterCallback (handle, SDLW_FALSE);
                    break; // SDL_WINDOWEVENT_LEAVE
                }
            break; // SDL_WINDOWEVENT
        }
    }
}

void SDLW_PresentWindow (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_RenderPresent (handle->renderer);
}

void SDLW_DestroyWindow (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_DestroyRenderer (handle->renderer);
    SDL_DestroyWindow (handle->window);

    free (handle);
}

/*************************************************************************
 *                      Get/Set related functions
 *************************************************************************/
void SDLW_SetWindowBordered (SDLW_Window* window, int bordered) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    handle->bordered = bordered;

    SDL_SetWindowBordered (handle->window, bordered);
}

int SDLW_IsWindowBordered (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->bordered;
}

int SDLW_SetWindowDisplayMode (SDLW_Window* window, const SDL_DisplayMode* mode) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int value = SDL_SetWindowDisplayMode (handle->window, mode);

    if (value) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());
    }

    return value;
}

int SDLW_GetWindowDisplayMode (SDL_Window* window, SDL_DisplayMode* mode) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int value = SDL_GetWindowDisplayMode (handle->window, mode);
    if (value) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());
    }

    return value;
}

int SDLW_SetWindowFullscreen (SDLW_Window* window, int fullscreen) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    Uint32 mode;

    if (fullscreen) {
        mode = SDL_WINDOW_FULLSCREEN;
    } else {
        mode = 0;
    }

    int value = SDL_SetWindowFullscreen (handle->window, mode);

    if (value) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());
    } else {
        handle->fullscreen = fullscreen;
    }

    return value;
}

int SDLW_SetWindowFullscreenDesktop (SDLW_Window* window, int fullscreen) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    Uint32 mode;

    if (fullscreen) {
        mode = SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else {
        mode = 0;
    }

    int value = SDL_SetWindowFullscreen (handle->window, mode);

    if (value) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());
    } else {
        handle->fullscreen = fullscreen;
    }

    return value;
}

int SDLW_IsWindowFullscreen (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->fullscreen;
}

void SDLW_SetWindowgrab (SDLW_Window* window, int grabbed) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_SetWindowGrab (handle->window, grabbed);
}

int SDLW_GetWindowgrab (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return SDL_GetWindowGrab (handle->window);
}

void SDLW_SetWindowIcon (SDLW_Window* window, SDL_Surface* icon) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    handle->icon = icon;

    // NOTE: Consider auto clearing icon pointer
    SDL_SetWindowIcon (handle->window, icon);
}

SDL_Surface* SDLW_GetWindowIcon (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->icon;
}

void SDLW_SetWindowMaximumSize (SDLW_Window* window, int width, int height) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_SetWindowMaximumSize (handle->window, width, height);
}

void SDLW_GetWindowMaximumSize (SDLW_Window* window, int* width, int* height) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_GetWindowMaximumSize (handle->window, width, height);
}

void SDLW_SetWindowMinimumSize (SDLW_Window* window, int width, int height) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_SetWindowMinimumSize (handle->window, width, height);
}

void SDLW_GetWindowMinimumSize (SDLW_Window* window, int* width, int* height) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_GetWindowMinimumSize (handle->window, width, height);
}

int SDLW_SetWindowOpacity (SDLW_Window* window, float opacity) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int value = SDL_SetWindowOpacity (handle->window, opacity);
    if (value) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());
    }

    return value;
}

int SDLW_GetWindowOpacity (SDLW_Window* window, float* opacity) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int value = SDL_GetWindowOpacity (handle->window, opacity);
    if (value) {
        SDL_Log ("SDLW Error: %s\n", SDL_GetError ());
    }

    return value;
}

void SDLW_SetWindowPosition (SDLW_Window* window, int x, int y) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_SetWindowPosition (handle->window, x, y);
}

void SDLW_GetWindowPosition (SDLW_Window* window, int* x, int* y) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_GetWindowPosition (handle->window, x, y);
}

void SDLW_SetWindowSize (SDLW_Window* window, int width, int height) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_SetWindowSize (handle->window, width, height);
}

void SDLW_GetWindowSize (SDLW_Window* window, int* width, int* height) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    // TODO: Work out a simple implimentation of `SDL_WINDOW_ALLOW_HIGHDPI` sizing
    SDL_GetWindowSize (handle->window, width, height);
}

void SDLW_SetWindowTitle (SDLW_Window* window, const char* title) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_SetWindowTitle (handle->window, title);
}

const char* SDLW_GetWindowTitle (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return SDL_GetWindowTitle(handle->window);
}

void SDLW_SetWindowResizable (SDLW_Window* window, int resizable) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    handle->resizable = resizable;

    SDL_SetWindowResizable (handle->window, resizable);
}

int SDLW_IsWindowResizable (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->resizable;
}

SDL_Window* SDLW_GetInternalWindow (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->window;
}

SDL_Renderer* SDLW_GetInternalRenderer (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->renderer;
}

/*************************************************************************
 *                      Callback related functions
 *************************************************************************/
SDLW_PositionFunction SDLW_SetWindowPositionCallback (SDLW_Window* window, SDLW_PositionFunction callback){
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.position = callback;
}

SDLW_ResizeFunction SDLW_SetWindowResizeCallback (SDLW_Window* window, SDLW_ResizeFunction callback){
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.resize = callback;
}

SDLW_CloseFunction SDLW_SetWindowCloseCallback (SDLW_Window* window, SDLW_CloseFunction callback){
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.close = callback;
}

SDLW_FocusFunction SDLW_SetWindowFocusCallback (SDLW_Window* window, SDLW_FocusFunction callback){
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.focus = callback;
}

SDLW_MaximiseFunction SDLW_SetWindowMaximiseCallback (SDLW_Window* window, SDLW_MaximiseFunction callback){
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.maximise = callback;
}

SDLW_MouseButtonFunction SDLW_SetMouseButtonCallback (SDLW_Window* window, SDLW_MouseButtonFunction callback) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.mouse_button = callback;
}

SDLW_MouseCursorFunction SDLW_SetMouseCursorCallback (SDLW_Window* window, SDLW_MouseCursorFunction callback) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.cursor = callback;
}

SDLW_MouseEnterFunction SDLW_SetMouseEnterCallback (SDLW_Window* window, SDLW_MouseEnterFunction callback) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.mouse_enter = callback;
}

SDLW_MouseScrollFunction SDLW_SetMouseScrollCallback (SDLW_Window* window, SDLW_MouseScrollFunction callback) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.mouse_scroll = callback;
}

SDLW_KeyFunction SDLW_SetKeyCallback (SDLW_Window* window, SDLW_KeyFunction callback) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return handle->callbacks.key = callback;
}


/*************************************************************************
 *                  Internal callback related functions
 *************************************************************************/
void _SDLW_PositionCallback (_SDLW_Window* window, int x, int y) {
    if (window->callbacks.position) {
        window->callbacks.position ((SDLW_Window*)window, x, y);
    }
} // SDL_WINDOWEVENT_MOVED

void _SDLW_ResizeCallback (_SDLW_Window* window, int width, int height) {
    if (window->callbacks.resize) {
        window->callbacks.resize ((SDLW_Window*)window, width, height);
    }
} // SDL_WINDOWEVENT_RESIZED

void _SDLW_CloseCallback (_SDLW_Window* window) {
    window->should_close = SDLW_TRUE;

    if (window->callbacks.close) {
        window->callbacks.close ((SDLW_Window*)window);
    }
} // SDL_QUIT

void _SDLW_FocusCallback (_SDLW_Window* window, int focused) {
    if (window->callbacks.focus) {
        window->callbacks.focus ((SDLW_Window*)window, focused);
    }
} // SDL_WINDOWEVENT_FOCUS_GAINED && SDL_WINDOWEVENT_FOCUS_LOST

void _SDLW_MaximiseCallback (_SDLW_Window* window, int maximised) {
    if (window->callbacks.maximise) {
        window->callbacks.maximise ((SDLW_Window*)window, maximised);
    }
} // SDL_WINDOWEVENT_MAXIMIZED && SDL_WINDOWEVENT_MINIMIZED

void _SDLW_MouseButtonCallback (_SDLW_Window* window, int x, int y, int button, int action, int clicks) {
    if (window->callbacks.mouse_button) {
        window->callbacks.mouse_button ((SDLW_Window*)window, x, y, button, action, clicks);
    }
} // SDL_MOUSEBUTTONDOWN && SDL_MOUSEBUTTONUP

void _SDLW_MouseCursorCallback (_SDLW_Window* window, int x, int y) {
    if (window->callbacks.cursor) {
        window->callbacks.cursor ((SDLW_Window*)window, x, y);
    }
} // SDL_MOUSEMOTION

void _SDLW_MouseEnterCallback (_SDLW_Window* window, int entered) {
    if (window->callbacks.mouse_enter) {
        window->callbacks.mouse_enter ((SDLW_Window*)window, entered);
    }
} // SDL_WINDOWEVENT_ENTER && SDL_WINDOWEVENT_LEAVE

void _SDLW_MouseScrollCallback (_SDLW_Window* window, int xscroll, int yscroll) {
    if (window->callbacks.mouse_scroll) {
        window->callbacks.mouse_scroll ((SDLW_Window*)window, xscroll, yscroll);
    }
} // SDL_MOUSEWHEEL

void _SDLW_KeyCallback (_SDLW_Window* window, int state, int repeat, SDL_Keysym key) {
    if (window->callbacks.key) {
        window->callbacks.key ((SDLW_Window*)window, state, repeat, key);
    }
} // SDL_KEYDOWN && SDL_KEYUP
