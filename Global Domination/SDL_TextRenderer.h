#pragma once
#include <string>

#include "SDL.h"
#include "sdl_ttf.h"

class SDL_TextRenderer
{
private:
	static TTF_Font* font;
public:
	~SDL_TextRenderer();
	static TTF_Font* getFont();
	static void renderText(SDL_Window* window, std::string text, SDL_Rect textLocation, SDL_Color foregroundColor);
};