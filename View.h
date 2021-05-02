#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Data_Types.h"
#include "Game_Speed.h"
#include "Model.h"
#include "Colors.h"
#include "Tetromino.h"
#include "Game_State.h"
#include "Text_Displayer.h"
#include "Draw_Functions.h"
#include "View_Data.h"

const s32 GRID_SIZE = 30;
const s32 SCORE_SURFACE_HEIGHT = 2;

void render_game(const Game_State* game, View_Data* renderer_data);

#endif //UI_VIEW_H
