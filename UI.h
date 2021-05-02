#ifndef UI_H
#define UI_H

#include "Data_Types.h"
#include "Controller.h"
#include "View.h"

void init_UI(View_Data* renderer_data, const char* TITLE, s32 screen_width, s32 screen_height);
void quit_UI(View_Data* renderer_data);

#endif //UI_H