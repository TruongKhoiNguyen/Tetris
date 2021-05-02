#ifndef UI_VIEW_TEXT_DISPLAYER_H
#define UI_VIEW_TEXT_DISPLAYER_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "Data_Types.h"
#include "Colors.h"

const char DEFAULT_FONT_NAME[] = "font/soviet-bold-expanded.ttf";
const s32 DEFAULT_FONT_SIZE = 26;

typedef TTF_Font Font;

enum class Text_Align
{
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
};

inline void init_font()
{
    if (TTF_Init() < 0)
    {
        exit(2);
    }
}

void draw_string(SDL_Renderer* renderer, TTF_Font* font, const char* text, 
                 s32 x, s32 y, Text_Align alignment, Color color);

#endif //UI_VIEW_TEXT_DISPLAYER_H