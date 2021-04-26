#ifndef CORE_TIMER_H
#define CORE_TIMER_H

#include "data_type.h"

struct Timer
{
    f32 next_drop_time;
    f32 highlight_end_time;
    f32 time;
};

#endif //CORE_TIMER_H