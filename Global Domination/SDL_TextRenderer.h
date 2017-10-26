#pragma once
#include <string>

#include "SDL.h"
#include "sdl_ttf.h"

namespace global_domination
{
	namespace text_renderer
	{
		TTF_Font* getFont();
		void renderText(SDL_Window* window, std::string text, SDL_Rect textLocation, SDL_Color foregroundColor);
	};
}