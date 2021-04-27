#include "Game_Renderer.h"

void
fill_rect(SDL_Renderer* renderer,
    s32 x, s32 y, s32 width, s32 height, Color color)
{
    SDL_Rect rect = {};
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}


void
draw_rect(SDL_Renderer* renderer,
    s32 x, s32 y, s32 width, s32 height, Color color)
{
    SDL_Rect rect = {};
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

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
render_game(const Game_State* game,
    SDL_Renderer* renderer,
    TTF_Font* font)
{

    char buffer[4096];

    Color highlight_color = color(0xFF, 0xFF, 0xFF, 0xFF);

    s32 margin_y = 60;

    draw_board(renderer, game->board, WIDTH, HEIGHT, 0, margin_y);

    if (game->phase == Game_Phase::GAME_PHASE_PLAY)
    {
        draw_piece(renderer, &game->piece, 0, margin_y);

        Piece_State piece = game->piece;
        while (check_piece_valid(&piece, game->board, WIDTH, HEIGHT))
        {
            piece.offset_pos.row++;
        }
        --piece.offset_pos.row;

        draw_piece(renderer, &piece, 0, margin_y, true);

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

                fill_rect(renderer, x, y,
                    WIDTH * GRID_SIZE, GRID_SIZE, highlight_color);
            }
        }
    }
    else if (game->phase == Game_Phase::GAME_PHASE_GAMEOVER)
    {
        s32 x = WIDTH * GRID_SIZE / 2;
        s32 y = (HEIGHT * GRID_SIZE + margin_y) / 2;
        draw_string(renderer, font, "GAME OVER",
            x, y, Text_Align::TEXT_ALIGN_CENTER, highlight_color);
    }
    else if (game->phase == Game_Phase::GAME_PHASE_START)
    {
        s32 x = WIDTH * GRID_SIZE / 2;
        s32 y = (HEIGHT * GRID_SIZE + margin_y) / 2;
        draw_string(renderer, font, "PRESS START",
            x, y, Text_Align::TEXT_ALIGN_CENTER, highlight_color);

        snprintf(buffer, sizeof(buffer), "STARTING LEVEL: %d", game->start_level);
        draw_string(renderer, font, buffer,
            x, y + 30, Text_Align::TEXT_ALIGN_CENTER, highlight_color);
    }

    fill_rect(renderer,
        0, margin_y,
        WIDTH * GRID_SIZE, (HEIGHT - VISIBLE_HEIGHT) * GRID_SIZE,
        color(0x00, 0x00, 0x00, 0x00));


    snprintf(buffer, sizeof(buffer), "LEVEL: %d", game->play_score.level);
    draw_string(renderer, font, buffer, 5, 5, Text_Align::TEXT_ALIGN_LEFT, highlight_color);

    snprintf(buffer, sizeof(buffer), "LINES: %d", game->play_score.line_count);
    draw_string(renderer, font, buffer, 5, 35, Text_Align::TEXT_ALIGN_LEFT, highlight_color);

    snprintf(buffer, sizeof(buffer), "POINTS: %d", game->play_score.points);
    draw_string(renderer, font, buffer, 5, 65, Text_Align::TEXT_ALIGN_LEFT, highlight_color);
}