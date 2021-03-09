#include "include.h"

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

inline u8
tetromino_get(const Tetromino* tetromino, s32 row, s32 col, s32 rotation)
{
    s32 side = tetromino->side;
    switch (rotation)
    {
    case 0:
        return tetromino->data[row * side + col];
    case 1:
        return tetromino->data[(side - col - 1) * side + row];
    case 2:
        return tetromino->data[(side - row - 1) * side + (side - col - 1)];
    case 3:
        return tetromino->data[col * side + (side - row - 1)];
    }
    return 0;
}

inline u8
check_row_filled(const u8* values, s32 width, s32 row)
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

inline u8
check_row_empty(const u8* values, s32 width, s32 row)
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

s32
find_lines(const u8* values, s32 width, s32 height, u8* lines_out)
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

void
clear_lines(u8* values, s32 width, s32 height, const u8* lines)
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


bool
check_piece_valid(const Piece_State* piece,
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
                s32 board_row = piece->offset_row + row;
                s32 board_col = piece->offset_col + col;
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

void
merge_piece(Game_State* game)
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
                s32 board_row = game->piece.offset_row + row;
                s32 board_col = game->piece.offset_col + col;
                matrix_set(game->board, WIDTH, board_row, board_col, value);
            }
        }
    }
}

inline s32
random_int(s32 min, s32 max)
{
    s32 range = max - min;
    return min + rand() % range;
}

inline f32
get_time_to_next_drop(s32 level)
{
    if (level > 29)
    {
        level = 29;
    }
    return FRAMES_PER_DROP[level] * TARGET_SECONDS_PER_FRAME;
}


void
spawn_piece(Game_State* game)
{
    game->piece = {};
    game->piece.tetromino_index = (u8)random_int(0, ARRAY_COUNT(TETROMINOES));
    game->piece.offset_col = WIDTH / 2;
    game->next_drop_time = game->time + get_time_to_next_drop(game->level);
}


inline bool
soft_drop(Game_State* game)
{
    ++game->piece.offset_row;
    if (!check_piece_valid(&game->piece, game->board, WIDTH, HEIGHT))
    {
        --game->piece.offset_row;
        merge_piece(game);
        spawn_piece(game);
        return false;
    }

    game->next_drop_time = game->time + get_time_to_next_drop(game->level);
    return true;
}

inline s32
compute_points(s32 level, s32 line_count)
{
    switch (line_count)
    {
    case 1:
        return 40 * (level + 1);
    case 2:
        return 100 * (level + 1);
    case 3:
        return 300 * (level + 1);
    case 4:
        return 1200 * (level + 1);
    }
    return 0;
}

inline s32
min(s32 x, s32 y)
{
    return x < y ? x : y;
}
inline s32
max(s32 x, s32 y)
{
    return x > y ? x : y;
}

inline s32
get_lines_for_next_level(s32 start_level, s32 level)
{
    s32 first_level_up_limit = min(
        (start_level * 10 + 10),
        max(100, (start_level * 10 - 50)));
    if (level == start_level)
    {
        return first_level_up_limit;
    }
    s32 diff = level - start_level;
    return first_level_up_limit + diff * 10;
}

void
update_game_start(Game_State* game, const Input_State* input)
{
    if (input->dup > 0)
    {
        ++game->start_level;
    }

    if (input->ddown > 0 && game->start_level > 0)
    {
        --game->start_level;
    }

    if (input->da > 0)
    {
        memset(game->board, 0, WIDTH * HEIGHT);
        game->level = game->start_level;
        game->line_count = 0;
        game->points = 0;
        spawn_piece(game);
        game->phase = Game_Phase::GAME_PHASE_PLAY;
    }
}

void
update_game_gameover(Game_State* game, const Input_State* input)
{
    if (input->da > 0)
    {
        game->phase = Game_Phase::GAME_PHASE_START;
    }
}

void
update_game_line(Game_State* game)
{
    if (game->time >= game->highlight_end_time)
    {
        clear_lines(game->board, WIDTH, HEIGHT, game->lines);
        game->line_count += game->pending_line_count;
        game->points += compute_points(game->level, game->pending_line_count);

        s32 lines_for_next_level = get_lines_for_next_level(game->start_level,
            game->level);
        if (game->line_count >= lines_for_next_level)
        {
            ++game->level;
        }

        game->phase = Game_Phase::GAME_PHASE_PLAY;
    }
}

void
update_game_play(Game_State* game,
    const Input_State* input)
{
    Piece_State piece = game->piece;
    if (input->dleft > 0)
    {
        --piece.offset_col;
    }
    if (input->dright > 0)
    {
        ++piece.offset_col;
    }
    if (input->dup > 0)
    {
        piece.rotation = (piece.rotation + 1) % 4;
    }

    if (check_piece_valid(&piece, game->board, WIDTH, HEIGHT))
    {
        game->piece = piece;
    }

    if (input->ddown > 0)
    {
        soft_drop(game);
    }

    if (input->da > 0)
    {
        while (soft_drop(game));
    }

    while (game->time >= game->next_drop_time)
    {
        soft_drop(game);
    }

    game->pending_line_count = find_lines(game->board, WIDTH, HEIGHT, game->lines);
    if (game->pending_line_count > 0)
    {
        game->phase = Game_Phase::GAME_PHASE_LINE;
        game->highlight_end_time = game->time + 0.5f;
    }

    s32 game_over_row = 0;
    if (!check_row_empty(game->board, WIDTH, game_over_row))
    {
        game->phase = Game_Phase::GAME_PHASE_GAMEOVER;
    }
}

void
update_game(Game_State* game,
    const Input_State* input)
{
    switch (game->phase)
    {
    case Game_Phase::GAME_PHASE_START:
        update_game_start(game, input);
        break;
    case Game_Phase::GAME_PHASE_PLAY:
        update_game_play(game, input);
        break;
    case Game_Phase::GAME_PHASE_LINE:
        update_game_line(game);
        break;
    case Game_Phase::GAME_PHASE_GAMEOVER:
        update_game_gameover(game, input);
        break;
    }
}