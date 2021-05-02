#include "include.h"
#include "UI.h"

int main(int argc, char* argv[])
{
    const char* TITLE = "TETRIS";
    const s32 SCREEN_WIDTH = WIDTH * GRID_SIZE;
    const s32 SCREEN_HEIGHT = (HEIGHT + SCORE_SURFACE_HEIGHT) * GRID_SIZE;

    View_Data* renderer_data = new View_Data();

    init_UI(renderer_data, TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    Game_State* game = new Game_State();
    Raw_Input_Data* raw_input = create_raw_input_data();
    Input_State* input = new Input_State();

    srand((u32)time(0));
    spawn_piece(game);

    game->quit = false;
    while (!game->quit)
    {
        game->timer.time = SDL_GetTicks() / 1000.0f;

        *input = get_input(raw_input);

        update_game(game, input);
        render_game(game, renderer_data);
    }

    delete raw_input;
    delete game;

    quit_UI(renderer_data);

    delete renderer_data;

    return 0;
}