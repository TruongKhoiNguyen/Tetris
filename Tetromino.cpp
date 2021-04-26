#include "Tetromino.h"

inline Tetromino tetromino(const u8* data, s32 side)
{
    return { data, side };
}