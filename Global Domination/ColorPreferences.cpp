#include "ColorPreferences.h"

namespace global_domination
{
	SDL_Color ColorPreferences::primary_background_color_ = SDL_Color{ 220, 225, 234 };
	SDL_Color ColorPreferences::secondary_background_color_ = SDL_Color{ 59, 103, 181 };
	SDL_Color ColorPreferences::primary_text_color_ = SDL_Color{ 59, 103, 181 };
	SDL_Color ColorPreferences::secondary_text_color_ = SDL_Color{ 220, 225, 234 };
	SDL_Color ColorPreferences::selected_text_color_ = SDL_Color{ 211, 148, 23 };

	SDL_Color ColorPreferences::getPrimaryBackgroundColor()
	{
		return primary_background_color_;
	}

	SDL_Color ColorPreferences::getSecondaryBackgroundColor()
	{
		return secondary_background_color_;
	}

	SDL_Color ColorPreferences::getSelectedTextColor()
	{
		return selected_text_color_;
	}

	SDL_Color ColorPreferences::getPrimaryTextColor()
	{
		return primary_text_color_;
	}

	SDL_Color ColorPreferences::getSecondaryTextColor()
	{
		return secondary_text_color_;
	}
}


