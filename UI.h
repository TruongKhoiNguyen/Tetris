#ifndef UI_H
#define UI_H

#include "data_type.h"
#include "Controller.h"
#include "Renderer.h"

void init_UI(Renderer_Data* renderer_data, const char* TITLE, s32 screen_width, s32 screen_height);
void quit_UI(Renderer_Data* renderer_data);

#endif //UI_H