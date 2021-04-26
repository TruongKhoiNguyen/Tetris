#pragma once

#include "Game_Speed.h"
#include "Tetromino.h"
#include "Input_State.h"
#include "Piece_State.h"
#include "Game_State.h"

bool check_piece_valid(const Piece_State* piece,
    const u8* board, s32 width, s32 height);

void spawn_piece(Game_State* game);

void update_game(Game_State* game,
    const Input_State* input);