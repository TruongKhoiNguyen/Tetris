#include "include.h"

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
draw_string(SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    s32 x, s32 y,
    Text_Align alignment,
    Color color)
{
    SDL_Color sdl_color = SDL_Color{ color.r, color.g, color.b, color.a };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, sdl_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;
    switch (alignment)
    {
    case Text_Align::TEXT_ALIGN_LEFT:
        rect.x = x;
        break;
    case Text_Align::TEXT_ALIGN_CENTER:
        rect.x = x - surface->w / 2;
        break;
    case Text_Align::TEXT_ALIGN_RIGHT:
        rect.x = x - surface->w;
        break;
    }

    SDL_RenderCopy(renderer, texture, 0, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
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
    const Tetrino* tetrino = TETRINOS + piece->tetrino_index;
    for (s32 row = 0;
        row < tetrino->side;
        ++row)
    {
        for (s32 col = 0;
            col < tetrino->side;
            ++col)
        {
            u8 value = tetrino_get(tetrino, row, col, piece->rotation);
            if (value)
            {
                draw_cell(renderer,
                    row + piece->offset_row,
                    col + piece->offset_col,
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
            piece.offset_row++;
        }
        --piece.offset_row;

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


    snprintf(buffer, sizeof(buffer), "LEVEL: %d", game->level);
    draw_string(renderer, font, buffer, 5, 5, Text_Align::TEXT_ALIGN_LEFT, highlight_color);

    snprintf(buffer, sizeof(buffer), "LINES: %d", game->line_count);
    draw_string(renderer, font, buffer, 5, 35, Text_Align::TEXT_ALIGN_LEFT, highlight_color);

    snprintf(buffer, sizeof(buffer), "POINTS: %d", game->points);
    draw_string(renderer, font, buffer, 5, 65, Text_Align::TEXT_ALIGN_LEFT, highlight_color);
}

int
wmain()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }

    if (TTF_Init() < 0)
    {
        return 2;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        300,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    const char* font_name = "novem___.ttf";
    TTF_Font* font = TTF_OpenFont(font_name, 24);

    Game_State game = {};
    Input_State input = {};

    srand((u32)time(0));

    spawn_piece(&game);

    game.piece.tetrino_index = 2;

    bool quit = false;
    while (!quit)
    {
        game.time = SDL_GetTicks() / 1000.0f;

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        s32 key_count;
        const u8* key_states = SDL_GetKeyboardState(&key_count);

        if (key_states[SDL_SCANCODE_ESCAPE])
        {
            quit = true;
        }

        Input_State prev_input = input;

        input.left = key_states[SDL_SCANCODE_LEFT];
        input.right = key_states[SDL_SCANCODE_RIGHT];
        input.up = key_states[SDL_SCANCODE_UP];
        input.down = key_states[SDL_SCANCODE_DOWN];
        input.a = key_states[SDL_SCANCODE_SPACE];

        input.dleft = input.left - prev_input.left;
        input.dright = input.right - prev_input.right;
        input.dup = input.up - prev_input.up;
        input.ddown = input.down - prev_input.down;
        input.da = input.a - prev_input.a;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        update_game(&game, &input);
        render_game(&game, renderer, font);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}