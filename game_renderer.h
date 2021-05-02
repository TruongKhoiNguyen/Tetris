#ifndef UI_GAME_RENDERER_H
#define UI_GAME_RENDERER_H

#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>

#include "data_type.h"
#include "Game_Speed.h"
#include "Model.h"
#include "colors.h"
#include "Tetromino.h"
#include "Game_State.h"
#include "Text_Displayer.h"
#include "Draw_Func.h"
#include "Renderer_Data.h"

const s32 GRID_SIZE = 30;
const s32 SCORE_SURFACE_HEIGHT = 2;

void render_game(const Game_State* game, Renderer_Data* renderer_data);

#endif //UI_GAME_RENDERER_H
