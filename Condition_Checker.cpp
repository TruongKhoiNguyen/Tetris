#include "Condition_Checker.h"

bool check_piece_valid(const Piece_State* piece,
    const u8* board, s32 width, s32 height)
{
    const Tetromino* tetromino = TETROMINOES + piece->tetromino_index;
    assert(tetromino);

    for (s32 row = 0;
        row < tetromino->side;
        ++row)
    {
        for (s32 col = 0;
            col < tetromino->side;
            ++col)
        {
            u8 value = tetromino_get(tetromino, row, col, piece->rotation);
            if (value > 0)
            {
                s32 board_row = piece->offset_pos.row + row;
                s32 board_col = piece->offset_pos.col + col;
                if (board_row < 0)
                {
                    return false;
                }
                if (board_row >= height)
                {
                    return false;
                }
                if (board_col < 0)
                {
                    return false;
                }
                if (board_col >= width)
                {
                    return false;
                }
                if (matrix_get(board, width, board_row, board_col))
                {
                    return false;
                }
            }
        }
    }
    return true;
}