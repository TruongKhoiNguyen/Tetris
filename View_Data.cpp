#include "View_Data.h"

void init_video(View_Data* renderer_data, const char* TITLE, s32 screen_width, s32 screen_height)
{
	init_font();
	init_sound();

	renderer_data->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screen_width, screen_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (renderer_data->window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	renderer_data->renderer = SDL_CreateRenderer(renderer_data->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_data->renderer)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer_data->renderer, screen_width, screen_height);
}

void load_data(View_Data* renderer_data)
{
	renderer_data->font = TTF_OpenFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE);

	for (int i = 0; i < MUSIC_LIST_SIZE; ++i)
	{
		renderer_data->music.insert(std::make_pair(MUSIC_LIST[i], Mix_LoadMUS(MUSIC_LIST[i].c_str())));
	}

	for (int i = 0; i < SOUND_EFFECT_SIZE; ++i)
	{
		renderer_data->effects.insert(std::make_pair(SOUND_EFFECT[i], Mix_LoadWAV(SOUND_EFFECT[i].c_str())));
	}

	Mix_PlayMusic(renderer_data->music[BGMUSIC], -1);
}

void destroy_render_data(View_Data* renderer_data)
{
	SDL_DestroyWindow(renderer_data->window);
	SDL_DestroyRenderer(renderer_data->renderer);
	TTF_CloseFont(renderer_data->font);

	Mix_CloseAudio();

	for (int i = 0; i < MUSIC_LIST_SIZE; ++i)
	{
		Mix_FreeMusic(renderer_data->music[MUSIC_LIST[i]]);
	}

	for (int i = 0; i < SOUND_EFFECT_SIZE; ++i)
	{
		Mix_FreeChunk(renderer_data->effects[SOUND_EFFECT[i]]);
	}
}