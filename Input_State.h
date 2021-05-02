#ifndef UI_GETTERSCANNER_INPUT_STATE_H
#define UI_GETTERSCANNER_INPUT_STATE_H

#include <SDL.h>

#include "data_type.h"
#include "Input_Data.h"

struct Input_State
{
    s8 dleft;
    s8 dright;
    s8 dup;
    s8 ddown;
    s8 da;

    bool quit;
};

inline Input_State get_input(Raw_Input_Data* raw_input)
{
    bool quit = false;

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            quit = true;
        }
    }

    s32 key_count;
    const u8* key_states = SDL_GetKeyboardState(&key_count);

    if (key_states[SDL_SCANCODE_ESCAPE])
    {
        quit = true;
    }

    raw_input->prev_input = raw_input->this_input;

    raw_input->this_input.left = key_states[SDL_SCANCODE_LEFT];
    raw_input->this_input.right = key_states[SDL_SCANCODE_RIGHT];
    raw_input->this_input.up = key_states[SDL_SCANCODE_UP];
    raw_input->this_input.down = key_states[SDL_SCANCODE_DOWN];
    raw_input->this_input.a = key_states[SDL_SCANCODE_SPACE];

    s8 dleft = raw_input->this_input.left - raw_input->prev_input.left;
    s8 dright = raw_input->this_input.right - raw_input->prev_input.right;
    s8 dup = raw_input->this_input.up - raw_input->prev_input.up;
    s8 ddown = raw_input->this_input.down - raw_input->prev_input.down;
    s8 da = raw_input->this_input.a - raw_input->prev_input.a;

    return Input_State{
        dleft,
        dright,
        dup,
        ddown,
        da,
        quit
    };
}

#endif //UI_GETTERSCANNER_INPUT_STATE_H
