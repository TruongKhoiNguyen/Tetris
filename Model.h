#ifndef MODEL_H
#define MODEL_H

#include "data_type.h"
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

#endif //MODEL_H