#ifndef PERIPHERALS_SCANNER_INPUT_DATA_H
#define PERIPHERALS_SCANNER_INPUT_DATA_H

#include "data_type.h"

struct Input_Data
{
    u8 left;
    u8 right;
    u8 up;
    u8 down;
    u8 a;

};

struct Raw_Input_Data
{
    Input_Data prev_input;
    Input_Data this_input;
};

inline Raw_Input_Data* create_raw_input_data()
{
    Raw_Input_Data* input_data = new Raw_Input_Data();

    input_data->prev_input.left = 0;
    input_data->prev_input.right = 0;
    input_data->prev_input.up = 0;
    input_data->prev_input.down = 0;
    input_data->prev_input.a = 0;

    input_data->this_input.left = 0;
    input_data->this_input.right = 0;
    input_data->this_input.up = 0;
    input_data->this_input.down = 0;
    input_data->this_input.a = 0;

    return input_data;
}

#endif //PERIPHERALS_SCANNER_INPUT_DATA_H