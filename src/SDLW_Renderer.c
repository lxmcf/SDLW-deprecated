#include "SDLW_Renderer.h"
#include "SDLW_Window.h"

int SDLW_RenderClear (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return SDL_RenderClear (handle->renderer);
}

int SDLW_RenderClearColour (SDLW_Window* window, SDL_Colour colour) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    Uint8 red, green, blue, alpha;

    SDL_GetRenderDrawColor (handle->renderer, &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor (handle->renderer, colour.r, colour.g, colour.b, colour.a);

    int result = SDL_RenderClear (handle->renderer);

    SDL_SetRenderDrawColor (handle->renderer, red, green, blue, alpha);

    return result;
}

int SDLW_RenderClearColor (SDLW_Window* window, SDL_Color color) {
    return SDLW_RenderClearColour (window, color);
}

int SDLW_RenderTexture (SDLW_Window* window, SDL_Texture* texture, int x, int y) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int width, height;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    SDL_Rect rect = {
        x, y,
        width, height
    };

    return SDL_RenderCopy (handle->renderer, texture, NULL, &rect);
}

int SDLW_RenderTextureRect (SDLW_Window* window, SDL_Texture* texture, const SDL_Rect* source, const SDL_Rect* destination) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return SDL_RenderCopy (handle->renderer, texture, source, destination);
}

int SDLW_RenderTextureRectEx (SDLW_Window* window, SDL_Texture* texture, const SDL_Rect* source, const SDL_Rect* destination, const double angle, const SDL_Point* origin, const SDL_RendererFlip flip) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return SDL_RenderCopyEx(handle->renderer, texture, source, destination, angle, origin, flip);
}

/*************************************************************************
 *                      Get/Set related functions
 *************************************************************************/

int SDLW_SetDrawBlendMode (SDLW_Window* window, SDL_BlendMode mode) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return SDL_SetRenderDrawBlendMode(handle->renderer, mode);
}

int SDLW_GetDrawBlendMode (SDLW_Window* window, SDL_BlendMode* mode) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int result = SDL_GetRenderDrawBlendMode (handle->renderer, mode);

    return result;
}

int SDLW_SetDrawColour (SDLW_Window* window, SDL_Colour colour) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int result = SDL_SetRenderDrawColor (handle->renderer, colour.r, colour.g, colour.b, colour.a);

    return result;
}

int SDLW_SetDrawColor (SDLW_Window* window, SDL_Color color) {
    return SDLW_SetDrawColour (window, color);
}

int SDLW_GetDrawColour (SDL_Window* window, SDL_Colour* colour) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int result = SDL_GetRenderDrawColor (handle->renderer, &colour->r, &colour->g, &colour->b, &colour->a);

    return result;
}

int SDLW_GetDrawColor (SDL_Window* window, SDL_Color* color) {
    return SDLW_GetDrawColour(window, color);
}

int SDLW_SetRenderTarget (SDLW_Window* window, SDL_Texture* texture) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int value = SDL_SetRenderTarget (handle->renderer, texture);

    return value;
}

SDL_Texture* SDLW_GetRenderTarget (SDLW_Window* window) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    return SDL_GetRenderTarget (handle->renderer);
}

int SDLW_SetRenderScale (SDLW_Window* window, float scale_x, float scale_y) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int value = SDL_RenderSetScale (handle->renderer, scale_x, scale_y);

    return value;
}

void SDLW_GetRenderScale (SDLW_Window* window, float* scale_x, float* scale_y) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_RenderGetScale (handle->renderer, scale_x, scale_y);
}

int SDLW_SetRenderViewport (SDLW_Window* window, const SDL_Rect* view) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    int value = SDL_RenderSetViewport (handle->renderer, view);

    return value;
}

void SDLW_GetRenderViewport (SDLW_Window* window, SDL_Rect* view) {
    _SDLW_Window* handle = (_SDLW_Window*)window;

    SDL_RenderGetViewport (handle->renderer, view);
}

/*************************************************************************
 *                          Internal functions
 *************************************************************************/

// TODO: Add internal draw colour function
// TODO: Add internal draw blend function
