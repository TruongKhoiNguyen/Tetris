#ifndef PERIPHERALS_GAME_RENDRERER_SOUND_H
#define PERIPHERALS_GAME_RENDRERER_SOUND_H

#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <string>

#include "Data_Types.h"

const int SOUND_FREQUENCY = 44100;
const int CHANNELS = 2;
const int CHUNKSIZE = 2048;

const std::string BGMUSIC = "sound/Korobeiniki.mp3";

const std::string MUSIC_LIST[] = {
	BGMUSIC
};
const s32 MUSIC_LIST_SIZE = sizeof(MUSIC_LIST) / sizeof(MUSIC_LIST[0]);

//const std::string CLEAR_SOUND = "sound/clear.wav";
const std::string FALL_SOUND = "sound/fall.wav";
const std::string GAMEOVER_SOUND = "sound/gameover.wav";
const std::string LINE_SOUND = "sound/line.wav";
const std::string SELECTION_SOUND = "sound/selection.wav";
//const std::string SUCCESS_SOUND = "sound/success.wav";

const std::string SOUND_EFFECT[] = {
	//CLEAR_SOUND,
	FALL_SOUND,
	GAMEOVER_SOUND,
	LINE_SOUND,
	SELECTION_SOUND,
	//SUCCESS_SOUND,
};
const s32 SOUND_EFFECT_SIZE = sizeof(SOUND_EFFECT) / sizeof(SOUND_EFFECT[0]);

void init_sound();

#endif //PERIPHERALS_GAME_RENDRERER_SOUND_H