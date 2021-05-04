#include <algorithm>
#include <string>

#include "Data_Types.h"
#include "Model.h"
#include "UI.h"

int main(int argc, char* argv[])
{
    const std::string TITLE = "TETRIS";
    const s32 SCREEN_WIDTH = WIDTH * GRID_SIZE;
    const s32 SCREEN_HEIGHT = (HEIGHT + SCORE_SURFACE_HEIGHT) * GRID_SIZE;

    View_Data* view_data = new View_Data();

    init_UI(view_data, TITLE.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);

    Game_State* game = new Game_State();
    Raw_Input_Data* raw_input = create_raw_input_data();
    Input_State* input = new Input_State();

    srand((u32)time(0));
    spawn_piece(game);

    game->quit = false;
    while (!game->quit)
    {
        game->timer.time = get_time();

        get_input(raw_input, input);

        update_game(game, input);
        render_game(game, view_data);
    }

    delete raw_input;
    delete game;

    quit_UI(view_data);

    delete view_data;

    return 0;
}