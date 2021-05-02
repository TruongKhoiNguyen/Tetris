#ifndef UI_GAME_RENDERER_H
#define UI_GAME_RENDERER_H

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
#include "Renderer_Data.h"

const s32 GRID_SIZE = 30;

void render_game(const Game_State* game,
    SDL_Renderer* renderer,
    TTF_Font* font);

#endif //UI_GAME_RENDERER_H
