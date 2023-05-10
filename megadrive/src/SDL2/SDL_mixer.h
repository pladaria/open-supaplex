#ifndef _SDL_MIXER_H
#define _SDL_MIXER_H 1

#include "../stddef.h"
#include "SDL.h"

#define SDL_MIX_MAXVOLUME 128
#define MIX_MAX_VOLUME SDL_MIX_MAXVOLUME

#define AUDIO_S16LSB
#define MIX_DEFAULT_FORMAT AUDIO_S16LSB

// Mix init flags
#define MIX_INIT_MOD 0x00000002;

typedef struct _Mix_Music Mix_Music;

typedef enum
{
    SDL_FALSE = 0,
    SDL_TRUE = 1
} SDL_bool;

typedef enum
{
    MIX_NO_FADING,
    MIX_FADING_OUT,
    MIX_FADING_IN
} Mix_Fading;

typedef struct
{
    const char *tag;
    // more fields
} Mix_MusicInterface;

struct _Mix_Music
{
    Mix_MusicInterface *interface;
    void *context;

    SDL_bool playing;
    Mix_Fading fading;
    int fade_step;
    int fade_steps;

    char filename[1024];
};

typedef struct Mix_Chunk
{
    int allocated;
    Uint8 *abuf;
    Uint32 alen;
    Uint8 volume;
} Mix_Chunk;

void SDL_InitSubSystem(Uint32 flags);
void Mix_Quit(void);
int Mix_PlayMusic(Mix_Music *music, int loops);
void Mix_PauseMusic(void);
void Mix_FreeMusic(Mix_Music *music);
int Mix_VolumeMusic(int volume);
int Mix_HaltChannel(int channel);
void Mix_FreeChunk(Mix_Chunk *chunk);
Mix_Chunk *Mix_LoadWAV(const char *file);
void Mix_CloseAudio(void);
void Mix_ResumeMusic(void);
int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops);

#endif