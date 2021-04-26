#ifndef CORE_GAME_STATE_H
#define CORE_GAME_STATE_H

#include "data_type.h"
#include "Piece_State.h"
#include "Game_Phase.h"
#include "Play_Score.h"
#include "Timer.h"

const int WIDTH = 10;
const int HEIGHT = 22;
const int VISIBLE_HEIGHT = 20;

struct Game_State
{
    u8 board[WIDTH * HEIGHT];
    u8 lines[HEIGHT];
    s32 pending_line_count;

    Piece_State piece;

    Game_Phase phase;

    Play_Score play_score;

    s32 start_level;


    Timer timer;
};

#endif //CORE_GAME_STATE_H