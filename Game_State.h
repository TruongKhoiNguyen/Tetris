#ifndef MODEL_GAME_STATE_H
#define MODEL_GAME_STATE_H

#include "Data_Types.h"
#include "Piece_State.h"
#include "Game_Phase.h"
#include "Play_Score.h"
#include "Timer.h"

struct Game_State
{
    u8 board[WIDTH * HEIGHT];
    u8 lines[HEIGHT];
    s32 pending_line_count;

    Piece_State piece;

    Game_Phase phase;

    Play_Score play_score;

    s32 start_level;

    bool quit;
    bool play_sound_signal;
    //s32 play_sound_counter;

    Timer timer;
};

inline u8
matrix_get(const u8* values, s32 width, s32 row, s32 col)
{
    s32 index = row * width + col;
    return values[index];
}

inline void
matrix_set(u8* values, s32 width, s32 row, s32 col, u8 value)
{
    s32 index = row * width + col;
    values[index] = value;
}

#endif //MODEL_GAME_STATE_H