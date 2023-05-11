#ifndef _SDL2_H
#define _SDL2_H 1

#define Uint8 unsigned char
#define Uint16 unsigned short
#define Sint16 short
#define Uint32 unsigned long
#define Sint32 long
#ifndef NULL
#define NULL 0
#endif

#define SDL_WINDOWPOS_UNDEFINED_MASK 0x1FFF0000u
#define SDL_WINDOWPOS_UNDEFINED_DISPLAY(X) (SDL_WINDOWPOS_UNDEFINED_MASK | (X))
#define SDL_WINDOWPOS_UNDEFINED SDL_WINDOWPOS_UNDEFINED_DISPLAY(0)

#define SDL_DISABLE 0
#define SDL_SWSURFACE 0

// init flags
#define SDL_INIT_TIMER 0x00000001u
#define SDL_INIT_AUDIO 0x00000010u
#define SDL_INIT_VIDEO 0x00000020u

// events
typedef enum
{
    SDL_QUIT = 0x100,
    SDL_WINDOWEVENT = 0x200,
} SDL_EventType;

#define SDL_PIXELFORMAT_RGB24 1 /* I don't care */

typedef enum
{
    SDL_WINDOW_FULLSCREEN = 0x00000001,
} SDL_WindowFlags;

typedef enum
{
    SDL_WINDOWEVENT_RESIZED,
} SDL_WindowEventID;

typedef enum
{
    SDL_RENDERER_ACCELERATED = 0x00000002,
    SDL_RENDERER_PRESENTVSYNC = 0x00000004,
} SDL_RendererFlags;

typedef enum
{
    SDL_TEXTUREACCESS_STREAMING,
} SDL_TextureAccess;

typedef enum
{
    SDL_FALSE = 0,
    SDL_TRUE = 1
} SDL_bool;

typedef struct SDL_Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} SDL_Color;

typedef struct SDL_Palette
{
    int ncolors;
    SDL_Color *colors;
    Uint32 version;
    int refcount;
} SDL_Palette;

typedef struct SDL_PixelFormat
{
    Uint32 format;
    SDL_Palette *palette;
    // add fields as needed
    struct SDL_PixelFormat *next;
} SDL_PixelFormat;

typedef struct SDL_Rect
{
    int x, y;
    int w, h;
} SDL_Rect;

typedef struct SDL_Window
{
    // fill if needed
} SDL_Window;

typedef struct SDL_Surface
{
    void *pixels;
    SDL_PixelFormat *format;
    int pitch;
    // add fields as needed
} SDL_Surface;

typedef struct SDL_Texture
{
    // fill if needed
} SDL_Texture;

typedef struct SDL_Renderer
{
    // fill if needed
} SDL_Renderer;

typedef union {
    Uint32 type;
    // add events as needed
} SDL_Event;

typedef int (*SDL_EventFilter)(void *userdata, SDL_Event *event);

// Mouse
#define SDL_BUTTON(X) (1 << ((X)-1))
#define SDL_BUTTON_LEFT 1
#define SDL_BUTTON_RIGHT 3

int SDL_Init(Uint32 flags);
Uint32 SDL_GetTicks(void);
void SDL_Quit(void);
int SDL_PollEvent(SDL_Event *event);
char *SDL_GetError(void);
SDL_Window *SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flag);
int SDL_InitSubSystem(Uint32 flags);
void SDL_SetWindowResizable(SDL_Window *window, SDL_bool resizable);
void SDL_AddEventWatch(SDL_EventFilter filter, void *userdata);
SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags);
SDL_Texture *SDL_CreateTexture(SDL_Renderer *renderer, Uint32 format, int access, int w, int h);
int SDL_UpdateTexture(SDL_Texture *texture, const SDL_Rect *rect, const void *pixels, int pitch);
SDL_Surface *SDL_CreateRGBSurfaceWithFormat(Uint32 flags, int width, int height, int depth, Uint32 format);
SDL_Surface *SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask,
                                  Uint32 Bmask, Uint32 Amask);
int SDL_BlitSurface(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect);
int SDL_GetRendererOutputSize(SDL_Renderer *renderer, int *w, int *h);
int SDL_RenderClear(SDL_Renderer *renderer);
int SDL_ShowCursor(int toggle);
int SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect);

#endif
