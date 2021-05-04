#ifndef UI_CONTROLLER_INPUT_STATE_H
#define UI_CONTROLLER_INPUT_STATE_H

#include <SDL.h>

#include "Data_Types.h"
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

void get_input(Raw_Input_Data* raw_input, Input_State* input);

#endif //UI_CONTROLLER_INPUT_STATE_H
