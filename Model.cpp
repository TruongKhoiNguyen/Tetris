#include "Model.h"

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
        game->play_score.level = game->start_level;
        game->play_score.line_count = 0;
        game->play_score.points = 0;
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
    if (game->timer.time >= game->timer.highlight_end_time)
    {
        clear_lines(game->board, WIDTH, HEIGHT, game->lines);
        game->play_score.line_count += game->pending_line_count;
        game->play_score.points += compute_points(game->play_score.level, game->pending_line_count);

        s32 lines_for_next_level = get_lines_for_next_level(game->start_level,
            game->play_score.level);
        if (game->play_score.line_count >= lines_for_next_level)
        {
            ++game->play_score.level;
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
        --piece.offset_pos.col;
    }
    if (input->dright > 0)
    {
        ++piece.offset_pos.col;
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

    while (game->timer.time >= game->timer.next_drop_time)
    {
        soft_drop(game);
    }

    game->pending_line_count = find_lines(game->board, WIDTH, HEIGHT, game->lines);
    if (game->pending_line_count > 0)
    {
        game->phase = Game_Phase::GAME_PHASE_LINE;
        game->timer.highlight_end_time = game->timer.time + 0.5f;
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
    if (input->quit)
    {
        game->quit = true;
    }

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