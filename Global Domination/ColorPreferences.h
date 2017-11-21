#pragma once

#include "SDL.h"

namespace global_domination
{
	class ColorPreferences
	{

	public:
		static SDL_Color getPrimaryBackgroundColor();
		static SDL_Color getSecondaryBackgroundColor();
		static SDL_Color getSelectedTextColor();
		static SDL_Color getPrimaryTextColor();
		static SDL_Color getSecondaryTextColor();

	private:
		static SDL_Color selected_text_color_;
		static SDL_Color primary_text_color_;
		static SDL_Color secondary_text_color_;
		static SDL_Color primary_background_color_;
		static SDL_Color secondary_background_color_;

	};
}
