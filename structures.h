#pragma once
#include "Tetromino.h"
#include "Game_State.h"

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