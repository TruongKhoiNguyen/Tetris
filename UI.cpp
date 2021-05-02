#include "UI.h"

void init_UI(Renderer_Data* renderer_data, const char* TITLE, s32 screen_width, s32 screen_height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 1)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	init_video(renderer_data, TITLE, screen_width, screen_height);
	load_data(renderer_data);
}
void quit_UI(Renderer_Data* renderer_data)
{
	destroy_render_data(renderer_data);

	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}