#include "Game.h"

Game::Game ()
{
    SDL_Init (SDL_INIT_VIDEO);
    TTF_Init ();

    window = SDL_CreateWindow (
        "Tetris",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        300, 720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer (
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    const char* font_name = "novem___.ttf";
    font = TTF_OpenFont (font_name, 24);
}

Game::~Game ()
{
    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run ()
{
    Game_State* game = new Game();
    Input_State* input = new Input_State();
    Input_State* prev_input = new Input_State();

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
}