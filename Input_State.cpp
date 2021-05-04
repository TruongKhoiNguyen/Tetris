#include "Input_State.h"

void get_input(Raw_Input_Data* raw_input, Input_State* input)
{
    bool quit = false;

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            input->quit = true;
        }
    }

    s32 key_count;
    const u8* key_states = SDL_GetKeyboardState(&key_count);

    if (key_states[SDL_SCANCODE_ESCAPE])
    {
        input->quit = true;
    }

    raw_input->prev_input = raw_input->this_input;

    raw_input->this_input.left = key_states[SDL_SCANCODE_LEFT];
    raw_input->this_input.right = key_states[SDL_SCANCODE_RIGHT];
    raw_input->this_input.up = key_states[SDL_SCANCODE_UP];
    raw_input->this_input.down = key_states[SDL_SCANCODE_DOWN];
    raw_input->this_input.a = key_states[SDL_SCANCODE_SPACE];

    input->dleft = raw_input->this_input.left - raw_input->prev_input.left;
    input->dright = raw_input->this_input.right - raw_input->prev_input.right;
    input->dup = raw_input->this_input.up - raw_input->prev_input.up;
    input->ddown = raw_input->this_input.down - raw_input->prev_input.down;
    input->da = raw_input->this_input.a - raw_input->prev_input.a;
}