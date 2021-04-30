#pragma once

#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>

#include "data_type.h"
#include "Game_Speed.h"
#include "Core.h"
#include "colors.h"
#include "Tetromino.h"
#include "Game_State.h"
#include "Font.h"
#include "Draw_Func.h"

typedef SDL_Window Window;
typedef SDL_Renderer Renderer;

const s32 GRID_SIZE = 30;

void render_game(const Game_State* game,
    SDL_Renderer* renderer,
    TTF_Font* font);
