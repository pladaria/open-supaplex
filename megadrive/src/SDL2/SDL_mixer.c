#include "SDL_mixer.h"

void SDL_InitSubSystem(Uint32 flags) {
}

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