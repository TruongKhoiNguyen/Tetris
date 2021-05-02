#ifndef MODEL_PIECE_STATE_H
#define MODEL_PIECE_STATE_H

#include <cstdlib>

#include "data_type.h"
#include "Position.h"
#include "Tetromino.h"

#define ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))

const int WIDTH = 10;
const int HEIGHT = 22;
const int VISIBLE_HEIGHT = 20;

struct Piece_State
{
    u8 tetromino_index;
    Position offset_pos;
    s32 rotation;
};

void generate_piece(Piece_State& piece);

#endif //MODEL_PIECE_STATE_H