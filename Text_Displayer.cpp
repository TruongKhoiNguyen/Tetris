#include "Text_Displayer.h"

void draw_string(SDL_Renderer* renderer, TTF_Font* font, const char* text, 
                 s32 x, s32 y, Text_Align alignment, Color color)
{
    SDL_Color sdl_color = SDL_Color{ color.r, color.g, color.b, color.a };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, sdl_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;
    switch (alignment)
    {
    case Text_Align::TEXT_ALIGN_LEFT:
        rect.x = x;
        break;
    case Text_Align::TEXT_ALIGN_CENTER:
        rect.x = x - surface->w / 2;
        break;
    case Text_Align::TEXT_ALIGN_RIGHT:
        rect.x = x - surface->w;
        break;
    }

    SDL_RenderCopy(renderer, texture, 0, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}