#include "SDLControl.h"

#include <assert.h>

namespace global_domination
{
	SDLControl::SDLControl()
	{
		id_ = UNDEFINED_CONTROL_ID;
		background_color_ = SDL_Color{ 115, 115, 115 };
	}

	unsigned int SDLControl::getId()
	{
		return id_;
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
}

