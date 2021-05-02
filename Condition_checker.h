#ifndef MODEL_CONDITION_CHECKER_H
#define MODEL_CONDITION_CHECKER_H

#include <cassert>

#include "Data_Types.h"
#include "Piece_State.h"
#include "Game_State.h"

inline u8 check_row_filled(const u8* values, s32 width, s32 row)
{
    for (s32 col = 0;
        col < width;
        ++col)
    {
        if (!matrix_get(values, width, row, col))
        {
            return 0;
        }
    }
    return 1;
}

inline u8 check_row_empty(const u8* values, s32 width, s32 row)
{
    for (s32 col = 0;
        col < width;
        ++col)
    {
        if (matrix_get(values, width, row, col))
        {
            return 0;
        }
    }
    return 1;
}

bool check_piece_valid(const Piece_State* piece, const u8* board, s32 width, s32 height);

#endif //MODEL_CONDITION_CHECKER_H
