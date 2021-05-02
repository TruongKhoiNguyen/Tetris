#include "UI.h"

void init_UI(View_Data* view_data, const char* TITLE, s32 screen_width, s32 screen_height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(5);
	}

	init_video(view_data, TITLE, screen_width, screen_height);
	load_data(view_data);
}
void quit_UI(View_Data* view_data)
{
	destroy_render_data(view_data);

	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}