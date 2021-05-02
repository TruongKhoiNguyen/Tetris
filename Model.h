#ifndef MODEL_H
#define MODEL_H

#include "Data_Types.h"
#include "Game_Speed.h"
#include "Tetromino.h"
#include "Input_State.h"
#include "Piece_State.h"
#include "Game_State.h"
#include "Condition_Checker.h"
#include "Game_State_Calculator.h"
#include "Game_Mechanics.h"

void spawn_piece(Game_State* game);

void update_game(Game_State* game,
    const Input_State* input);

inline f32 get_time()
{
    return SDL_GetTicks() / 1000.0f;
}

#endif //MODEL_H