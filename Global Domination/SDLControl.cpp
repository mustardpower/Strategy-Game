#include "SDLControl.h"

#include <assert.h>

#include "ColorPreferences.h"

namespace global_domination
{
	SDLControl::SDLControl(SDL_Window* parent)
	{
		id_ = UNDEFINED_CONTROL_ID;
		parent_ = parent;
		use_secondary_color_scheme_ = false;
	}

	unsigned int SDLControl::getId()
	{
		return id_;
	}

	SDL_Color SDLControl::getBackgroundColor()
	{
		if (use_secondary_color_scheme_)
		{
			return ColorPreferences::getSecondaryBackgroundColor();
		}
		return ColorPreferences::getPrimaryBackgroundColor();
	}

	SDL_Color SDLControl::getTextColor()
	{
		if (use_secondary_color_scheme_)
		{
			return ColorPreferences::getSecondaryTextColor();
		}
		return ColorPreferences::getPrimaryTextColor();
	}

	void SDLControl::setFontSize(int font_size)
	{
		font_size_ = font_size;
	}

	void SDLControl::setId(ControlID id)
	{
		assert(id_ == UNDEFINED_CONTROL_ID);
		id_ = id;
	}
	void SDLControl::useSecondaryColorScheme()
	{
		use_secondary_color_scheme_ = true;
	}
}

