#pragma once
#include "Tetromino.h"
#include "Position.h"

const int WIDTH = 10;
const int HEIGHT = 22;
const int VISIBLE_HEIGHT = 20;
const s32 GRID_SIZE = 30;

#define ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))

const u8 FRAMES_PER_DROP[] = {
    48,
    43,
    38,
    33,
    28,
    23,
    18,
    13,
    8,
    6,
    5,
    5,
    5,
    4,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    1
};

const f32 TARGET_SECONDS_PER_FRAME = 1.f / 60.f;

enum class Game_Phase
{
    GAME_PHASE_START,
    GAME_PHASE_PLAY,
    GAME_PHASE_LINE,
    GAME_PHASE_GAMEOVER
};

struct Piece_State
{
    u8 tetromino_index;
    Position offset_pos;
    s32 rotation;
};

struct Game_State
{
    u8 board[WIDTH * HEIGHT];
    u8 lines[HEIGHT];
    s32 pending_line_count;

    Piece_State piece;

    Game_Phase phase;

    s32 start_level;
    s32 level;
    s32 line_count;
    s32 points;

    f32 next_drop_time;
    f32 highlight_end_time;
    f32 time;
};

struct Input_State
{
    u8 left;
    u8 right;
    u8 up;
    u8 down;

    u8 a;

    s8 dleft;
    s8 dright;
    s8 dup;
    s8 ddown;
    s8 da;
};

enum class Text_Align
{
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
};