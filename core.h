#ifndef CORE_H
#define CORE_H

#include "Game_Speed.h"
#include "Tetromino.h"
#include "Input_State.h"
#include "Piece_State.h"
#include "Game_State.h"
#include "Condition_checker.h"
#include "Game_State_Calculator.h"
#include "Game_Mechanics.h"

void spawn_piece(Game_State* game);

void update_game(Game_State* game,
    const Input_State* input);

#endif //CORE_H