#include "Piece_State.h"

inline s32 random_int(s32 min, s32 max)
{
    s32 range = max - min;
    return min + rand() % range;
}

void generate_piece(Piece_State& piece)
{
    piece = {};
    piece.tetromino_index = (u8)random_int(0, ARRAY_COUNT(TETROMINOES));
    piece.offset_pos.col = WIDTH / 2;
}