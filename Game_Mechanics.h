#ifndef MODEL_GAME_MECHANICS_H
#define MODEL_GAME_MECHANICS_H

#include <cstring>

#include "data_type.h"
#include "Game_State.h"
#include "Condition_Checker.h"
#include "Game_State_Calculator.h"

s32 find_lines(const u8* values, s32 width, s32 height, u8* lines_out);
void clear_lines(u8* values, s32 width, s32 height, const u8* lines);
void merge_piece(Game_State* game);
void spawn_piece(Game_State* game);

inline bool
soft_drop(Game_State* game)
{
    ++game->piece.offset_pos.row;
    if (!check_piece_valid(&game->piece, game->board, WIDTH, HEIGHT))
    {
        --game->piece.offset_pos.row;
        merge_piece(game);
        spawn_piece(game);
        return false;
    }

    game->timer.next_drop_time = game->timer.time + get_time_to_next_drop(game->play_score.level);
    return true;
}

#endif //MODEL_GAME_MECHANICS_H