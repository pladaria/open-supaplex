#ifndef _SDL2_H
#define _SDL2_H 1

#include "../stddef.h"

// init flags
#define SDL_INIT_TIMER 0x00000001u
#define SDL_INIT_AUDIO 0x00000010u

// events
#define SDL_QUIT 0x100

typedef union {
    Uint32 type;
    // add events as needed
} SDL_Event;

int SDL_Init(Uint32 flags);
Uint32 SDL_GetTicks(void);
void SDL_Quit(void);
int SDL_PollEvent(SDL_Event *event);

#endif
