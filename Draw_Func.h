#ifndef PERIPHERALS_DRAW_FUNC_H
#define PERIPHERALS_DRAW_FUNC_H

#include <SDL.h>

#include "data_type.h"
#include "colors.h"

void fill_rect(SDL_Renderer* renderer,
    s32 x, s32 y, s32 width, s32 height, Color color);


void draw_rect(SDL_Renderer* renderer,
    s32 x, s32 y, s32 width, s32 height, Color color);

#endif //PERIPHERALS_DRAW_FUNC_H