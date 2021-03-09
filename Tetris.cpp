#include "include.h"

int main(int argc, char* argv[])
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

    const char* font_name = "Futura Black.ttf";
    TTF_Font* font = TTF_OpenFont(font_name, 24);

    Game_State* game = new Game_State();
    Input_State* input = new Input_State();
    Input_State* prev_input = new Input_State();


    srand((u32)time(0));

    spawn_piece(game);

    game->piece.tetromino_index = 2;

    bool quit = false;
    while (!quit)
    {
        game->time = SDL_GetTicks() / 1000.0f;

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

        *prev_input = *input;

        input->left = key_states[SDL_SCANCODE_LEFT];
        input->right = key_states[SDL_SCANCODE_RIGHT];
        input->up = key_states[SDL_SCANCODE_UP];
        input->down = key_states[SDL_SCANCODE_DOWN];
        input->a = key_states[SDL_SCANCODE_SPACE];

        input->dleft = input->left - prev_input->left;
        input->dright = input->right - prev_input->right;
        input->dup = input->up - prev_input->up;
        input->ddown = input->down - prev_input->down;
        input->da = input->a - prev_input->a;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        update_game(game, input);
        render_game(game, renderer, font);

        SDL_RenderPresent(renderer);
    }

    delete prev_input;
    delete input;
    delete game;

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}