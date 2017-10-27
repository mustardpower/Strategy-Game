#pragma once
#include "SDL_TextRenderer.h"

namespace global_domination
{
	namespace text_renderer {

		namespace {
			TTF_Font* font = NULL;
		}


		TTF_Font * getFont()
		{
			if (font) { return font; }

			const int font_size = 30;
			font = TTF_OpenFont(".\\fonts\\ARIAL.TTF", font_size);
			if (!font)
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font loading failed with error : %s\n", SDL_GetError());
				return nullptr;
			}

			return font;
		}

		void renderText(SDL_Window* window, std::string text, SDL_Rect text_location, SDL_Color foreground_color)
		{
			SDL_Color background_color = { 0, 0, 0 };
			SDL_Surface* text_surface = TTF_RenderText_Shaded(getFont(), text.c_str(), foreground_color, background_color);

			// Pass zero for width and height to draw the whole surface
			SDL_Surface* screen = SDL_GetWindowSurface(window);
			SDL_BlitSurface(text_surface, NULL, screen, &text_location);

			SDL_FreeSurface(text_surface);
			TTF_CloseFont(font);
			font = nullptr;
		}
	}
}
