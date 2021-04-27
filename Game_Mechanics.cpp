#include "Game_Mechanics.h"

s32 find_lines(const u8* values, s32 width, s32 height, u8* lines_out)
{
    s32 count = 0;
    for (s32 row = 0;
        row < height;
        ++row)
    {
        u8 filled = check_row_filled(values, width, row);
        lines_out[row] = filled;
        count += filled;
    }
    return count;
}

void clear_lines(u8* values, s32 width, s32 height, const u8* lines)
{
    s32 src_row = height - 1;
    for (s32 dst_row = height - 1;
        dst_row >= 0;
        --dst_row)
    {
        while (src_row >= 0 && lines[src_row])
        {
            --src_row;
        }

        if (src_row < 0)
        {
            memset(values + dst_row * width, 0, width);
        }
        else
        {
            if (src_row != dst_row)
            {
                memcpy(values + dst_row * width,
                    values + src_row * width,
                    width);
            }
            --src_row;
        }
    }
}

void merge_piece(Game_State* game)
{
    const Tetromino* tetromino = TETROMINOES + game->piece.tetromino_index;
    for (s32 row = 0;
        row < tetromino->side;
        ++row)
    {
        for (s32 col = 0;
            col < tetromino->side;
            ++col)
        {
            u8 value = tetromino_get(tetromino, row, col, game->piece.rotation);
            if (value)
            {
                s32 board_row = game->piece.offset_pos.row + row;
                s32 board_col = game->piece.offset_pos.col + col;
                matrix_set(game->board, WIDTH, board_row, board_col, value);
            }
        }
    }
}

void spawn_piece(Game_State* game)
{
    generate_piece(game->piece);
    game->timer.next_drop_time = game->timer.time + get_time_to_next_drop(game->play_score.level);
}