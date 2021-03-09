#pragma once

#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>
#include "data_type.h"
#include "structures.h"
#include "core.h"
#include "colors.h"

void render_game(const Game_State* game,
    SDL_Renderer* renderer,
    TTF_Font* font);
