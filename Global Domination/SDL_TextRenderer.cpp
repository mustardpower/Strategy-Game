#pragma once
#include "SDL_TextRenderer.h"

namespace global_domination
{
	namespace text_renderer {

		TTF_Font* font = NULL;


		TTF_Font * getFont(int font_size)
		{
			if (font) { TTF_CloseFont(font); }

			font = TTF_OpenFont(".\\fonts\\ARIAL.TTF", font_size);
			if (!font)
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font loading failed with error : %s\n", SDL_GetError());
				return nullptr;
			}

			return font;
		}

		void getTextDimensions(std::string text, int &w, int &h)
		{
			const int default_font_size = 30;
			if(!font){font = getFont(default_font_size);}

			int result = TTF_SizeText(font, text.c_str(), &w, &h);
			if (result < 0)
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot calculate the resulting surface size of the text using font : %s\n", SDL_GetError());
			}
		}

		void renderText(SDL_Window* window, std::string text, SDL_Rect text_location, SDL_Color foreground_color, SDL_Color background_color, int font_size)
		{
			const int kWrapLength = 200;
			SDL_Surface* text_surface = TTF_RenderText_Blended_Wrapped(getFont(font_size), text.c_str(), foreground_color, kWrapLength);

			// Pass zero for width and height to draw the whole surface
			SDL_Surface* screen = SDL_GetWindowSurface(window);
			SDL_BlitSurface(text_surface, NULL, screen, &text_location);

			SDL_FreeSurface(text_surface);
			TTF_CloseFont(font);
			font = nullptr;
		}
	}
}
