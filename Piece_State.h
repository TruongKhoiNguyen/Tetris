#ifndef CORE_PIECE_STATE_H
#define CORE_PIECE_STATE_H

#include "data_type.h"
#include "Position.h"

struct Piece_State
{
    u8 tetromino_index;
    Position offset_pos;
    s32 rotation;
};

#endif //CORE_PIECE_STATE_H