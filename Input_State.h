#ifndef PERIPHERALS_SCANNER_INPUT_STATE_H
#define PERIPHERALS_SCANNER_INPUT_STATE_H

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

inline Input_State get_input(Input_Data* prev_input, Input_Data* input)
{
    s32 key_count;
    const u8* key_states = SDL_GetKeyboardState(&key_count);

    bool quit = false;
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

    s8 dleft = input->left - prev_input->left;
    s8 dright = input->right - prev_input->right;
    s8 dup = input->up - prev_input->up;
    s8 ddown = input->down - prev_input->down;
    s8 da = input->a - prev_input->a;

    return Input_State{
        dleft,
        dright,
        dup,
        ddown,
        da,
        quit
    };
}

#endif //PERIPHERALS_SCANNER_INPUT_STATE_H
