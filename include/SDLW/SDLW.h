/**
 * @file SDLW.h
 * @author Alex Macafee (lxmcf20@gmail.com)
 * @brief
 * @version 2.0.0
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SDLW_H
#define SDLW_H

#include "SDL2/SDL.h"

#define SDLW_TRUE 1
#define SDLW_FALSE 0

#define SDLW_VERSION_MAJOR 2
#define SDLW_VERSION_MINOR 0
#define SDLW_VERSION_REVISION 0

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
 *                      Window related functions
 *
 * All functions in this section should relate directly to window actions
 * and requests.
 *************************************************************************/

/**
 * @brief The object used to identify the window.
 *
 */
typedef struct SDLW_Window SDLW_Window;

/**
 * @brief Creates a new SDLW Window.
 *
 * @param[in] title The title for the window
 * @param[in] width The desired width of the window in screen coordinates
 * @param[in] height The desired height of the window in screen coordinates
 * @param[in] window_flags The SDL window flags to create the window with
 * @param[in] renderer_flags The SDL window flags to create the window with
 * @return SDLW_Window* - The new window object or NULL on failure; (Failure reasons will be logged automatically)
 */
SDLW_Window* SDLW_CreateWindow (char* title, int width, int height, Uint32 window_flags, Uint32 renderer_flags);

/**
 * @brief Checks whether a desired window should close.
 *
 * @param[in] window The window to check
 * @return int - 1 if true, 0 if false
 */
int SDLW_ShouldWindowClose (SDLW_Window* window);

/**
 * @brief Set whether the desired window should close or not.
 *
 * @param[in] window The desired window
 * @param[in] value The value (SDLW_TRUE or SDLW_FALSE)
 * @return int - returns 1 if value already set else returns 0
 */
int SDLW_SetWindowShouldClose (SDLW_Window* window, int value);

/**
 * @brief Poll the desired window for any relevent events.
 *
 * @param[in] window The window to check
 */
void SDLW_PollWindowEvents (SDLW_Window* window);

/**
 * @brief Update the window with any rendering calls since prior function call
 *
 * @param[in] window The window to present
 */
void SDLW_PresentWindow (SDLW_Window* window);

/**
 * @brief Destroys the given window and free's all related memory
 *
 * @param[in] window The window to destroy
 */
void SDLW_DestroyWindow (SDLW_Window* window);

/**
 * @brief Set whether the desired window should be bordered.
 *
 * @param[in] window The desired window
 * @param[in] bordered The value (SDLW_TRUE or SDLW_FALSE)
 */
void SDLW_SetWindowBordered (SDLW_Window* window, int bordered);

/**
 * @brief Get's whether the desired window is bordered.
 *
 * @param[in] window The desired window
 * @return int - 1 if true, 0 if false
 */
int SDLW_IsWindowBordered (SDLW_Window* window);

/**
 * @brief Set's the desired window's display mode
 *
 * @param[in] window The desired window
 * @param[in] mode
 * @return int - 0 on success or a negative error code; (Failure reasons will be logged automatically)
 */
int SDLW_SetWindowDisplayMode (SDLW_Window* window, const SDL_DisplayMode* mode);

/**
 * @brief Get's the desired window's display mode
 *
 * @param[in] window The desired window
 * @param[out] mode A pointer filled with the window display mode
 * @return int  - 0 on success or a negative error code; (Failure reasons will be logged automatically)
 */
int SDLW_GetWindowDisplayMode (SDL_Window* window, SDL_DisplayMode* mode);

/**
 * @brief Set's the desired window's fullscreen state
 *
 * @param[in] window The desired window
 * @param[in] fullscreen The value (SDLW_TRUE or SDLW_FALSE)
 * @return int - 0 on success or a negative error code; (Failure reasons will be logged automatically)
 */
int SDLW_SetWindowFullscreen (SDLW_Window* window, int fullscreen);

/**
 * @brief Set's the desired window's fake fullscreen state
 *
 * @param[in] window The desired window
 * @param[in] fullscreen The value (SDLW_TRUE or SDLW_FALSE)
 * @return int - 0 on success or a negative error code; (Failure reasons will be logged automatically)
 */
int SDLW_SetWindowFullscreenDesktop (SDLW_Window* window, int fullscreen);

/**
 * @brief Get's the desired window's fullscreen state
 *
 * @param[in] window The desired window
 * @return int - 1 if true, 0 if false
 */
int SDLW_IsWindowFullscreen (SDLW_Window* window);

/**
 * @brief Set a desired window's input grab mode. When input is grabbed, the mouse is confined to the window.
 *
 * @param[in] window The desired window
 * @param[in] grabbed The value (SDLW_TRUE or SDLW_FALSE)
 */
void SDLW_SetWindowgrab (SDLW_Window* window, int grabbed);

/**
 * @brief Get's a desired window's input grab mode.
 *
 * @param[in] window The desired window
 * @return int - 1 if true, 0 if false
 */
int SDLW_GetWindowgrab (SDLW_Window* window);

/**
 * @brief Set's the desired window's icon
 *
 * @param[in] window The desired window
 * @param[in] icon - The desired icon surface
 */
void SDLW_SetWindowIcon (SDLW_Window* window, SDL_Surface* icon);

/**
 * @brief Get's the desired window's icon
 *
 * @param[in] window The desired window
 * @return SDL_Surface* - The desired window icon surface
 */
SDL_Surface* SDLW_GetWindowIcon (SDLW_Window* window);

/**
 * @brief Set's the desired window's maximum size
 *
 * @param[in] window The desired window
 * @param[in] width The desired width in screen coordinates
 * @param[in] height The desired height in screen coordinates
 */
void SDLW_SetWindowMaximumSize (SDLW_Window* window, int width, int height);

/**
 * @brief Get's the desired windows maximum size
 *
 * @param[in] window The desired window
 * @param[out] width The desired window's width in screen coordinates
 * @param[out] height The desired window's height in screen coordinates
 */
void SDLW_GetWindowMaximumSize (SDLW_Window* window, int* width, int* height);

/**
 * @brief Set's the desired window's minimum size
 *
 * @param[in] window The desired window
 * @param[in] width The desired minimum width in screen coordinates
 * @param[in] height The desired minimum height in screen coordinates
 */
void SDLW_SetWindowMinimumSize (SDLW_Window* window, int width, int height);

/**
 * @brief Get's the desired window's maximum size
 *
 * @param[in] window The desired window
 * @param[out] width The desired window's minimum height in screen coordinates
 * @param[out] height The desired window's minimum height in screen coordinates
 */
void SDLW_GetWindowMinimumSize (SDLW_Window* window, int* width, int* height);

/**
 * @brief Set's the desired window's opacity
 *
 * @param[in] window The desired window
 * @param[in] opacity The desired opacity
 * @return int - 0 on success or a negative error code; (Failure reasons will be logged automatically)
 */
int SDLW_SetWindowOpacity (SDLW_Window* window, float opacity);

/**
 * @brief Get's the desired window's opacity
 *
 * @param[in] window The desired window
 * @param[out] opacity A float for opacity value
 * @return int  - 0 on success or a negative error code; (Failure reasons will be logged automatically)
 */
int SDLW_GetWindowOpacity (SDLW_Window* window, float* opacity);

/**
 * @brief Set's the desired window's position
 *
 * @param[in] window The desired window
 * @param[in] x The x coordinate of the window in screen coordinates
 * @param[in] y The y coordinate of the window in screen coordinates
 */
void SDLW_SetWindowPosition (SDLW_Window* window, int x, int y);

/**
 * @brief Get's the desired window's position
 *
 * @param[in] window The desired window
 * @param[out] x A pointer filled in with the x position of the window in screen coordinates
 * @param[out] y A pointer filled in with the y position of the window in screen coordinates
 */
void SDLW_GetWindowPosition (SDLW_Window* window, int* x, int* y);

/**
 * @brief Set's the desired window's size
 *
 * @param[in] window The desired window
 * @param[in] width
 * @param[in] height
 */
void SDLW_SetWindowSize (SDLW_Window* window, int width, int height);

/**
 * @brief Set's the desired window's size
 *
 * @param[in] window The desired window
 * @param[out] width A pointer filled in with the width of the window in screen coordinates
 * @param[out] height A pointer filled in with the height of the window in screen coordinates
 */
void SDLW_GetWindowSize (SDLW_Window* window, int* width, int* height);

/**
 * @brief Set's the desired window's title
 *
 * @param[in] window The desired window
 * @param[in] title The desired window title
 */
void SDLW_SetWindowTitle (SDLW_Window* window, const char* title);

/**
 * @brief Get's the desired window's title
 *
 * @param[in] window The desired window
 * @return const char* - The title of the desired window
 */
const char* SDLW_GetWindowTitle (SDLW_Window* window);

/**
 * @brief Set's whether the desired window can be resized or not
 *
 * @param[in] window The desired window
 * @param[in] resizable The value (SDLW_TRUE or SDLW_FALSE)
 */
void SDLW_SetWindowResizable (SDLW_Window* window, int resizable);

/**
 * @brief Get's whether the desired window can be resized or not
 *
 * @param[in] window The desired window
 * @return int - 1 if true, 0 if false (SDLW_TRUE or SDLW_FALSE)
 */
int SDLW_IsWindowResizable (SDLW_Window* window);

/**
 * @brief Returns the desired windows internal SDL window
 *
 * @param[in] window The desired window
 * @return SDL_Window* The internal SDL Window
 */
SDL_Window* SDLW_GetInternalWindow (SDLW_Window* window);

/*************************************************************************
 *                      Renderer related functions
 *
 * All functions in this section should relate directly to renderer actions
 * and requests.
 *************************************************************************/

int SDLW_RenderClear (SDLW_Window* window);
int SDLW_RenderClearColour (SDLW_Window* window, SDL_Colour colour);
int SDLW_RenderClearColor (SDLW_Window* window, SDL_Color color); // NOTE: Should make this a macro

int SDLW_RenderTexture (SDLW_Window* window, SDL_Texture* texture, int x, int y);
int SDLW_RenderTextureRect (SDLW_Window* window, SDL_Texture* texture, const SDL_Rect* source, const SDL_Rect* destination);
int SDLW_RenderTextureRectEx (SDLW_Window* window, SDL_Texture* texture, const SDL_Rect* source, const SDL_Rect* destination, const double angle, const SDL_Point* origin, const SDL_RendererFlip flip);

int SDLW_SetDrawBlendMode (SDLW_Window* window, SDL_BlendMode mode);
int SDLW_GetDrawBlendMode (SDLW_Window* window, SDL_BlendMode* mode);

int SDLW_SetDrawColour (SDLW_Window* window, SDL_Colour colour);
int SDLW_SetDrawColor (SDLW_Window* window, SDL_Color color); // NOTE: Should make this a macro

int SDLW_GetDrawColour (SDL_Window* window, SDL_Colour* colour);
int SDLW_GetDrawColor (SDL_Window* window, SDL_Color* color); // NOTE: Should make this a macro

int SDLW_SetRenderTarget (SDLW_Window* window, SDL_Texture* texture);
SDL_Texture* SDLW_GetRenderTarget (SDLW_Window* window);

int SDLW_SetRenderScale (SDLW_Window* window, float scale_x, float scale_y);
void SDLW_GetRenderScale (SDLW_Window* window, float* scale_x, float* scale_y);

int SDLW_SetRenderViewport (SDLW_Window* window, const SDL_Rect* view);
void SDLW_GetRenderViewport (SDLW_Window* window, SDL_Rect* view);

/**
 * @brief Returns the desired windows internal SDL renderer
 *
 * @param[in] window The desired window The desired window
 * @return SDL_Renderer*
 */
SDL_Renderer* SDLW_GetInternalRenderer (SDLW_Window* window);

/*************************************************************************
 *                      Callback type definition
 *************************************************************************/

typedef void (*SDLW_PositionFunction) (SDLW_Window* window, int x, int y);
typedef void (*SDLW_ResizeFunction) (SDLW_Window* window, int width, int height);
typedef void (*SDLW_CloseFunction) (SDLW_Window* window);
typedef void (*SDLW_FocusFunction) (SDLW_Window* window, int focused);
typedef void (*SDLW_MaximiseFunction) (SDLW_Window* window, int maximised);

typedef void (*SDLW_MouseButtonFunction) (SDLW_Window* window, int x, int y, int button, int action, int clicks);
typedef void (*SDLW_MouseCursorFunction) (SDLW_Window* window, int x, int y);
typedef void (*SDLW_MouseEnterFunction) (SDLW_Window* window, int entered);
typedef void (*SDLW_MouseScrollFunction) (SDLW_Window* window, int xscroll, int yscroll);
typedef void (*SDLW_KeyFunction) (SDLW_Window* window, int state, int repeat, SDL_Keycode key);

typedef void (*SDLW_UnknownFunction) (SDLW_Window* window, SDL_Event* event);

/*************************************************************************
 *                      Callback related functions
 *************************************************************************/

SDLW_PositionFunction SDLW_SetWindowPositionCallback (SDLW_Window* window, SDLW_PositionFunction callback);
SDLW_ResizeFunction SDLW_SetWindowResizeCallback (SDLW_Window* window, SDLW_ResizeFunction callback);
SDLW_CloseFunction SDLW_SetWindowCloseCallback (SDLW_Window* window, SDLW_CloseFunction callback);
SDLW_FocusFunction SDLW_SetWindowFocusCallback (SDLW_Window* window, SDLW_FocusFunction callback);
SDLW_MaximiseFunction SDLW_SetWindowMaximiseCallback (SDLW_Window* window, SDLW_MaximiseFunction callback);

SDLW_MouseButtonFunction SDLW_SetMouseButtonCallback (SDLW_Window* window, SDLW_MouseButtonFunction callback);
SDLW_MouseCursorFunction SDLW_SetMouseCursorCallback (SDLW_Window* window, SDLW_MouseCursorFunction callback);
SDLW_MouseEnterFunction SDLW_SetMouseEnterCallback (SDLW_Window* window, SDLW_MouseEnterFunction callback);

SDLW_MouseScrollFunction SDLW_SetMouseScrollCallback (SDLW_Window* window, SDLW_MouseScrollFunction callback);
SDLW_KeyFunction SDLW_SetKeyCallback (SDLW_Window* window, SDLW_KeyFunction callback);

SDLW_UnknownFunction SDLW_SetUnknownCallback (SDLW_Window* window, SDLW_UnknownFunction callback);

#ifdef __cplusplus
}
#endif

#endif // SDLW_H
