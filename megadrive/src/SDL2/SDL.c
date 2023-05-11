#include "SDL.h"

int SDL_Init(Uint32 flags)
{
    return 0;
}

Uint32 SDL_GetTicks(void)
{
    return 0;
}

void SDL_Quit(void)
{
}

int SDL_PollEvent(SDL_Event *event)
{
    return 0;
}

char *SDL_GetError(void)
{
    return NULL;
}

SDL_Window *SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flag)
{
    return NULL;
}

int SDL_InitSubSystem(Uint32 flags)
{
    return 0;
}

void SDL_SetWindowResizable(SDL_Window *window, SDL_bool resizable)
{
    return;
}

void SDL_AddEventWatch(SDL_EventFilter filter, void *userdata)
{
    return;
}

SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags)
{
    return NULL;
}

SDL_Texture *SDL_CreateTexture(SDL_Renderer *renderer, Uint32 format, int access, int w, int h)
{
    return NULL;
}

int SDL_UpdateTexture(SDL_Texture *texture, const SDL_Rect *rect, const void *pixels, int pitch)
{
    return 0;
}

SDL_Surface *SDL_CreateRGBSurfaceWithFormat(Uint32 flags, int width, int height, int depth, Uint32 format)
{
    return NULL;
}

SDL_Surface *SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask,
                                  Uint32 Bmask, Uint32 Amask)
{
    return NULL;
}

int SDL_BlitSurface(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect)
{
    return 0;
}

int SDL_GetRendererOutputSize(SDL_Renderer *renderer, int *w, int *h)
{
    return 0;
}

int SDL_RenderClear(SDL_Renderer *renderer)
{
    return 0;
}

int SDL_ShowCursor(int toggle)
{
    return 0;
}

int SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
{
    return 0;
}

void SDL_RenderPresent(SDL_Renderer *renderer)
{
}

int SDL_SetPaletteColors(SDL_Palette *palette, const SDL_Color *colors, int firstcolor, int ncolors)
{
    return 0;
}

Uint32 SDL_GetMouseState(int *x, int *y)
{
    return 0;
}

void SDL_FreeSurface(SDL_Surface *surface)
{
}

void SDL_WarpMouseInWindow(SDL_Window *window, int x, int y)
{
}

void SDL_DelEventWatch(SDL_EventFilter filter, void *userdata)
{
}

void SDL_GetWindowSize(SDL_Window *window, int *w, int *h)
{
}

void SDL_DestroyTexture(SDL_Texture *texture)
{
}

void SDL_DestroyRenderer(SDL_Renderer *renderer)
{
}

void SDL_DestroyWindow(SDL_Window *window)
{
}

int SDL_SetWindowFullscreen(SDL_Window *window, Uint32 flags)
{
    return 0;
}

Uint32 SDL_GetWindowFlags(SDL_Window *window)
{
    return 0;
}

int SDL_GetNumTouchDevices(void)
{
    return 0;
}

SDL_TouchID SDL_GetTouchDevice(int index)
{
    return 0;
}

int SDL_GetNumTouchFingers(SDL_TouchID touchID)
{
    return 0;
}

SDL_Finger *SDL_GetTouchFinger(SDL_TouchID touchID, int index)
{
    return NULL;
}

const Uint8 *SDL_GetKeyboardState(int *numkeys)
{
    return NULL;
}

SDL_Keycode SDL_GetKeyFromScancode(SDL_Scancode scancode)
{
    return 0;
}

int SDL_NumJoysticks(void)
{
    return 0;
}

SDL_bool SDL_IsGameController(int joystick_index)
{
    return SDL_FALSE;
}

SDL_GameController *SDL_GameControllerOpen(int joystick_index)
{
    return NULL;
}

Sint16 SDL_GameControllerGetAxis(SDL_GameController *gamecontroller, SDL_GameControllerAxis axis)
{
    return 0;
}

Uint8 SDL_GameControllerGetButton(SDL_GameController *gamecontroller, SDL_GameControllerButton button)
{
    return 0;
}

Uint16 SDL_Swap16(Uint16 x)
{
    return 0;
}

Uint16 SDL_SwapLE16(Uint16 x)
{
    return 0;
}

void SDL_Delay(Uint32 ms)
{
}