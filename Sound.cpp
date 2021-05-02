#include "Sound.h"

void init_sound()
{
	if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNKSIZE) != 0)
	{
		std::cout << Mix_GetError() << std::endl;
		exit(6);
	}
}