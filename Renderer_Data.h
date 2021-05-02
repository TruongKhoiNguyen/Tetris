#ifndef UI_RENDERER_RENDERER_DATA_H
#define UI_RENDERER_RENDERER_DATA_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <map>
#include <string>

#include "data_type.h"
#include "Font.h"
#include "Sound.h"

struct Renderer_Data
{

	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font;

	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> effects;
};

void init_video(Renderer_Data* renderer_data, const char* TITLE, s32 screen_width, s32 screen_height);
void load_data(Renderer_Data* renderer_data);
void destroy_render_data(Renderer_Data* renderer_data);

#endif //UI_RENDERER_RENDERER_DATA_H