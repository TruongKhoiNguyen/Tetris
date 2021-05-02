#ifndef UI_VIEW_DRAW_FUNCTIONS_H
#define UI_VIEW_DRAW_FUNCTIONS_H

#include <SDL.h>

#include "Data_Types.h"
#include "Colors.h"

void fill_rect(SDL_Renderer* renderer,
    s32 x, s32 y, s32 width, s32 height, Color color);


void draw_rect(SDL_Renderer* renderer,
    s32 x, s32 y, s32 width, s32 height, Color color);

#endif //UI_VIEW_DRAW_FUNCTIONS_H