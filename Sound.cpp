#include "Sound.h"

void init_sound()
{
	if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNKSIZE) != 1)
	{
		std::cout << Mix_GetError() << std::endl;
	}
}