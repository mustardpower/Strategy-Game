#pragma once
#include <string>

#include "SDL.h"
#include "sdl_ttf.h"

namespace global_domination
{
	namespace text_renderer
	{
		TTF_Font* getFont(int font_size);
		void getTextDimensions(std::string text, int &w, int &h);
		void renderText(SDL_Window* window, std::string text, SDL_Rect text_location, SDL_Color foreground_color, SDL_Color background_color, int font_size = 30);
	};
}