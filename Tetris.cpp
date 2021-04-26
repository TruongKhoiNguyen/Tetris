#include "include.h"
#include "Input_Data.h"
#include "Input_State.h"
#include "Font.h"

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

    font_init();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        printf("%s", Mix_GetError());
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

    Font* font = load_font();

    Game_State* game = new Game_State();

    Input_Data* this_input = new Input_Data();
    Input_Data* prev_input = new Input_Data();
    Input_State* input = new Input_State();


    srand((u32)time(0));

    spawn_piece(game);

    game->piece.tetromino_index = 2;

    Mix_Music* music = Mix_LoadMUS("sound/Korobeiniki.mp3");
    if (music == NULL)
    {
        printf("%s", Mix_GetError());
    }
    Mix_PlayMusic(music, -1);

    bool quit = false;
    while (!quit)
    {
        game->timer.time = SDL_GetTicks() / 1000.0f;

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        *input = get_input(prev_input, this_input);
        quit = input->quit;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        update_game(game, input);
        render_game(game, renderer, font);

        SDL_RenderPresent(renderer);
    }

    delete prev_input;
    delete this_input;
    delete game;

    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}