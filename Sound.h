#ifndef PERIPHERALS_GAME_RENDRERER_SOUND_H
#define PERIPHERALS_GAME_RENDRERER_SOUND_H

#include <SDL_mixer.h>
#include <iostream>

#include "data_type.h"

const int SOUND_FREQUENCY = 44100;
const int CHANNELS = 2;
const int CHUNKSIZE = 2048;

const char BGMUSIC[] = "sound/Korobeiniki.mp3";
const char CLEAR_SOUND[] = "sound/clear.wav";
const char FALL_SOUND[] = "sound/fall.wav";
const char GAMEOVER_SOUND[] = "sound/gameover.wav";
const char LINE_SOUND[] = "sound/line.wav";
const char SELECTION_SOUND[] = "sound/selection.wav";
const char SUCCESS_SOUND[] = "sound/success.wav";

typedef Mix_Music Music;

inline void init_sound()
{
    if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNKSIZE) == -1)
    {
        std::cout << Mix_GetError << std::endl;
    }
}

inline Music* load_bgmusic()
{
    Mix_Music* music = Mix_LoadMUS("sound/Korobeiniki.mp3");
    if (music == NULL)
    {
        std::cout << Mix_GetError() << std::endl;
    }
    return music;
}

inline void quit_mix()
{
    Mix_CloseAudio();
    Mix_Quit();
}

inline void play_bgmusic(Music* mus, s32 loop = -1)
{
    Mix_PlayMusic(mus, loop);
}

inline void stop_bgmusic()
{
    Mix_HaltMusic();
}

#endif //PERIPHERALS_GAME_RENDRERER_SOUND_H