#ifndef UI_VIEW_VIEW_DATA_H
#define UI_VIEW_VIEW_DATA_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <map>
#include <string>

#include "Data_Types.h"
#include "Text_Displayer.h"
#include "Sound.h"

struct View_Data
{

	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font;

	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> effects;
};

void init_video(View_Data* view_data, const char* TITLE, s32 screen_width, s32 screen_height);
void load_data(View_Data* view_data);
void destroy_render_data(View_Data* view_data);

#endif //UI_VIEW_VIEW_DATA_H