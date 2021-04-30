#include "include.h"
#include "Input_Data.h"
#include "Input_State.h"
#include "Font.h"
#include "Sound.h"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }

    font_init();
    Font* font = load_font();

    init_sound();
    Music* mus = load_bgmusic();
    Sound_Effect sound_effect = load_sound_effect();

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

    Game_State* game = new Game_State();
    Input_Data* this_input = new Input_Data();
    Input_Data* prev_input = new Input_Data();
    Input_State* input = new Input_State();

    srand((u32)time(0));
    spawn_piece(game);

    play_bgmusic(mus);
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
        if (input->quit)
        {
            quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        update_game(game, input);
        render_game(game, renderer, font);

        SDL_RenderPresent(renderer);
    }

    delete prev_input;
    delete this_input;
    delete game;

    quit_mix();
    close_font(font);
    exit_ttf();
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}