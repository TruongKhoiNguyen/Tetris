#ifndef CORE_GAME_STATE_CALCULATOR
#define CORE_GAME_STATE_CALCULATOR

#include "data_type.h"
#include "Game_Speed.h"

inline f32 get_time_to_next_drop(s32 level)
{
    if (level > 29)
    {
        level = 29;
    }
    return FRAMES_PER_DROP[level] * TARGET_SECONDS_PER_FRAME;
}

inline s32 compute_points(s32 level, s32 line_count)
{
    switch (line_count)
    {
    case 1:
        return 40 * (level + 1);
    case 2:
        return 100 * (level + 1);
    case 3:
        return 300 * (level + 1);
    case 4:
        return 1200 * (level + 1);
    }
    return 0;
}

inline s32 min(s32 x, s32 y)
{
    return x < y ? x : y;
}

inline s32 max(s32 x, s32 y)
{
    return x > y ? x : y;
}

inline s32 get_lines_for_next_level(s32 start_level, s32 level)
{
    s32 first_level_up_limit = min(
        (start_level * 10 + 10),
        max(100, (start_level * 10 - 50)));
    if (level == start_level)
    {
        return first_level_up_limit;
    }
    s32 diff = level - start_level;
    return first_level_up_limit + diff * 10;
}


#endif //CORE_GAME_STATE_CALCULATOR
