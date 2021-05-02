#ifndef MODEL_TIMER_H
#define MODEL_TIMER_H

#include "Data_Types.h"

struct Timer
{
    f32 next_drop_time;
    f32 highlight_end_time;
    f32 time;
};

#endif //MODEL_TIMER_H