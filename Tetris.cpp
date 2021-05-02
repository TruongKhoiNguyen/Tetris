#include "include.h"
#include "UI.h"

int main(int argc, char* argv[])
{
    const char* TITLE = "TETRIS";
    const s32 SCREEN_WIDTH = WIDTH * GRID_SIZE;
    const s32 SCREEN_HEIGHT = (HEIGHT + 2) * GRID_SIZE;

    Renderer_Data* renderer_data = new Renderer_Data();

    init_UI(renderer_data, TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    Game_State* game = new Game_State();
    Raw_Input_Data* raw_input = create_raw_input_data();
    Input_State* input = new Input_State();

    srand((u32)time(0));
    spawn_piece(game);

    bool quit = false;
    while (!quit)
    {
        game->timer.time = SDL_GetTicks() / 1000.0f;

        *input = get_input(raw_input);

        if (input->quit)
        {
            quit = true;
        }

        SDL_SetRenderDrawColor(renderer_data->renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer_data->renderer);

        update_game(game, input);
        render_game(game, renderer_data->renderer, renderer_data->font);

        SDL_RenderPresent(renderer_data->renderer);
    }

    delete raw_input;
    delete game;

    quit_UI(renderer_data);

    delete renderer_data;

    return 0;
}