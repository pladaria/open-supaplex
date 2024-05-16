#include "SDL_mixer.h"

void Mix_Quit(void)
{
}

int Mix_PlayMusic(Mix_Music *music, int loops) {
    return 0;
}

void Mix_PauseMusic(void) {
}

void Mix_FreeMusic(Mix_Music *music) {
}

int Mix_VolumeMusic(int volume) {
    return 0;
}

int Mix_HaltChannel(int channel) {
    return 0;
}

void Mix_FreeChunk(Mix_Chunk *chunk) {
}

Mix_Chunk *Mix_LoadWAV(const char *file) {
    return NULL;
}

void Mix_CloseAudio(void) {
}

void Mix_ResumeMusic(void) {
}

int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize) {
    return 0;
}

int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops) {
    return 0;
}

int Mix_Volume(int channel, int volume) {
    return 0;
}

int Mix_Init(int flags) {
    return 0;
}

int Mix_QuerySpec(int *frequency, Uint16 *format, int *channels) {
    return 0;
}

Mix_Music *Mix_LoadMUS(const char *file)
{
    return NULL;
}