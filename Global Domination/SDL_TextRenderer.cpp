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

			const int fontSize = 30;
			font = TTF_OpenFont(".\\fonts\\ARIAL.TTF", fontSize);
			if (!font)
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font loading failed with error : %s\n", SDL_GetError());
				return nullptr;
			}

			return font;
		}

		void renderText(SDL_Window* window, std::string text, SDL_Rect textLocation, SDL_Color foregroundColor)
		{
			SDL_Color backgroundColor = { 0, 0, 0 };
			SDL_Surface* textSurface = TTF_RenderText_Shaded(getFont(), text.c_str(), foregroundColor, backgroundColor);

			// Pass zero for width and height to draw the whole surface
			SDL_Surface* screen = SDL_GetWindowSurface(window);
			SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

			SDL_FreeSurface(textSurface);
			TTF_CloseFont(font);
			font = nullptr;
		}
	}
}
