#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include "include.h"

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font;
public:
	Game();
	~Game();
	void run();
};

#endif 