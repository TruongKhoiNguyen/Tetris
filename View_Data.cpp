#include "View_Data.h"

void init_video(View_Data* view_data, const char* TITLE, s32 screen_width, s32 screen_height)
{
	init_font();
	init_sound();

	view_data->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screen_width, screen_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (view_data->window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(3);
	}

	view_data->renderer = SDL_CreateRenderer(view_data->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (view_data->renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(4);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(view_data->renderer, screen_width, screen_height);
}

void load_data(View_Data* view_data)
{
	view_data->font = TTF_OpenFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE);

	for (int i = 0; i < MUSIC_LIST_SIZE; ++i)
	{
		view_data->music.insert(std::make_pair(MUSIC_LIST[i], Mix_LoadMUS(MUSIC_LIST[i].c_str())));
	}

	for (int i = 0; i < SOUND_EFFECT_SIZE; ++i)
	{
		view_data->effects.insert(std::make_pair(SOUND_EFFECT[i], Mix_LoadWAV(SOUND_EFFECT[i].c_str())));
	}

	Mix_PlayMusic(view_data->music[BGMUSIC], -1);
}

void destroy_render_data(View_Data* view_data)
{
	SDL_DestroyWindow(view_data->window);
	SDL_DestroyRenderer(view_data->renderer);
	TTF_CloseFont(view_data->font);

	Mix_CloseAudio();

	for (int i = 0; i < MUSIC_LIST_SIZE; ++i)
	{
		Mix_FreeMusic(view_data->music[MUSIC_LIST[i]]);
	}

	for (int i = 0; i < SOUND_EFFECT_SIZE; ++i)
	{
		Mix_FreeChunk(view_data->effects[SOUND_EFFECT[i]]);
	}
}