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