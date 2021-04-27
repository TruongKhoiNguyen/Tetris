#ifndef PERIPHERALS_GAME_RENDERER_FONT_H
#define PERIPHERALS_GAME_RENDERER_FONT_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "data_type.h"
#include "colors.h"

const char FONT_NAME[] = "font/PressStart2P-vaV7.ttf";
const s32 FONT_SIZE = 16;

typedef TTF_Font Font;

enum class Text_Align
{
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
};

inline void font_init()
{
    if (TTF_Init() < 0)
    {
        exit(2);
    }
}

inline void close_font(Font* font)
{
    TTF_CloseFont(font);
}

inline void exit_ttf()
{
    TTF_Quit();
}

inline Font* load_font()
{
	return TTF_OpenFont(FONT_NAME, FONT_SIZE);
}

void draw_string(SDL_Renderer* renderer, TTF_Font* font, const char* text, 
                 s32 x, s32 y, Text_Align alignment, Color color);

#endif //PERIPHERALS_GAME_RENDERER_FONT_H