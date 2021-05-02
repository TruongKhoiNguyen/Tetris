#include "View.h"

void
draw_cell(SDL_Renderer* renderer,
    s32 row, s32 col, u8 value,
    s32 offset_x, s32 offset_y,
    bool outline = false)
{
    Color base_color = BASE_COLORS[value];
    Color light_color = LIGHT_COLORS[value];
    Color dark_color = DARK_COLORS[value];


    s32 edge = GRID_SIZE / 8;

    s32 x = col * GRID_SIZE + offset_x;
    s32 y = row * GRID_SIZE + offset_y;

    if (outline)
    {
        draw_rect(renderer, x, y, GRID_SIZE, GRID_SIZE, base_color);
        return;
    }

    fill_rect(renderer, x, y, GRID_SIZE, GRID_SIZE, dark_color);
    fill_rect(renderer, x + edge, y,
        GRID_SIZE - edge, GRID_SIZE - edge, light_color);
    fill_rect(renderer, x + edge, y + edge,
        GRID_SIZE - edge * 2, GRID_SIZE - edge * 2, base_color);
}

void
draw_piece(SDL_Renderer* renderer,
    const Piece_State* piece,
    s32 offset_x, s32 offset_y,
    bool outline = false)
{
    const Tetromino* tetromino = TETROMINOES + piece->tetromino_index;
    for (s32 row = 0;
        row < tetromino->side;
        ++row)
    {
        for (s32 col = 0;
            col < tetromino->side;
            ++col)
        {
            u8 value = tetromino_get(tetromino, row, col, piece->rotation);
            if (value)
            {
                draw_cell(renderer,
                    row + piece->offset_pos.row,
                    col + piece->offset_pos.col,
                    value,
                    offset_x, offset_y,
                    outline);
            }
        }
    }
}

void
draw_board(SDL_Renderer* renderer,
    const u8* board, s32 width, s32 height,
    s32 offset_x, s32 offset_y)
{
    fill_rect(renderer, offset_x, offset_y,
        width * GRID_SIZE, height * GRID_SIZE,
        BASE_COLORS[0]);
    for (s32 row = 0;
        row < height;
        ++row)
    {
        for (s32 col = 0;
            col < width;
            ++col)
        {
            u8 value = matrix_get(board, width, row, col);
            if (value)
            {
                draw_cell(renderer, row, col, value, offset_x, offset_y);
            }
        }
    }
}

void
render_game(Game_State* game, View_Data* view_data)
{
    const Color highlight_color = color(0xFF, 0xFF, 0xFF, 0xFF);
    const s32 margin_y = SCORE_SURFACE_HEIGHT * GRID_SIZE;

    char buffer[4096];

    SDL_SetRenderDrawColor(view_data->renderer, 0, 0, 0, 0);
    SDL_RenderClear(view_data->renderer);

    draw_board(view_data->renderer, game->board, WIDTH, HEIGHT, 0, margin_y);

    if (game->phase == Game_Phase::GAME_PHASE_PLAY)
    {
        draw_piece(view_data->renderer, &game->piece, 0, margin_y);

        Piece_State piece = game->piece;
        while (check_piece_valid(&piece, game->board, WIDTH, HEIGHT))
        {
            piece.offset_pos.row++;
        }
        --piece.offset_pos.row;

        draw_piece(view_data->renderer, &piece, 0, margin_y, true);

        if (game->play_sound_signal)
        {
            Mix_PlayChannel(-1, view_data->effects[FALL_SOUND], 0);
            game->play_sound_signal = false;
        }
    }

    if (game->phase == Game_Phase::GAME_PHASE_LINE)
    {
        for (s32 row = 0;
            row < HEIGHT;
            ++row)
        {
            if (game->lines[row])
            {
                s32 x = 0;
                s32 y = row * GRID_SIZE + margin_y;

                fill_rect(view_data->renderer, x, y,
                    WIDTH * GRID_SIZE, GRID_SIZE, highlight_color);
            }
        }

        if (game->play_sound_signal)
        {
            Mix_PlayChannel(-1, view_data->effects[LINE_SOUND], 0);
            game->play_sound_signal = false;
        }
    }
    else if (game->phase == Game_Phase::GAME_PHASE_GAMEOVER)
    {
        s32 x = WIDTH * GRID_SIZE / 2;
        s32 y = (HEIGHT * GRID_SIZE + margin_y) / 2;
        draw_string(view_data->renderer, view_data->font, "GAME OVER",
            x, y, Text_Align::TEXT_ALIGN_CENTER, highlight_color);

        if (game->play_sound_signal)
        {
            Mix_PlayChannel(-1, view_data->effects[GAMEOVER_SOUND], 0);
            game->play_sound_signal = false;
        }
    }
    else if (game->phase == Game_Phase::GAME_PHASE_START)
    {
        s32 x = WIDTH * GRID_SIZE / 2;
        s32 y = (HEIGHT * GRID_SIZE + margin_y) / 2;
        draw_string(view_data->renderer, view_data->font, "PRESS START",
            x, y, Text_Align::TEXT_ALIGN_CENTER, highlight_color);

        snprintf(buffer, sizeof(buffer), "STARTING LEVEL: %d", game->start_level);
        draw_string(view_data->renderer, view_data->font, buffer,
            x, y + 30, Text_Align::TEXT_ALIGN_CENTER, highlight_color);

        if (game->play_sound_signal)
        {
            Mix_PlayChannel(-1, view_data->effects[SELECTION_SOUND], 0);
            game->play_sound_signal = false;
        }
    }

    fill_rect(view_data->renderer,
        0, margin_y,
        WIDTH * GRID_SIZE, (HEIGHT - VISIBLE_HEIGHT) * GRID_SIZE,
        color(0x00, 0x00, 0x00, 0x00));


    snprintf(buffer, sizeof(buffer), "LEVEL: %d", game->play_score.level);
    draw_string(view_data->renderer, view_data->font, buffer, 5, 5, Text_Align::TEXT_ALIGN_LEFT, highlight_color);

    snprintf(buffer, sizeof(buffer), "LINES: %d", game->play_score.line_count);
    draw_string(view_data->renderer, view_data->font, buffer, 5, 35, Text_Align::TEXT_ALIGN_LEFT, highlight_color);

    snprintf(buffer, sizeof(buffer), "POINTS: %d", game->play_score.points);
    draw_string(view_data->renderer, view_data->font, buffer, 5, 65, Text_Align::TEXT_ALIGN_LEFT, highlight_color);

    SDL_RenderPresent(view_data->renderer);
}